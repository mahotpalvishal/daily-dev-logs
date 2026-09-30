import java.util.*;

// Abstract base class
abstract class Plan {
    protected String customer;
    protected String tier;

    public Plan(String customer, String tier) {
        this.customer = customer;
        this.tier = tier;
    }

    // Tier-specific pricing
    public abstract double monthlyCost();

    // Shared invoice formatting
    public String invoiceLine() {
        return String.format("%s (%s): $%.2f",
                customer, tier, monthlyCost());
    }
}

// Free plan
class FreePlan extends Plan {
    public FreePlan(String customer) {
        super(customer, "Free");
    }

    @Override
    public double monthlyCost() {
        return 0.0;
    }
}

// Pro plan
class ProPlan extends Plan {
    private int seats;

    public ProPlan(String customer, int seats) {
        super(customer, "Pro");
        this.seats = seats;
    }

    @Override
    public double monthlyCost() {
        return seats * 12.0;
    }
}

// Enterprise plan
class EnterprisePlan extends Plan {
    private int seats;
    private double discountPercent;

    public EnterprisePlan(String customer, int seats, double discountPercent) {
        super(customer, "Enterprise");
        this.seats = seats;
        this.discountPercent = discountPercent;
    }

    @Override
    public double monthlyCost() {
        double baseCost = seats * 20.0;
        return baseCost * (1.0 - discountPercent / 100.0);
    }
}

class Subscriptions {
    private final List<Plan> plans = new ArrayList<>();

    public Subscriptions() {
    }

    public int addFree(String customer) {
        plans.add(new FreePlan(customer));
        return plans.size() - 1;
    }

    public int addPro(String customer, int seats) {
        plans.add(new ProPlan(customer, seats));
        return plans.size() - 1;
    }

    public int addEnterprise(String customer, int seats, double discountPercent) {
        plans.add(new EnterprisePlan(customer, seats, discountPercent));
        return plans.size() - 1;
    }

    public double monthlyCost(int index) {
        return plans.get(index).monthlyCost();
    }

    public String invoiceLine(int index) {
        return plans.get(index).invoiceLine();
    }

    public double totalMonthly() {
        double sum = 0;
        for (Plan plan : plans) {
            sum += plan.monthlyCost();
        }
        return sum;
    }

    public int planCount() {
        return plans.size();
    }
}

class Main {
    public static void main(String[] args) {
        Subscriptions s = new Subscriptions();

        s.addFree("Alice");
        s.addPro("Bob", 5);
        s.addEnterprise("Corp", 10, 25);

        System.out.println(s.invoiceLine(0)); // Alice (Free): $0.00
        System.out.println(s.invoiceLine(1)); // Bob (Pro): $60.00
        System.out.println(s.invoiceLine(2)); // Corp (Enterprise): $150.00
        System.out.println(s.totalMonthly()); // 210.0
    }
}
``
