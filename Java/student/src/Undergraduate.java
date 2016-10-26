/**
 * Created by dgeibi on 10/3/16.
 */
public class Undergraduate extends Student{
    public Undergraduate(String name, double performance) {
        super(name,performance);
    }
    public char getLevel() {
        char level;
        if (performance >= 90) level = 'A';
        else if (performance >= 80) level = 'B';
        else if (performance >= 70) level = 'C';
        else if (performance >= 60) level = 'D';
        else level = 'E';
        return level;
    }
}
