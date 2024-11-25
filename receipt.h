#ifndef RECEIPT_H
#define RECEIPT_H

#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include "giftcard.h" 
using namespace std;

class Receipt {
private:
    struct OrderItem {
        string name;
        float price;
        int quantity;
    };

    vector<OrderItem> orderedItems;
    float totalCost;
    float discountAmount;

public:
    Receipt() : totalCost(0.0f), discountAmount(0.0f) {}

    void addItem(const string& name, float price, int quantity) {
        for (auto& item : orderedItems) {
            if (item.name == name) {
                item.quantity += quantity;
                totalCost += price * quantity;
                return;
            }
        }
        orderedItems.push_back({name, price, quantity});
        totalCost += price * quantity;
    }

    void addTicket(const string& movieTitle, float ticketPrice, int seatCount = 1) {
        addItem("Ticket: " + movieTitle, ticketPrice, seatCount);
    }

    void applyGiftCard(GiftCard& giftCard, const string& code) {
        if (totalCost <= 0.0f) {
            cout << "No items in receipt to apply a gift card.\n";
            return;
        }

        float balance = giftCard.getBalance(code);
        if (balance <= 0.0f) {
            cout << "Gift card balance is zero or invalid.\n";
            return;
        }

        float amountToUse = min(balance, totalCost);
        if (giftCard.useGiftCard(code, amountToUse)) {
            discountAmount += amountToUse;
            totalCost -= amountToUse;
            cout << "Gift card applied successfully. Discount: $" << amountToUse << endl;
        } else {
            cout << "Failed to apply gift card.\n";
        }
    }

    void displayReceipt() const {
        cout << "\n========== Receipt ==========\n";
        cout << setw(40) << left << "Item"
             << setw(10) << left << "Qty"
             << setw(10) << left << "Price"
             << setw(10) << left << "Total" << endl;
        cout << "----------------------------\n";

        for (const auto& item : orderedItems) {
            float itemTotal = item.price * item.quantity;
            cout << setw(40) << left << item.name
                 << setw(10) << left << item.quantity
                 << "$" << setw(9) << left << item.price
                 << "$" << setw(9) << left << itemTotal << endl;
        }

        if (discountAmount > 0) {
            cout << "----------------------------\n";
            cout << setw(40) << left << "Gift Card Discount"
                 << "-$" << discountAmount << endl;
        }

        cout << "----------------------------\n";
        cout << setw(40) << left << "Total Cost"
             << "$" << totalCost << endl;
        cout << "=============================\n";
    }

    float getTotalCost() const {
        return totalCost;
    }

    void clear() {
        orderedItems.clear();
        discountAmount = 0.0f;
    }

    void resetTotalCost() {
        totalCost = 0.0f;
    }

    float getDiscountAmount() const {
    return discountAmount;
}

};

#endif