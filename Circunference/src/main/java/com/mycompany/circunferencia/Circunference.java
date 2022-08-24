/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */
package com.mycompany.circunferencia;

import java.util.Scanner;

/**
 * ^
 * \n
 *
 * @author se202
 */
public class Circunference {

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        double radius;
        System.out.println("\tWELCOME TO THE CIRCUNFERENCE CALCULATOR");
        System.out.println("\nTYPE RADIUS OF THE CIRCUMFERENCE: ");
        radius = s.nextDouble();
        calculating(radius);
    }

    private static void calculating(double radius) {
        double area, length;
        area = Math.PI * Math.pow(radius, 2);
        length = 2 * Math.PI * radius;
        System.out.println("CIRCUMFERENTIAL AREA: " + area);
        System.out.println("CIRCUMFERENTIAL LENGTH: " + length);
    }
}
