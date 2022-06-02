package com.example.appbanco;

import androidx.annotation.Nullable;
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
import com.example.appbanco.databinding.ActivityTranferirQrBinding;
import com.google.zxing.integration.android.IntentIntegrator;
import com.google.zxing.integration.android.IntentResult;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class tranferirQR extends AppCompatActivity {

    private EditText cuenta;
    usuario usuarios = new usuario();
    RequestQueue request;
    ActivityTranferirQrBinding binding;
    ProgressDialog pDialog;

    String numberBillE;
    String numberBillR;
    String amount;
    String confirmAmount;
    String token;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityTranferirQrBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Bundle parametros = this.getIntent().getExtras();
        usuarios.setNumeroCuenta(parametros.getString("numCuenta"));
        usuarios.setToken(parametros.getString("token"));

        viewscann();
        datos();

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        IntentResult result = IntentIntegrator.parseActivityResult(requestCode, resultCode, data);
        if (result != null) {
            if (result.getContents() == null) {
                Toast.makeText(this, "reading canceled", Toast.LENGTH_LONG).show();
            } else {
                Toast.makeText(this, result.getContents(), Toast.LENGTH_LONG).show();
                String codeQr = String.valueOf(result.getContents());
                cuenta = binding.cuentaScanner;
                cuenta.setText(codeQr);
            }
        } else {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    private void viewscann() {
        binding.btnScanner.setOnClickListener(view -> {
            dialogo("Iniciando camara");
            IntentIntegrator integrator = new IntentIntegrator(tranferirQR.this);
            integrator.setDesiredBarcodeFormats(IntentIntegrator.ALL_CODE_TYPES);
            integrator.setPrompt("Lector - QR");
            integrator.setCameraId(0);
            integrator.setOrientationLocked(false);
            integrator.setBeepEnabled(true);
            integrator.setCaptureActivity(AdaptadorHorizontal.class);
            integrator.setBarcodeImageEnabled(true);
            integrator.initiateScan();
            pDialog.dismiss();
        });
    }

    private void datos() {

        binding.transferirScanner.setOnClickListener(view -> {
            dialogo("Transfiriendo");
            cuenta = binding.cuentaScanner;
            amount = binding.montoScanner.getText().toString();
            confirmAmount = binding.confirMontoScanner.getText().toString();
            numberBillE = usuarios.getNumeroCuenta();
            numberBillR = cuenta.getText().toString();
            token = usuarios.getToken();
            request = Volley.newRequestQueue(getBaseContext());

            if (numberBillR.isEmpty() && amount.isEmpty() && confirmAmount.isEmpty()) {
                pDialog.dismiss();
                Toast.makeText(this, "Llene los campos", Toast.LENGTH_SHORT).show();
            } else if (!amount.equals(confirmAmount)) {
                Toast.makeText(this, "Vefirifique el monto", Toast.LENGTH_SHORT).show();
            } else {
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
                            if (response.optBoolean("status")) {
                                pDialog.dismiss();
                                new AlertDialog.Builder(tranferirQR.this)
                                        .setTitle("Transferencia exitosa")
                                        .setMessage("Volver a operaciones")
                                        .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                            @Override
                                            public void onClick(DialogInterface dialog, int which) {
                                                Intent intent = new Intent(tranferirQR.this, OperacionesBancarias.class);
                                                startActivity(intent);
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

    private void dialogo(String mensage) {
        pDialog = new ProgressDialog(this);
        pDialog.setMessage(mensage);
        pDialog.setCancelable(false);
        pDialog.show();
    }
}