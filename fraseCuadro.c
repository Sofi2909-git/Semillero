#include<stdio.h>
#include<string.h>
//menu
int main(){
	
	//datos
	char fraseIngresada[50]; // cantidad de espacios para agregar frase en consola 
	int vi;/*representa la parte vertical izquierda de la frase ingresada */
	int vd;/* representa la parte vertical derecha de la frsea ingresada*/
	int longitudH; /*representa la longitud o el largo de la frase ingresada */
	int espacio; /*representa los espacios que tengo que dejar en medio del cuadro */
	
	//texto en pantalla
	printf("Ingrese una frase: ");
	gets(fraseIngresada); //gets me lee o guarda la frase ingresada pero no la muestra en pantalla. Tiene la misma funcion de scanf pero gets guarda espacios
	
	//valor de datos 
	longitudH=strlen(fraseIngresada); // La función strlen me va a calcular y guardar la cantidad de caracteres que ingresamos en la frase 
	vd=longitudH-2; // es decir que vd vale lo que vale longitud menos 2
	vi=1; // la vertical izquierda va de uno en uno
	
	//frase en la parte superior del cuadro
	printf("\n%s",fraseIngresada); // voy a imprimir en la pantalla la frase ingresada en el teclado
		
		// empiezo el bucle
	while(vi<longitudH-1 && vd>=1){ // vi se ejecuta mientras sea menor a longitud-1 y (&&) vd se ejecuta mientras sea mayor o igual a 1
		printf("\n%c",fraseIngresada[vi]); // se va a imprimir en pantalla caracter a caracter la frase ingresada en la posicion de vi que es la posicion 1
		
		espacio=1;
		//IMPRIME LOS ESPACIOS
	for(espacio=0; espacio<longitudH-2;espacio++){ // espacio es la mitad hueca del cuadro. inicia en la posicion 0 y se cumple cuando es menor a longitud-2 
			printf(" "); //cuando se cumple esta condicion en pantalla se dibuja un espacio
		}
		printf("%c",fraseIngresada[vd]);// se va leyendo caracter a caracter lo ingresado en la  frase pero en la posicion vd  
		vi++; //va aumentando y dibujando caracter a caracter 
		vd--; // va a empezar en la posicion de longitud-2 y va a ir disminuyendo y ointando en pantalla 
	}
    printf("\n"); 
	//IMPRIME LA FRASE AL REVES EN LA PARTE DE ABAJO
	for(vi=longitudH-1;vi>=0;vi--){ //inicio en la posicion longitud-1 y la condicion es que vi sea mayor o igual a 0 y vi va en decremento
	printf("%c",fraseIngresada[vi]); // pido que se muestre caracter a caracter lo que estoy pidiendo en vi 
	}
	
	return 0;
}
