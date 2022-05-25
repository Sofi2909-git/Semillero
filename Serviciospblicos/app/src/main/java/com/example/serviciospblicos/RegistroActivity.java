package com.example.serviciospblicos;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

public class RegistroActivity extends AppCompatActivity {
    public static ArrayList<Usuario> datosUsuario = new ArrayList<>();
    Usuario usuarios;
    private EditText nombre;
    private EditText cedula;
    private EditText clave;
    private EditText deposito;
    private EditText deposito_confirmar;
    private Button registro;
    private Button volver;

    String name;
    String id;
    String password;
    String balance, balan_confirma;
    int balance1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_registro);

        nombre = findViewById(R.id.NombrePersonName2);
        cedula = findViewById(R.id.cedula);
        clave = findViewById(R.id.clave);
        deposito = findViewById(R.id.deposito);
        deposito_confirmar = findViewById(R.id.deposito_confirma);
        registro = findViewById(R.id.registro);
        volver = findViewById(R.id.bntVolver);

        registro.setOnClickListener(view -> {
            usuarios = new Usuario();

            name = nombre.getText().toString();
            id = cedula.getText().toString();
            password = clave.getText().toString();
            balance = deposito.getText().toString();
            balan_confirma = deposito_confirmar.getText().toString();

            if (!balance.isEmpty()) {
                balance1 = Integer.parseInt(balance);
            }

            if (name.isEmpty() && id.isEmpty() && password.isEmpty() && balance.isEmpty() && balan_confirma.isEmpty()) {
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            } else if (id.length() != 10) {
                Toast.makeText(this, "Introduzca una cédula válida", Toast.LENGTH_LONG).show();
            } else if (password.length() < 8) {
                Toast.makeText(this, "Clave muy corta", Toast.LENGTH_SHORT).show();
            } else if (!validarClave(password)) {
                Toast.makeText(this, "Contraseña invalida", Toast.LENGTH_LONG).show();
            } else if (!balance.equals(balan_confirma)) {
                Toast.makeText(this, "Verifique su monto", Toast.LENGTH_SHORT).show();
            } else if (balance1 < 1000) {
                Toast.makeText(this, "Deposito minimo de 1000", Toast.LENGTH_SHORT).show();
            } else if (validarUsuario(id)) {
                Toast.makeText(this, "Este usuario ya esta registrado", Toast.LENGTH_LONG).show();
            } else {
                usuarios.setNombre(name);
                usuarios.setCedula(id);
                usuarios.setClave(password);
                usuarios.setSaldo(balance1);
                datosUsuario.add(usuarios);
                new AlertDialog.Builder(this)
                        .setTitle("Registro exitoso")
                        .setMessage("Nombre: " + name + "\nCédula: " + id + "\nSaldo:  " + balance1 + "\nFecha y hora: " + Hora())
                        .setPositiveButton("Aceptar", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                Intent intentIncio = new Intent(RegistroActivity.this, MainActivity.class);
                                startActivity(intentIncio);
                            }
                        }).setNegativeButton("Cancelar", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Log.d("Acción", "Se cancelo la operación");
                    }
                }).show();
            }
        });

        volver.setOnClickListener(view ->

        {
            Intent intentIncio = new Intent(RegistroActivity.this, MainActivity.class);
            startActivity(intentIncio);
        });
    }


    private boolean validarUsuario(String id) {
        for (int i = 0; i < datosUsuario.size(); i++) {
            if (datosUsuario.get(i).getCedula().equals(id)) {
                return true;
            }
        }
        return false;
    }

    public String Hora() {

        SimpleDateFormat dtf = new SimpleDateFormat("yyyy/MM/dd  HH:mm");
        Calendar calendar = Calendar.getInstance();
        Date dateObj = calendar.getTime();
        String formattedDate = dtf.format(dateObj);
        System.out.println(formattedDate);
        return formattedDate;
    }

    private boolean validarClave(String password) {

        int contadorMayusculas = 0, contadorMinisculas = 0, contadorSpecial = 0, contadorNumeros = 0;

        for (int i = 0; i < password.length(); i++) {
            char c = password.charAt(i);
            if (Character.isUpperCase(c)) {
                contadorMayusculas++;
            } else if (Character.isLowerCase(c)) {
                contadorMinisculas++;
            } else if (c >= 48 && c <= 57) {
                contadorNumeros++;
            } else if (c >= 33 && c <= 46 || c == 64) {
                contadorSpecial++;
            }
        }
        if (contadorMayusculas != 0 && contadorMinisculas != 0 && contadorNumeros != 0 && contadorSpecial != 0) {
            return true;
        } else {
            return false;
        }
    }
}
