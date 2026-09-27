import java.util.ArrayList;
import java.util.List;

class PaymentMethods {

    public static void main(String[] args) {

        PaymentGateway gateway = new PaymentGateway();

        int cardIndex = gateway.addCard("CARD001", 1000.00);
        int upiIndex = gateway.addUpi("UPI001", 500.00);
        int walletIndex = gateway.addWallet("WALLET001", 2000.00);

        System.out.println(gateway.fee(cardIndex));
        System.out.println(gateway.settlement(cardIndex));
        System.out.println(gateway.receipt(cardIndex));

        System.out.println(gateway.fee(upiIndex));
        System.out.println(gateway.settlement(upiIndex));
        System.out.println(gateway.receipt(upiIndex));

        System.out.println(gateway.fee(walletIndex));
        System.out.println(gateway.settlement(walletIndex));
        System.out.println(gateway.receipt(walletIndex));

        System.out.println("Total fees: " + gateway.totalFees());
    }
}

abstract class Payment {

    private final String reference;
    private final String method;
    private final double amount;

    public Payment(String reference, String method, double amount) {
        this.reference = reference;
        this.method = method;
        this.amount = amount;
    }

    public String getReference() {
        return reference;
    }

    public String getMethod() {
        return method;
    }

    public double getAmount() {
        return amount;
    }

    // Each subclass provides its own fee calculation
    public abstract double fee();

    // Common behavior for all payment types
    public double settlement() {
        return amount - fee();
    }

    // Common receipt format
    public String receipt() {
        return String.format(
            "%s (%s): charged $%.2f, fee $%.2f, settled $%.2f",
            reference,
            method,
            amount,
            fee(),
            settlement()
        );
    }
}


// Card Payment
class CardPayment extends Payment {

    public CardPayment(String reference, double amount) {
        super(reference, "Card", amount);
    }

    @Override
    public double fee() {
        return getAmount() * 0.02;
    }
}


// UPI Payment
class UpiPayment extends Payment {

    public UpiPayment(String reference, double amount) {
        super(reference, "UPI", amount);
    }

    @Override
    public double fee() {
        return 0.0;
    }
}


// Wallet Payment
class WalletPayment extends Payment {

    public WalletPayment(String reference, double amount) {
        super(reference, "Wallet", amount);
    }

    @Override
    public double fee() {
        return Math.min(getAmount() * 0.01, 10.0);
    }
}


// Provided class - do not modify
class PaymentGateway {

    private final List<Payment> payments = new ArrayList<>();

    public PaymentGateway() {
    }

    public int addCard(String reference, double amount) {
        payments.add(new CardPayment(reference, amount));
        return payments.size() - 1;
    }

    public int addUpi(String reference, double amount) {
        payments.add(new UpiPayment(reference, amount));
        return payments.size() - 1;
    }

    public int addWallet(String reference, double amount) {
        payments.add(new WalletPayment(reference, amount));
        return payments.size() - 1;
    }

    public double fee(int index) {
        return payments.get(index).fee();
    }

    public double settlement(int index) {
        return payments.get(index).settlement();
    }

    public String receipt(int index) {
        return payments.get(index).receipt();
    }

    public double totalFees() {
        double total = 0;

        for (Payment payment : payments) {
            total += payment.fee();
        }

        return total;
    }
}


