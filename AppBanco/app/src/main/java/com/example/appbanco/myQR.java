package com.example.appbanco;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
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

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class myQR extends AppCompatActivity {

    private TextView nombre;
    private ImageView qr;
    private Button volver;
    usuario usuarios = new usuario();
    RequestQueue request;

    String countNumber;
    String img;
    String token;
    String name;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_qr);

        nombre = findViewById(R.id.nombreUsuario);
        qr = findViewById(R.id.qr);
        volver = findViewById(R.id.volverQr);

        request = Volley.newRequestQueue(getBaseContext());

        Bundle parametros = this.getIntent().getExtras();
        usuarios.setName(parametros.getString("user_name"));
        usuarios.setToken(parametros.getString("token"));
        usuarios.setNumeroCuenta(parametros.getString("numCuenta"));

        countNumber = usuarios.getNumeroCuenta();
        token = usuarios.getToken();
        name = usuarios.setName();
        nombre.setText(name);

        obtenerQR();

        volver.setOnClickListener(view->{
            Intent intentMain = new Intent(this, OperacionesBancarias.class);
            startActivity(intentMain);
        });

    }

    private void obtenerQR() {

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
                                qr.setImageBitmap(imgQr);
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