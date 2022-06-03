package com.example.appbanco;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;
import com.example.appbanco.databinding.ActivityLoginUsuarioBinding;
import com.example.appbanco.databinding.ActivityTransferenciaBinding;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class Transferencia extends AppCompatActivity {

    usuario usuarios = new usuario();
    RequestQueue request;
    ActivityTransferenciaBinding binding;
    ProgressDialog pDialog;

    String numberBillE;
    String numberBillR;
    String amount;
    String confirmAmount;
    String token;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityTransferenciaBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        onClick();
    }
    private void onClick() {
        recibirParametros();
        Transferencia();
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
    private void Transferencia(){
        binding.btnTransferencia.setOnClickListener(view -> {

            numberBillR = binding.cuentaTransferir.getText().toString();
            amount = binding.montoTransferir.getText().toString();
            confirmAmount = binding.confirmarMontoTranferir.getText().toString();
            numberBillE = usuarios.getNumeroCuenta();
            token = usuarios.getToken();
            request = Volley.newRequestQueue(getBaseContext());
            int saldo=Integer.parseInt(amount);

            if (numberBillR.isEmpty() && amount.isEmpty() && confirmAmount.isEmpty()) {
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            } else if (!amount.equals(confirmAmount)) {
                Toast.makeText(this, "Vefirifique el monto", Toast.LENGTH_SHORT).show();
            }  else if (saldo<1000) {
                Toast.makeText(this, "Monto minimo de mil", Toast.LENGTH_SHORT).show();
             //  pDialog.dismiss();
            }else {
                dialogo("Transfiriendo");
                cargarWebService();
            }
        });
    }
    private void cargarWebService() {

        HashMap<String, String> paramsAuth = new HashMap<>();
        paramsAuth.put("numberBill", numberBillE);
        paramsAuth.put("typeTransaction", "TRANSFERENCIA");
        paramsAuth.put("amount", amount);
        paramsAuth.put("numberBillDestiny", numberBillR);
        try {
            request = Volley.newRequestQueue(getBaseContext());
            JsonObjectRequest arrayRequest = new JsonObjectRequest(
                    Request.Method.PUT,
                    "http://10.51.1.89:8080/transaction/transfer",
                    new JSONObject(paramsAuth),
                    new Response.Listener<JSONObject>() {
                        public void onResponse(JSONObject response) {
                            Log.e("Response", "onResponse: " + response.toString());
                            if (response.optBoolean("status")) {
                                pDialog.dismiss();
                                new AlertDialog.Builder(Transferencia.this)
                                        .setTitle("Transferencia exitosa")
                                        .setMessage("Volver a operaciones")
                                        .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                            @Override
                                            public void onClick(DialogInterface dialog, int which) {
                                              volverOperaciones();
                                            }
                                        }).show();
                            } else {
                               pDialog.dismiss();
                                Toast.makeText(getApplicationContext(), response.optString("msg"), Toast.LENGTH_LONG).show();
                            }
                        }
                    },
                    new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                           pDialog.dismiss();
                            Log.e("Error", "onErrorResponse: " + error.toString());
                        }
                    }) {
                @Override
                public Map<String, String> getHeaders() throws AuthFailureError {
                    Map<String, String> params = new HashMap<>();
                    params.put("Authorization", token);
                    return params;
                }
            };
            request.add(arrayRequest);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private void volverOperaciones() {
        Intent intent = new Intent(Transferencia.this, OperacionesBancarias.class);
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
    private void dialogo(String mensage) {
        pDialog = new ProgressDialog(this);
        pDialog.setMessage(mensage);
        pDialog.setCancelable(false);
        pDialog.show();
    }
}