package com.example.appbanco;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.JsonRequest;
import com.android.volley.toolbox.Volley;
import com.example.appbanco.databinding.ActivityLoginUsuarioBinding;
import com.example.appbanco.databinding.ActivityRegistroUsuarioBinding;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegistroUsuario extends AppCompatActivity {

    public static ArrayList<usuario> datosUsuario = new ArrayList<>(); //hago publica y estatica esta lista de datos
    usuario usuarios;
    ActivityRegistroUsuarioBinding binding;

    String name;
    String id;
    String mail;
    String password;
    //establecen la conexiopn con el web service
    RequestQueue request;
    JsonRequest jsonRequest;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityRegistroUsuarioBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        usuarios = new usuario();
        onClick();
    }
    private void onClick() {
        registrar();
        volver();
    }

    private void registrar(){
        binding.btnRegistrar.setOnClickListener(view -> {

            name = binding.nombreR.getText().toString();
            id = binding.identificacionR.getText().toString();
            mail = binding.correoR.getText().toString();
            password = binding.claveR.getText().toString();
            request = Volley.newRequestQueue(getApplicationContext());

            if (name.isEmpty() && id.isEmpty() && mail.isEmpty() && password.isEmpty()) {
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            } else if (id.length() != 10) {
                Toast.makeText(this, "Ingrese una identificación válida", Toast.LENGTH_LONG).show();
            } else if (!validarCorreo(mail).find()) { //se valida que el usuario coloque un correo valido
                Toast.makeText(this, "Correo invalido", Toast.LENGTH_LONG).show();
            } else if (validarUsuario(mail)) {
                Toast.makeText(this, "Este usuario ya existe, inicie sesion", Toast.LENGTH_LONG).show();
            } else if (password.length() < 8) {
                Toast.makeText(this, "Contraseña muy corta", Toast.LENGTH_LONG).show();
            } else if (!validarClave(password)) {
                Toast.makeText(this, "Contraseña invalida", Toast.LENGTH_LONG).show();
            } else {
                cargarWebService();
            }

        });
    }

    private boolean validarUsuario(String id) {
        for (int i = 0; i < datosUsuario.size(); i++) {
            if (datosUsuario.get(i).mail.equals(id)) {
                return true;
            }
        }
        return false;
    }

    private void envieLoguin() {
        Intent intentMain = new Intent(this, LoginUsuario.class);
        startActivity(intentMain);
    }
    private void volver(){
        binding.btnVolverR.setOnClickListener(view -> {
            Intent intentMain = new Intent(this, MainActivity.class);
            startActivity(intentMain);
        });
    }

    private void cargarWebService() {

        HashMap<String, String> paramsAuth = new HashMap<>();
        paramsAuth.put("user_name", name);
        paramsAuth.put("user_identification", id);
        paramsAuth.put("user_email", mail);
        paramsAuth.put("user_password", password);
        paramsAuth.put("user_estate", "ACTIVO");
        Log.e("cargarWebService: ", "" + name + id + mail + password);
        try {
            request = Volley.newRequestQueue(getBaseContext());
            JsonObjectRequest arrayRequest = new JsonObjectRequest(
                    Request.Method.POST, //ENVIAR UNA PETICION Y  RECIBE UNA RESPUESTA
                    "http://10.51.1.89:8080/user/register",
                    new JSONObject(paramsAuth),
                    new Response.Listener<JSONObject>() {
                        public void onResponse(JSONObject response) {
                            Log.e("Response", "onResponse: " + response.toString());
                            System.out.println("Estado::::" + response.optBoolean("status"));
                            if (response.optBoolean("status")) {
                                Log.e("Response", "if: " + response.toString());
                                Toast.makeText(getApplicationContext(), response.optString("msg"), Toast.LENGTH_LONG).show();
                                envieLoguin();
                            } else {
                                Toast.makeText(getApplicationContext(), response.optString("msg"), Toast.LENGTH_LONG).show();
                            }
                        }
                    },
                    new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("Error", "onErrorResponse: " + error.toString());
                            Toast.makeText(RegistroUsuario.this, "Error: "+ error.toString(), Toast.LENGTH_SHORT).show();
                        }
                    }) {

            };
            request.add(arrayRequest);
        } catch (Exception e) {
            Toast.makeText(this, "Error: "+ e.toString(), Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }
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