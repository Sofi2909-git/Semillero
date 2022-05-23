#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
 
struct LIBRO{ 
	
	char nombreLibro[50];
	long precioLibro;
	
}ventas[6];

struct COMPRAS{
	
	char nombreLibro[50];
	long totalPrecio;
	int cantidadLibros;
	
}comprasCaseta1[30], comprasCaseta2[30],comprasCaseta3[30];

struct TOTALPRECIO{
	
	char nombreLibro[50];
	long totalPrecio;
	
}compras[30];

void llenarCasetas();
void filtroPorCaseta(int casetaUno, int casetaDos, int casetaTres);
int cantidadObraVendida(char* obra);
void filtroPorLibro(int obra1, int obra2, int obra3,int obra4,int obra5,int obra6);


void main (){
	
	llenarCasetas(); //llamo la funcion
	
	int opcionLibro, cantidadLibro, casetas; //casetas me guarda lel numero de la caseta que selecciono la persona; opcion libro me guarda el numero del titulo que escogio las persona; cantidad libro guarda cuantos libros compraron
	int casetaUno=0, casetaDos=0, casetaTres=0;
	int contador; //ayuda a recorrer el for de opciones de libros
	int contadorCompras1=0,contadorCompras2=0, contadorCompras3=0; //estos contadores son los que guardan la posision de la cadena copiada de ventas 
	int contadorPrecio; // me ayuda a fijar el precio total
	int filtros;
	int obra1,obra2,obra3,obra4,obra5,obra6;
	
	while(1){
		
		printf("\t\tBienvenido a la feria de libros\n\t\t------------------------------");
		
		while(1){
			// muestro las casetas disponibles para comprar
			printf("\n\nCaseta de ventas\n---------------");
			printf("\nCaseta 1");
			printf("\nCaseta 2");
			printf("\nCaseta 3");
			printf("\nSeleccione la caseta donde va a comprar la obra: ");
			scanf("%i", &casetas);
			
			if(casetas<1 || casetas>3){
				printf("\nSeleccione una caseta correcta");
			} else{
				break; 
			}
		}
		 system("cls");	
		 printf("\nCaseta %d\n", casetas);
		 
		//	MUESTRA LA OPCION DE LIBROS QUE HAY 
		for(contador = 0; contador < 6; contador++ ){ //i=numero del libro; .= por diseño; s=nombre del libro; $= por diseño; i=precios;
			printf("%i.%s\t $ %i\n", contador + 1, ventas[contador].nombreLibro, ventas[contador].precioLibro);
		}
		while(1){
			
			printf("\nSeleccione el libro que desea comprar: ");
			scanf("%i",&opcionLibro);
			
			if(opcionLibro>=1 && opcionLibro<=6){
				printf("\nCuantos libros desea de %s? ", ventas[opcionLibro - 1].nombreLibro);
				scanf("%i", &cantidadLibro);
				
				if(casetas==1){
					// strcpy copia una cadena en otra
					strcpy(comprasCaseta1[contadorCompras1].nombreLibro, ventas[opcionLibro - 1].nombreLibro);
					comprasCaseta1[contadorCompras1].cantidadLibros = cantidadLibro;
					comprasCaseta1[contadorCompras1].totalPrecio = cantidadLibro*ventas[opcionLibro - 1].precioLibro;
					contadorCompras1++;
					casetaUno+= cantidadLibro;
					
				} else if(casetas==2){
					strcpy(comprasCaseta2[contadorCompras2].nombreLibro, ventas[opcionLibro - 1].nombreLibro);
					comprasCaseta2[contadorCompras2].cantidadLibros = cantidadLibro;
					comprasCaseta2[contadorCompras2].totalPrecio = cantidadLibro*ventas[opcionLibro - 1].precioLibro;
					contadorCompras2++;
					casetaDos += cantidadLibro;
				} else{
					strcpy(comprasCaseta3[contadorCompras3].nombreLibro, ventas[opcionLibro - 1].nombreLibro);
					comprasCaseta3[contadorCompras3].cantidadLibros = cantidadLibro;
					comprasCaseta3[contadorCompras3].totalPrecio = cantidadLibro*ventas[opcionLibro - 1].precioLibro;
					contadorCompras3++;
					casetaTres+= cantidadLibro;
				}
				break;
			} 
		}
		
	// Ya conociendo el libro y la cantidad, guardo en la variable compras el nombre del libro y su precio total
		strcpy(compras[contadorPrecio].nombreLibro, ventas[opcionLibro - 1].nombreLibro );
		compras[contadorPrecio].totalPrecio = ventas[opcionLibro - 1].precioLibro * cantidadLibro;
		
		system("cls");
		printf("\tTotal\n\n 1 %s\t$ %i", compras[contadorPrecio].nombreLibro, compras[contadorPrecio].totalPrecio);
		
		printf("\nDesea finalizar las compras?\n\n1.Si\n2.No\n ");
		scanf("%d", &opcionLibro);
		
		if(opcionLibro==1){
			break;
		}else{
			system("cls");
		}
	}
	while(1){
	
	printf("\n\t\tResultado de ventas\n\n1. Filtro por libros\n2. Filtro por casetas\n");
	scanf ("%d", &filtros);
	
		while(1){
			
			if(filtros==1){
				system("cls");
				printf("\n\t\tFiltro por Libros\n");
				
				obra1 = cantidadObraVendida(ventas[0].nombreLibro);
				obra2 = cantidadObraVendida(ventas[1].nombreLibro);
				obra3 = cantidadObraVendida(ventas[2].nombreLibro);
				obra4 = cantidadObraVendida(ventas[3].nombreLibro);
				obra5 = cantidadObraVendida(ventas[4].nombreLibro);
				obra6 = cantidadObraVendida(ventas[5].nombreLibro);
				
				filtroPorLibro(obra1, obra2, obra3, obra4, obra5, obra6);
				break;
				
			} else if(filtros==2){
				system("cls");
				printf("\n\t\tFiltro por casetas\n");
				filtroPorCaseta(casetaUno, casetaDos, casetaTres);
				break;
			} 
		}
		
		printf("\nDesea volver a resultado de ventas\n\n1.Si\n2.No\n ");
		scanf("%d", &opcionLibro);
		
		if(opcionLibro==1){
			system("cls");
		}else{
			break;
		}
	}
}

void llenarCasetas(){ //se guarda en la estructura de ventas en nombre libro y en precio libro para luego mostrarla en la funcion principal
	
	strcpy(ventas[0].nombreLibro, "Las luces de Septiembre");
	strcpy(ventas[1].nombreLibro, "El principe de la Niebla");
	strcpy(ventas[2].nombreLibro, "El Palacio de Medianoche");
	strcpy(ventas[3].nombreLibro, "Marina");
	strcpy(ventas[4].nombreLibro, "La Sombra del Viento");
	strcpy(ventas[5].nombreLibro, "El Juego del Angel");
	
	ventas[0].precioLibro = 24000;
	ventas[1].precioLibro = 28000;
	ventas[2].precioLibro = 45000;
	ventas[3].precioLibro = 15000;
	ventas[4].precioLibro = 27000;
	ventas[5].precioLibro = 30000;
	
}

int cantidadObraVendida(char* obra){
	

	 int cantidadVentas=0, contador, contadorV;
	
	 for(contador=0; contador<30; contador++){
	 	
	 	if (strcmp(comprasCaseta1[contador].nombreLibro,obra)==0){
	 		cantidadVentas+= comprasCaseta1[contador].cantidadLibros;
	 		
		} else if (strcmp(comprasCaseta2[contador].nombreLibro, obra)==0){ //strcmp: compara dos cadenas.
	 		cantidadVentas+= comprasCaseta2[contador].cantidadLibros;	
		}else if(strcmp(comprasCaseta3[contador].nombreLibro, obra)==0){
				cantidadVentas+= comprasCaseta3[contador].cantidadLibros;
			}
		}
	 return cantidadVentas;
}

void filtroPorLibro(int obra1, int obra2, int obra3,int obra4,int obra5,int obra6){
	
	//LIBRO 1 
	if(obra1>=obra2 && obra1>=obra3 && obra1>=obra4 && obra1>=obra5 && obra1>=obra6 ){
		
		printf("\n1. Las luces de Septiembre: %d ", obra1);
		
		if(obra2>=obra3 &&  obra2>=obra4 &&  obra2>=obra5 &&  obra2>=obra6 ){
			printf("\n2. El principe de la Niebla: %d", obra2);
			printf("\n3. El Palacio de Medianoche: %d", obra3);
			printf("\n4. Marina: %d", obra4);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		}else if (obra3>=obra2 && obra3>=obra4 && obra3>=obra5 && obra3>=obra6){
			printf("\n2.  El Palacio de Medianoche: %d", obra3);
			printf("\n3.  El principe de la Niebla: %d", obra2);
			printf("\n4. Marina: %d", obra4);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra4>=obra2 && obra4>=obra3 && obra4>=obra5 && obra4>=obra6){
			printf("\n2. Marina: %d", obra4);
			printf("\n3. El principe de la Niebla: %d", obra2);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra5>=obra2 && obra5>=obra3 && obra5>=obra4 && obra5>=obra6){
			printf("\n2. La Sombra del Viento: %d", obra5);
			printf("\n3. El principe de la Niebla: %d", obra2);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else{
			printf("\n2.El Juego del Angel: %d", obra6);
			printf("\n3. El principe de la Niebla: %d", obra2);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. La Sombra del Viento: %d", obra5);
		}
	}
		
		//LIBRO 2
	if(obra2>=obra1 && obra2>=obra3 && obra2>=obra4 && obra2>=obra5 && obra2>=obra6 ){
		
		printf("\n1. El principe de la Niebla: %d ", obra2);
		
		if(obra1>=obra3 &&  obra1>=obra4 &&  obra1>=obra5 &&  obra1>=obra6 ){
			printf("\n2. Las luces de Septiembre: %d", obra1);
			printf("\n3. El Palacio de Medianoche: %d", obra3);
			printf("\n4. Marina: %d", obra4);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		}else if (obra3>=obra1 && obra3>=obra4 && obra3>=obra5 && obra3>=obra6){
			printf("\n2.  El Palacio de Medianoche: %d", obra3);
			printf("\n3.  Las luces de Septiembre: %d", obra1);
			printf("\n4. Marina: %d", obra4);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra4>=obra1 && obra4>=obra3 && obra4>=obra5 && obra4>=obra6){
			printf("\n2. Marina: %d", obra4);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra5>=obra1 && obra5>=obra3 && obra5>=obra4 && obra5>=obra6){
			printf("\n2. La Sombra del Viento: %d", obra5);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else{
			printf("\n2.El Juego del Angel: %d", obra6);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6.La Sombra del Viento: %d", obra5);
		}
	}
		//LIBRO 3
	if(obra3>=obra1 && obra3>=obra2 && obra3>=obra4 && obra3>=obra5 && obra3>=obra6 ){
		
		printf("\n1. El Palacio de Medianoche: %d ", obra3);
		
		if(obra1>=obra2 &&  obra1>=obra4 &&  obra1>=obra5 &&  obra1>=obra6 ){
			printf("\n2. Las luces de Septiembre: %d", obra1);
			printf("\n3. El principe de la Niebla: %d", obra2);
			printf("\n4. Marina: %d", obra4);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		}else if (obra2>=obra1 && obra2>=obra4 && obra2>=obra5 && obra2>=obra6){
			printf("\n2. El principe de la Niebla: %d", obra2);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. Marina: %d", obra4);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra4>=obra1 && obra4>=obra2 && obra4>=obra5 && obra4>=obra6){
			printf("\n2. Marina: %d", obra4);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra5>=obra1 && obra5>=obra2 && obra5>=obra4 && obra5>=obra6){
			printf("\n2. La Sombra del Viento: %d", obra5);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else{
			printf("\n2. El Juego del Angel: %d", obra6);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. La Sombra del Viento: %d", obra5);
		}
	}
		//LIBRO 4
	if(obra4>=obra1 && obra4>=obra2 && obra4>=obra3 && obra4>=obra5 && obra4>=obra6 ){
		
		printf("\n1. Marina: %d ", obra4);
		
		if(obra1>=obra2 &&  obra1>=obra3 &&  obra1>=obra5 &&  obra1>=obra6 ){
			printf("\n2. Las luces de Septiembre: %d", obra1);
			printf("\n3. El principe de la Niebla: %d", obra2);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		}else if (obra2>=obra1 && obra2>=obra3 && obra2>=obra5 && obra2>=obra6){
			printf("\n2. El principe de la Niebla: %d", obra2);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra3>=obra1 && obra3>=obra2 && obra3>=obra5 && obra3>=obra6){
			printf("\n2. El Palacio de Medianoche: %d", obra3);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. La Sombra del Viento: %d", obra5);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra5>=obra1 && obra5>=obra2 && obra5>=obra3 && obra5>=obra6){
			printf("\n2. La Sombra del Viento: %d", obra5);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. El Palacio de Medianoche: %d", obra3);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else{
			printf("\n2. El Juego del Angel: %d", obra6);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. El Palacio de Medianoche: %d", obra3);
			printf("\n6. La Sombra del Viento: %d", obra5);
		}
	}
		//LIBRO 5
	if(obra5>=obra1 && obra5>=obra2 && obra5>=obra3 && obra5>=obra4 && obra5>=obra6 ){
		
		printf("\n1. La Sombra del Viento: %d ", obra5);
		
		if(obra1>=obra2 &&  obra1>=obra3 &&  obra1>=obra4 &&  obra1>=obra6 ){
			printf("\n2. Las luces de Septiembre: %d", obra1);
			printf("\n3. El principe de la Niebla: %d", obra2);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. El Juego del Angel: %d", obra6);
		}else if (obra2>=obra1 && obra2>=obra3 && obra2>=obra4 && obra2>=obra6){
			printf("\n2. El principe de la Niebla: %d", obra2);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra3>=obra1 && obra3>=obra2 && obra3>=obra4 && obra3>=obra6){
			printf("\n2. El Palacio de Medianoche: %d", obra3);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else if (obra4>=obra1 && obra4>=obra2 && obra4>=obra3 && obra4>=obra6){
			printf("\n2. Marina: %d", obra4);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. El Palacio de Medianoche: %d", obra3);
			printf("\n6. El Juego del Angel: %d", obra6);
		} else{
			printf("\n2. El Juego del Angel: %d", obra6);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. El Palacio de Medianoche: %d", obra3);
			printf("\n6. Marina: %d", obra4);
		}
	}
		//LIBRO 6
	if(obra6>=obra1 && obra5>=obra2 && obra6>=obra3 && obra6>=obra4 && obra6>=obra5 ){
		
		printf("\n1. El Juego del Angel: %d ", obra6);
		
		if(obra1>=obra2 &&  obra1>=obra3 &&  obra1>=obra4 &&  obra1>=obra5 ){
			printf("\n2. Las luces de Septiembre: %d", obra1);
			printf("\n3. El principe de la Niebla: %d", obra2);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. La Sombra del Viento: %d", obra5);
		}else if (obra2>=obra1 && obra2>=obra3 && obra2>=obra4 && obra2>=obra5){
			printf("\n2. El principe de la Niebla: %d", obra2);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El Palacio de Medianoche: %d", obra3);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. La Sombra del Viento: %d", obra5);
		} else if (obra3>=obra1 && obra3>=obra2 && obra3>=obra4 && obra3>=obra5){
			printf("\n2. El Palacio de Medianoche: %d", obra3);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. Marina: %d", obra4);
			printf("\n6. La Sombra del Viento: %d", obra5);
		} else if (obra4>=obra1 && obra4>=obra2 && obra4>=obra3 && obra4>=obra5){
			printf("\n2. Marina: %d", obra4);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. El Palacio de Medianoche: %d", obra3);
			printf("\n6. La Sombra del Viento: %d", obra5);
		} else{
			printf("\n2. La Sombra del Viento: %d", obra5);
			printf("\n3. Las luces de Septiembre: %d", obra1);
			printf("\n4. El principe de la Niebla: %d", obra2);
			printf("\n5. El Palacio de Medianoche: %d", obra3);
			printf("\n6. Marina: %d", obra4);
		}
	}
}

void filtroPorCaseta(int casetaUno, int casetaDos, int casetaTres){
	
	if(casetaUno<=casetaDos && casetaUno<=casetaTres){
		
		printf("\n1. Caseta uno: %d libros", casetaUno);
		if(casetaDos<=casetaTres){
			printf("\n2. Caseta dos: %d libros", casetaDos);
			printf("\n3. Caseta tres: %d libros", casetaTres);
		}else{
			printf("\n2. Caseta tres: %d libros", casetaTres);
			printf("\n3. Caseta dos: %d libros", casetaDos);
		}
		
	} else	if(casetaDos<=casetaUno && casetaDos<=casetaTres){
		
		printf("\n1. Caseta dos: %d libros", casetaDos);
		if(casetaUno<=casetaTres){
			printf("\n2. Caseta uno: %d libros", casetaUno);
			printf("\n3. Caseta tres: %d libros", casetaTres);
		}else{
			printf("\n2. Caseta tres: %d libros", casetaTres);
			printf("\n3. Caseta uno: %d libros", casetaUno);
		}
		
	}else	{
		printf("\n1. Caseta tres: %d libros", casetaTres);
		if(casetaUno<=casetaDos){
			printf("\n2. Caseta uno: %d libros", casetaUno);
			printf("3. Caseta dos: %d libros", casetaDos);
		}else{
			printf("\n2. Caseta dos: %d libros", casetaDos);
			printf("\n3. Caseta uno: %d libros", casetaUno);
		}
	}
}
