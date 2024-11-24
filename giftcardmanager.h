#ifndef GIFTCARDMANAGER_H
#define GIFTCARDMANAGER_H

#include "GiftCard.h"
#include <unordered_map>

class GiftCardManager {
private:
    unordered_map<string, GiftCard> giftCards;

public:
    void generateCard(string id, double amount, string expiry);
    bool redeemCard(string id, double amount);
    void displayAllCards() const;
};

#endif
