public class Main {

    public static void main(String[] args) {
        Student[] stuArray = new Student[2];
        Undergraduate ug = new Undergraduate("Mike",87.22);
        Postgraduate pg = new Postgraduate("Ken", 98);
        stuArray[0] = ug;
        stuArray[1] = pg;
        for (Student s:
             stuArray) {
            System.out.println("name: " + s.name + ", performance: " + s.performance + ", level: " + s.getLevel());
        }
    }
}
