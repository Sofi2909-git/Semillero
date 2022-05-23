#include <stdio.h>
#include <conio.h>
#include <string.h> 
#include <stdlib.h>
#include<ctype.h>
#include<time.h>
#define INTENTOS 3
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 80
#define USUARIO "admin@wposs.com"
#define CLAVE "Admin123*"
#define MONTO 1000000
#define HABILITADO 1
#define DESHABILITADO 0


int validarClave(char *clave);
int validarCadena(char *cadena);
int generadorNumCuenta();
int validarCedula(char *cedula);
int validarNumeros(char *numero);
int validarCedulaRepetida(char *cedula);
int validarCorreo(char *correo);
int validaCorreoRepetido(char *correo);
void menuUsuario(int y);
void menuAdmin();
void retirar(int y);
void depositar(int y);
void transferir(int y);
int validarCuentaExistente(int cuenta);
void detallesUsuario(int y);
void listarUsuarios();
void habilitarOInhabilitar();
int validarEstado(int cuenta);
void pantallaInicial();
void crearUsuario();
void ingresarUsuario();
void ingresarAdministrador();
char* validarLetras();
char* validarN();
void salir();

int contUsuarios;
int i=0;
int cuenta=0;
char *cedula;
char *nombre;
char correo[80];
char clave[80];
char caracter; 
float saldo=0;

struct{
	
	int cedula;
	char nombre[80];
	char correo[80];
	char clave[80];
	int numeroCuenta;
	float saldo;
	int estado;
	
}usuarios[10];

int main(){
	pantallaInicial();
	return 0;
}

void pantallaInicial(){
	
	char opcion;
	
	do{
		system("cls");
		printf("\n\t\t\tMENU PRINCIPAL\n");
		printf("\n1.Crear Usuario");
		printf("\n2.Ingresar Usuario");
		printf("\n3.Ingresar Administrador");
		printf("\n4.Salir");
		printf("\nElige une una opcion: ");
		fflush(stdin);
		scanf("%c", &opcion);
		switch(opcion){
			case '1':
				crearUsuario();
				break;
			case '2':
				ingresarUsuario();
				break;
			case '3':
				ingresarAdministrador();
				break;
			case '4':
				salir();
				break;
			default:
				printf("\n\tOpcion incorrecta!");
		}
	}while(opcion!=52);
}

void crearUsuario(){
	
	nombre = (char *)malloc(20);
	cedula= (char *)malloc(11);
	
	int salir=0;
	do{
		system("cls");
		printf("\n\t\t[1].REGISTRO USUARIO\n");
		printf("\n\nIngrese su nombre: ");
		fflush(stdin);
		nombre=validarLetras();
		while(validarCadena(nombre)==0){
			printf("\nError!\n\tPor favor su nombre: ");
			fflush(stdin);
			nombre=validarLetras();
		}
		printf("\n\nIngrese su numero de cedula: ");
		fflush(stdin);
		cedula=validarN();
		while(validarCedula(cedula)!=1){
			printf("\nPor favor, ingrese una cedula valida: ");
			fflush(stdin);
			cedula=validarN();
		}
		while(validarCedulaRepetida(cedula)==0 || validarCedula(cedula)!=1){
			if(validarCedulaRepetida(cedula)==0){
				printf("\nEl usuario ya esta registrado, ingrese una  nueva cedula: ");
			}else{
				printf("\nPor favor digite un cedula valida: ");
			}
			fflush(stdin);
			cedula=validarN();
		}
		printf("\nIngrese un correo Valido: ");
		fflush(stdin);
		gets(correo);
		validarCorreo(correo);
		while(validaCorreoRepetido(correo)!=0){
			printf("\nPor favor, ingrese otro correo: ");
			fflush(stdin);
			gets(correo);
			validarCorreo(correo);
		}
		while(validarCorreo(correo)!=1  ){
			printf("\nPor favor, ingrese un correo Valido: ");
			fflush(stdin);
			gets(correo);
			validarCorreo(correo);
		}
		printf("\nIngrese una clave alfanumerica: ");
		while(caracter=getch()){
			if(caracter==13){
				clave[i]='\0';
				break;
			}else if(caracter == 8){
				if(i>0){
					i--;
					printf("\b \b");
				}
			}else{
				if(i<LONGITUD){
					printf("*");
					clave[i]=caracter;
					i++;
				}
			}
		}
		fflush(stdin);
		while(validarClave(clave)!=1){
			printf("\nPor favor, ingrese una clave alfanumerica: ");
			for(i=0;i<strlen(clave);i++){
				clave[i]='\0';
			}
			i=0;
			while(caracter=getch()){
				if(caracter==13){
					clave[i]='\0';
					break;
				}else if(caracter == 8){
					if(i>0){
						i--;
						printf("\b \b");
					}
				}else{
					if(i<LONGITUD){
						printf("*");
						clave[i]=caracter;
						i++;
					}
				}
			}
		}
		strcpy(usuarios[contUsuarios].nombre,nombre);
		usuarios[contUsuarios].cedula=atoi(cedula);
		strcpy(usuarios[contUsuarios].correo,correo);
		strcpy(usuarios[contUsuarios].clave, clave);
		usuarios[contUsuarios].saldo=MONTO;
		usuarios[contUsuarios].numeroCuenta=generadorNumCuenta();
		usuarios[contUsuarios].estado=HABILITADO;
		contUsuarios++;
		system("CLS");
		printf("\n\t\tRegistro exitoso!\n");
		printf("\nNombre: %s\nCedula: %d\nCorreo: %s\nclave: %s\nSaldo: $%.2f\nNumero de cuenta: %d\nEstado: %d",
			usuarios[contUsuarios-1].nombre,usuarios[contUsuarios-1].cedula,usuarios[contUsuarios-1].correo,usuarios[contUsuarios-1].clave,
			usuarios[contUsuarios-1].saldo,usuarios[contUsuarios-1].numeroCuenta,usuarios[contUsuarios-1].estado);
		printf("\n\nOprima cualquier tecla para regresar al menu principal --> ");
		getchar();
		system("cls");
		salir=1;	
	}while(salir!=1);
}

void ingresarUsuario(){
	
	int ingresa=0;
	int intento=0;
	int y=0;
	int j;
	do{
		i=0;
		if(contUsuarios==0){
				
				printf("\n\tNo hay usuarios registrados en el sistema.\n");
				printf("\n\n\tOprima una tecla para continuar");
				getchar();
				getchar();
				break;
		}
		system("cls");
		printf("\n\n\t\tINICIO DE SESION\n"); 
		printf("\nCorreo: ");
		fflush(stdin);
		gets(correo);
		validarCorreo(correo);
		validarCorreo(correo);	
		printf("\nClave: ");
		fflush(stdin);
		while(caracter=getch()){
			if(caracter==13){
				clave[i]='\0';
				break;
			}else if(caracter == 8){
				if(i>0){
					i--;
					printf("\b \b");
				}
			}else{
				if(i<LONGITUD){
					printf("*");
					clave[i]=caracter;
					i++;
				}
			}
		}
		for(i=0;i<contUsuarios;i++){
			if(strcmp(correo,usuarios[i].correo)==0 && strcmp(clave,usuarios[i].clave)==0 && usuarios[i].estado==1){	
			    y=i;
				ingresa =1;
				break;
			}
			getchar();
		}
		if(ingresa==0) {
			printf("\nCorreo y/o clave incorrectos\n");
			intento++;
			getchar();	
		}
	}while(intento<INTENTOS && ingresa==0  ) ;
	
	if(ingresa==1){
		printf("\n\tBienvenido al Sistema!");
		printf("\n\tOprima cualquier tecla para continuar.");
		getchar();
		menuUsuario(y);
	}else {
		printf("\n\nHa sobrepasado el numero maximo de intentos permitidos\n");
	}
}

void ingresarAdministrador(){
	
	int ingresa=0;
	int intento=0;
	int y=0;
	do{
		i=0;
		system("cls");
		printf("\n\n\t\tINICIO DE SESION\n");
		printf("\t\t----------------\n");  
		printf("\nCorreo: ");
		fflush(stdin);
		gets(correo);	
		printf("\n%s",correo);	
		printf("\nClave: ");
		fflush(stdin);
		while(caracter=getch()){
			if(caracter==13){
				clave[i]='\0';
				break;
			}else if(caracter == 8){
				if(i>0){
					i--;
					printf("\b \b");
				}
			}else{
				if(i<LONGITUD){
					printf("*");
					clave[i]=caracter;
					i++;
				}
			}
		}
		printf("\n%s",clave);
		if(strcmp(correo,USUARIO)==0 && strcmp(clave,CLAVE)==0){
			ingresa =1;
			break;
		}
		if(ingresa==0){
			printf("\n\tCorreo y/o clave incorrectos\n");
			intento++;
			getchar();
		}
	}while(intento<INTENTOS && ingresa==0  ) ;
	if(ingresa==1){
		printf("\n\tBienvenido al Sistema!");
		printf("\n\tOprima cualquier tecla para continuar.");
		getchar();
		menuAdmin();
	}else {
		printf("\n\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
	}
}
void salir(){
	printf("\n\tPrograma Finalizado\n\n");
}
int validarClave(char *clave){
	int i=0,tamClave=0,num=0,letras=0;
	tamClave=strlen(clave);
	
	if(tamClave>=8){
		for(i=0;i<tamClave;i++){
			if(isdigit(clave[i])!=0){
				num++;
			}
			 if(isalpha(clave[i])!=0){
				letras++;
			}
		}
		if(num!=0 && letras!=0){
				return 1;
		}
	}
	return 0;
}

int validarCadena(char *cadena){
	int i=0,r=1,tamaCadena;		
	tamaCadena=strlen(cadena);
	if(tamaCadena==0 || tamaCadena<8){
		r=0;
	}else{
		while(i<tamaCadena && r==1){
			if((cadena[i]>64 && cadena[i]<91) || (cadena[i]>96 && cadena[i]<123) || (cadena[i]>163 && cadena[i]<166) || cadena[i]==' '){
				i++; 
			}else{
				r=0;
			}
		}
	}
	return r;
}

int validarCedula(char *cedula){
	int tamaCedu=0;
	tamaCedu=strlen(cedula);
	if(tamaCedu>=8 && tamaCedu<=11){
		if(validarNumeros(cedula)==1){
			return 1;
		}else{
			return 0;
		}
	}
	return 0;
}

int validarNumeros(char *numero){
	int i,r=1;
	while(i<strlen(numero) && r==1){
		if(numero[i]>=48 && numero[i]<=57){
			i++;
		}else{
			r=0;
		}
	}
	return r;
}

int validarCedulaRepetida(char *cedula){
	for(i=0;i<contUsuarios;i++){
		if(usuarios[i].cedula==atoi(cedula)){
			return 0;
		}else{
			return 1;
		}
	}
	return 1;
}

int validarCorreo(char *correo){
	
    int     i;
    char    *pos1, *pos2;
    char    *ch = correo;

    while (1) {
    	
        for (i = 0, ch = correo; *ch; *ch++) {
                if (*ch == '@') {
                    pos1 = ch;  // <--almacena la última dirección @
                    i++;
                }
            }
            pos2 = ch;          // Guarda la dirección final ("\0") de la prueba

        /* Si sólo hay una "@"*/
        if (i == 1) {

            /* Pos1 - test <-un carácter debe estar antes de "@". Ch - pos1 <-Cuenta
             * hacia atrás desde el final de la cadena hacia "@". Un carácter
             * debe estar entre "@" y "." */
            while (pos1 - correo && ch - pos1 > 1) {

                /*Desde el final de la cadena hasta "." tiene que haber al menos 2 caracteres */
                if ((pos2 - ch) > 2 && *ch == '.') {
                    return 1;
                }
                ch--;
            }
        }
        system("cls");
        puts("El correo electronico es incorrecto. Introduzca de nuevo:"); // se usa para escribir una secuencia de caracteres al flujo de salida estándar
        scanf("%39s", correo);
    }
    return 1;
}

int validaCorreoRepetido(char *correo){
	for(i=0;i<contUsuarios;i++){
		if(strcmp(usuarios[i].correo,correo)==0){
			return 1;
		}else{
			return 0;
		}
	}
	return 0;
}

int generadorNumCuenta(){
	int numCuenta;
	srand(time(NULL));
	numCuenta=1000000000+rand()%1000000000;
	return numCuenta;
}

void menuUsuario(int y){
	char op;
	do{
		system("cls");
		printf("\n\tBienvenido(a) %s\n",usuarios[y].nombre);
		printf("\n\n\t\t\tMENU USUARIO\n");
		printf("\n1.Retirar");
		printf("\n2.Depositar");
		printf("\n3.Transferir");
		printf("\n4.Detalles");
		printf("\n5.Salir");
		fflush(stdin);
		printf("\n\tElige una opcion: ");
		scanf("%c",&op);
		switch(op){
			case '1':
				retirar(y);
				break;
			case '2':
				depositar(y);
				break;
			case '3':
				transferir(y);
				break;
			case '4':
				detallesUsuario(y);
				break;
			case '5':
				break;
			default:
				printf("\n\tOpcion incorrecta!\n");
		}
	}while(op!=53);
}

void menuAdmin(){
	char op;
	do{
		system("cls");
		printf("\n\n\t\tMENU ADMINISTRADOR\n");
		printf("\n1.Listar usuarios");
		printf("\n2.Inhabilitar/Habilitar usuarios");
		printf("\n3.Salir");
		printf("\n\tElige una opcion: ");
		scanf("%c",&op);
		switch(op){
			case '1':
				listarUsuarios();
				break;
			case '2':
				habilitarOInhabilitar();
				break;
			case '3':
				system("cls");
				break;
			default:
				printf("\n\tOpcion incorrecta");
		}
	}while(op!=51);
}

void retirar(int y){
	int op2=0;
	system("cls");
	printf("\nNumero Cuenta: %d\nNombre: %s\n",usuarios[y].numeroCuenta,usuarios[y].nombre);
	printf("\n\n\t\tRETIRAR\n");
	printf("\n%s, su saldo actual es: $%.2f",usuarios[y].nombre,usuarios[y].saldo);
	while(1){
		printf("\nIngrese el valor a retirar: $");
		scanf("%f",&saldo);
		printf("\nConfirme si el valor a retirar es: $%.2f\n 1.Si\n 2.No\n 3.Cancelar\n\n Seleccione una opcion --> ",saldo);
		scanf("%d",&op2);
		if(op2==1){
			break;
		}else if(op2==3){
			break;
		}else{
			printf("\nIntente nuevamente");
		}
	}
	getchar();
	if(saldo>usuarios[y].saldo){
		printf("\nSaldo insuficiente");
		printf("\nOprima cualquier tecla para regresar al menu principal --> ");
		getchar();
	}else{
		if(op2==1){
			usuarios[y].saldo-=saldo;
			printf("\n%s, su nuevo saldo es: $%.2f",usuarios[y].nombre,usuarios[y].saldo);
			printf("\nOprima cualquier tecla para regresar al menu principal --> ");
			getchar();
		}else{
			printf("\nOperacion anulada.");
			printf("\nOprima una tecla para continuar\n");
			getchar();
		}
	}
	system("cls");
}

void depositar(int y){
	int op2=0;
	system("cls");
	printf("\nNumero Cuenta: %d\nNombre: %s\n",usuarios[y].numeroCuenta,usuarios[y].nombre);
	printf("\n\n\t\tDEPOSITAR\n");
	printf("\n%s, su saldo actual es: $%.2f",usuarios[y].nombre,usuarios[y].saldo);
	do{
		printf("\nIngrese el valor a depositar: $");
		scanf("%f",&saldo);
		printf("\nConfirme si el valor a depositar es: $%.2f\n\t[1].Si\n\t[2].No\nElige una opcion ",saldo);
		scanf("%d",&op2);
		getchar();
	}while(op2!=1);
	usuarios[y].saldo+=saldo;
	printf("\n%s, su nuevo saldo es: $%.2f",usuarios[y].nombre,usuarios[y].saldo);
	printf("\nOprima una tecla para volver al menu");
	getchar();
}

void transferir(int y){
	int op2=0;
	int op3=0;
	system("cls");
	printf("\nNumero Cuenta: %d\nNombre: %s\n",usuarios[y].numeroCuenta,usuarios[y].nombre);
	printf("\n\n\t\tTRANSFERIR");
	printf("\n%s, su saldo actual es: $%.2f",usuarios[y].nombre,usuarios[y].saldo);
	do{
		printf("\nIngrese el numero de cuenta a tranferir: ");
		scanf("%d",&cuenta);
		if(cuenta!=usuarios[y].numeroCuenta){
			if(validarCuentaExistente(cuenta)==1 && validarEstado(cuenta)==1){
				printf("\nIngrese el valor a transferir: ");
				scanf("%f",&saldo);
				printf("\nConfirme si el valor a transferir es: $%.2f\n\t[1].Si\n\t[2].No\n\tElige una opcion ",saldo);
				
				scanf("%d",&op2);
			}else{
				printf("\ncuenta: %d\n Numero de cuenta incorrecta!\n intentelo de nuevo.",cuenta);
				printf("\nDesea salir:\n\t[1].Si\n\t[2].No\n\tElige una opcion ");
				scanf("%d",&op3);
				if(op3==1){
					break;
				}
			}
		}else{
			printf("\nError!, es su misma cuenta\nintente nuevamente");
		}
		getchar();
	}while(op2!=1);
	if(saldo>usuarios[y].saldo){
		printf("\nError!, Saldo insuficiente.");
		getchar();
	}else{
		usuarios[y].saldo-=saldo;
	for(i=0;i<contUsuarios;i++){
			if(cuenta==usuarios[i].numeroCuenta){
				usuarios[i].saldo+=saldo;
			}
		}
		printf("\nSu nuevo saldo es: %.2f",usuarios[y].saldo);
		getchar();
	}
}

int validarCuentaExistente(int cuenta){
	for(i=0;i<contUsuarios;i++){
		if(cuenta==usuarios[i].numeroCuenta){
			return 1;
		}
	}
	return 0;
}

void detallesUsuario(int y){
	system("cls");
	printf("\nNumero Cuenta: %d\nNombre: %s\n\t",usuarios[y].numeroCuenta,usuarios[y].nombre);
	printf("\n\n\t\t DETALLES\n");
	printf("\nNumero de cuenta: %d",usuarios[y].numeroCuenta);
	printf("\nNombre: %s",usuarios[y].nombre);
	printf("\nCedula: %i",usuarios[y].cedula);
	printf("\nCorreo: %s",usuarios[y].correo);
	printf("\nClave: ###########");
	printf("\nSaldo: %.2f",usuarios[y].saldo);
	printf("\nOprima una tecla para continuar");
	getchar();
	getchar();
	
}

void listarUsuarios(){
	system("cls");
	printf("\n\n\t\tLISTA USUARIOS\n");
	if(usuarios[0].numeroCuenta==NULL){
		printf("\n\tNo hay usuarios");
		getchar();
	}else{
		for(i=0;i<contUsuarios;i++){	
			printf("\nNombre: %s\nCorreo: %s\nClave: %s\nNumero cuenta: %d\nSaldo: %.2f\nEstado: %d",usuarios[i].nombre,usuarios[i].correo,usuarios[i].clave,usuarios[i].numeroCuenta,usuarios[i].saldo,usuarios[i].estado);
		}
		getchar();
	}
	printf("\nOprima una tecla para continuar");
	getchar();
}


void habilitarOInhabilitar(){
	int op=0;
	system("cls");
	printf("\n\n\tINHABILITAR / HABILITAR");
	printf("\nIngrese el numero de cuenta : ");
	scanf("%d",&cuenta);
	if(validarCuentaExistente(cuenta)==1){
		for(i=0;i<contUsuarios;i++){
			if(cuenta==usuarios[i].numeroCuenta){
				printf("\nOpciones:\n[1].Inhabilitar\n[2].Habilitar\nElige una opcion: ");
				getchar();
				scanf("%d",&op)	;
				if(op==1){
					usuarios[i].estado=0;
					printf("\nUsuario con numero de cuenta %d esta Inhabilitado: %d",usuarios[i].numeroCuenta,usuarios[i].estado);
					printf("\nOprima una tecla para continuar ");
					getchar();
				}else if(op==2){
					usuarios[i].estado=1;
					printf("\nUsuario con numero de cuenta %d esta Habilitado: %d",usuarios[i].numeroCuenta,usuarios[i].estado);
					printf("\nOprima una tecla para continuar ");
					getchar();
				}else{
					printf("\nOpcion incorrecta");
					getchar();
				}		
			}
		}
	}else{
		printf("\nError!, la cuenta no existe\nOprima una tecla para continuar ");
		getchar();
	}
	getchar();
}

int validarEstado(int cuenta){
	for(i=0;i<contUsuarios;i++){
		if(usuarios[i].numeroCuenta==cuenta){
			if(usuarios[i].estado==1){
				return 1;
			}
		}
	}
	return 0;
}
char* validarLetras(){

	char* cadena; 	
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
