#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>


struct DATOS{
	
	char lugares[20]; 
	char placa[10];
	int precioHora;
	
}carros[10], motos[6];

struct FACTURA{
	
	char placa[10];
	int horaE,minE,segE;
	int horaS,minS,segS;
	int horaEstimada, minEstimado;
	int pagoT;
	
}Factura[50];

void llenarLugaresC();
void llenarLugaresM();
void Hora(char* placa, int tipoHora);
int validarN();
int horasMinutos(int posicion, int entradaSalida);
int BuscarVehiculo(char* placa, int opcion); 
int BuscarFacturaLibre ();
void ImprimirFactura(int p,int tipoVehiculo);
int salidaVehiculo(int posicion,int tipovehiculo);


void main(){
	
	int vehiculo, contadorC=0, contadorM;
	int lugarC=0,lugarM=0, opcion;
	char placaC[20], placaM[20], placaSalida[20];
	int horaE,horaS;
	int lugares=0;
	
	horaE=1;
	horaS=2;
	
	printf("\n\t\tBienvenido al estacionamiento\n\t\t-----------------------------");
	
	while(1){
		
		printf("\nTipo de vehiculo:\n\n1.Carros\n2.Moto\n");
		vehiculo=validarN();
		
		if(vehiculo=='1'){
			system("cls");
			printf("\nCarros\n");
			while(1){
			
				for(contadorC = 0; contadorC < 10; contadorC++ ){
					llenarLugaresC();
					printf("\n%i.%s\t $ %i Por hora", contadorC + 1, carros[contadorC].lugares, carros[contadorC].precioHora);
				}
				printf("\n\nSeleccione el lugar a estacionar: ");
				scanf("%d", &lugarC);
				
				if(lugarC>=1 && lugarC<=10){
					printf("\nNumero de placa del vehiculo:");
					scanf("%s", &placaC);
					
					if (strlen(carros[lugarC].placa)==0){
						printf("\nLugar disponible\n");
						Hora(placaC, horaE);
						strcpy(carros[lugarC].placa,placaC);
						printf("\n\nTiempo estimado de parqueo\nHoras:");
						scanf("%d", &Factura[lugarC-1].horaEstimada);
						printf("\nMinutos:");
						scanf("%d", &Factura[lugarC-1].minEstimado);
						contadorC++;
						break;
						
					} else{
						printf("\nOcupado por %s\n", carros[lugarC].placa);
						printf("\nPresione una tecla para buscar otro lugar");
		    			getch();
		    			system("cls");
					}
				}
			}	
		}else if (vehiculo=='2'){
			system("cls");
			printf("\nMotos\n");
			
			while(1){
			
				for(contadorM = 0; contadorM < 6; contadorM++ ){
					llenarLugaresM();
					printf("\n%i.%s\t $ %i Por hora", contadorM + 1, motos[contadorM].lugares, motos[contadorM].precioHora);
				}
				printf("\n\nSeleccione el lugar a estacionar: ");
				scanf("%d", &lugarM);
				
				if(lugarM>=1 && lugarM<=6){
					printf("\nNumero de placa del vehiculo:");
					scanf("%s", &placaM);
					if (strlen(motos[lugarM].placa)==0){
						printf("\nLugar disponible\n");
						strcpy(motos[lugarM].placa,placaM);
						Hora(placaM, horaE);
						printf("\n\nTiempo estimado de parqueo\nHoras:");
						scanf("%d", &Factura[lugarM-1].horaEstimada);
						printf("Minutos:");
						scanf("%d", &Factura[lugarM-1].minEstimado);
						contadorM++;
						break;
						
					} else {
						printf("\n Ocupado por %s\n", motos[lugarM].placa);
						printf("\nPresione una tecla para buscar otro lugar");
		    			getch();
		    			system("cls");
					}
				}
			}
		}
		system("cls");
		printf("\n\nOPCION\n\n1.Continuar registros\n2.Imprimir factura\n ");
		opcion=validarN();
		
		if(opcion=='1'){
			system("cls");
		}else{
			//imprimir factura
			printf("\n\t\tSALIDA");
			printf("\nIngrese el tipo de vehiculo que va a salir:\n\n1.Carros\n2.Moto\n");
			vehiculo=validarN();
			
			int pos;
			int posFactura;
			
			printf("\nIngrese el numero de placa:");
			scanf("%s",&placaSalida);
			Hora(placaSalida, horaS);
			
			if(vehiculo=='1'){
				system("cls");
				printf("\n\t\tFACTURA DE VEHICULO\n\t\t-----------------");
				//Posicion vehiculo
				pos=BuscarVehiculo(placaSalida, 1);
				printf("\nPosicion:%d", pos);
				//Posicion factura
				posFactura=BuscarFacturaPlaca(placaSalida);
				//Calcular agregar la fecha de salida con la posicion de factura
				ImprimirFactura(posFactura, 1);
				salidaVehiculo(pos,1);
			
			}else if(vehiculo=='2'){
				system("cls");
				printf("\n\n\t\tFACTURA DE VEHICULO\n\t\t-----------------");
				//Posicion vehiculo
				pos=BuscarVehiculo(placaSalida, 2);
				//Posicion factura
				posFactura=BuscarFacturaPlaca(placaSalida);
				//Calcular agregar la fecha de salida con la posicion de factura
				ImprimirFactura(posFactura, 2);
				salidaVehiculo(pos,2);
			}
			
		}
		
		printf("\n\nOPCION\n\n1.Continuar registros\n2.Salir\n ");
		opcion=validarN();
		
		if(opcion=='1'){
			system("cls");
		}else{
			break;
		}
	}
		
}



void llenarLugaresC(){
	
	strcpy(carros[0].lugares, "Espacio 1");
	strcpy(carros[1].lugares, "Espacio 2");
	strcpy(carros[2].lugares, "Espacio 3");
	strcpy(carros[3].lugares, "Espacio 4");
	strcpy(carros[4].lugares, "Espacio 5");
	strcpy(carros[5].lugares, "Espacio 6");
	strcpy(carros[6].lugares, "Espacio 7");
	strcpy(carros[7].lugares, "Espacio 8");
	strcpy(carros[8].lugares, "Espacio 9");
	strcpy(carros[9].lugares, "Espacio 10");
	
	carros[0].precioHora=3000;
	carros[1].precioHora=3000;
	carros[2].precioHora=3000;
	carros[3].precioHora=3000;
	carros[4].precioHora=3000;
	carros[5].precioHora=3000;
	carros[6].precioHora=3000;
	carros[7].precioHora=3000;
	carros[8].precioHora=3000;
	carros[9].precioHora=3000;
}
void llenarLugaresM(){
	
	strcpy(motos[0].lugares, "Espacio 1");
	strcpy(motos[1].lugares, "Espacio 2");
	strcpy(motos[2].lugares, "Espacio 3");
	strcpy(motos[3].lugares, "Espacio 4");
	strcpy(motos[4].lugares, "Espacio 5");
	strcpy(motos[5].lugares, "Espacio 6");
	
	motos[0].precioHora=1000;
	motos[1].precioHora=1000;
	motos[2].precioHora=1000;
	motos[3].precioHora=1000;
	motos[4].precioHora=1000;
	motos[5].precioHora=1000;
}

int validarN(){

	int caracter;		

	while(1){
		caracter = getch();
		
		if(caracter>='0' && caracter<='9' ){
			putchar(caracter);
			break;
		}
	}
	return caracter;
}

void Hora(char* placa, int tipoHora){
	
	int hora, min, seg;
	int i,p,ps;


	time_t t;
	time(&t);
	
	
  	struct tm *tm= localtime(&t);
	char fechayhora[100];
	strftime(fechayhora, 100, "%H:%M:%S", tm);
	hora=tm->tm_hour;
	min=tm->tm_min;
	seg=tm->tm_sec;
	p=BuscarFacturaLibre();
	
	if(tipoHora==1){
		//Creando factura nueva
		strcpy(Factura[p].placa, placa);
		Factura[p].horaE=hora;
		Factura[p].minE=min;
		Factura[p].segE=seg;
		printf("\nHora de entrada: %d:%d.%d", Factura[p].horaE, Factura[p].minE, Factura[p].segE);
			
	}else if(tipoHora==2){
		//Terminando factura 
		ps=BuscarFacturaPlaca(placa);
		Factura[ps].horaS=hora;
		Factura[ps].minS=min;
		Factura[ps].segS=seg;
		printf("\nHora de salida: %d:%d.%d", Factura[ps].horaS, Factura[ps].minS, Factura[ps].segS);
	}
}


int BuscarFacturaLibre (){
	int i,pos;
	
	for(i=0;i<50;i++){
		if(strlen(Factura[i].placa)==0){
			pos=i;
			break;
		}
	}
	return pos;
}

int BuscarFacturaPlaca(char * placa){
	
	int i,pos=0;
		
	for(i=0;i<=50;i++){
		
		if((strcmp(Factura[i].placa, placa)==0)){
			pos=i;
			break;
		}
	}
	return pos;
}


void ImprimirFactura(int p,int tipoVehiculo){

	int hour1,min1,s1;
	int tiempoEsHora,tiempoEsMin;
	int costeTotal=0,minutosExtras,horasExtras;
	int horaTotal,minTotal,segTotal;
	int hour2,min2,s2;
	int hour,min,s;
	int tarifa;
	
	int total;
	
	//]Entrada
	hour1=Factura[p].horaE;
	min1=Factura[p].minE;
	s1=Factura[p].segE;
	printf("\nHora entrada %d:%d.%d",hour1,min1,s1);
	//Salida
	hour2=Factura[p].horaS;
	min2=Factura[p].minS;
	s2=Factura[p].segS;
	printf("\nHora salida %d:%d.%d",hour2,min2,s2);
	
	//tiempo total del parqueadero
	
	//segundos totales
	if(s2<s1){
		s2+=60;
		segTotal=s2-s1-60;
		min2-=1;
	}else{
		segTotal=s2-s1;
	}
	
	//minutos totales
	if(min2<min1){
		if(s2>=s1){
			s2+=60;
			segTotal=s2-s1-60;
			min2-=1; 
		min2+=60;
		minTotal=min2-min1+1;
		hour2-=1;
		}else{
			minTotal=min2-min1;
		}
	}
	
	//horas totales
	horaTotal=hour2-hour1;

	
	//tiempo estimado
	tiempoEsHora=Factura[p].horaEstimada;
	tiempoEsMin=Factura[p].minEstimado;
	
	//tiempo extra
	horasExtras=horaTotal-tiempoEsHora;
	minutosExtras=minTotal-tiempoEsMin;

	
	
	printf("\nTiempo total  %d:%d.%d",abs(horaTotal),abs(minTotal),abs(segTotal)); //abs: le quita el negativo a los enteros
	printf("\nTiempo extra  %d:%d",abs(horasExtras), abs(minutosExtras));
	
	if(tipoVehiculo==1){
		
		tarifa=3000;
		
		if(horaTotal>1){
			
			costeTotal+=horaTotal*3000;
			
			if(minutosExtras>=2){
				
				costeTotal+=200*minutosExtras;
			}
		}else {
			
			costeTotal+=tarifa;
			
			if(minutosExtras>2){
				costeTotal+=200*minutosExtras;
			}
		}
		
		Factura[p].pagoT=costeTotal;
		printf("\nTotal a pagar:%d", costeTotal);
	}
	else if(tipoVehiculo==2){
		
		tarifa=1000;
		
	if(horaTotal>1){
			
			costeTotal+=horaTotal * 1000;
			
			if(minutosExtras>=2){
				
				costeTotal+=200*minutosExtras;
			}
		}else {
			costeTotal+=tarifa;
			if(minutosExtras>=2){
				costeTotal+=200*minutosExtras;
			}
		}

		Factura[p].pagoT=costeTotal;
		printf("\nTotal a pagar:%d", costeTotal);
	}

}


int BuscarVehiculo(char* placa, int opcion){

		int pos;
		
		if(opcion==1){
			int i;
			
			for(i=0;i<=10;i++){
				if (strcmp(placa, carros[i].placa) == 0){
					printf("\nPlaca %s", placa);
					pos=i;
					break;
				
  				} 
			}
			
		}else if (opcion==2){
			
			int j;
			
			for(j=0; j<=6;j++){	
				if (strcmp(placa, motos[j].placa) == 0){
				printf("\nPlaca %s.", placa);
				pos=j;
				break;
  				} 
			}
	}
	return pos;
}

int salidaVehiculo(int posicion,int tipovehiculo){
	
	if(tipovehiculo==1){
		strcpy(carros[posicion].placa,"");
	}
	if(tipovehiculo==2){
		strcpy(carros[posicion].placa,"");
	}
	
	return posicion;
}
