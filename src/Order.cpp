#include "../header_files/Order.h"
#include <iostream>


Order::Order(int idNumber, bool buyOrSell, int shares, int limitPrice, int entryTime) {
    this->id=idNumber;
    this->buyOrSell=buyOrSell;
    this->shares=shares;
    this->limitPrice=limitPrice;
    this->entryTime=entryTime;
    this->nextOrder=nullptr;
    this->prevOrder=nullptr;
    this->parentLimit=nullptr;
}

void Order::PrintOrder() {
    std::cout << "order->id=" << this->id << "\n";
    std::cout << "order->buyOrSell=" << this->buyOrSell << "\n";
    std::cout << "order->shares=" << this->shares << "\n";
    std::cout << "order->limitPrice=" << this->limitPrice << "\n";
    std::cout << "order->entryTime=" << this->entryTime << "\n";
}