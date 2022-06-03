package com.example.appbanco;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.example.appbanco.databinding.ActivityLoginUsuarioBinding;
import com.example.appbanco.databinding.ActivityOperacionesBancariasBinding;

public class OperacionesBancarias extends AppCompatActivity {

    @NonNull
    ActivityOperacionesBancariasBinding binding;
    usuario usuarios = new usuario();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityOperacionesBancariasBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        onClick();
    }
    private void onClick() {
        recibirParametros();
        retirar();
        transferir();
        historial();
        myQr();
        volver();
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


    private void retirar() {
        binding.btnRetirar.setOnClickListener(view -> {
            Intent intent = new Intent(this, Retirar.class);
            Bundle bundle = new Bundle();

            bundle.putString("user_name", usuarios.getName());
            bundle.putString("user_identification", usuarios.getIdentificacion());
            bundle.putString("user_email", usuarios.getMail());
            bundle.putString("numCuenta", usuarios.getNumeroCuenta());
            bundle.putInt("bill_amount", usuarios.getSaldo());
            bundle.putString("token", usuarios.getToken());
            intent.putExtras(bundle);
            startActivity(intent);

        });
    }

    private void transferir() {
        binding.btnTransferir.setOnClickListener(view -> {

            new AlertDialog.Builder(this)
                    .setTitle("Tranferir por QR")
                    .setPositiveButton("Si", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            Intent intent = new Intent(OperacionesBancarias.this, tranferirQR.class);
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
                    })
                    .setNegativeButton("No", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            Intent intent = new Intent(OperacionesBancarias.this, Transferencia.class);
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
                    }).show();

        });
    }

    private void historial() {
        binding.btnCuentas.setOnClickListener(view -> {
            Intent intent = new Intent(this, Cuentas.class);
            Bundle bundle = new Bundle();

            bundle.putString("user_name", usuarios.getName());
            bundle.putString("user_identification", usuarios.getIdentificacion());
            bundle.putString("user_email", usuarios.getMail());
            bundle.putString("numCuenta", usuarios.getNumeroCuenta());
            bundle.putInt("bill_amount", usuarios.getSaldo());
            bundle.putString("token", usuarios.getToken());
            intent.putExtras(bundle);
            startActivity(intent);
        });
    }

    private void myQr() {
        binding.btnQR.setOnClickListener(view -> {
            Intent intent = new Intent(this, myQR.class);
            Bundle bundle = new Bundle();

            bundle.putString("user_name", usuarios.getName());
            bundle.putString("user_identification", usuarios.getIdentificacion());
            bundle.putString("user_email", usuarios.getMail());
            bundle.putString("numCuenta", usuarios.getNumeroCuenta());
            bundle.putInt("bill_amount", usuarios.getSaldo());
            bundle.putString("token", usuarios.getToken());
            intent.putExtras(bundle);
            startActivity(intent);
        });
    }

    private void volver() {
        binding.btnVolverOB.setOnClickListener(view -> {
            Intent intentMain = new Intent(this, LoginUsuario.class);
            startActivity(intentMain);
        });
    }
}

