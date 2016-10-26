/**
 * Created by dgeibi on 10/2/16.
 *
 */
public class Book {
    private String name;
    private String author;
    private int monthlySales;
    public Book() {}
    public Book(String name, String author, int monthlySales) {
        this.name = name;
        this.author = author;
        this.monthlySales = monthlySales;
    }
    public void setBook(String name, String author, int monthlySales) {
        this.name = name;
        this.author = author;
        this.monthlySales = monthlySales;
    }
    public void printBook() {
        System.out.println(this.name + " by " + this.author + ", monthly sales: " + this.monthlySales);
    }
}
