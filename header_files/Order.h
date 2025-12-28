#pragma once

class Limit;

class Order {
    private:
        
    public:
        int id;
        bool buyOrSell;
        int shares;
        int limitPrice;
        int entryTime;
        Order *nextOrder;
        Order *prevOrder;
        Limit *parentLimit;
        Order(int idNumber, bool buyOrSell, int shares, int limitPrice, int entryTime);
        void PrintOrder();
};
