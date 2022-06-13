package com.example.bitmapfinal;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentTransaction;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;

import com.example.bitmapfinal.databinding.ActivityCalcularBitmapBinding;

import java.util.ArrayList;
import java.util.HashMap;

public class calcularBitmap extends AppCompatActivity {

    private ArrayList<ValorBitmap> list;
    private RecyclerView.Adapter adapter;
    ActivityCalcularBitmapBinding binding;
    String hexadecimales;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityCalcularBitmapBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        list = new ArrayList<>();
        llenarList();
        calcularBitmaps();
    }

    private void calcularBitmaps() {
        setAdapter();
        calcular();
    }

    private void setAdapter() {
        RecyclerView.LayoutManager layoutManager = new GridLayoutManager(this, 4);
        binding.RecyclerId.setLayoutManager(new GridLayoutManager(this, 4));
        adapter = new AdapterDatos(list, binding.hexadecimal);
        binding.RecyclerId.setHasFixedSize(true);
        binding.RecyclerId.setAdapter(adapter);
    }

    private void llenarList() {
        for (int i = 1; i < 129; i++) {
            if (i <= 99) {
                list.add(new ValorBitmap("Bit 0" + i, false, "0"));
            } else {
                list.add(new ValorBitmap("Bit " + i, false, "0"));
            }
        }
    }

    private void calcular() {

        binding.btnCalcular.setOnClickListener(view -> {
            hexadecimales = binding.hexadecimal.getText().toString();
            String bin = hexToBinary(hexadecimales);
            Log.e("calcular: ", "Respuesta: " + bin);
            cambiarEstado(bin);
        });
    }

    private String hexToBinary(String hexadecimal) {
        String binary = "";  // para almacenar la secuencia binaria convertida
        hexadecimal = hexadecimal.toUpperCase(); //conversión de la cadena a mayúsculas

        // inicializar la clase HashMap

        HashMap<Character, String> hashMap // Un HashMap básicamente designa claves únicaspara los valores correspondientes que se pueden recuperar en cualquier punto dado.
                = new HashMap<Character, String>();

        // almacenar los pares clave-valor
        hashMap.put('0', "0000");
        hashMap.put('1', "0001");
        hashMap.put('2', "0010");
        hashMap.put('3', "0011");
        hashMap.put('4', "0100");
        hashMap.put('5', "0101");
        hashMap.put('6', "0110");
        hashMap.put('7', "0111");
        hashMap.put('8', "1000");
        hashMap.put('9', "1001");
        hashMap.put('A', "1010");
        hashMap.put('B', "1011");
        hashMap.put('C', "1100");
        hashMap.put('D', "1101");
        hashMap.put('E', "1110");
        hashMap.put('F', "1111");

        int i;
        // bucle para iterar a través de la longitud de la cadena hexadecimal
        for (i = 0; i < hexadecimal.length(); i++) {
            char ch = hexadecimal.charAt(i); // extraer cada carácter

            if (hashMap.containsKey(ch)) { // comprobar si el carácter está presente en las claves
                binary += hashMap.get(ch); //// añadiendo a la Secuencia Binario el valor correspondiente de la clave
            } else {
                binary = "Invalid Hexadecimal String"; // devuelve Hexadecimal inválido Cadena si el carácter no está presente en las claves
                return binary;
            }
        }
        // devolver el binario convertido
        return binary;
    }


    private void cambiarEstado(String binarios) {
        for (int i = 0; i < list.size(); i++) {
            list.get(i).setEstado(false);
        }
        for (int i = 0; i < binarios.length(); i++) {
            if (binarios.charAt(i) == '1') {
                list.get(i).setEstado(true);
                list.get(i).setValorBinario("1");
            }
        }
        setAdapter();
    }


}

