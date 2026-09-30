#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

using namespace std;

// Abstract base class
class Discount {
public:
    virtual double apply(double price) const = 0;
    virtual string label() const = 0;

    string describe(double price) const {
        stringstream ss;
        ss << fixed << setprecision(2);
        ss << label() << ": $" << price
           << " -> $" << apply(price);
        return ss.str();
    }

    virtual ~Discount() = default;
};

// Percentage discount
class PercentageDiscount : public Discount {
private:
    int percent;

public:
    PercentageDiscount(int percent) : percent(percent) {}

    double apply(double price) const override {
        return price * (1 - percent / 100.0);
    }

    string label() const override {
        return to_string(percent) + "% off";
    }
};

// Flat discount
class FlatDiscount : public Discount {
private:
    double amount;

public:
    FlatDiscount(double amount) : amount(amount) {}

    double apply(double price) const override {
        return max(0.0, price - amount);
    }

    string label() const override {
        stringstream ss;
        ss << fixed << setprecision(2);
        ss << "$" << amount << " off";
        return ss.str();
    }
};

// Buy One Get One Free discount
class BuyOneGetOneFree : public Discount {
public:
    double apply(double price) const override {
        return price / 2.0;
    }

    string label() const override {
        return "Buy 1 Get 1 Free";
    }
};

int main() {
    double price = 100.0;

    vector<unique_ptr<Discount>> discounts;
    discounts.push_back(make_unique<PercentageDiscount>(20));
    discounts.push_back(make_unique<FlatDiscount>(15.0));
    discounts.push_back(make_unique<BuyOneGetOneFree>());

    for (const auto& discount : discounts) {
        cout << discount->describe(price) << endl;
    }

    return 0;
}
`
