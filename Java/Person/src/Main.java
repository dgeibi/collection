public class Main {
    public static void testMarry(Person p1, Person p2) {
        if(p1.marry(p2)) {
            System.out.println(p1.name + " can marry " + p2.name + '.');
        } else {
            System.out.println("Nope.");
        }
    }
    public static void main(String[] args) {
	    Person jack = new Person("Jack","male",null,24);
        Person marry = new Person("Marry","female",null,25);
        Main.testMarry(jack,marry);
        Person alice = new Person("Alice","female",null,23);
        Main.testMarry(alice,jack);
        Person john = new Person("John","male",null,21);
        Main.testMarry(john,alice);
        Person mike = new Person("Mike","male",null,24);
        Person xavier = new Person("Xavier","male",null,24);
        Main.testMarry(mike,xavier);
    }
}