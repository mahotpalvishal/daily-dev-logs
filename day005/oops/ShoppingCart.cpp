/**
Design a ShoppingCart class that manages items, a single promotional discount, and checkout. The cart begins open for changes. Once checkout succeeds, it becomes a record of the order and must reject any further attempt to add items or apply a discount.

Implement the ShoppingCart class:
    - ShoppingCart() creates an empty cart that has not been checked out.
    - boolean addItem(String name, double price) adds an item and returns true. If the cart has already been checked out, the method leaves the cart unchanged and returns false.
    - boolean applyDiscount(String code) applies a 10% discount and returns true, but only when the code is "SAVE10", no discount has been applied before, and the cart is still open. If any condition fails, the method returns false without changing the cart. The discount may be applied even when the cart is empty.
    - double getTotal() returns the sum of all item prices, multiplied by 0.9 when the discount is active. Store the original item prices and apply the discount while calculating the total. This ensures that items added after the code was accepted receive the discount too.
    - boolean checkout() checks out a non-empty, open cart and returns true. If the cart is empty or has already been checked out, it returns false without changing anything.
    - boolean isCheckedOut() returns whether checkout has succeeded.
Keep the item collection, discount state, and checkout state encapsulated. Callers must not be able to modify any of them directly or bypass the rules above.
*/
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class ShoppingCart{
  private:
    bool isCheckedOut;
    bool notAppliedYet;
    unordered_map<string, double> myCart;

  public:
    ShoppingCart(){
        this->isCheckedOut = false;
        this->notAppliedYet = false;
    }
    
    bool addItem(string name, double price){
        if(!this->isCheckedOut){
            this->myCart[name] += price;
            return true;
        }
        return false;
    }

    bool applyDiscount(string code){
        if(!isCheckedOut && !notAppliedYet){
            if(code == "SAVE10"){
                notAppliedYet = true;
                return true;
            }
        }
        return false;
    }

    double getTotal(){
        double sum=0.0;
        for(auto& x: this->myCart){
            sum += x.second;
        }
        if(notAppliedYet){
            sum *= 0.9;
        }
        return sum;
    }

    bool checkout(){
        if(this->myCart.empty() || !isCheckedOut){
            return false;
        }
        isCheckedOut = true;
        return true;
    }
};

int main() {

    ShoppingCart cart;

    cout << "Checkout empty cart: "
              << cart.checkout() << endl;      // false

    cout << "Apply SAVE10 on empty cart: "
              << cart.applyDiscount("SAVE10") << endl; // true

    cout << "Apply second discount: "
              << cart.applyDiscount("SAVE10") << endl; // false

    cart.addItem("Book", 100);
    cart.addItem("Pen", 50);

    cout << "Total after discount: "
              << cart.getTotal() << endl;      // 135

    cout << "Checkout: "
              << cart.checkout() << endl;      // true

    cout << "Checkout again: "
              << cart.checkout() << endl;      // false

    cout << "Add item after checkout: "
              << cart.addItem("Notebook", 20) << endl; // false

    cout << "Apply discount after checkout: "
              << cart.applyDiscount("SAVE10") << endl; // false

    cout << "Final Total: "
              << cart.getTotal() << endl;      // 135

    return 0;
}
