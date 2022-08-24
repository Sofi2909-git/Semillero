/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */
package com.mycompany.doubletriplenumber;

import java.util.Scanner;
import javax.swing.SizeRequirements;

/**
 *
 * @author se202
 */
public class DoubleTripleNumber {

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int number;
        System.out.println("\tWELCOME");
        System.out.println("\nINSERT NUMBER:");
        number = s.nextInt();
        calculate(number);
    }

    private static void calculate(int number) {
        int doubleNumber, tripleNumber;
        doubleNumber = number * 2;
        tripleNumber = number * 3;
        System.out.println("DOUBLE THE NUMBER IS: " + doubleNumber);
        System.out.println("TRIPLE THE NUMBER IS: " + tripleNumber);
    }
}
