#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

char* limiteFrase(char* fraseCompleta);
void palindromo(char* palabra);
int myStrlenSofi(char* cadena);
int myStrcmp(char* primeraCadena, char* segundaCadena);
int contarConsonantes(char *cadena);
int contarVocales(char *cadena);
int esVocal(char letra);
void espaciosEnBlanco(char* frase);
void vocalMasUtilizada(char *cadena);

void main(){
	
	char fraseCompleta[50], palabra[50], caracter;
	int contador = 0, contadorPalabra = 0;
	char matrizPalabras[20][50];
	int contadorH=0, contadorV=0;
	memset(palabra,'\0',sizeof(palabra)); //copia los fin de linea en todos los espacios reservador de la memorio a palabra
	
	printf("\t\tBienvenido\n\t\t-----------\n\nIngrese una frase:");
	
	limiteFrase(fraseCompleta);
	printf("\n");
	
	//palabra palindromo
	while(fraseCompleta[contador] !='\0'){
		
		if(fraseCompleta[contador] != ' '){
			palabra[contadorPalabra] = fraseCompleta[contador];
			contadorPalabra++;
			palabra[contadorPalabra]='\0';
		}else {
			palindromo(palabra);
			contadorPalabra = 0;
			memset(palabra,'\0',sizeof(palabra));
		}
		contador++;
		
		// Necesito validar si ya acabo la cadena, para enviar la ultima palabra
		if(fraseCompleta[contador] =='\0'){
			palindromo(palabra);
		}
	}
	
	contador=0;
	
	//separar palabras
	while(fraseCompleta[contador] !='\0'){

		if(fraseCompleta[contador] != ' '){
			matrizPalabras[contadorH][contadorV]=fraseCompleta[contador];
			contadorV++;
			matrizPalabras[contadorH][contadorV]='\0';
		}else{
			contadorH++;
			contadorV=0;
		}
		contador++;
	}
	
	contador=0;
	contadorV=0;
	
	//palabras iguales
	while(contador<=contadorH){
		
		contadorV=contador+1;
		
		while(contadorV<=contadorH){
			
			if(myStrcmp(matrizPalabras[contador], matrizPalabras[contadorV])==0){
				printf("\nLa palabra %s es igual a %s", matrizPalabras[contador], matrizPalabras[contadorV]);
			}
			contadorV++;
		}
		contador++;
	}
	//cantidad de palabras
	printf("\nHay %d palabras en la frase", contadorH+1);
	
	//cantidad de consonantes y de vocales
	int consonantes = contarConsonantes(fraseCompleta);
	int vocales=contarVocales(fraseCompleta);
	
    printf("\nLa cadena tiene %d consonantes", consonantes);
    printf("\nLa cadena tiene %d vocales",vocales);
    
    //cantidad de espacios en blanco
   espaciosEnBlanco(fraseCompleta);
   
   //vocal mas usada 
   
   vocalMasUtilizada(fraseCompleta);	
}

char* limiteFrase(char* fraseCompleta){
	
	int contador = 0;
	char caracter;

	while(1){

		caracter = getch();
		
		if(caracter == '\r'){
			break;
		}else if( caracter == '\b' ){
		
		if( contador > 0 ){
			putchar('\b');
			putchar(' ');
			putchar('\b');
			contador--;
			fraseCompleta[contador] = '\0';
		}
		
		}else{
			if(contador<49){
				putchar(caracter);
				fraseCompleta[contador] = caracter;
				contador++;
				fraseCompleta[contador] = '\0';
			}
		}
	}
	
	return fraseCompleta;
}

void palindromo(char* palabra){
	
	char comparar[50]; //aca se guarda la palabra al reves
	memset(comparar,'\0',sizeof(comparar));
	int cantidadCaracteres = myStrlenSofi(palabra);
	cantidadCaracteres--;
	int contadorInicial;
	
	
	for(contadorInicial = 0; cantidadCaracteres >= 0; contadorInicial++){
		comparar[contadorInicial]= palabra[cantidadCaracteres];
		cantidadCaracteres--;
	}
	comparar[contadorInicial]='\0';
	contadorInicial = 0;
	
	while(palabra[contadorInicial] != '\0'){
		if(palabra[contadorInicial]!= comparar[contadorInicial]){
			return;
		}else{
			contadorInicial++;
		}
	}
	
	printf("\nPalindromo en la oracion: %s ",palabra); // Si llego aca, significa que son iguales, entonces muestro la cadena
}

int myStrlenSofi(char* cadena){

	int contador=0;
	
	while (cadena[contador] != '\0'){
		contador++;
		
		if (cadena[contador] == '\0') {
			break;
		}else {
			contador++;
		}
	}
	return contador;
}
int myStrcmp(char* primeraCadena, char* segundaCadena){
		
	int contadorUno = 0;
		
	while( primeraCadena[contadorUno] != '\0' ){
			
		if(primeraCadena[contadorUno] < segundaCadena[contadorUno]){
				return -1;
		}else if(primeraCadena[contadorUno] > segundaCadena[contadorUno]){
				return 1;
		}
			contadorUno++;
		}
		
	return 0;
}

int esVocal(char letra){
    // Convertir a mayúscula para evitar hacer más comparaciones
    char letraEnMinucula = (char) tolower(letra);
    
    return letraEnMinucula == 'a' ||
           letraEnMinucula == 'e' ||
           letraEnMinucula == 'i' ||
           letraEnMinucula == 'o' ||
           letraEnMinucula == 'u';
}
int contarVocales(char *cadena){
	
	int vocales = 0;
	int indice;
	
	// Recorrer toda la cadena
	for (indice= 0; cadena[indice] != '\0'; ++indice){

		// Obtener el char de la posición en donde está el índice
		// y por otro lado convertirla a minúscula

		char letraActual = tolower(cadena[indice]);
		
		if (letraActual == 'a' || letraActual == 'e' || letraActual == 'i' || 	letraActual == 'o' || letraActual == 'u'){
			vocales++;
		}
	}
	return vocales;
}

int contarConsonantes(char cadena[]) {
	
    int consonantes = 0;// Almacenar la cantidad de consonantes
    int i = 0;// El índice para recorrer la cadena
    
    while (cadena[i]) {
        // Si es del alfabeto pero no es vocal
        if (isalpha(cadena[i]) && !esVocal(cadena[i])) {
            consonantes++;
        }
        i++;
    }
    return consonantes;
}

void espaciosEnBlanco(char* frase){

	int contador=0, espacios=0;
	
 	for(contador; frase[contador] != '\0'; contador++){
		if( frase[contador]== ' '){
			espacios++;
		}
	} 
	printf("\nLos espacios de la frase son: %d", espacios);
}

void vocalMasUtilizada(char *cadena){
	
	int contador=0;
	int a=0, e=0, i=0, o=0, u=0;
	
	
	for (contador; cadena[contador]!= '\0'; contador++){
		
	esVocal(cadena[contador]);
		
			if(cadena[contador]=='a'){
				a++;
			} else if(cadena[contador]=='e'){
				e++;
			}else if(cadena[contador]=='i'){
				i++;
			}else if(cadena[contador]=='o'){
				o++;
			}else if(cadena[contador]=='u'){
				u++;
			}
		}
		
	if(a>e && a>i && a>o && a>u){
		printf("\nLa vocal mas usada es la a.");
	}else if(e>a && e>i && e>o && e>u){
		printf("\nLa vocal mas usada es la e.");
	}else if(i>a && i>e && i>o && i>u){
		printf("\nLa vocal mas usada es la i.");
	}else if(o>a && o>e && o>i && o>u){
		printf("\nLa vocal mas usada es la o.");
	}else if(u>a && u>e && u>i && u>o){
		printf("\nLa vocal mas usada es la u.");
	}
}
