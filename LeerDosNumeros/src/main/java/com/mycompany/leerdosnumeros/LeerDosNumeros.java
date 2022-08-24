/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */
package com.mycompany.leerdosnumeros;

import java.util.Scanner;

/**
 * \n
 *
 * @author se202
 */
public class LeerDosNumeros {

    private static Scanner s = new Scanner(System.in);
    private static int num1;
    private static int num2;

    public static void main(String[] args) {
        System.out.println("PRIMER VALOR:");
        num1 = s.nextInt();
        System.out.println("\nSEGUNDO VALOR:");
        num2 = s.nextInt();
        System.out.println("\n\tLOS VALORES INGRESADOS SON \nPRIMER VALOR:" + num1 + "\nSEGUNDO VALOR:" + num2);
    }
}
