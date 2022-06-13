package com.example.bitmapfinal;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class AdapterDatos extends RecyclerView.Adapter<AdapterDatos.ViewHolderDatos> {
    EditText text;

    private ArrayList<ValorBitmap> list;

    public AdapterDatos(ArrayList<ValorBitmap> list, EditText text) {  // a este adaptador le va a llegar una lista de datos y se va a asignar al arrraylist
        this.list = list;
        this.text = text;
    }

    @NonNull
    @Override
    public ViewHolderDatos onCreateViewHolder(@NonNull ViewGroup parent, int viewType) { //enlaza este adaptador con el archivo recyclerview
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.recycler_view, null);
        return new AdapterDatos.ViewHolderDatos(v);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolderDatos holder, int position) { //se encarga de establecer la comunicación entre nuestro adaptador y la clase viewholderdatos
        Log.e("onBindViewHolder: ", "lista " + list.get(position));
        holder.asignarDatos(list.get(position), position);
    }

    @Override
    public int getItemCount() { // Returns the total number of items in the data set held by the adapter.
        return list.size();
    }

    public class ViewHolderDatos extends RecyclerView.ViewHolder {
        CheckBox checkBox;
        TextView textView;

        public ViewHolderDatos(@NonNull View view) {
            super(view);
            checkBox = view.findViewById(R.id.idCheckBox);
            textView = view.findViewById(R.id.idDatos);
        }

        public void asignarDatos(ValorBitmap dato, int position) {
            textView.setText(dato.getNumero());
            Log.e("asignardatos", "" + dato.getEstado());
            checkBox.setChecked(dato.getEstado());

            checkBox.setOnClickListener(view -> {
                if (checkBox.isChecked()) {
                    dato.setValorBinario("1");
                    dato.setEstado(true);
                } else {
                    dato.setValorBinario("0");
                    dato.setEstado(false);
                }
                list.set(position, dato);

                String concateneado = "";
                for (int i = 0; i < list.size(); i++) {
                    concateneado += list.get(i).getValorBinario();
                }
                concateneado = BintoHexa.binarioHexadecimal(concateneado);
                text.setText(concateneado);
            });
        }
    }
}
