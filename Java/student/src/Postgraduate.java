/**
 * Created by dgeibi on 10/3/16.
 */
public class Postgraduate extends Student{
    public Postgraduate(String name, double performance) {
        super(name,performance);
    }
    public char getLevel() {
        char level;
        if (performance >= 95) level = 'A';
        else if (performance >= 85) level = 'B';
        else if (performance >= 75) level = 'C';
        else if (performance >= 60) level = 'D';
        else level = 'E';
        return level;
    }
}
