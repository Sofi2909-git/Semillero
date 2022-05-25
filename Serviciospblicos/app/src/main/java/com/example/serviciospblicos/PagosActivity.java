package com.example.serviciospblicos;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

public class PagosActivity extends AppCompatActivity {

    private EditText factura;
    private EditText monto;
    private EditText montoConfirma;
    private Spinner spinner;
    private Button paga;
    public ArrayList<Usuario> datosUsuario = new ArrayList<>();

    String account;
    String balance;
    String balanceConfirm;
    String opcion;
    int pos;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mostrar);

        Bundle posicion = this.getIntent().getExtras();//se usa para obtener lo que trae el objeto Intent


        if (posicion != null) {
            pos = posicion.getInt("posicion");
        }

        datosUsuario = RegistroActivity.datosUsuario;
        factura = findViewById(R.id.factura);
        monto = findViewById(R.id.monto_Pagar);
        montoConfirma = findViewById(R.id.monto_confirma);
        spinner = findViewById(R.id.spinner);
        paga = findViewById(R.id.pago);

        String[] opciones = {"CENS", "AGUAS KAPITAL", "VEOLIA", "DIRECTV", "CANAL EXITO"};
        ArrayAdapter<String> empresas = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, opciones);
        spinner.setAdapter(empresas);

        paga.setOnClickListener(view -> {

            account = factura.getText().toString();
            balance = monto.getText().toString();
            balanceConfirm = montoConfirma.getText().toString();
            opcion = spinner.getSelectedItem().toString();

            int valorMonto = 0;
            if (!balance.isEmpty()) {
                valorMonto = Integer.parseInt(balance);
            }

            if (account.isEmpty() && balance.isEmpty() && balanceConfirm.isEmpty()) {
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_SHORT).show();
            } else if (account.length() != 10) {
                Toast.makeText(this, "Ingrese una factura válida", Toast.LENGTH_SHORT).show();
            } else if (valorMonto < 1000) {
                Toast.makeText(this, "Monto mínimo a pagar es 1000", Toast.LENGTH_SHORT).show();
            } else if (!balance.equals(balanceConfirm)) {
                Toast.makeText(this, "Verifique su monto", Toast.LENGTH_SHORT).show();
            } else if (!balance.isEmpty() && !balanceConfirm.isEmpty()) {
                int saldoPersona = datosUsuario.get(pos).getSaldo();
                if (valorMonto > saldoPersona) {
                    new AlertDialog.Builder(this)
                            .setTitle("Saldo insuficiente")
                            .setMessage("¿Desea depositar?")
                            .setPositiveButton("Si", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    Intent intent = new Intent(PagosActivity.this, DepositarActivity.class);
                                    startActivity(intent);
                                }
                            })
                            .setNegativeButton("No", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    finish();
                                }
                            }).show();
                } else {
                    int resultado = saldoPersona - valorMonto;
                    datosUsuario.get(pos).setSaldo(resultado);

                    new AlertDialog.Builder(this)
                            .setTitle("Pago exitoso")
                            .setMessage("Su saldo restante es: " + resultado + "\nFecha y hora: " + Hora())
                            .setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    Intent intentIncio = new Intent(PagosActivity.this, MainActivity.class);
                                    startActivity(intentIncio);
                                }
                            }).show();
                }
            }

        });
    }

    public String Hora() {

        SimpleDateFormat dtf = new SimpleDateFormat("yyyy/MM/dd  HH:mm");
        Calendar calendar = Calendar.getInstance();
        Date dateObj = calendar.getTime();
        String formattedDate = dtf.format(dateObj);
        System.out.println(formattedDate);
        return formattedDate;
    }
}