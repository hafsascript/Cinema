#ifndef GIFTCARD_H
#define GIFTCARD_H

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class GiftCard {
private:
    string cardID;
    double balance;
    string expiryDate;
    bool active;

public:
    GiftCard(string id, double initialBalance, string expiry)
        : cardID(id), balance(initialBalance), expiryDate(expiry), active(true) {}

    string getCardID() const { return cardID; }
    double getBalance() const { return balance; }
    string getExpiryDate() const { return expiryDate; }
    bool isActive() const { return active; }

    bool redeem(double amount);
    void deactivate() { active = false; }
    void displayCardDetails() const;
};

#endif
