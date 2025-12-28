#include "../header_files/Limit.h"
#include "../header_files/Order.h"
#include <iostream>


Limit::Limit(int limitPrice, int size, int totalVolume) {
    this->limitPrice=limitPrice;
    this->size=size;
    this->totalVolume=totalVolume;
    this->parentLimit=nullptr;
    this->leftChild=nullptr;
    this->rightChild=nullptr;
    this->headOrder=nullptr;
    this->tailOrder=nullptr;
    this->height = 0;
}

void Limit::AddOrderToLimit(Order *order) {
    order->prevOrder = nullptr;
    order->nextOrder = nullptr;
    order->parentLimit = this;

    if (headOrder == nullptr) {
        headOrder = tailOrder = order;
    } else {
        tailOrder->nextOrder = order;
        order->prevOrder = tailOrder;
        tailOrder = order;
    }

    size++;
    totalVolume += order->shares;
    orderMap[order->id] = order;
}


Order* Limit::PopOrderFromLimit() {
    if (headOrder == nullptr) {
        return nullptr;
    }

    Order* order = headOrder;

    if (headOrder == tailOrder) {
        // single element
        headOrder = tailOrder = nullptr;
    } else {
        headOrder = order->nextOrder;
        headOrder->prevOrder = nullptr;
    }

    size--;
    totalVolume -= order->shares;
    orderMap.erase(order->id);

    // fully detach
    order->nextOrder = nullptr;
    order->prevOrder = nullptr;
    order->parentLimit = nullptr;

    return order;
}

void Limit::CancelOrderById(int orderId) {
    auto it = orderMap.find(orderId);
    if (it == orderMap.end()) return; // Not found

    Order* order = it->second; // Acsess value of type order
    Limit* limit = order->parentLimit;

    // Remove from linked list
    if (order->prevOrder) order->prevOrder->nextOrder = order->nextOrder;
    else limit->headOrder = order->nextOrder; // Head

    if (order->nextOrder) order->nextOrder->prevOrder = order->prevOrder;
    else limit->tailOrder = order->prevOrder; // Tail

    // Update limit stats
    limit->size--;
    limit->totalVolume -= order->shares;

    // Remove from map
    orderMap.erase(it);

    // Optional: free memory
    delete order;
}

void Limit::PrintElements() {
    Order* order = headOrder;
    std::cout << "\n=================================\n";
    std::cout << "LIMIT START\n";
    std::cout << "limitPrice=" << limitPrice << "\n";
    std::cout << "size=" << size << "\n";
    std::cout << "totalVolume=" << totalVolume << "\n";
    while (order != nullptr) {        
        order->PrintOrder();
        order = order->nextOrder;
    }
    std::cout << "LIMIT END\n";
    std::cout << "=================================\n";
}

int Limit::getBalanceFactor() {
    int leftHeight  = (leftChild  ? leftChild->height  : -1);
    int rightHeight = (rightChild ? rightChild->height : -1);

    return leftHeight - rightHeight;
}

// -1 --> Empty, 1--> non-empty
int Limit::isEmpty() {
    if (headOrder == nullptr) {
        return -1;
    }
    return 1;
}