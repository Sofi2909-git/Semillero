package com.example.appbanco;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.example.appbanco.databinding.MostrarDatosBinding;
import java.util.ArrayList;

public class AdapterDatos extends RecyclerView.Adapter<AdapterDatos.ViewHolderHistory> {

    private ArrayList<HistorialCuenta> historyList;

    public AdapterDatos(ArrayList<HistorialCuenta> historyList) {
        this.historyList = historyList;
    }

    @NonNull
    @Override
    public ViewHolderHistory onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {

        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        MostrarDatosBinding itemlist = MostrarDatosBinding.inflate(layoutInflater, parent, false);
        RecyclerView.ViewHolder data = null;
        data = (RecyclerView.ViewHolder) (new AdapterDatos.ViewHolderHistory(itemlist));
        return (ViewHolderHistory) data;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolderHistory holder, int position) {
        HistorialCuenta transf = historyList.get(position);
        holder.binding.vistaDatosid.setText(transf.getId());
        holder.binding.vistaDatostype.setText(transf.getType());
        holder.binding.vistaDatosdescription.setText(transf.getDescription());
        holder.binding.vistaDatosamount.setText(transf.getAmount());
        holder.binding.vistaDatosdate.setText(transf.getDate());

    }

    @Override
    public int getItemCount() {
        return historyList.size();
    }

    public class ViewHolderHistory extends RecyclerView.ViewHolder {

        private final MostrarDatosBinding binding;

        public ViewHolderHistory(@NonNull MostrarDatosBinding binding) {
            super((View) binding.getRoot());
            this.binding = binding;
        }
    }
}
