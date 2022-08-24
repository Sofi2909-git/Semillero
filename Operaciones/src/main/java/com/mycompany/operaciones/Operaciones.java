/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.operaciones;

import java.util.Scanner;

/**
 *
 * @author se202
 */
public class Operaciones {

    public static double num1;
    public static double num2;
    public static double result;
    public static String opt;
    public static Scanner s = new Scanner(System.in);

    protected static void sum() {
        result = num1 + num2;
        System.out.println("\nSUMA:" + result);
    }

    protected static void subtrac() {
        result = num1 - num2;
        System.out.println("\nRESTA:" + result);

    }

    protected static void multiply() {
        result = num1 * num2;
        System.out.println("\nMULTIPLICACION:" + result);
    }

    protected static void division() {
        result = num1 / num2;
        System.out.println("\nDIVISION:" + result);
    }

    protected static void allOperations() {
        System.out.println("\tRESULTADOS");
        sum();
        subtrac();
        multiply();
        division();
    }

}
