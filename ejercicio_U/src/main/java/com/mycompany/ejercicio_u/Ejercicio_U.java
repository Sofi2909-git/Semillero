package com.mycompany.ejercicio_u;

import java.util.Scanner;

/**
 * @author se202
 */
public class Ejercicio_U {

    private static Scanner sc = new Scanner(System.in);
    private static String name, surname;
    private static double materias[];
    private static int n;
    private static double materia;

    public static void main(String[] args) {
        index();
    }

    private static void index() {
        getData();
        getGrades();
    }

    private static void getData() {
        while (true) {
            System.out.println("Ingrese su primer nombre: ");
            name = sc.nextLine();
            if (validateName(name)) {
                break;
            }
        }
        while (true) {
            System.out.println("Ingrese su primer apellido: ");
            surname = sc.nextLine();
            if (validateName(surname)) {
                break;
            }
        }
    }

    private static void getGrades() {
        n = (int) Math.round((validateGrades("Ingrese cantidad de materias del semestre: ")));
        materias = new double[n];
        for (int i = 0; i < n; i++) {
            materia = validateGrades("Ingrese notas de la materia " + (i + 1));
            materias[i] = materia;
        }
        getAverage();
    }

    private static void getAverage() {
        double average = 0, aux = 0;
        for (int i = 0; i < materias.length; i++) {
            aux += materias[i];
        }
        average = aux / n;
        System.out.println(name + " " + surname + " su promedio final es: " + average);
    }

    private static double validateGrades(String message) {
        String grades = "";
        boolean ciclon;
        do {
            System.out.println(message);
            grades = sc.nextLine();
            if (String.valueOf(grades).matches("[0-9].*")) {
                ciclon = false;
            } else {
                System.out.println("Digita nuevamente \n");
                ciclon = true;
            }
        } while (ciclon);
        return Double.parseDouble(grades);
    }

    private static boolean validateName(String data) {
        boolean ciclon = false;
        if (data.isEmpty()) {
            ciclon = false;
            System.out.println("Por favor, complete el campo \n");
        } else if (!data.matches("[a-zA-Z]*")) {
            ciclon = false;
            System.out.println("Por favor ingrese solo letras");
        } else {
            ciclon = true;
        }
        return ciclon;
    }

}
