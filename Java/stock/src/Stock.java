/**
设计一个股票类 Stock 的类,这个类包括:
1) 一个名为 symbol 的字符串数据域表示股票代码
2) 一个名为 name 的字符串数据域表示股票名字
3) 一个名为 previousClosingPrice 的 double 型数据域,它存储的是前一日的
股票值
4) 一个名为 currentPrice 的 double 型数据域,它存储的是当时的股票值。
5) 创建一支有特定代码和名字的股票的构造方法。
6) 一个名为 getChangePercent()的方法返回从 previousClosingPrice 变化到
currentPrice 的百分比。
实现这个类,编写一个测试程序,创建一个 Stock 对象,它的股票代码是
Java,股票名字为 Sun Mircro,前一日收盘价是 4.5。设置新的当前值为 4.35,
然后显示市值变化的百分比。
 **/
public class Stock {
    String symbol;
    String name;
    double previousClosingPrice;
    double currentPrice;

    public Stock(String symbol,String name) {
        this.symbol = symbol;
        this.name = name;
    }
    public String getChangePercent() {
        return Double.toString((this.currentPrice - this.previousClosingPrice) / this.previousClosingPrice * 100) + '%';
    }
    public static void main(String[] args) {
        Stock java = new Stock("Java", "Sun Mircro");
        java.previousClosingPrice = 4.5;
        java.currentPrice = 4.35;
        System.out.println(java.getChangePercent());
    }
}
