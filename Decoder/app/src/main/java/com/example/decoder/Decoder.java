package com.example.decoder;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.example.decoder.databinding.ActivityDecoderBinding;
import java.util.ArrayList;
import java.util.HashMap;

public class Decoder extends AppCompatActivity {
    ActivityDecoderBinding binding;
    private ArrayList<Datos> list;
    ArrayList<Integer> pos = new ArrayList<>();
    private RecyclerView.Adapter adapter;
    String msg;
    String bits;
    String hexadecimales;
    String trama;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityDecoderBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        list = new ArrayList<>();
        trama="00c3600000099908102020010002800019930010000001000030303632313733353532004441435455414c495a4143494f4e204150524f4241444120434f4e46494755524143494f4e205820475255504f00514e417c35322e38372e39322e35347c383136397c307c4e417c4e417c4e417c4e417c4e417c4e417c4e417c4e417c4e417c4e41003d4355505f454e474c4953485f383231302e677a2d364442373434344145423134413542344439383637453243343343423344334233334244323033370a";
        tomarTrama();
    }
    private void tomarTrama() {
        binding.btnRespuesta.setOnClickListener(view -> {
            list.clear();
            msg = trama.substring(14, 18);
            list.add(new Datos("00", "Tipo de mensaje", msg));
            hexadecimales = trama.substring(18, 34);
            list.add(new Datos("01", "Mapa de bits", hexadecimales));
            bits = hexToBinary(hexadecimales);
            pos = indexBitmap(bits);
            camposRespuesta(pos);
            setAdapter();
        });
    }
    private void setAdapter() {
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this.getBaseContext());
        binding.recyclerView.setLayoutManager(new LinearLayoutManager(this));
        adapter = new AdapterDatos(list);
        binding.recyclerView.setHasFixedSize(true);
        binding.recyclerView.setAdapter(adapter);
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
                binary = "Cadena hexadecimal invalida"; // devuelve Hexadecimal inválido Cadena si el carácter no está presente en las claves
                return binary;
            }
        }
        // devolver el binario convertido
        return binary;
    }
    private ArrayList<Integer> indexBitmap(String bitmapBin) {
        ArrayList<Integer> arrayNbytes = new ArrayList<>();
        for (int i = 0; i < bitmapBin.length(); i++) {
            if (bitmapBin.substring(i, i + 1).equals("1")) {
                arrayNbytes.add(i + 1);
            }
        }
        return arrayNbytes;
    }
    private void camposRespuesta(ArrayList<Integer> pos) {
        int iterador = 34;
        for (int i = 0; i < pos.size(); i++) {
            switch (pos.get(i)) {
                case 1:
                    String bitExtend = trama.substring(iterador, iterador + 64);
                    String bitBinExtend = hexToBinary(bitExtend);
                    list.add(new Datos("Bit 01 ", "Mapa de bits extendido", bitBinExtend));
                    iterador += 64;
                    break;
                case 2:
                    String PAN = trama.substring(iterador, iterador + 19);
                    String panNum = hextoNum(PAN);
                    list.add(new Datos("Bit 02 ", "Número de cuenta principal", panNum));
                    iterador += 19;
                    break;
                case 3:
                    String proceCode = trama.substring(iterador, iterador + 6);
                    list.add(new Datos("Bit 03 ", "Código de procesamiento", proceCode));
                    iterador += 6;
                    break;
                case 4:
                    String amount_trans = trama.substring(iterador, iterador + 12);
                    String amount_transNum = hextoNum(amount_trans);
                    list.add(new Datos("Bit 04 ", "Importe, transacción", amount_transNum));
                    iterador += 12;
                    break;
                case 5:
                    String amount_Sett = trama.substring(iterador, iterador + 12);
                    String amount_SettNum = hextoNum(amount_Sett);
                    list.add(new Datos("Bit 05 ", "Importe, liquidación", amount_SettNum));
                    iterador += 12;
                    break;
                case 6:
                    String amount_cardholBill = trama.substring(iterador, iterador + 12);
                    String amount_cardholBillNum = hextoNum(amount_cardholBill);
                    list.add(new Datos("Bit 06 ", "Importe, facturación del titular de la tarjeta", amount_cardholBillNum));
                    iterador += 12;
                    break;
                case 7:
                    String tranDateTime = trama.substring(iterador, iterador + 10);
                    String tranDateTimeNum = hextoNum(tranDateTime);
                    list.add(new Datos("Bit 07 ", "Fecha y hora de la transmisión", tranDateTimeNum));
                    iterador += 10;
                    break;
                case 8:
                    String amount_cardholdBillfee = trama.substring(iterador, iterador + 8);
                    String amount_cardholdBillfeeNum = hextoNum(amount_cardholdBillfee);
                    list.add(new Datos("Bit 08 ", "Importe, tasa de facturación del titular de la tarjeta", amount_cardholdBillfeeNum));
                    iterador += 8;
                    break;
                case 9:
                    String converRate_Sett = trama.substring(iterador, iterador + 8);
                    String converRate_SettNum = hextoNum(converRate_Sett);
                    list.add(new Datos("Bit 09 ", "Tasa de conversión, Liquidación", converRate_SettNum));
                    iterador += 8;
                    break;
                case 10:
                    String converRate_cardholdBill = trama.substring(iterador, iterador + 8);
                    String converRate_cardholdBillNum = hextoNum(converRate_cardholdBill);
                    list.add(new Datos("Bit 10 ", "Tasa de conversión, facturación al titular de la tarjeta", converRate_cardholdBillNum));
                    iterador += 8;
                    break;
                case 11:
                    String sysTrace = trama.substring(iterador, iterador + 6);
                    String sysTraceNum = hextoNum(sysTrace);
                    list.add(new Datos("Bit 11 ", "Número de auditoría de seguimiento de sistemas", sysTraceNum));
                    iterador += 6;
                    break;
                case 12:
                    String time_LocalTrans = trama.substring(iterador, iterador + 6);
                    String time_LocalTransNum = hextoNum(time_LocalTrans);
                    list.add(new Datos("Bit 12 ", "Tiempo, transacción local", time_LocalTransNum));
                    iterador += 6;
                    break;
                case 13:
                    String date_LocalTrans = trama.substring(iterador, iterador + 4);
                    String date_LocalTransNum = hextoNum(date_LocalTrans);
                    list.add(new Datos("Bit13 ", "Fecha, operación local (MMdd)", date_LocalTransNum));
                    iterador += 4;
                    break;
                case 14:
                    String date_expiration = trama.substring(iterador, iterador + 4);
                    String date_expirationNum = hextoNum(date_expiration);
                    list.add(new Datos("Bit 14 ", "Fecha, caducidad", date_expirationNum));
                    iterador += 4;
                    break;
                case 15:
                    String date_Settlement = trama.substring(iterador, iterador + 4);
                    String date_SettlementNum = hextoNum(date_Settlement);
                    list.add(new Datos("Bit 15 ", "Fecha, Liquidación", date_SettlementNum));
                    iterador += 4;
                    break;
                case 16:
                    String date_conversion = trama.substring(iterador, iterador + 4);
                    String date_conversionNum = hextoNum(date_conversion);
                    list.add(new Datos("Bit 16 ", "Fecha, conversión", date_conversionNum));
                    iterador += 4;
                    break;
                case 17:
                    String date_capture = trama.substring(iterador, iterador + 4);
                    String date_captureNum = hextoNum(date_capture);
                    list.add(new Datos("Bit 17 ", "Fecha, captura", date_captureNum));
                    iterador += 4;
                    break;
                case 18:
                    String merchantType = trama.substring(iterador, iterador + 4);
                    String merchantTypeNum = hextoNum(merchantType);
                    list.add(new Datos("Bit 18 ", "Tipo de comerciante", merchantTypeNum));
                    iterador += 4;
                    break;
                case 19:
                    String codeCountry = trama.substring(iterador, iterador + 3);
                    String codeCountryNum = hextoNum(codeCountry);
                    list.add(new Datos("Bit 19 ", "Código de país de la institución adquirente", codeCountryNum));
                    iterador += 3;
                    break;
                case 20:
                    String panEx_counCode = trama.substring(iterador, iterador + 3);
                    String panEx_counCodeNum = hextoNum(panEx_counCode);
                    list.add(new Datos("Bit 20 ", "PAN ampliado, código de país", panEx_counCodeNum));
                    iterador += 3;
                    break;
                case 21:
                    String forInt_counCode = trama.substring(iterador, iterador + 3);
                    String forInt_counCodeNum = hextoNum(forInt_counCode);
                    list.add(new Datos("Bit 21 ", "Institución remitente, código de país", forInt_counCodeNum));
                    iterador += 3;
                    break;
                case 22:
                    String pointServi = trama.substring(iterador, iterador + 3);
                    String pointServiNum = hextoNum(pointServi);
                    list.add(new Datos("Bit 22 ", "Modo de entrada en el punto de servicio", pointServiNum));
                    iterador += 3;
                    break;
                case 23:
                    String apliPanNumber = trama.substring(iterador, iterador + 3);
                    String apliPanNum = hextoNum(apliPanNumber);
                    list.add(new Datos("Bit 23 ", "Número PAN de la solicitud", apliPanNum));
                    iterador += 3;
                    break;
                case 24:
                    String functCode_netInter = trama.substring(iterador, iterador + 4);
                    String functCode_netInterNum = hextoNum(functCode_netInter);
                    list.add(new Datos("Bit 24 ", "Código de función (ISO 8583:1993)/Identificador internacional de red", functCode_netInterNum));
                    iterador += 4;
                    break;
                case 25:
                    String pointServiCondCode = trama.substring(iterador, iterador + 2);
                    String pointServiCondCodeNum = hextoNum(pointServiCondCode);
                    list.add(new Datos("Bit 25 ", "Código de condición del punto de servicio", pointServiCondCodeNum));
                    iterador += 2;
                    break;
                case 26:
                    String pointServiCapCode = trama.substring(iterador, iterador + 2);
                    String pointServiCapCodeNum = hextoNum(pointServiCapCode);
                    list.add(new Datos("Bit 26 ", "Código de captura del punto de servicio", pointServiCapCodeNum));
                    iterador += 2;
                    break;
                case 27:
                    String autIdeResLeng = trama.substring(iterador, iterador + 1);
                    String autIdeResLengNum = hextoNum(autIdeResLeng);
                    list.add(new Datos("Bit 27 ", "Longitud de respuesta de identificación de autorización", autIdeResLengNum));
                    iterador += 1;
                    break;
                case 28:
                    String amount_transFee = trama.substring(iterador, iterador + 8);
                    String amount_transFeeNum = hextoNum(amount_transFee);
                    list.add(new Datos("Bit 28 ", "Importe, tasa de transacción", amount_transFeeNum));
                    iterador += 8;
                    break;
                case 29:
                    String amount_settFee = trama.substring(iterador, iterador + 8);
                    String amount_settFeeNum = hextoNum(amount_settFee);
                    list.add(new Datos("Bit 29 ", "Importe. tasa de liquidación", amount_settFeeNum));
                    iterador += 8;
                    break;
                case 30:
                    String amount_transProcFee = trama.substring(iterador, iterador + 8);
                    String amount_transProcFeeNum = hextoNum(amount_transProcFee);
                    list.add(new Datos("Bit 30 ", "Importe, tasa de procesamiento de la transacción", amount_transProcFeeNum));
                    iterador += 8;
                    break;
                case 31:
                    String amount_settProcFee = trama.substring(iterador, iterador + 8);
                    String amount_settProcFeeNum = hextoNum(amount_settProcFee);
                    list.add(new Datos("Bit 31 ", "Importe, tasa de tramitación de la liquidación", amount_settProcFeeNum));
                    iterador += 8;
                    break;
                case 32:
                    String acquInstIdentCode = trama.substring(iterador, iterador + 11);
                    String acquInstIdentCodeNum = hextoNum(acquInstIdentCode);
                    list.add(new Datos("Bit 32 ", "Código de identificación de la entidad adquirente", acquInstIdentCodeNum));
                    iterador += 11;
                    break;
                case 33:
                    String forwInstIdenCode = trama.substring(iterador, iterador + 11);
                    String forwInstIdenCodeNum = hextoNum(forwInstIdenCode);
                    list.add(new Datos("Bit 33 ", "Código de identificación de la institución remitente", forwInstIdenCodeNum));
                    iterador += 11;
                    break;
                case 34:
                    String primAccNum_extend = trama.substring(iterador, iterador + 28);
                    String primAccNum_extendNum = hextoNum(primAccNum_extend);
                    list.add(new Datos("Bit 34 ", "Número de cuenta principal, ampliado", primAccNum_extendNum));
                    iterador += 28;
                    break;
                case 35:
                    String track2Data = trama.substring(iterador, iterador + 37);
                    list.add(new Datos("Bit 35 ", "Datos de la vía 2", track2Data));
                    iterador += 37;
                    break;
                case 36:
                    String track3Data = trama.substring(iterador, iterador + 104);
                    list.add(new Datos("Bit 36 ", "Datos de la vía 3", track3Data));
                    iterador += 104;
                    break;
                case 37:
                    String retriRefNum = trama.substring(iterador, iterador + 12);
                    String retriRefNumAn = hexToAscci(retriRefNum);
                    list.add(new Datos("Bit 37 ", "Número de referencia de la recuperación", retriRefNumAn));
                    iterador += 12;
                    break;
                case 38:
                    String authIdenResp = trama.substring(iterador, iterador + 6);
                    String authIdenRespAn = hexToAscci(authIdenResp);
                    list.add(new Datos("Bit 38 ", "Respuesta de identificación de la autorización", authIdenRespAn));
                    iterador += 6;
                    break;
                case 39:
                    String resCode = trama.substring(iterador, iterador + 4);
                    String resCodeAn = hexToAscci(resCode);
                    list.add(new Datos("Bit 39 ", "Código de respuesta", resCodeAn));
                    iterador += 4;
                    break;
                case 40:
                    String serResCode = trama.substring(iterador, iterador + 3);
                    String serResCodeAn = hexToAscci(serResCode);
                    list.add(new Datos("Bit 40 ", "Código de restricción del servicio", serResCodeAn));
                    iterador += 3;
                    break;
                case 41:
                    String cardAccTerIden = trama.substring(iterador, iterador + 16);
                    String cardAccTerIdenAns = hexToAscci(cardAccTerIden);
                    list.add(new Datos("Bit 41 ", "Identificación del terminal de aceptación de tarjetas", cardAccTerIdenAns));
                    iterador += 16;
                    break;
                case 42:
                    String cardAccIdenCode = trama.substring(iterador, iterador + 15);
                    String cardAccIdenCodeAns = hexToAscci(cardAccIdenCode);
                    list.add(new Datos("Bit 42 ", "Código de identificación del aceptador de tarjetas", cardAccIdenCodeAns));
                    iterador += 15;
                    break;
                case 43:
                    String cardAcceNameLocat = trama.substring(iterador, iterador + 40);
                    String cardAcceNameLocatAns = hexToAscci(cardAcceNameLocat);
                    list.add(new Datos("Bit 43 ", "Nombre/ubicación del aceptador de tarjetas", cardAcceNameLocatAns));
                    iterador += 40;
                    break;
                case 44:
                    String addiResData = trama.substring(iterador, iterador + 25);
                    String addiResDataAn = hexToAscci(addiResData);
                    list.add(new Datos("Bit 44 ", "Código de restricción del servicio", addiResDataAn));
                    iterador += 25;
                    break;
                case 45:
                    String track1Data = trama.substring(iterador, iterador + 76);
                    String track1DataAn = hexToAscci(track1Data);
                    list.add(new Datos("Bit 45 ", "Datos de la pista 1", track1DataAn));
                    iterador += 76;
                    break;
                case 46:
                    String addicDataISO = trama.substring(iterador, iterador + 106);
                    String addicDataISOAn = hexToAscci(addicDataISO);
                    list.add(new Datos("Bit 46 ", "Datos adicionales - ISO", addicDataISOAn));
                    iterador += 106;
                    break;
                case 47:
                    String addicDataNat = trama.substring(iterador, iterador + 106);
                    String addicDataNatAn = hexToAscci(addicDataNat);
                    list.add(new Datos("Bit 47 ", "Datos adicionales - Nacionales", addicDataNatAn));
                    iterador += 106;
                    break;
                case 48:
                    String addicDataPrivate = trama.substring(iterador, iterador + 106);
                    String addicDataPrivateAn = hexToAscci(addicDataPrivate);
                    list.add(new Datos("Bit 48 ", "Datos adicionales - Privados", addicDataPrivateAn));
                    iterador += 106;
                    break;
                case 49:
                    String curreCode_trans = trama.substring(iterador, iterador + 3);
                    String curreCode_transA = hexToAscci(curreCode_trans);
                    list.add(new Datos("Bit 49 ", "Código de moneda, transacción", curreCode_transA));
                    iterador += 3;
                    break;
                case 50:
                    String curreCode_sett = trama.substring(iterador, iterador + 3);
                    String curreCode_settAn = hexToAscci(curreCode_sett);
                    list.add(new Datos("Bit 50 ", "Código de moneda, liquidación", curreCode_settAn));
                    iterador += 3;
                    break;
                case 51:
                    String curreCode_cardhBill = trama.substring(iterador, iterador + 3);
                    String curreCode_cardhBillA = hexToAscci(curreCode_cardhBill);
                    list.add(new Datos("Bit 51 ", "Código de moneda, facturación del titular de la tarjeta", curreCode_cardhBillA));
                    iterador += 3;
                    break;
                case 52:
                    String perIdentNumData = trama.substring(iterador, iterador + 16);
                    String perIdentNumDataBin = hexToBinary(perIdentNumData);
                    list.add(new Datos("Bit 52 ", "Datos del número de identificación personal", perIdentNumDataBin));
                    iterador += 16;
                    break;
                case 53:
                    String secuRelaControlInf = trama.substring(iterador, iterador + 18);
                    String secuRelaControlInfNum = hextoNum(secuRelaControlInf);
                    list.add(new Datos("Bit 53 ", "Información de control relacionada con la seguridad", secuRelaControlInfNum));
                    iterador += 18;
                    break;
                case 54:
                    String additAmounts = trama.substring(iterador, iterador + 128);
                    String additAmountsAn = hexToAscci(additAmounts);
                    list.add(new Datos("Bit 50 ", "Importes adicionales", additAmountsAn));
                    iterador += 128;
                    break;
                case 55:
                    String ReservedISO = trama.substring(iterador, iterador + 106);
                    String ReservedISOAns = hexToAscci(ReservedISO);
                    list.add(new Datos("Bit 55 ", "ISO reservado", ReservedISOAns));
                    iterador += 106;
                    break;
                case 56:
                    String reservedISO = trama.substring(iterador, iterador + 106);
                    String reservedISOAns = hexToAscci(reservedISO);
                    list.add(new Datos("Bit 56 ", "ISO reservado", reservedISOAns));
                    iterador += 106;
                    break;
                case 57:
                    String ReservedNational = trama.substring(iterador, iterador + 106);
                    String ReservedNationalAns = hexToAscci(ReservedNational);
                    list.add(new Datos("Bit 57 ", "Reservado Nacional", ReservedNationalAns));
                    iterador += 106;
                    break;
                case 58:
                    String reservedNational = trama.substring(iterador, iterador + 106);
                    String reservedNationalAns = hexToAscci(reservedNational);
                    list.add(new Datos("Bit 58 ", "Reservado Nacional", reservedNationalAns));
                    iterador += 106;
                    break;
                case 59:
                    String ReservForNationalUse = trama.substring(iterador, iterador + 106);
                    String ReservForNationalUseAns = hexToAscci(ReservForNationalUse);
                    list.add(new Datos("Bit 59 ", "Reservado para uso nacional", ReservForNationalUseAns));
                    iterador += 106;
                    break;
                case 60:
                    String advReasonCode = trama.substring(iterador, iterador + 92);
                    String advReasonCodeAn = hexToAscci(advReasonCode);
                    list.add(new Datos("Bit 60 ", "Código de consejo/razón (privado reservado)", advReasonCodeAn));
                    iterador += 92;
                    break;
                case 61:
                    String ReservedPrivate = trama.substring(iterador, iterador + 106);
                    String ReservedPrivateAns = hexToAscci(ReservedPrivate);
                    list.add(new Datos("Bit 61 ", "Reservado Privado", ReservedPrivateAns));
                    iterador += 106;
                    break;
                case 62:
                    String reservedPrivate = trama.substring(iterador, iterador + 106);
                    String reservedPrivateAns = hexToAscci(reservedPrivate);
                    list.add(new Datos("Bit 62 ", "Reservado Privado", reservedPrivateAns));
                    iterador += 106;
                    break;
                case 63:
                    String reserved_private = trama.substring(iterador, iterador + 106);
                    String reserved_privateAns = hexToAscci(reserved_private);
                    list.add(new Datos("Bit 63 ", "Reservado Privado", reserved_privateAns));
                    iterador += 106;
                    break;
                case 64:
                    String MAC = trama.substring(iterador, iterador + 16);
                    list.add(new Datos("Bit 64 ", "Código de autenticación de mensajes (MAC)", MAC));
                    iterador += 16;
                    break;
            }
        }
    }
    public String hextoNum(String hex) {
        Long hex2 = Long.parseLong(hex, 16);
        String s = hex2.toString();
        return s;

    }
    private String hexToAscci(String hexStr) {
        StringBuilder output = new StringBuilder("");
        for (int i = 0; i < hexStr.length() - 1; i += 2) {
            String str = hexStr.substring(i, i + 2);
            output.append((char) Integer.parseInt(str, 16));
        }
        return output.toString();
    }
}
