package com.example.decoder;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class AdapterDatos extends RecyclerView.Adapter<AdapterDatos.ViewHolderDatos> {
    private ArrayList<Datos> list;
    public AdapterDatos(ArrayList<Datos> list) {
        this.list = list;
    }

    @NonNull
    @Override
    public AdapterDatos.ViewHolderDatos onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.recycler_view, null);
        return new AdapterDatos.ViewHolderDatos(v);
    }
    @Override
    public void onBindViewHolder(@NonNull AdapterDatos.ViewHolderDatos holder, int position) {
        holder.asignarDatos(list.get(position));
    }
    @Override
    public int getItemCount() {
        return list.size();
    }

    public class ViewHolderDatos extends RecyclerView.ViewHolder {
        TextView data;
        TextView type;
        TextView usage;

        public ViewHolderDatos(@NonNull View View) {
            super(View);
            data = View.findViewById(R.id.id_data);
            type = View.findViewById(R.id.id_type);
            usage = View.findViewById(R.id.id_usage);
        }
        public void asignarDatos(Datos dato) {
            data.setText(dato.getData());
            type.setText(dato.getType());
            usage.setText(dato.getUsage());
        }
    }
}
