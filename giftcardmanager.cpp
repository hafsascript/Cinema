#include "GiftCardManager.h"

void GiftCardManager::generateCard(string id, double amount, string expiry) {
    if (giftCards.find(id) == giftCards.end()) {
        giftCards[id] = GiftCard(id, amount, expiry);
        cout << "Gift card " << id << " created successfully!\n";
    } else {
        cout << "Gift card ID already exists!\n";
    }
}

bool GiftCardManager::redeemCard(string id, double amount) {
    if (giftCards.find(id) != giftCards.end() && giftCards[id].isActive()) {
        return giftCards[id].redeem(amount);
    }
    cout << "Invalid or inactive gift card!\n";
    return false;
}

void GiftCardManager::displayAllCards() const {
    for (const auto& card : giftCards) {
        card.second.displayCardDetails();
    }
}
