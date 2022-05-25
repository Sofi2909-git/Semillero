package com.example.serviciospblicos;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    public ArrayList<Usuario> datosUsuario = new ArrayList<>();
    public Usuario usuarios;
    private EditText cedula;
    private EditText clave;
    private Button inicio;
    private Button registro;
    int posUsuario;
    boolean existe;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        datosUsuario= RegistroActivity.datosUsuario;
        cedula=findViewById(R.id.cedulaI);
        clave=findViewById(R.id.claveI);
        inicio=findViewById(R.id.inicio);
        registro=findViewById(R.id.registrar);

        registro.setOnClickListener(view-> {
            Intent intentRegistro = new Intent(this, RegistroActivity.class);
            startActivity(intentRegistro);
        });

        inicio.setOnClickListener(view->{
            String cc=cedula.getText().toString();
            String password=clave.getText().toString();

            if (password.isEmpty() && cc.isEmpty()) { //se valida que el campo tenga algo y se pasa de editText a string
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            } else if (datosUsuario.size() == 0) {
                Toast.makeText(this, "Usuario no registrado", Toast.LENGTH_LONG).show();
            } else if (cc.isEmpty()) {
                Toast.makeText(this, "Ingrese su cédula", Toast.LENGTH_LONG).show();
            } else if (password.isEmpty()) {
                Toast.makeText(this, "Ingrese su clave", Toast.LENGTH_SHORT).show();
            }else {
                for (int i = 0; i < datosUsuario.size(); i++) {
                    if (cc.equals(datosUsuario.get(i).getCedula()) && password.equals(datosUsuario.get(i).getClave())) {
                        existe=true;
                        posUsuario=i;
                        break;
                    }
                }
            }
            if(existe){
                Toast.makeText(this, "Inicio exitoso", Toast.LENGTH_LONG).show();
                Intent intent = new Intent(this, PagosActivity.class);
                Bundle parmetros = new Bundle();
                parmetros.putInt("posicion", posUsuario);
                intent.putExtras(parmetros);
                startActivity(intent);
            }

        });
    }
}