#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Abstract Base Class
class Payment {
private:
    string reference;
    string method;
    double amount;

public:
    Payment(const string& reference,
            const string& method,
            double amount)
        : reference(reference),
          method(method),
          amount(amount) {}

    virtual ~Payment() = default;

    string getReference() const {
        return reference;
    }

    string getMethod() const {
        return method;
    }

    double getAmount() const {
        return amount;
    }

    // Pure virtual function
    virtual double fee() const = 0;

    // Common behavior
    double settlement() const {
        return amount - fee();
    }

    // Common receipt
    string receipt() const {
        ostringstream output;

        output << fixed << setprecision(2)
               << reference
               << " (" << method << "): charged $"
               << amount
               << ", fee $" << fee()
               << ", settled $" << settlement();

        return output.str();
    }
};


// Card Payment
class CardPayment : public Payment {
public:
    CardPayment(const string& reference, double amount)
        : Payment(reference, "Card", amount) {}

    double fee() const override {
        return getAmount() * 0.02;
    }
};


// UPI Payment
class UpiPayment : public Payment {
public:
    UpiPayment(const string& reference, double amount)
        : Payment(reference, "UPI", amount) {}

    double fee() const override {
        return 0.0;
    }
};


// Wallet Payment
class WalletPayment : public Payment {
public:
    WalletPayment(const string& reference, double amount)
        : Payment(reference, "Wallet", amount) {}

    double fee() const override {
        return min(getAmount() * 0.01, 10.0);
    }
};


// Payment Gateway
class PaymentGateway {
private:
    vector<unique_ptr<Payment>> payments;

public:
    PaymentGateway() = default;

    int addCard(const string& reference, double amount) {
        payments.push_back(
            make_unique<CardPayment>(reference, amount)
        );

        return payments.size() - 1;
    }

    int addUpi(const string& reference, double amount) {
        payments.push_back(
            make_unique<UpiPayment>(reference, amount)
        );

        return payments.size() - 1;
    }

    int addWallet(const string& reference, double amount) {
        payments.push_back(
            make_unique<WalletPayment>(reference, amount)
        );

        return payments.size() - 1;
    }

    double fee(int index) const {
        return payments[index]->fee();
    }

    double settlement(int index) const {
        return payments[index]->settlement();
    }

    string receipt(int index) const {
        return payments[index]->receipt();
    }

    double totalFees() const {
        double total = 0.0;

        for (const auto& payment : payments) {
            total += payment->fee();
        }

        return total;
    }
};


// Test
int main() {
    PaymentGateway gateway;

    int cardIndex = gateway.addCard("CARD001", 1000.00);
    int upiIndex = gateway.addUpi("UPI001", 500.00);
    int walletIndex = gateway.addWallet("WALLET001", 2000.00);

    cout << gateway.receipt(cardIndex) << endl;
    cout << gateway.receipt(upiIndex) << endl;
    cout << gateway.receipt(walletIndex) << endl;

    cout << fixed << setprecision(2);
    cout << "Total fees: "
         << gateway.totalFees()
         << endl;

    return 0;
}
