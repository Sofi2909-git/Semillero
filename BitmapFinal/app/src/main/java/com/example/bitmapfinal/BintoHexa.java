package com.example.bitmapfinal;

public class BintoHexa {

    public static String binarioHexadecimal(String bitStream) {
        int byteLength = 4;
        int bitStartPos = 0, bitPos = 0;
        String hexString = "";
        int sum = 0;

        if (bitStream.length() % 4 != 0) {
            int tempCnt = 0;
            int tempBit = bitStream.length() % 4;
            while (tempCnt < (byteLength - tempBit)) {
                bitStream = "0" + bitStream;
                tempCnt++;
            }
        }
        while (bitStartPos < bitStream.length()) {
            while (bitPos < byteLength) {
                sum = (int) (sum + Integer.parseInt("" + bitStream.charAt(bitStream.length() - bitStartPos - 1)) * Math.pow(2, bitPos));
                bitPos++;
                bitStartPos++;
            }
            if (sum < 10)
                hexString = Integer.toString(sum) + hexString;
            else
                hexString = (char) (sum + 55) + hexString;

            bitPos = 0;
            sum = 0;
        }
        return (hexString);
    }

    }
