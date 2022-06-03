package com.example.appbanco;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;
import com.example.appbanco.databinding.ActivityCuentasBinding;
import com.example.appbanco.databinding.ActivityMyQrBinding;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class myQR extends AppCompatActivity {

    ActivityMyQrBinding binding;
    usuario usuarios = new usuario();
    RequestQueue request;

    String countNumber;
    String img;
    String token;
    String name;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMyQrBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        request = Volley.newRequestQueue(getBaseContext());
        onClick();
    }
    private void onClick() {
        recibirParametros();
        obtenerQR();
        volver();
    }
    private void volver() {
        //VOLVER
        binding.volverQr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(myQR.this, OperacionesBancarias.class);
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
        });

    }
    private void recibirParametros() {
        Bundle parametros = this.getIntent().getExtras();
        usuarios.setName(parametros.getString("user_name"));
        usuarios.setIdentificacion(parametros.getString("user_identification"));
        usuarios.setMail(parametros.getString("user_email"));
        usuarios.setNumeroCuenta(parametros.getString("numCuenta"));
        usuarios.setToken(parametros.getString("token"));
        usuarios.setSaldo(parametros.getInt("bill_amount"));
    }
    private void obtenerQR() {
        countNumber = usuarios.getNumeroCuenta();
        token = usuarios.getToken();
        name = usuarios.setName();
        binding.nombreUsuario.setText(name);
        HashMap<String, String> paramsAuth = new HashMap<>();
        paramsAuth.put("numberBill", countNumber);
        try {
            request = Volley.newRequestQueue(getBaseContext());
            JsonObjectRequest arrayRequest = new JsonObjectRequest(
                    Request.Method.POST,
                    "http://10.51.1.89:8080/QR/createCommonQRCode",
                    new JSONObject(paramsAuth),
                    new Response.Listener<JSONObject>() {
                        public void onResponse(JSONObject response) {
                            Log.e("Response", "onResponse: " + response.toString());
                            if (response.optBoolean("status")) {
                                Log.e("Response", "if: " + response.toString());
                                img = response.optString("img");
                                byte[] bytes = Base64.decode(img, Base64.DEFAULT);
                                Bitmap imgQr = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
                                binding.qr.setImageBitmap(imgQr);
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
                @Override
                public Map<String, String> getHeaders() throws AuthFailureError {
                    Map<String, String> params = new HashMap<>();
                    params.put("Authorization", token);
                    Log.e("Authorization1", params.toString());
                    return params;
                }
            };
            request.add(arrayRequest);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}