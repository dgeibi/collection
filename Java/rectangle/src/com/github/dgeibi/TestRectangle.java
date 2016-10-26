package com.github.dgeibi;

/**
 * Created by dgeibi on 10/2/16.
 */
public class TestRectangle {
    public static void main(String [] args) {
        Rectangle rect = new Rectangle(4,5);
        System.out.println("Area: " + rect.getArea());
        System.out.println("Perimeter: " + rect.getPerimeter());
        rect.Draw();
    }
}
