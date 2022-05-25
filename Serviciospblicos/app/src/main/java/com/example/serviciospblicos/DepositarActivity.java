package com.example.serviciospblicos;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

public class DepositarActivity extends AppCompatActivity {

    private EditText cedula;
    private EditText monto;
    private EditText montoConfirma;
    private Button depositar;
    private TextView mostrarSaldo;
    public ArrayList<Usuario> datosUsuario = new ArrayList<>();

    String id;
    String saldo;
    String saldoConfirmar;
    int pos;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_depositar);

        Bundle posicion = this.getIntent().getExtras();//se usa para obtener lo que trae el objeto Intent

        if (posicion != null) {
            pos = posicion.getInt("posicion");
        }

        cedula = findViewById(R.id.identificacion);
        monto = findViewById(R.id.monto_Deposito);
        montoConfirma = findViewById(R.id.monto_confirma_De);
        datosUsuario = RegistroActivity.datosUsuario;
        depositar=findViewById(R.id.button_Depositar);
        mostrarSaldo=findViewById(R.id.saldo);

        mostrarSaldo.setText(String.valueOf(datosUsuario.get(pos).getSaldo()));

        depositar.setOnClickListener(view -> {
            id = cedula.getText().toString();
            saldo = monto.getText().toString();
            saldoConfirmar = montoConfirma.getText().toString();

            int valorMonto = 0;
            if (!saldo.isEmpty()) {
                valorMonto = Integer.parseInt(saldo);
            }

            if (id.isEmpty() && saldo.isEmpty() && saldoConfirmar.isEmpty()) {
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_SHORT).show();
            } else if (id.length() != 10) {
                Toast.makeText(this, "Ingrese una cédula válida", Toast.LENGTH_SHORT).show();
            } else if (valorMonto < 1000) {
                Toast.makeText(this, "Monto minimo de 1000", Toast.LENGTH_SHORT).show();
            } else if (!saldo.equals(saldoConfirmar)) {
                Toast.makeText(this, "Verifique su monto", Toast.LENGTH_SHORT).show();
            } else {
                int saldoPersona = datosUsuario.get(pos).getSaldo();
                int resultado = saldoPersona + valorMonto;
                datosUsuario.get(pos).setSaldo(resultado);

                new AlertDialog.Builder(this)
                        .setTitle("Deposito exitoso")
                        .setMessage("Su saldo actual es: " + resultado+ "\nFecha y hora: "+Hora())
                        .setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                Intent intentIncio = new Intent(DepositarActivity.this, PagosActivity.class);
                                startActivity(intentIncio);
                            }
                        }).show();
            }


        });
    }
    public String Hora () {

        SimpleDateFormat dtf = new SimpleDateFormat("yyyy/MM/dd  HH:mm");
        Calendar calendar = Calendar.getInstance();
        Date dateObj = calendar.getTime();
        String formattedDate = dtf.format(dateObj);
        System.out.println(formattedDate);
        return formattedDate;
    }
}