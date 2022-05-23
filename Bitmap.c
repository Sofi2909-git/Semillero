#include <stdio.h> // INCLUIR LA BIBLIOTECA STUDIO.H

int main(){ // MAIN ES UNA FUNCION PRINCIPAL, EL PROGRAMA EMPIEZA A EJECUTARSE
	
	// Variables para el campo hexadecimal 2
	char hexadecimal[17];
	int contador = 0;
	char caracter; 
	
	printf("Ingrese un numero hexadecimal : ");  //TEXTO EN PANTALLA 
	
	while(1){ //para permitir la ejecución sin límite del contenido del ciclo
	
	
		
		caracter = getch(); /*nos permite guardar una letra en una variable pero no muestra la letra en pantalla
							tiene otra función llamada getche, que hace lo mismo solo que esta última 
							muestra la letra en pantalla*/
							
	//codigo para borrar 
	
	if( caracter == '\r' ){   // Si caracter es igual a enter, es decir que la persona presione enter, entonces caracter no me va a guardar mas caracteres en la variable getch
			break;
		}
		else if( caracter == '\b' ){					// Si presionamos retroceso o borrar, entonces....
			
			if (contador > 0) {						// Validamos que haya algo en consola, es decir nos aseguramos que la persona escribio algo y necesita borrar
				contador--;							// Se cumple la condicion de borrar o retroceder un caracter en contador
				putchar('\b');						// La funcion de putchar es la de tomar caracteres guardados en getch y mostrarlos en pantalla. 
													// Retrocedemos un espacio del cursor en la consola eso es lo que hace. 
				putchar(' ');						// Borramos lo que este en consola
				putchar('\b');						// nos volvemos a retroceder en la consola
				hexadecimal[contador] = '\0';	// Borramos de la variable el caracter que se borro en consola (Contador ya vale uno menos)
			}		
	} else if( contador <= 15 ){				// Valido que no se haya llegado al limite 
			hexadecimal[contador] = caracter;	// Guardamos en la posicion actual el CARACTER que ingresa el usuario
			hexadecimal[contador + 1] = '\0';	// Cerramos la cadena para evitar que se guarde basura en la variable
			putchar(caracter);						// Muestro en consola el caracter que se ingreso
			contador++;	
			}							// Aumento el contador
		}
	
	int contadorCadenaCaracteres, contadorCasillasBinarias = 0;
	int validacion[64];
    
    // for funciona asi: for(inicialización;condición;incremento){ 
    // instruciones}
    for( contadorCadenaCaracteres = 0; contadorCadenaCaracteres < 64; contadorCadenaCaracteres++ ){ // lo que estoy diciendo aca es que el entero contador de caracteres lo inicio en 0
    																								// la condicion es que contador cadena de caracteres sea menos a 64 y va en incremento de 1
		validacion[contadorCadenaCaracteres] = 0; //valido que inicie en 0 para evitar errores
	}
	
	// for va a inicializar en 0,la condicion es que contador cadena de caracteres se ejecute si es diferente al cierre la cadena y el contador va en incremento
	 for(contadorCadenaCaracteres = 0; hexadecimal[contadorCadenaCaracteres] != '\0'; contadorCadenaCaracteres++){
    	
    // lo sigueintes if o condiciones son de los numeros binarios de acuerdo a su lenguaje binario se colocan 
    
    /*por ejmplo en el primero lo que estoy diciendo es que si el exadecimal conntadorCdenaCaracteres es igual a 1 osea la persona coloca un 1 en teclado entonces
    validamos que inicie en 0 y el entero contadorCasillas binarias que esta en la posicion 0 es igual 
	al primer numero del codigo binario en este caso 0 y va aumentando en 1 colocando un nuevo numero del coigo binario en la siguiente posicion 
	al terminar de ubicar los cuatro binarios, contador va a valer o, asi que si alguien coloca otro digito lo vamos a ubicar en la posicion 4 desde el primer binario 
	de la posicion anterior para eso es el +=4*/
	
    	if( hexadecimal[contadorCadenaCaracteres] == '1' ){
    		validacion[contadorCasillasBinarias] = 0;
    		validacion[contadorCasillasBinarias + 1] = 0;
    		validacion[contadorCasillasBinarias + 2] = 0;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == '2' ){
    		validacion[contadorCasillasBinarias] = 0;
    		validacion[contadorCasillasBinarias + 1] = 0;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 0;
    		contadorCasillasBinarias += 4;
    	} else if( hexadecimal[contadorCadenaCaracteres] == '3' ){
    		validacion[contadorCasillasBinarias] = 0;
    		validacion[contadorCasillasBinarias + 1] = 0;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == '4' ){
    		validacion[contadorCasillasBinarias] = 0;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 0;
    		validacion[contadorCasillasBinarias + 3] = 0;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == '5' ){
    		validacion[contadorCasillasBinarias] = 0;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 0;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4; 
    	} else if( hexadecimal[contadorCadenaCaracteres] == '6' ){
    		validacion[contadorCasillasBinarias] = 0;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 0;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == '7' ){
    		validacion[contadorCasillasBinarias] = 0;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == '8' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 0;
    		validacion[contadorCasillasBinarias + 2] = 0;
    		validacion[contadorCasillasBinarias + 3] = 0; 
    		contadorCasillasBinarias += 4;
    	} else if( hexadecimal[contadorCadenaCaracteres] == '9' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 0;
    		validacion[contadorCasillasBinarias + 2] = 0;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == 'A' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 0;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 0;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == 'B' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 0;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4;
    	} else if( hexadecimal[contadorCadenaCaracteres] == 'C' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 0;
    		validacion[contadorCasillasBinarias + 3] = 0;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == 'D' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 0;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4;
		} else if( hexadecimal[contadorCadenaCaracteres] == 'E' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 0;
    		contadorCasillasBinarias += 4;
    	} else if( hexadecimal[contadorCadenaCaracteres] == 'F' ){
    		validacion[contadorCasillasBinarias] = 1;
    		validacion[contadorCasillasBinarias + 1] = 1;
    		validacion[contadorCasillasBinarias + 2] = 1;
    		validacion[contadorCasillasBinarias + 3] = 1;
    		contadorCasillasBinarias += 4;
    }
}
	
	printf("\n"); // se coloca para que al momento de formarse las columnas haya un espacio entre el mensaje inicial y las columnas y no se vea desorden 

	for( contador = 0; contador < 16; contador++ ){ /* la condicion que establezco aca es contador va a inicia en 0; se cumple la condicion si contador es menor a 16
													menor a 16 porque las columnas estan formadas por 16 filas; y contador ira aumentando de 1 en 1*/
		
		/* respecto a las columnas aca se ejecuta de la siguiente manera el programa: voy a pintar en consola un salto de linea y una tabulacion
		esto para llevar un orden y que se alinien las columnas. luego se ejecuta una condicion que dice que si validacion que tiene un valor de 64 espacios
		se inicia en cobtador, desde la posicion 0 y el numero que haya en la posicion es un 1, de acuerdo al codigo binario que represente la letra o numero
		colocado por la persona en el teclado entonces se va a marcar un - mas un espacio; Sino es asi y lo que marca el numero binario es 0, entonces va a 
		hacerse dos espacion, esto para el orden. una vez se cumpla esta condicion, prinft pintara en pantalla la palbra bit 0 y el numero que corresponda del 1-64*/ 

		// PRIMERA COLUMNA
		
		printf("\n\t"); 
		
		if( validacion[contador] == 1 ){
			printf("- ");
		}else{
			printf("  ");
		}
		
		printf("Bit 0%i", contador + 1); // algo importante es que contador esta en la posicion o para que a la persona le aparezca o se pinte e la consola desde el 1 tenemos que colocar contador mas 1
		
		// SEGUNDA COLUMNA
		
		printf("\t\t");
		
		if( validacion[contador + 16] == 1 ){  //y se coloca un numero menos que el que pinta la pantalla porque la posicion de contador inicia en 0 y no en 1
			printf("- ");
		}else{
			printf("  ");
		}
		
		printf("Bit 0%i", contador + 17);
		
		// TERCERA COLUMNA
		
		printf("\t\t");
		
		if( validacion[contador + 32] == 1 ){
			printf("- ");
		}else{
			printf("  ");
		}
		
		printf("Bit 0%i", contador + 33);
		
		// CUARTA COLUMNA
		
		printf("\t\t");
		
		if( validacion[contador + 48] == 1 ){
			printf("- ");
		}else{
			printf("  ");
		}
		
		printf("Bit 0%i", contador + 49);
			
	}

}

