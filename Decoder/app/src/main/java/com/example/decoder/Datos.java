package com.example.decoder;

public class Datos {

    public String data;
    public String type;
    public String usage;

    public Datos(String data, String type, String usage) {
        this.data = data;
        this.type = type;
        this.usage = usage;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getUsage() {
        return usage;
    }

    public void setUsage(String usage) {
        this.usage = usage;
    }
}
