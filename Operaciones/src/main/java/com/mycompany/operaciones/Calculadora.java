/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.operaciones;

/**
 *
 * @author se202
 */
public class Calculadora extends Operaciones {

    private static boolean valor = true;

    public static void main(String[] args) {
        inicio();
    }

    public static void inicio() {
        System.out.println("\tBIENVENIDOS A SU CALCULADORA VIRTUAL:");
        while (valor) {
            System.out.println("\nINGRESE EL PRIMER VALOR:");
            opt = s.nextLine();
            if (valiNumbers(opt)) {
                num1 = Double.parseDouble(opt);
                do {
                    System.out.println("\nINGRESE EL SEGUNDO VALOR VALOR:");
                    opt = s.nextLine();
                    if (valiNumbers(opt)) {
                        num2 = Double.parseDouble(opt);
                        menu();
                        break;
                    }
                } while (valor);
            }
        }
    }

    public static void menu() {
        while (true) {
            System.out.println("1.SUMA\n2.RESTA\n3.MULTIPLICACION\n4.DIVISION\n5.TODAS\nELIJA UNA OPCION:");
            opt = s.nextLine();
            if (valiNumbers(opt)) {
                if (opt.matches("[1-5]")) {
                    switch (Integer.parseInt(opt)) {
                        case 1:
                            sum();
                            break;
                        case 2:
                            subtrac();
                            break;
                        case 3:
                            multiply();
                            break;
                        case 4:
                            division();
                            break;
                        case 5:
                            allOperations();
                            break;
                    }
                    if (closeCalculate() == 1) {
                        valor = false;
                        break;
                    } else if (closeCalculate() == 2) {
                        closeCalculate();
                    } else {
                        break;
                    }
                } else {
                    System.out.println("OPCION INCORRECTA");
                }
            }

        }
    }

    private static boolean valiNumbers(String opt) {
        boolean resp;
        try {
            Integer.parseInt(opt);
            resp = true;
        } catch (NumberFormatException e) {
            System.out.println("INGRESE SOLO NUMEROS");
            resp = false;
        }
        return resp;
    }

    private static int closeCalculate() {
        int respuesta;
        System.out.println("\nSALIR DE LA CALCULADORA: \n0.NO\n1.SI");
        opt = s.nextLine();
        if (opt.matches("[0-1]") && valiNumbers(opt)) {
            if (opt.equals("0")) {
                respuesta = 0;
            } else {
                respuesta = 1;
                System.out.println("GRACIAS POR USAR LA CALCULADORA");
            }
        } else {
            System.out.println("OPCION INCORRECTA");
            System.out.println("INGRESE SOLO NUMEROS");
            respuesta = 2;
        }
        return respuesta;
    }
}
