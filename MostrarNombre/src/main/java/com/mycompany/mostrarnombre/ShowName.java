/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */
package com.mycompany.mostrarnombre;

import java.util.Scanner;

/**
 *
 * @author se202
 */
public class ShowName {

    public static void main(String[] args) {
        String name;
        Scanner s = new Scanner(System.in);
        System.out.println("ENTER YOUR NAME:");
        name=s.nextLine();
        System.out.println("WELCOME " + name);
    }
}
