import java.util.*;

// Abstract base class
abstract class Discount {

    // Calculates the discounted price
    public abstract double apply(double price);

    // Returns the discount label
    public abstract String label();

    // Shared description logic
    public String describe(double price) {
        return String.format(
            "%s: $%.2f -> $%.2f",
            label(),
            price,
            apply(price)
        );
    }
}

// Percentage discount
class PercentageDiscount extends Discount {
    private int percent;

    public PercentageDiscount(int percent) {
        this.percent = percent;
    }

    @Override
    public double apply(double price) {
        return price * (1 - percent / 100.0);
    }

    @Override
    public String label() {
        return percent + "% off";
    }
}

// Flat discount
class FlatDiscount extends Discount {
    private double amount;

    public FlatDiscount(double amount) {
        this.amount = amount;
    }

    @Override
    public double apply(double price) {
        return Math.max(0.0, price - amount);
    }

    @Override
    public String label() {
        return String.format("$%.2f off", amount);
    }
}

// Buy One Get One Free discount
class BuyOneGetOneFree extends Discount {

    @Override
    public double apply(double price) {
        return price / 2.0;
    }

    @Override
    public String label() {
        return "Buy 1 Get 1 Free";
    }
}
