package bank;
public class DepositAndWithDrawal implements Runnable {
    private Account account;

    public DepositAndWithDrawal(Account account) {
        this.account = account;
    }

    public void run() {
        for (int x = 0; x < 5; x++) {
            job();
            try {
                Thread.sleep(500);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    public synchronized void job() {
        double amount = 500 + Math.random()*500;
        double random = Math.random()*2;
        if(random > 1) {
            System.out.println(Thread.currentThread().getName() + " is about to deposit, + " + amount);
            account.deposit(amount);
            System.out.println(Thread.currentThread().getName() + " completes the deposit");
        } else {
            if (this.account.getBalance() >= amount) {
                System.out.println(Thread.currentThread().getName() + " is about to withdrawal, try - " + amount);
                account.withdraw(amount);
                System.out.println(Thread.currentThread().getName() + " completes the withdrawal");
            }
            else {
                System.out.println("Sorry, not enough for " + this.account.getName());
            }
        }
        this.account.printAccount();
    }
}
