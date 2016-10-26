/**
 * Created by dgeibi on 10/3/16.
 *
 * 请定义一个交通工具(Vehicle)的类
 1) 其中有属性:速度(speed),体积(size).
 2) 方法:移动(move()),设置速度(setSpeed(int speed)),加速 speedUp(),减速speedDown()等等.
 3) 最后在测试类 Vehicle 中的 main()中实例化一个交通工具对象,并通过方
 法给它初始化 speed,size 的值,并且通过打印出来。另外,调用加速,减速的方
 法对速度进行改变。
 */
public class Vehicle {
    double speed;
    double size;
    public void move() {
        System.out.println("do do do do.");
    }
    public void setSpeed(int speed) {
        this.speed = speed;
    }
    public void speedUp() {
        this.speed += 5;
    }
    public void speedDown() {
        this.speed -= 5;
    }
    public Vehicle(double speed, double size) {
        this.speed = speed;
        this.size = size;
    }
    public static void printInfo(Vehicle v) {
        System.out.println("speed: " + v.speed + ", size: " + v.size);
    }
    public static void main(String [] args) {
        Vehicle bmw = new Vehicle(60.3, 50);
        Vehicle.printInfo(bmw);
        bmw.speedDown();
        Vehicle.printInfo(bmw);
        bmw.speedDown();
        Vehicle.printInfo(bmw);
        bmw.speedUp();
        Vehicle.printInfo(bmw);
        bmw.speedUp();
        bmw.speedUp();
        Vehicle.printInfo(bmw);
    }
}
