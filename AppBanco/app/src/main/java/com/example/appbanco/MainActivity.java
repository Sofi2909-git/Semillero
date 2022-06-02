package com.example.appbanco;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.appbanco.databinding.ActivityLoginUsuarioBinding;
import com.example.appbanco.databinding.ActivityMainBinding;
import com.example.appbanco.databinding.ActivityRegistroUsuarioBinding;

public class MainActivity extends AppCompatActivity {

     ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        binding.bntRegistro.setOnClickListener(view->{
            Intent intentRegistro = new Intent(this, RegistroUsuario.class);
            startActivity(intentRegistro);
        });

        binding.bntInicio.setOnClickListener(view->{
            Intent intentInicio = new Intent(this, LoginUsuario.class);
            startActivity(intentInicio);
        });

    }
}