package com.example.appbanco;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;
import com.example.appbanco.databinding.ActivityLoginUsuarioBinding;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;

public class LoginUsuario extends AppCompatActivity {

    private String mail;
    private String password;
    usuario usuarios = new usuario();
    ActivityLoginUsuarioBinding binding;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityLoginUsuarioBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        onClick();
    }

    private void onClick() {
        inicio();
        volver();
    }
    private void inicio(){
        binding.btnIniciar.setOnClickListener(view -> {
            mail = binding.correoI.getText().toString();
            password = binding.claveI.getText().toString();

            if (mail.isEmpty() && password.isEmpty()) {
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            } else {
                cargarWebService();
            }
        });
    }
    private void volver(){
        binding.btnvolverI.setOnClickListener(view -> {
            Intent intentMain = new Intent(this, MainActivity.class);
            startActivity(intentMain);
        });
    }
    private void cargarWebService() {

        HashMap<String, String> paramsAuth = new HashMap<>();
        paramsAuth.put("user_email", mail);
        paramsAuth.put("user_password", password);
        try {
            RequestQueue request = Volley.newRequestQueue(getBaseContext());
            JsonObjectRequest arrayRequest = new JsonObjectRequest(
                    Request.Method.POST, //ENVIAR UNA PETICION Y  RECIBE UNA RESPUESTA
                    "http://10.51.1.89:8080/user/login",
                    new JSONObject(paramsAuth),
                    new Response.Listener<JSONObject>() {
                        public void onResponse(JSONObject response) {
                            Log.e("Response", "onResponse: " + response.toString());
                            if (response.optBoolean("status")) {
                                Log.e("Response", "if: " + response.toString());
                                Toast.makeText(getApplicationContext(), response.optString("msg"), Toast.LENGTH_LONG).show();

                                JSONObject data = response.optJSONObject("data");
                                usuarios.setName(data.optString("user_name"));
                                usuarios.setIdentificacion(data.optString("user_identification"));
                                usuarios.setMail(data.optString("user_email"));
                                JSONObject bill = data.optJSONObject("bill");
                                usuarios.setSaldo(bill.optInt("bill_amount"));
                                String pasar = String.valueOf(bill.optLong("bill_number"));
                                System.out.println("TOKEN::: " + response.optString("token"));
                                usuarios.setToken(response.optString("token"));
                                usuarios.setNumeroCuenta(pasar);

                                envieOperaciones();
                            } else {
                                Toast.makeText(getApplicationContext(), response.optString("msg"), Toast.LENGTH_LONG).show();
                            }
                        }
                    },
                    new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("Error", "onErrorResponse: " + error.toString());

                        }
                    }) {

            };
            request.add(arrayRequest);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private void envieOperaciones() {
        Intent intent = new Intent(this, OperacionesBancarias.class);
        Bundle bundle = new Bundle();

        bundle.putString("user_name", usuarios.getName());
        bundle.putString("user_identification", usuarios.getIdentificacion());
        bundle.putString("user_email", usuarios.getMail());
        bundle.putString("numCuenta", usuarios.getNumeroCuenta());
        bundle.putInt("bill_amount", usuarios.getSaldo());
        bundle.putString("token", usuarios.getToken());
        intent.putExtras(bundle);
        startActivity(intent);
    }

}