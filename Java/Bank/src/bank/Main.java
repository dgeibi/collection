package bank;

public class Main {
    public static void main(String[] args) {
        Account account = new Account(5, "BlackFamily");
        DepositAndWithDrawal bankJob = new DepositAndWithDrawal(account);
        Thread one = new Thread(bankJob);
        Thread two = new Thread(bankJob);
        one.setName("Mike");
        two.setName("Ken");
        one.start();
        two.start();
    }
}
