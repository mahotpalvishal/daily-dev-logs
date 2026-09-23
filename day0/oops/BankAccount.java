
class SavingsAccount extends BankAccount{
    private float interestRate;

    @Override
    public void withdraw(){
        System.out.println("SavingsAccount withdraw");
    }

    public void applyInterest(){
        System.out.println("SavingsAccount Apply interest");
    }
}

class CheckingAccount extends BankAccount{
    private float overdraftLimit;

    @Override
    public void withdraw(){
        System.out.println("CheckingAccount withdraw");
    }
} 

public class BankAccount{
    private String ownerName;
    private long accountNumber;
    protected double balance;
    protected String className;
    
    public BankAccount(){

    }
    public void deposit(){
        System.out.println("BankAccount deposit");
    }

    public void withdraw(){
        System.out.println("BankAccount withdraw");
    }

    public void displayAccount(){
        System.out.println("Account Display");
    }

    public static void main(String[] args){
        BankAccount bk = new BankAccount();
        bk.deposit();
        bk.withdraw();
        bk.displayAccount();

        SavingsAccount ck = new SavingsAccount();
        ck.deposit();
        ck.withdraw();
        ck.displayAccount();
        ck.applyInterest();

        CheckingAccount sk = new CheckingAccount();
        sk.deposit();
        sk.withdraw();
        sk.displayAccount();

        BankAccount fsck = bk;
        fsck.deposit();
        fsck.withdraw();
        fsck.displayAccount();
    }
}