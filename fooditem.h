#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
#include <vector>
using namespace std;

class FoodItem {
public:
    FoodItem(string name, double price) : name(name), price(price) {}

    string getName() const { return name; }
    double getPrice() const { return price; }

private:
    string name;
    double price;
};

#endif
