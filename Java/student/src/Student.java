/**
 * Created by dgeibi on 10/2/16.
 * 设计 3 个类,分别是学生类 Student,本科生类 Undergraduate,研究生类
 Postgraduate。
 1)
 其中 Student 类是一个抽象类,它包含一个学生的基本信息如姓名、平均
 成绩等,及一个计算课程成绩等级的抽象方法。
 2)
 类 Undergraduate 和 Postgraduate 是其子类,它们计算课程成绩等级的方
 法有所不同(自己设计)。
 3)
 设计一个学生数组,既能放本科生对象又能放研究生对象。编写测试类
 测试以上功能。
 */
public abstract class Student {
    String name;
    double performance;
    public Student(String name, double performance) {
        this.name = name;
        this.performance = performance;
    }
    public Student () {}
    public abstract char getLevel();
}
