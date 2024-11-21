#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
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

public:
    Receipt() : totalCost(0.0f) {}

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

        cout << "----------------------------\n";
        cout << setw(40) << left << "Total Cost"
             << "$" << totalCost << endl;
        cout << "=============================\n";
    }

    float getTotalCost() const {
        return totalCost;
    }
};

