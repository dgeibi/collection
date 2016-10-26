package com.github.dgeibi;

public class Rectangle {

    private int width;
    private int height;
    public int getArea() {
        return this.width * this.height;
    }
    public int getPerimeter() {
        return (this.width+this.height) * 2;
    }
    public void Draw() {
        for (int i = 0; i<this.height; i+=1) {
            for(int j = 0; j<this.width; j+=1){
                System.out.print('*');
            }
            System.out.print('\n');
        }
    }
    public Rectangle(int w,int h) {
        if(w>50) this.width =50; else if (w<0) this.width = 0; else this.width = w;
        if(h>50) this.height = 50; else if (h<0) this.height = 0; else this.height = h;
    }
}
