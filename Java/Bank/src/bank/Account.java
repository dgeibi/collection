package bank;

/**
 * Created by dgeibi on 10/23/16.
 */
public class Account {
    private String name = "unnamed";
    private double balance = 100;

    public Account() {
    }

    public Account(double balance, String name) {
        this.name = name;
        this.balance = balance;
    }

    public double getBalance() {
        return this.balance;
    }

    public String getName() {
        return this.name;
    }

    public void printAccount() {
        System.out.println(this.name + "'s balance is " + this.getBalance());
    }

    public void withdraw(double amount) {
        this.balance = this.balance - amount;
    }

    public void deposit(double amount) {
        this.balance = this.balance + amount;
    }
}

