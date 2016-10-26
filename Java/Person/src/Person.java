/**
 * Created by dgeibi on 10/2/16.
 *
 * 写一个 Person 类,定义人的基本属性:name(姓名)、age(年龄)、gender(性别) 、partner(配偶)。
 要求至少为 Person 类写一个 marry(Person p)方法,来判断两个人是否可以结
 婚。如果可以结婚,将其 partner 属性赋值为其配偶。
 结婚必须满足以下 3 个条件。
 1) 必须是异性,同性暂时不允许结婚
 2) 有配偶者不能结婚,犯重婚罪。3) 要达到年龄方可结婚:男方 23 岁以上,女性 21 岁以上。
 */
public class Person {
    String name;
    String gendar;
    String partner;
    int age;
    public Person(String name,String gendar,String partner, int age) {
        this.name = name;
        this.gendar = gendar;
        this.partner = partner;
        this.age = age;
    }
    public Person() {}
    public boolean marry(Person p) {
        if (this.gendar == p.gendar ) return false;
        if(this.gendar == "male" && this.age < 23 ||
                this.gendar == "female" && this.age<21 ||
                p.gendar == "male" && p.age < 23 ||
                p.gendar == "female" && p.age<21) return false;
        if(this.partner != null || p.partner != null) return false;
        p.partner = this.name;
        this.partner = p.name;
        return true;
    }
}
