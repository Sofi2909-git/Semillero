#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

struct pedido {
	
	char nombreProducto[30];
	int precioUnidad;
	int vecesPedido;
	int subtotal;
	
}pedidosActuales[10]={{" ",0,0,0},{" ",0,0,0},{" ",0,0,0},{" ",0,0,0},{" ",0,0,0},{" ",0,0,0},{" ",0,0,0},{" ",0,0,0},{" ",0,0,0},{" ",0,0,0}};

struct plato{
	
	int id;
	char nombre[30];
	int precio;
	
} platosEntrada[4]={{1,"Tiraditos de atun",10000},{2,"Hongos al ajillo",12000},{3,"Sopes de filete",15000},{4,"Croquetas de pollo",30000}},						
  platosFuerte[4]={ {1,"Pulpo a la parrillla",50000},{2,"Salmon con arroz verde",55000},{3,"Camarones al ajillo",60000},{4,"Pollo en crema",35000}},
  platosPostre[4]={ {1,"Pye de maracuya",2500},{2,"Tiramisu",3000},{3,"Torta tres leches",1000},{4,"Quesillo",2000}},				  
  platosBebidas[4]={{1,"Cafe negro",1000},{2,"Limonada",2500},{3,"Gaseosa personal",3000},{4,"Agua",2000}};
;

struct USUARIO{
	
	char usuario[11];
	char password[5];
	
}UsuarioAdmin= {"88229967","2002"};


char* validarN();
char* claveValida(char* claveI);
void menuUsuario();
int buscarPossLibre();
void mostrarPlatos(int seleccion);
void agregarAPedido(int posProducto,int tipo);
int buscarPossLibre();
int verificarPedidoExistente(char* producto);
int eleccionMenu();
void mostrarPedidoActual();
 
int main (){
	
	char *username;
	char* clave;
	
	username = (char *)malloc(5); 
	clave = (char *)malloc(5); 
	while(1){
		printf("\n\t\tBIENVENIDO AL RESTAURANTE 'MIL DELICIAS'\n\n");
		printf("\n\tInicie Sesion\n");
		printf("\n\tUsuario: ");
		username=validarN();
		printf("\n\tClave: ");
		claveValida(clave);
		int respUsuario= validarUsuario(username,clave);
		
		if(respUsuario==1){	
			break;
		}
		else{
			system("cls");
			printf("\nDatos de login incorrectos");
		}
	}
	menuUsuario();
	return 0;
}
void menuUsuario(){
	
	system("cls");	
	int opcion;
	
	printf("\n\tBienvenido");
	
	while(1){
		printf("\n\n1.Plato de Entrada\n2.Plato Fuerte\n3.Postre\n4.Bebidas\n5.Generar Factura\n\tElige una opcion: ");
		scanf("%d",&opcion);
		
		switch(opcion){
		case 1:
			mostrarPlatos(opcion);
			break;
		case 2 :
			mostrarPlatos(opcion);
			break;
		case 3 :
			mostrarPlatos(opcion);
			break;
		case 4 : 
			mostrarPlatos(opcion);
			break;
			
		case 5 :		
			if(strcmp(pedidosActuales[0].nombreProducto," ")==0){
				system("cls");
				printf("\n\tAntes de la facturacion debe ordenar algo");
			}else{
				mostrarPedidoActual();
			break;
			}			
		}
	}
}
void mostrarPlatos(int seleccion){
	
	system("cls");
	
	int item, i;
	int seleccionPlato;
	
	switch(seleccion){
		case 1:
			printf("\nPlatos de entrada");
			for(i=0;i<4;i++){
					printf("\n[%d].%s %d",i+1,platosEntrada[i].nombre,platosEntrada[i].precio);
			}		
			break;
		case 2:
			printf("\n\tPlatos fuertes");
			for(i=0;i<4;i++){
					printf("\n[%d].%s %d",i+1, platosFuerte[i].nombre,platosFuerte[i].precio);
			}		
			break;
		case 3 :
			printf("\nPostres");
			for(i=0;i<4;i++){
					printf("\n[%d].%s %d",i+1,platosPostre[i].nombre,platosPostre[i].precio);
			}		
			break;
		case 4: 
			printf("\nBebidas");
			for(i=0;i<4;i++){
					printf("\n[%d].%s %d",i+1,platosBebidas[i].nombre,platosBebidas[i].precio);
			}		
			break;
	}
	printf("\nSeleccione un plato: ");
	scanf("%d",&seleccionPlato);
	agregarAPedido(seleccionPlato,seleccion);
	
	int confirmar;
	printf("\nDesea Seguir ordenando algo del menu\n\n1.Si\n2.No\nElige una opcion: ");
	scanf("%d",&confirmar);
	
	if(confirmar==1){
		menuUsuario();	
	}else{
		mostrarPedidoActual();
	}

}
void agregarAPedido(int posProducto,int tipo){
	
	posProducto-=1;
	int pos= buscarPossLibre();
	int existeEnPedido;
	
	if(tipo==1){
		existeEnPedido=verificarPedidoExistente(platosEntrada[posProducto].nombre);
		if(existeEnPedido!=0){
			pedidosActuales[existeEnPedido].vecesPedido+=1;
			pedidosActuales[existeEnPedido].subtotal+=platosEntrada[posProducto].precio;	
		}
		else{
			strcpy(pedidosActuales[pos].nombreProducto,platosEntrada[posProducto].nombre);
			pedidosActuales[pos].vecesPedido+=1;
			pedidosActuales[pos].precioUnidad=platosEntrada[posProducto].precio;	
			pedidosActuales[pos].subtotal+=platosEntrada[posProducto].precio;	

		}
	}
	if(tipo==2){
		existeEnPedido=verificarPedidoExistente(platosFuerte[posProducto].nombre);
			if(existeEnPedido!=0){
			pedidosActuales[existeEnPedido].vecesPedido+=1;
			pedidosActuales[existeEnPedido].subtotal+=platosFuerte[posProducto].precio;	
			}
		else{
			strcpy(pedidosActuales[pos].nombreProducto,platosFuerte[posProducto].nombre);
			pedidosActuales[pos].vecesPedido+=1;
			pedidosActuales[pos].precioUnidad=platosFuerte[posProducto].precio;
			pedidosActuales[pos].subtotal+=platosFuerte[posProducto].precio;
		}		
	}
	
	if(tipo==3){		
		existeEnPedido=verificarPedidoExistente(platosPostre[posProducto].nombre);
		if(existeEnPedido!=0){
			pedidosActuales[existeEnPedido].vecesPedido+=1;
			pedidosActuales[existeEnPedido].subtotal+=platosPostre[posProducto].precio;	
		}
		else{
			strcpy(pedidosActuales[pos].nombreProducto,platosPostre[posProducto].nombre);
			pedidosActuales[pos].vecesPedido+=1;
			pedidosActuales[pos].precioUnidad=platosPostre[posProducto].precio;
			pedidosActuales[pos].subtotal+=platosPostre[posProducto].precio;
		}
	}
	
	if(tipo==4){
		existeEnPedido=verificarPedidoExistente(platosBebidas[posProducto].nombre);
		if(existeEnPedido!=0){
			pedidosActuales[existeEnPedido].vecesPedido+=1;
			pedidosActuales[existeEnPedido].subtotal+=platosBebidas[posProducto].precio;	
		}
		else{
			strcpy(pedidosActuales[pos].nombreProducto,platosBebidas[posProducto].nombre);
			pedidosActuales[pos].vecesPedido+=1;
			pedidosActuales[pos].precioUnidad=platosBebidas[posProducto].precio;
			pedidosActuales[pos].subtotal+=platosBebidas[posProducto].precio;
		}	
	}	
}
void mostrarPedidoActual(){
	
	system("cls");
	int totalPedido,i;
	int opcion;
	
	printf("\n\t\tFACTURA\n");
	printf("\nCantidad Producto\t\tPrecio Subtotal");		
	for(i=0;i<10;i++){
		if(strcmp(pedidosActuales[i].nombreProducto," ")!=0){
			totalPedido+=pedidosActuales[i].subtotal;
		printf("\n%d %s \t\t%d \t%d ",pedidosActuales[i].vecesPedido,pedidosActuales[i].nombreProducto,pedidosActuales[i].precioUnidad,pedidosActuales[i].subtotal);		
		}
	}
	printf("\n\t\t\t\tTotal a pagar: $%d",totalPedido);
    eleccionMenu();
}
int eleccionMenu(){
	
	int accion=	accionMenu();
	switch(accion){
		case 0:
			return 0;
			break;
		case 1 :			
			return 1;
			break;
	}	
}
int accionMenu(){
	
	int valor=0;
	int opcion;
	
	printf("\n1.Menu principal\n2.Salir el programa\n\tElige una opcion: ");
	scanf("%d",&opcion);
	if(opcion==1){	
		system("cls");
		valor=1;
		main();
	}
	else
	 if(opcion==2){
		system("cls");
		valor=0;
	}
	return valor;
}
int buscarPossLibre(){
	int pos, i;
	for(i=0;i<20;i++){
		if(strcmp(pedidosActuales[i].nombreProducto," ")==0 ){
			pos=i;
			break;
		}
	}
	return pos;
}
int verificarPedidoExistente(char* producto){
	int pos=0, i;
	for(i=0;i<10;i++){
		if(strcmp(pedidosActuales[i].nombreProducto,producto)==0){
			pos=i;
			break;
		}
	}
	return pos;
}
char* validarN(){

	char* cadena; 		// Aqui se iran guardando todos los caracteres
	char caracter;		// Aqui recogemos caracter a caracter
	int contador = 0;
	cadena = (char *)malloc(20); // malloc: para solicitar un bloque de memoria del tamaño suministrado como parámetro. Devuelve un puntero a la zona de memoria concedida 
	while(1){
		
		caracter = getch();
		
		if(caracter == '\r' && contador<10){
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
char* claveValida(char* claveI){ // Aqui se iran guardando todos los caracteres

	char caracter;		// Aqui recogemos caracter a caracter
	int contador = 0;
	
	while(1){
		
		caracter = getch();
		
		if(caracter == '\r' && contador==4){
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
			if((caracter>=48 && caracter<=57) && contador<4 ){
				putchar('*');
				claveI[contador] = caracter;
				claveI[contador + 1] = '\0';
				contador++;
			}
		}
	}
	
	return claveI;
}
int validarUsuario(char* usuario, char* clave){
	
	int valor=0;
	int lenUsuario=strlen(usuario);
	
	if(lenUsuario>3 && lenUsuario<11 && strcmp(usuario,UsuarioAdmin.usuario)==0 && strcmp(clave, UsuarioAdmin.password)==0){
		valor=1;
	}
	return valor;
}

