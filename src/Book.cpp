#include <iostream>
#include <nlohmann/json.hpp>

#include "../header_files/Book.h"
using std::string;
using json = nlohmann::json;


Book::Book() {
    std::cout << "Initilizing Book\n";
    highestBuy = nullptr;
    lowestSell = nullptr;
}

string Book::addOrder(int id, int price, int shares, bool buyOrSell) {
    Order *order = new Order(id, buyOrSell, shares, price, 0);
    if (buyOrSell == true) { // buy
        Limit* limit = searchLimit(buyTree, price);
        if (limit != nullptr) {
            limit->AddOrderToLimit(order);
        }
        else {
            limit = new Limit(price, 0, 0);
            limit->AddOrderToLimit(order);
            buyTree = insertLimit(buyTree, limit);
        }

        if (highestBuy == nullptr) {
            highestBuy = limit;
        }
        else if (price > highestBuy->limitPrice) {
            highestBuy = limit;
        }
    }
    else {
        Limit* limit = searchLimit(sellTree, price);
        if (limit != nullptr) {
            limit->AddOrderToLimit(order);
        }
        else {
            limit = new Limit(price, 0, 0);
            limit->AddOrderToLimit(order);
            sellTree = insertLimit(sellTree, limit);
        }

        if (lowestSell == nullptr) {
            lowestSell = limit;
        }
        else if (price < lowestSell->limitPrice) {
            lowestSell->limitPrice = price;
        }
    }
    return "addOrder Executed";
}

string Book::cancelOrder(int id, int price, bool buyOrSell) {
    Limit* foundLimit;
    if (buyOrSell == true) {
        foundLimit = searchLimit(buyTree, price);
        foundLimit->CancelOrderById(id);
        if (foundLimit->isEmpty() == -1) {
            buyTree = deleteLimit(buyTree, price);
        }
    }
    else {
        foundLimit = searchLimit(sellTree, price);
        foundLimit->CancelOrderById(id);
        if (foundLimit->isEmpty() == -1) {
            sellTree = deleteLimit(sellTree, price);
        }
    }

    highestBuy = findMax(buyTree);
    lowestSell = findMin(sellTree);

    return "cancelOrder Executed";
}

string Book::executeOrder(int shares, bool buyOrSell) {
    int remaining = shares;

    while (remaining > 0) {
        Limit* limit = buyOrSell ? lowestSell : highestBuy;
        if (!limit) break;  // book empty

        Order* order = limit->headOrder;
        if (!order) {
            // defensive: empty limit should not exist
            if (buyOrSell)
                sellTree = deleteLimit(sellTree, limit->limitPrice);
            else
                buyTree = deleteLimit(buyTree, limit->limitPrice);

            lowestSell = findMin(sellTree);
            highestBuy = findMax(buyTree);
            continue;
        }

        if (order->shares <= remaining) {
            remaining -= order->shares;
            limit->PopOrderFromLimit();
        } else {
            order->shares -= remaining;
            remaining = 0;
        }

        if (limit->isEmpty()) {
            if (buyOrSell)
                sellTree = deleteLimit(sellTree, limit->limitPrice);
            else
                buyTree = deleteLimit(buyTree, limit->limitPrice);

            lowestSell = findMin(sellTree);
            highestBuy = findMax(buyTree);
        }
    }

    return "executeOrder Executed";
}

int Book::getVolumeAtLimit(int price, bool buyOrSell) {
    if (buyOrSell == true) {
        Limit* foundLimit = searchLimit(buyTree, price);
        return foundLimit->totalVolume;
    }
    else {
        Limit* foundLimit = searchLimit(sellTree, price);
        return foundLimit->totalVolume;
    }
}

int Book::getBestOffer(bool buyOrSell) {
    if (buyOrSell == true) {
        return lowestSell->limitPrice;
    }
    else {
        return highestBuy->limitPrice;
    }
}

int Book::height(Limit* node) {
    if (node == nullptr) return -1;
    return node->height;
}

void Book::updateHeight(Limit* node) {
    if (!node) return;
    node->height = 1 + std::max(height(node->leftChild), height(node->rightChild));
}

Limit* Book::rotateLeft(Limit *x) {
    Limit* y = x->rightChild;
    Limit* T2 = y->leftChild;

    y->leftChild = x;
    x->rightChild = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Limit* Book::rotateRight(Limit *y) {
    Limit* x = y->leftChild;
    Limit* T2 = x->rightChild;

    x->rightChild = y;
    y->leftChild = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Limit* Book::searchLimit(Limit* root, int price) {
    if (root == nullptr || root->limitPrice == price)
        return root;

    if (price < root->limitPrice)
        return searchLimit(root->leftChild, price);

    return searchLimit(root->rightChild, price);
}

Limit* Book::insertLimit(Limit* node, Limit* newLimit) {

    // 1. Normal BST insert
    if (node == nullptr)
        return newLimit;

    if (newLimit->limitPrice < node->limitPrice)
        node->leftChild = insertLimit(node->leftChild, newLimit);
    else if (newLimit->limitPrice > node->limitPrice)
        node->rightChild = insertLimit(node->rightChild, newLimit);
    else
        return node;  // duplicate price (should not happen)

    // 2. Update height
    updateHeight(node);

    // 3. Balance
    int balance = node->getBalanceFactor();

    // 4. Rebalance cases

    // LL
    if (balance > 1 && node->leftChild && newLimit->limitPrice < node->leftChild->limitPrice)
        return rotateRight(node);

    // RR
    if (balance < -1 && node->rightChild && newLimit->limitPrice > node->rightChild->limitPrice)
        return rotateLeft(node);

    // LR
    if (balance > 1 && node->leftChild && newLimit->limitPrice > node->leftChild->limitPrice) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }

    // RL
    if (balance < -1 && node->rightChild && newLimit->limitPrice < node->rightChild->limitPrice) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }
    return node;
}

Limit* Book::minValueNode(Limit* node) {
    Limit* current = node;
    while (current->leftChild != nullptr)
        current = current->leftChild;
    return current;
}

Limit* Book::deleteLimit(Limit* root, int price) {

    if (root == nullptr)
        return root;

    // BST delete
    if (price < root->limitPrice)
        root->leftChild = deleteLimit(root->leftChild, price);
    else if (price > root->limitPrice)
        root->rightChild = deleteLimit(root->rightChild, price);
    else {
        // node with 0 or 1 child
        if (!root->leftChild || !root->rightChild) {
            Limit* child = root->leftChild ? root->leftChild : root->rightChild;
            delete root;
            return child;
        }
        else {
            // two children
            Limit* temp = minValueNode(root->rightChild);
            root->limitPrice = temp->limitPrice;
            root->rightChild = deleteLimit(root->rightChild, temp->limitPrice);
        }
    }

    if (root == nullptr)
        return root;

    // Update height
    updateHeight(root);

    int balance = root->getBalanceFactor();

    // LL
    if (balance > 1 && root->leftChild->getBalanceFactor() >= 0)
        return rotateRight(root);

    // LR
    if (balance > 1 && root->leftChild->getBalanceFactor() < 0) {
        root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }

    // RR
    if (balance < -1 && root->rightChild->getBalanceFactor() <= 0)
        return rotateLeft(root);

    // RL
    if (balance < -1 && root->rightChild->getBalanceFactor() > 0) {
        root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    return root;
}


void Book::printTreeInOrder(Limit* root) {
    if (root == nullptr)
        return;

    // Print smaller prices first
    printTreeInOrder(root->leftChild);
    root->PrintElements();

    // Print larger prices
    printTreeInOrder(root->rightChild);
}

json Book::limitToJson(Limit* limit) {
    if (!limit) return nullptr;

    json orders = json::array();
    for (const auto& [id, order] : limit->orderMap) {
        orders.push_back({
            {"orderId", id},
            {"shares", order->shares}
        });
    }

    return {
        {"limitPrice", limit->limitPrice},
        {"size", limit->size},
        {"totalVolume", limit->totalVolume},
        {"height", limit->height},
        {"orderCount", limit->orderMap.size()},
        {"orders", orders}
    };
}

void Book::returnTreeLimitsInOrder(Limit* root, json& result) {
    if (root == nullptr)
        return;

    returnTreeLimitsInOrder(root->leftChild, result);
    result.push_back(limitToJson(root));
    returnTreeLimitsInOrder(root->rightChild, result);
}

Limit* Book::findMin(Limit* root) {
    if (!root) return nullptr;

    Limit* current = root;
    while (current->leftChild) {
        current = current->leftChild;
    }
    return current;
}

Limit* Book::findMax(Limit* root) {
    if (!root) return nullptr;

    Limit* current = root;
    while (current->rightChild) {
        current = current->rightChild;
    }
    return current;
}