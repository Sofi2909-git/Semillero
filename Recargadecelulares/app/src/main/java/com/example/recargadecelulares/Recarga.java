package com.example.recargadecelulares;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

public class Recarga extends AppCompatActivity {

    private EditText numero, confirma_numero;
    private EditText monto, monto_confirma;
    private Spinner spinner;
    private Button confirma;
    String num1;
    String num2;
    String monto1;
    String monto2;
    String operador;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recarga);

        numero=findViewById(R.id.numero);
        confirma_numero=findViewById(R.id.numero_confirma);
        monto=findViewById(R.id.monto);
        monto_confirma=findViewById(R.id.monto_confirma);
        spinner=findViewById(R.id.spinner);
        confirma=findViewById(R.id.btnconfirma);

        //arreglo del spinner
        String[] opciones= {"Claro", "Movistar", "Tigo", "Avantel"};
        ArrayAdapter <String> operadores=new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, opciones);
        spinner.setAdapter(operadores);

        confirma.setOnClickListener(view->{
            num1=numero.getText().toString();
            num2=confirma_numero.getText().toString();
            monto1=monto.getText().toString();
            monto2=monto_confirma.getText().toString();
            operador=spinner.getSelectedItem().toString();

            int valorMonto=0;
            if(!monto1.isEmpty()){
                valorMonto = Integer.parseInt(monto1);
            }

            if (num1.isEmpty() && num2.equals("") && monto1.equals("") && monto2.equals("")){
                Toast.makeText(this, "Llene todos los campos", Toast.LENGTH_LONG).show();
            }else if (num1.length()!=10){
                Toast.makeText(this, "Ingrese un número válido", Toast.LENGTH_LONG).show();
                numero.requestFocus();
            }else if (!num1.equals(num2)){
                Toast.makeText(this, "Verifique su numero", Toast.LENGTH_LONG).show();
            }else if (valorMonto<1000){
                Toast.makeText(this, "Monto minimo de 1000", Toast.LENGTH_LONG).show();
            }else if(!monto1.equals(monto2)){
                Toast.makeText(this, "Verifique su monto", Toast.LENGTH_SHORT).show();
            }else{
                new AlertDialog.Builder(this)
                        .setTitle("Confirmar recarga")
                        .setMessage("Numero: "+num1+"\nMonto: "+monto1+"\nOperador: "+operador)
                        .setPositiveButton("Aceptar",new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                new AlertDialog.Builder(Recarga.this)
                                        .setTitle("Recarga exitosa")
                                        .setPositiveButton("Aceptar",new DialogInterface.OnClickListener() {
                                            @Override
                                            public void onClick(DialogInterface dialog, int which) {
                                                Intent intentVolver = new Intent(Recarga.this, MainActivity.class);
                                                startActivity(intentVolver);
                                            }
                                        }).setNegativeButton("Cancelar", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int which) {
                                        Log.d("Acción","Se cancelo la operación");
                                    }
                                }).show();
                            }
                        }).setNegativeButton("Cancelar", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Log.d("Acción","Se cancelo la operación");
                    }
                }).show();
            }
        });

    }
}