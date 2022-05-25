package com.example.recargadecelulares;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Registro extends AppCompatActivity {

    public static ArrayList<Usuario> datosUsuario = new ArrayList<>(); //hago publica y estatica esta lista de datos
    Usuario usuarios;
    private EditText usuario;
    private EditText clave;
    private Button registrar;
    private Button volver;
    String usename;
    String password;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_registro);

        usuario = findViewById(R.id.email_registro); //lo que entra a teclado se guarda en esas variables
        clave = findViewById(R.id.password_registro);
        registrar = findViewById(R.id.btnRegistrar);
        volver = findViewById(R.id.btnVolver);

        registrar.setOnClickListener(view -> {
            usuarios = new Usuario();
            usename = usuario.getText().toString();
            password = clave.getText().toString();

            if (password.equals("") && usename.equals("")) { //se valida que el campo tenga algo y se pasa de editText a string
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            } else if (!validarCorreo(usename).find()) { //se valida que el usuario coloque un correo valido
                Toast.makeText(this, "Correo invalido", Toast.LENGTH_SHORT).show();
            } else if (password.length() < 8) { //una contraseña de minimo 8
                Toast.makeText(this, "Clave muy corta", Toast.LENGTH_SHORT).show();
            } else if (!validarClave(password)) {
                Toast.makeText(this, "Contraseña invalida", Toast.LENGTH_LONG).show();
            } else if (validarUsuario(usename)) {
                Toast.makeText(this, "Este usuario ya existe, inicie sesion", Toast.LENGTH_LONG).show();
            } else {
                usuarios.setCorreo(usename);
                usuarios.setClave(password);
                datosUsuario.add(usuarios);
                Toast.makeText(this, "Usuario registrado correctamente", Toast.LENGTH_SHORT).show();
                Intent intentInicio = new Intent(this, MainActivity.class);
                startActivity(intentInicio);
            }
        });

        volver.setOnClickListener(view -> {
            Intent intentInicio = new Intent(this, MainActivity.class);
            startActivity(intentInicio);
        });

    }

    private boolean validarUsuario(String id) {
        for (int i = 0; i < datosUsuario.size(); i++) {
            if (datosUsuario.get(i).getCorreo().equals(id)) {
                return true;
            }
        }
        return false;
    }

    public Matcher validarCorreo(String usuario) {
        //correo y clave
        Pattern pattern = Pattern.compile("^[_A-Za-z0-9-\\+]+(\\.[_A-Za-z0-9-]+)*@" + "[A-Za-z0-9-]+(\\.[A-Za-z0-9]+)*(\\.[A-Za-z]{2,})$");
        Matcher mather = pattern.matcher(usuario);
        return mather;
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