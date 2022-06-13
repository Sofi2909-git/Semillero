package com.example.bitmapfinal;

public class ValorBitmap {
    String numero;
    boolean estado;
    String ValorBinario;


    public ValorBitmap(String numero, boolean estado,String ValorBinario) {
        this.numero = numero;
        this.estado = estado;
        this.ValorBinario=ValorBinario;
    }

    public String getValorBinario() {
        return ValorBinario;
    }

    public void setValorBinario(String valorBinario) {
        ValorBinario = valorBinario;
    }

    public String getNumero() {
        return numero;
    }

    public void setNumero(String numero) {
        this.numero = numero;
    }

    public boolean getEstado() {
        return estado;
    }

    public void setEstado(boolean estado) {
        this.estado = estado;
    }

    @Override
    public String toString() {
        return "ValorBitmap{" +
                "numero='" + numero + '\'' +
                ", estado=" + estado +
                ", ValorBinario='" + ValorBinario + '\'' +
                '}';
    }
}