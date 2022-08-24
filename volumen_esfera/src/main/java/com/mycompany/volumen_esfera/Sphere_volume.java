/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */
package com.mycompany.volumen_esfera;

import java.util.Scanner;

/**
 *
 * @author se202
 */
public class Sphere_volume {

    public static void main(String[] args) {
        byte radius;
        Scanner sc = new Scanner(System.in);
        System.out.println("\t\tWelcome to calculator of sphere volume\nPlease type the sphere radius");
        radius = sc.nextByte();
        System.out.println("The volume of the sphere is: " + (4.0 / 3) * Math.PI * Math.pow(radius, 3));
    }
}
