package com.example.recargadecelulares;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private EditText username;
    private EditText password;
    private Button inicio;
    private Button registrar;
    ArrayList<Usuario> datosUsuario = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        datosUsuario=Registro.datosUsuario; //aca llamo la lista que antes hice publica, le hago una copia
        username = findViewById(R.id.email);
        password = findViewById(R.id.password);
        registrar = findViewById(R.id.btnRegistrar);
        registro();
        inicio = findViewById(R.id.btnInicio);
        inicioSesion();
        //TODO VER FLUJO DE DATOS
        Log.e("Hola", "ad" + datosUsuario.size());
    }

    private void registro() {
        registrar.setOnClickListener(view -> {
            Intent intentRegistro = new Intent(this, Registro.class);
            startActivity(intentRegistro);
        });
    }

    private void inicioSesion() {
        inicio.setOnClickListener(view -> {
            String usuario = username.getText().toString();
            String clave = password.getText().toString();

            if (clave.equals("") && usuario.equals("")) { //se valida que el campo tenga algo y se pasa de editText a string
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            } else if (datosUsuario.size() == 0) {
                Toast.makeText(this, "Usuario no registrado", Toast.LENGTH_LONG).show();
            } else if (usuario.equals("")) {
                Toast.makeText(this, "Ingrese su correo", Toast.LENGTH_LONG).show();
            } else if (clave.equals("")) {
                Toast.makeText(this, "Ingrese su clave", Toast.LENGTH_SHORT).show();
            }else if (!clave.equals("") && !usuario.equals("")) {
                for (int i = 0; i < datosUsuario.size(); i++) {
                    if (usuario.equals(datosUsuario.get(i).getCorreo()) && clave.equals(datosUsuario.get(i).getClave())) {
                        Toast.makeText(this, "Inicio exitoso", Toast.LENGTH_LONG).show();
                        Intent intent = new Intent(this, Recarga.class);
                        startActivity(intent);
                    }else{
                        Toast.makeText(this, "Correo y/o clave incorrectos", Toast.LENGTH_LONG).show();
                    }
                }
            }
        });
    }

}