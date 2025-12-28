#include <iostream>
#include <nlohmann/json.hpp>

#include "header_files/Book.h"
#include "header_files/Limit.h"
#include "header_files/Order.h"
#include "header_files/httplib.h"
using std::string;
using json = nlohmann::json;


static Book* book = new Book();
static Limit* limit = new Limit(0,0,0);

int main() {
    // Create a server object
    httplib::Server svr;

    svr.Post("/addOrder", [](const httplib::Request &req, httplib::Response &res) {
        json body = json::parse(req.body);
        int id = body["id"];
        int price = body["price"];
        int shares = body["shares"];
        bool buyOrSell = body["buyOrSell"];

        string reply = book->addOrder(id, price, shares, buyOrSell);

        res.set_content(reply, "text/plain");
    });

    svr.Post("/cancelOrder", [](const httplib::Request &req, httplib::Response &res) {
        json body = json::parse(req.body);
        int id = body["id"];
        int price = body["price"];
        bool buyOrSell = body["buyOrSell"];
        string reply = book->cancelOrder(id, price, buyOrSell);
        res.set_content(reply, "text/plain");
    });

    svr.Post("/executeOrder", [](const httplib::Request &req, httplib::Response &res) {
        json body = json::parse(req.body);
        int shares = body["shares"];
        bool buyOrSell = body["buyOrSell"];
        string reply = book->executeOrder(shares, buyOrSell);
        res.set_content(reply, "text/plain");
    });

    svr.Get("/getVolumeAtLimit", [](const httplib::Request &req, httplib::Response &res) {
        json body = json::parse(req.body);
        int price = body["price"];
        bool buyOrSell = body["buyOrSell"];
        string reply = std::to_string(book->getVolumeAtLimit(price, buyOrSell));
        res.set_content(reply, "text/plain");
    });

    svr.Get("/getBestOffer", [](const httplib::Request &req, httplib::Response &res) {
        json body = json::parse(req.body);
        bool buyOrSell = body["buyOrSell"];
        string reply = std::to_string(book->getBestOffer(buyOrSell));
        res.set_content(reply, "text/plain");
    });


    svr.Post("/limitAdd", [](const httplib::Request &req, httplib::Response &res) {
        json body = json::parse(req.body);
        int id = body["id"];
        int price = body["price"];
        int shares = body["shares"];
        bool buyOrSell = body["buyOrSell"];
        Order* order = new Order(id, buyOrSell, shares, price, 0);
        limit->AddOrderToLimit(order);
    });

    svr.Post("/limitPop", [](const httplib::Request &req, httplib::Response &res) {
        limit->PopOrderFromLimit();
    });

    svr.Post("/limitPrint", [](const httplib::Request &req, httplib::Response &res) {
        limit->PrintElements();
    });

    svr.Get("/getTrees", [](const httplib::Request &req, httplib::Response &res) {
        json buyTreeJson = json::array();
        json sellTreeJson = json::array();

        book->returnTreeLimitsInOrder(book->buyTree, buyTreeJson);
        book->returnTreeLimitsInOrder(book->sellTree, sellTreeJson);

        json response = {
            {"buyTree", buyTreeJson},
            {"sellTree", sellTreeJson}
        };
        res.set_content(response.dump(2), "text/plain");
    });

    svr.Get("/getHighestBuyAndLowestSell", [](const httplib::Request &req, httplib::Response &res) {
        json highestBuyJson = book->limitToJson(book->highestBuy);
        json lowestSellJson = book->limitToJson(book->lowestSell);

        json response = {
            {"highestBuy", highestBuyJson},
            {"lowestSell", lowestSellJson}
        };
        res.set_content(response.dump(2), "text/plain");
    });

    std::cout << "Server listening on http://localhost:8080\n";

    // Start the server on port 8080
    svr.listen("0.0.0.0", 8080);

    return 0;
}