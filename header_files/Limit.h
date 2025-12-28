#pragma once
#include "Order.h"
#include <unordered_map> 

class Limit {
    private:

    public:
        std::unordered_map<int, Order*> orderMap;
        int limitPrice;
        int size;
        int totalVolume;
        Limit *parentLimit;
        Limit *leftChild;
        Limit *rightChild; 
        Order *headOrder;
        Order *tailOrder;
        int height;
        Limit(int limitPrice, int size, int totalVolume);
        void AddOrderToLimit(Order *order);
        void InsertOrder(Order *order);
        Order* PopOrderFromLimit();
        void PrintElements();
        int getBalanceFactor();
        void CancelOrderById(int orderId);
        int isEmpty();

};
