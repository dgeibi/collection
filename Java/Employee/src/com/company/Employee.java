package com.company;

import java.util.*;
public class Employee {
    private String name;
    private double salary;
    private Date hireDay;

    public static void main(String[] args) {
        Employee [] employees = new Employee [3];

        employees[0] = new Employee("Jin",7800,2003,8,2);
        employees[1] = new Employee("Ken",8453,2002,4,13);
        employees[2] = new Employee("White",9832,2008,2,14);

        for (int i = 0; i<3;i++){
            System.out.println(employees[i].getName() + "'s salary is " + employees[i].getSalary() +
                    ", hired at " + employees[i].getHireDay().toString());
        }

    }

    public Employee (){};
    public Employee(String n, double s, int year , int month , int day ) {
        Calendar c = Calendar.getInstance();
        c.set(year,month,day);
        this.setHireDay(new Date(c.getTimeInMillis()));
        this.setName(n);
        this.setSalary(s);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getSalary() {
        return salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public Date getHireDay() {
        return hireDay;
    }

    public void setHireDay(Date hireDay) {
        this.hireDay = hireDay;
    }

    public void raiseSalary(double salaryRate) {
        this.salary = salary * (1 + salaryRate);
    }
}
