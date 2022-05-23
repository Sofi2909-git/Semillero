#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

struct usuario {
	
	char nombre[30];
	char fecha[30];
	char hora[30];
	char cedula[30];
	char clave[30];
	int saldo;	
	
}usuarios[30];

char* nombre;
char* fecha;
char* hora;
char* cedula;
char* clave;
int cantidad=0;

char *validarLetras();
char* validarN();
int validarClave (char *clave);
char* claveProtegida(char* claveI);
int validarCcRegistrada(char* CcInicioSesion);
int validarRegistro(char* cedula);
void registro();
void login();
void fecha_hora();
int myStrlen(char *ced);
void pagos(int usu);
int myStrcmp(char *c1, char *c2);
void optionFactura(int usu, int menu);

int main(){
	
	int menu;
	
	do{
		printf("\n\t\tPAGUE SUS SERVICIOS");
		printf("\n1.Iniciar sesion en el sistema");
		printf("\n2.Registrarse en el sistema");
		printf("\n3.Salir");
		printf("\nElige una opcion: ");
		scanf("%d", &menu);
		
		switch(menu){
			case 1: 
				login();
			break;
			case 2: 
				registro();
			break;
		}
	}while(menu!=3);
	system("pause");
}
void fecha_hora(){
    time_t tiempoAhora; // creamos una variable de tipo time_t
	time(&tiempoAhora);
	struct tm *miTiempo=localtime(&tiempoAhora);
	printf("\nFecha: %d/%d/%d\nHora: %d:%d:%d",miTiempo->tm_mday,miTiempo->tm_mon+1,miTiempo->tm_year+1900,miTiempo->tm_hour,miTiempo->tm_min,miTiempo->tm_sec);

}
void registro() {
	
	nombre = (char *)malloc(30); 
	cedula = (char *)malloc(30); 
	clave = (char *)malloc(30); 
	int validar=0, validarCc;
	
	system("cls");
	fflush(stdin);
	printf("\n\t\tREGISTRO\n");
	while(1){
		//nombre
		printf("\nDigite su nombre:");
		nombre=validarLetras();
		strcpy(usuarios[cantidad].nombre,nombre);
		//cedula
		while(1){
			printf("\nDigite su numero de identificacion:");
			cedula=validarN();
			validarCc=validarRegistro(cedula);
			if(validarCc==1){
				//system("cls");
				printf("\nUsuario registrado\nIngrese un nuevo usuario");
			}else{
				strcpy(usuarios[cantidad].cedula,cedula);
				break;
			}
		}
		break;
	}
	
	//clave
	while(1){
		printf("\nDigite una clave:");
		claveProtegida(clave);
		validar=validarClave(clave);
		strcpy(usuarios[cantidad].clave,clave);
		if (validar == 0){
			system("cls");
			printf ("\nClave incompleta, intente de nuevo:\n");
		}else{
			break; 
		}
	}
	
	//deposito
	while(1){
		printf("\n\n\tATENCION: Para continuar con el registro se debe hacer un deposito inical de $1000\n");
		printf("\n\tDeposito Inicial\n\t->");
		scanf("%d", &usuarios[cantidad].saldo);
		
		if(usuarios[cantidad].saldo>=1000){
			system("cls");
			fecha_hora();
			printf("\n%s su saldo disponible es %d", usuarios[cantidad].nombre, usuarios[cantidad].saldo);
			printf("\n\n\tREGISTRO EXITOSO AHORA PUEDE INICIAR SESION\n");
			cantidad++;
			break;
	    }else{
	    	system("cls");
	    } 
	}
}
void login() {
	
	system("cls");
	nombre = (char *)malloc(30); 
	cedula = (char *)malloc(30); 
	clave = (char *)malloc(30); 
	
	int usu=0;
	int i;
	int valid=0, validarCc, validar;

	
	printf("\n\tINICIO DE SESION\n");
	while(1){
		//cedula
		while(1){
			printf("\nDigite su numero de identificacion:");
			cedula=validarN();
			validarCc=validarCcRegistrada(cedula);
			if(validarCc=1){
			   	break;
			}else{
				system("cls");
				printf("\nCedula de usuario no registrada");
			}
		}
		//clave
		while(1){
		printf("\nDigite su Clave:");
		claveProtegida(clave);
		validar=validarClave(clave);
			if (validar == 0){
				system("cls");
				printf ("\nClave incompleta, intente de nuevo:\n");
			}else{
				break; 
			}
		}
		for(i=0; i<cantidad; i++) {
			if(myStrcmp(usuarios[i].cedula, cedula)== 0 && myStrcmp(usuarios[i].clave, clave)==0) {
			   valid=1;	
			   usu=i;
			}
		}
		if(valid==1){
			break;
		}else{
			system("cls");
			printf("\n\tCedula y/o Clave no valido!\n");
		}
	}
	pagos(usu);
}
void pagos(int usu){
	
	int menu;
	system("cls");
	printf("\n\t\tVENTANA DE PAGOS\n");
	do {
		system("cls");
		printf("\n\tSelecione el tipo de factura");
		printf("\n1.CENS");
		printf("\n2.AGUAS KPITAL");
		printf("\n3.VEOLIA");
		printf("\n4.DIRECTV");
		printf("\n5.CANAL EXITO");
		printf("\n6.VOLVER AL MENU PRINCIPAL");
		printf("\nElige una opcion: ");
		scanf("%d", &menu);
		
		switch(menu){
			
			case 1: 
				optionFactura(usu, menu);
			break;
			case 2: 
				optionFactura(usu, menu);	
			break;
			case 3:
				optionFactura(usu, menu);	
			break;
			case 4:
				optionFactura(usu, menu);	
			break;
			case 5: 
				optionFactura(usu, menu);	
			break;
		}
	}while(menu!=6);	
}
void optionFactura(int usu, int menu) {
	
	char factura[30];
	int monto;
	int confirmMonto;
	int valid=0;
	int nuevoSaldo;
	
	printf("\nDigite el numero de su factura: ");
	scanf("%s", &factura);
	printf("\nDigite el monto a pagar: ");
	scanf("%d", &monto);
	printf("\nConfirme el monto a pagar: ");
	scanf("%d", &confirmMonto);
	printf("\n\tSu saldo es: %d", usuarios[usu].saldo);
	printf("\n\tEl monto es: %d ", monto);
	
	if(myStrlen(factura)==10) {
		if(monto==confirmMonto) {
			if(monto<=usuarios[usu].saldo) {
				if(monto>=1000) {
					system("cls");
					printf("\n\tPago exitoso\n");
					fecha_hora();
					printf("\n\tNombre en la factura: %s", usuarios[usu].nombre);
					printf("\n\tCedula en la factura: %s", usuarios[usu].cedula);
					usuarios[usu].saldo=usuarios[usu].saldo-monto;
					printf("\n\tSu saldo disponible es: %d", usuarios[usu].saldo);

					switch(menu) {
					case 1: 
					  printf("\n\tEl pago lo realizo en: CENS\n");
					break;
					case 2: 
						printf("\n\tEl pago lo realizo en: AGUAS KPITAL\n");
					break;
					case 3:
						printf("El pago lo realizo en: VEOLIA\n");
					break;
					case 4:
						printf("\n\tEl pago lo realizo en: DIRECTV\n");
					break;
					case 5:
						printf("\n\tEl pago lo realizo en: CANAL EXITO\n");
					break;
					}
					system("pause");
				}else{
					printf("\n\tEl monto minimo a pagar es de 1000\n");
					optionFactura(usu, menu);
					return;
				}
			}else{
			printf("\n\tPAGO CANCELADO, NO CUENTA CON SALDO SUFICIENTE\n");
			printf("\n\tATENCION: Puedes agregar dinero a tu cuenta\n");
			printf("\n\tDigite la cantidad que desea agregar a su cuenta\n\t");
			scanf("%d", &nuevoSaldo);
			usuarios[usu].saldo=usuarios[usu].saldo+nuevoSaldo;
			printf("\n\tSu nuevo saldo es: %d \n", usuarios[usu].saldo);
			optionFactura(usu, menu);
			return;
			}
		}else{
			printf("\n\tEl Monto y su confirmacion deben ser iguales\n");
			optionFactura(usu, menu);
			return;
		}
	}else{
		printf("\n\tEl numero de la factura debe contener 10 digitos\n");
		optionFactura(usu, menu);
		return;
	}
}
int myStrlen(char ced[100]) {
	int len = 0;
	while(ced[len] != '\0' && ced[len] != '\n'){
		len++;
	}
	return len;   
}
int myStrcmp(char c1[30], char c2[30]){
	int i;
	int my = myStrlen(c1);
	int my2 = myStrlen(c2);
	for(i=0; i<my; i++){
		if(c1[i]<c2[i]){
			return -1;
		}else if(c1[i]>c2[i]){
			return 1;
		}
	}
	return 0;
}
char *validarLetras(){

	char *cadena; 	
	char caracter;		
	int contador = 0;
	cadena = (char *)malloc(20); 
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
				cadena[contador] = '\0';
			} 
			
		}else{
			if((caracter>=65 && caracter<=90) || (caracter>=97 && caracter<=122) || caracter==32 ){
				putchar(caracter);
				cadena[contador] = caracter;
				cadena[contador + 1] = '\0';
				contador++;
			}
		}
	}	
	return cadena;
}
char* validarN(){

	char* cadena; 		// Aqui se iran guardando todos los caracteres
	char caracter;		// Aqui recogemos caracter a caracter
	int contador = 0;
	cadena = (char *)malloc(20); // malloc: para solicitar un bloque de memoria del tamaño suministrado como parámetro. Devuelve un puntero a la zona de memoria concedida 
	while(1){
		
		caracter = getch();
		
		if(caracter == '\r' && contador==10){
			break;
		}else if( caracter == '\b' ){
			
			if( contador > 0 ){
				putchar('\b');
				putchar(' ');
				putchar('\b');
				contador--;
				cadena[contador] = '\0';
			} 
			
		}else{
			if((caracter>=48 && caracter<=57) && contador<10 ){
				putchar(caracter);
				cadena[contador] = caracter;
				cadena[contador + 1] = '\0';
				contador++;
			}
		}
	}	
	return cadena;
}
char* claveProtegida(char* claveI){ // Aqui se iran guardando todos los caracteres

	char caracter;		// Aqui recogemos caracter a caracter
	int contador = 0;
	
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
				claveI[contador] = '\0';
			}
			
		}else{
			putchar('*');
			claveI[contador] = caracter;
			claveI[contador + 1] = '\0';
			contador++;
		}
		
	}
	
	return claveI;
}
int validarClave (char *clave){
	
	int contador=0;
	int contadorMayusculas = 0;
	int contadorMinusculas = 0;
	int contadorNumeros = 0;
	int contadorCaracteresEspeciales = 0;
	
	if(strlen(clave)<8){
		return 0;
	}
	
	while (clave[contador]!='\0'){
		if (clave[contador]>='A' && clave[contador]<='Z'){
			contadorMayusculas++;
		} else if (clave[contador]>='a' && clave[contador]<='z'){
			contadorMinusculas++;
		} else if (clave[contador]>='0' && clave[contador]<='9'){
			contadorNumeros++;
		} else {
			contadorCaracteresEspeciales++;
		}
		contador++;
	}
	if (contadorMayusculas!=0 && contadorMinusculas!=0 && contadorNumeros!=0 && contadorCaracteresEspeciales!=0){
		return 1; 
	}else{
		return 0;
	}
}
int validarCcRegistrada(char* CcInicioSesion){
	
	int i;
	for(i=0;i>0;i++){
		if(strcmp(CcInicioSesion, usuarios[i].cedula)){
			return 1;
		}else{ 
			return 0;
		}
	}
}
int validarRegistro(char* cedula){
	
	int i;
	for(i=0;i<30;i++){
		if(strcmp(cedula,usuarios[i].cedula)==0){
			return 1;
		}else{
			return 0;
		}
	}
}

