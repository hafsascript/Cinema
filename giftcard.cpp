#include "GiftCard.h"

bool GiftCard::redeem(double amount) {
    if (!active || balance < amount) return false;
    balance -= amount;
    if (balance <= 0) active = false;
    return true;
}

void GiftCard::displayCardDetails() const {
    cout << "Card ID: " << cardID << "\nBalance: " << balance
         << "\nExpiry Date: " << expiryDate
         << "\nStatus: " << (active ? "Active" : "Inactive") << endl;
}
