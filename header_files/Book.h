#pragma once

#include <nlohmann/json.hpp>
#include "Limit.h"
using std::string;
using json = nlohmann::json;


class Book {
    private:
        int height(Limit* node);
        void updateHeight(Limit* node);

    public:
        Limit *buyTree;
        Limit *sellTree;
        Limit *lowestSell;
        Limit *highestBuy;
        Book();
        string addOrder(int id, int price, int shares, bool buyOrSell);
        string cancelOrder(int id, int price, bool buyOrSell);
        string executeOrder(int shares, bool buyOrSell);
        int getVolumeAtLimit(int price, bool buyOrSell);
        int getBestOffer(bool buyOrSell); 

        
        Limit* rotateLeft(Limit *x);
        Limit* rotateRight(Limit *y);
        
        Limit* searchLimit(Limit* root, int price);
        Limit* insertLimit(Limit* node, Limit* newLimit);
        Limit* minValueNode(Limit* node);
        Limit* deleteLimit(Limit* root, int price);
        void printTreeInOrder(Limit* root);

        void returnTreeLimitsInOrder(Limit* root, json& result);
        json limitToJson(Limit* limit);

        Limit* findMax(Limit* root);
        Limit* findMin(Limit* root);
};