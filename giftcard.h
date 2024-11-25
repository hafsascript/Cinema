#ifndef GIFTCARD_H
#define GIFTCARD_H

#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

class GiftCard {
private:
    unordered_map<string, float> cards; 

public:
    void addGiftCard(const string& code, float value) {
        cards[code] = value;
        cout << "Gift card added with code: " << code << " and value: $" << value << endl;
    }

    float getBalance(const string& code) const {
        if (cards.find(code) != cards.end()) {
            return cards.at(code);
        } else {
            cout << "Gift card not found or invalid.\n";
            return 0.0f;
        }
    }

    bool useGiftCard(const string& code, float amount) {
        if (cards.find(code) != cards.end() && cards[code] > 0) {
            if (amount <= cards[code]) {
                cards[code] -= amount;
                return true;
            } else {
                cout << "Insufficient balance on gift card.\n";
                return false;
            }
        } else {
            cout << "Gift card not found or already redeemed.\n";
            return false;
        }
    }

    void displayGiftCards() const {
        cout << "\n--- Available Gift Cards ---\n";
        for (const auto& card : cards) {
            cout << "Code: " << card.first << ", Value: $" << card.second << endl;
        }
    }
};

#endif

