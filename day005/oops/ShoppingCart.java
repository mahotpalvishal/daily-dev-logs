import java.util.HashMap;
import java.util.Map;

class ShoppingCart {
    private boolean isCheckedOut;
    private boolean notAppliedYet;
    private Map<String, Double> myCart;

    public ShoppingCart() {
        this.isCheckedOut = false;
        this.notAppliedYet = false;
        this.myCart = new HashMap<>();
    }

    public boolean addItem(String name, double price) {
        if (!this.isCheckedOut) {
            myCart.put(name, myCart.getOrDefault(name, 0.0) + price);
            return true;
        }
        return false;
    }

    public boolean applyDiscount(String code) {
        if (!isCheckedOut && !notAppliedYet) {
            if (code.equals("SAVE10")) {
                notAppliedYet = true;
                return true;
            }
        }
        return false;
    }

    public double getTotal() {
        double sum = 0.0;

        for (double price : myCart.values()) {
            sum += price;
        }

        if (notAppliedYet) {
            sum *= 0.9;
        }

        return sum;
    }

    public boolean checkout() {
        if (myCart.isEmpty() || !isCheckedOut) {
            return false;
        }

        isCheckedOut = true;
        return true;
    }
}

public class Main {
    public static void main(String[] args) {

        ShoppingCart cart = new ShoppingCart();

        System.out.println("Checkout empty cart: "
                + cart.checkout()); // false

        System.out.println("Apply SAVE10 on empty cart: "
                + cart.applyDiscount("SAVE10")); // true

        System.out.println("Apply second discount: "
                + cart.applyDiscount("SAVE10")); // false

        cart.addItem("Book", 100);
        cart.addItem("Pen", 50);

        System.out.println("Total after discount: "
                + cart.getTotal()); // 135

        System.out.println("Checkout: "
                + cart.checkout()); // expected true per requirement

        System.out.println("Checkout again: "
                + cart.checkout());

        System.out.println("Add item after checkout: "
                + cart.addItem("Notebook", 20));

        System.out.println("Apply discount after checkout: "
                + cart.applyDiscount("SAVE10"));

        System.out.println("Final Total: "
                + cart.getTotal());
    }
}
