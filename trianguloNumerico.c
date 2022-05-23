#include <stdio.h>

int main() 
{
    int numero; 
    printf("INGRESE UN NUMERO: ");
    scanf("%d", &numero); //Entero numero es lo que la persona coloca en teclado y se guarda en numero
    int filas;
    for (filas = 1; filas <= numero; filas++) //filas (vertical) empieza en 1 mientras sea menor o igual al numero ingresado en teclado
    {
        int cicloDeImpresion ;
        for (cicloDeImpresion = 0; cicloDeImpresion < filas;cicloDeImpresion++) // ciclo de impresio (horizontal) inicia en 0 mientras que sea menor a filas y va sumando 1
        {
            printf("%d ",numero-cicloDeImpresion); // imprimo numero ingresado en teclado disminuyendo segun el ciclo de impresion
        }
        printf("\n");
    }
    return 0;
}
