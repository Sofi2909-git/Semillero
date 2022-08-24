/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */
package com.mycompany.convertdegrees;

import java.util.Scanner;

/**
 *
 * @author se202
 */
public class ConvertDegrees {

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        double degrees;
        System.out.println("\tWELCOME TO DEGREE CONVERT");
        System.out.println("\nINSERT DEGREES IN CENTIGRADE:");
        degrees = s.nextDouble();
        converter(degrees);
    }

    private static void converter(double centigrade) {
        double fahrenheit, kelvin;
        fahrenheit = 32 + (9 * centigrade / 5);
        kelvin = centigrade + 273;
        System.out.println("CENTIGRADE TO FAHRENHEIT: " + fahrenheit);
        System.out.println("CENTIGRADE TO KELVIN: " + kelvin);
    }
}
