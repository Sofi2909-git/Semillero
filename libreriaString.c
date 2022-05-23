#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myStrlenSofi (char* cadenaNombre);
char* myStrcatSofi(char* cadenaNombre, char* cadenaApellido);
char* myStrcpySofi (char* nombrePersona, char* apellidoPersona);
char* myStrncatSofi (char* cadenaUno, char* cadenaDos, int cantidadLetras);
int myStrcmp (char* primeraCadena, char* segundaCadena);
int myStrncmp (char* cadenaUno, char* cadenaDos, int contadorCaracteres);
int h=0;
void main(){
 	
 	char nombre[20];
 	char apellido[20];
 
 	printf ("Ingrese su nombre: ");
 	scanf("%s", nombre); 
 	fflush(stdin);//realiza la limpieza del buffer de entrada
 	
 	printf ("\nIngrese su apellido: ");
 	scanf("%s", apellido); 
 	fflush(stdin);
 	
 	printf ("\nSu nombre completo es: %s", myStrcatSofi (nombre, apellido));
 	
 	printf ("\nla cantidad de letras de su nombre:  %d", myStrlenSofi(nombre));
 	
 	printf ("\nla cantidad de letras de su apellido:  %d", myStrlenSofi(apellido));
 	
 	printf ("\nCadena de caracteres copiados: %s",myStrncatSofi(nombre, apellido,3) );
 	
 	printf ("\nValor de comparacion de cadenas caracter a caracter: %d", myStrcmp (nombre,apellido));
 	
 	printf ("\nValor de comparacion de cadenas con 3 caracteres: %d", myStrncmp(nombre, apellido, 3) );
 	
 	printf ("\nCadena copiada: %s", myStrcpySofi(nombre,apellido) ); 
 	
 	}

// para hacer el codigo que reemplazo la funcion strlen hice lo siegiente

	int myStrlenSofi (char* cadenaNombre) { // pedi un entero con nombre myStrlenSofi luego dije que ese dato recibiria caracteres indefinidos y los llame cadenaNombre
	 	 
	 	int nombre; // luego hice el cuerpo de la funcion, donde dije que un entero llamado int
	 	int contadorNombre=0; // y un entero llamado contadorNombre inicializado en la posicion 0
	 	
	 	while (cadenaNombre[contadorNombre] != '\0'){ // entrarian a un ciclo para cumplir una condicion que dice que mientras cadenaNombre en la posicion 0 sea diferente al cierre de cadena  
			contadorNombre++; // entonces contadorNombre aumentara una posicion cada que se repita el ciclo
			
	 		if (cadenaNombre[contadorNombre] == '\0') { // pero si cadenaNombre llega a el cierre de cadena se rompa el ciclo 
	 			break;
			 }
			 else {
			 	contadorNombre++; // sino contador sigue aumentando en 1
			 }
		}
	
	    return contadorNombre; // y quiero que esta funcion me devuelva lo que hay en contadorNombre una vez se cumpla su ciclo
	}
	
	
 // une dos cadenas 
	char* myStrcatSofi(char* cadenaNombre, char* cadenaApellido) {
	
		char* cadenaCompleta;
		int contadorUno; // Va a servir para las variables nombre y apellido
		int contadorDos = 0; // Va a servir para la variable que se va a retornar
		
		for( contadorUno = 0; cadenaNombre[contadorUno] != '\0'; contadorUno++ ){
			cadenaCompleta[contadorDos] = cadenaNombre[contadorUno];
			contadorDos++;
		}
			for( contadorUno = 0; cadenaApellido[contadorUno] != '\0'; contadorUno++ ){
			cadenaCompleta[contadorDos] = cadenaApellido[contadorUno];
			contadorDos++;
		}
		
		return cadenaCompleta;
	}
	
	// COPIA UNA CADENA EN OTRA
	
	char* myStrcpySofi (char* nombrePersona, char* apellidoPersona){
			
			int contador=0;
			
			while (apellidoPersona[contador] != '\0'){
			nombrePersona[contador] = apellidoPersona[contador];
				contador++;
				
			} 
			nombrePersona[contador] = '\0';
			
			return nombrePersona;
			
	}
	
	// UNE DETERMINADO NUMERO DE CARACTERES DE UNA CADENA A OTRA 
	
	char* myStrncatSofi (char* cadenaUno, char* cadenaDos, int cantidadLetras){
			
		int contadorUno; //Va a servir para las variable nombre
		int contadorDos; // Va a servir para las variable apellido
		int contadorResultado = 0; // Va a servir para la variable que se va a retornar
		
		contadorResultado = myStrlenSofi(cadenaUno);
		
			for( contadorUno = 0; contadorUno<cantidadLetras ; contadorUno++ ){ // Sofi Galvis 3 = SofiGal
				cadenaUno[contadorResultado] = cadenaDos[contadorUno];
				contadorResultado++; 
		}
			
			return cadenaUno;
	}
		
	// NOTA: No estoy validando o comparando la longitud de la cadena, estoy validando es la posicion de las letras en el codigo ascii
	
	//compara dos cadenas
	
	int myStrcmp (char* primeraCadena, char* segundaCadena){
		
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
	
//	compara un numero de caracteres de ambas cadena
	
	int myStrncmp (char* cadenaUno, char* cadenaDos, int contadorCaracteres){
		
	int contadorUno = 0;
	int contador=0;
		
		
		for( contadorUno=0; contadorUno < contadorCaracteres; contadorUno++ ){
			
			if(cadenaUno[contadorUno] < cadenaDos[contadorUno]){
				contador= -1;
				break;
			}else if(cadenaUno[contadorUno] > cadenaDos[contadorUno]){
				contador= 1;
				break;
			}
		}
		
		return contador;
		
	}
