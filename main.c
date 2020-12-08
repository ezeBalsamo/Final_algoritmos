#include <stdio.h>
#include <stdlib.h>
#include "algoritmo_de_cifrado.h"

int main() {

    char* clave = "FRBAUTN";
    int cabecera = 10825;

    NodoDigito* algoritmo_de_cifrado = cargar_caracteres(clave, cabecera);

    char* palabra_a_cifrar = "HURACAN";
    char* palabra_cifrada = encriptar(palabra_a_cifrar, algoritmo_de_cifrado);

    /*
     * (8,2),(1,5),(1,2),(1,4),(0,3),(1,4),(0,2)
     */

    printf("La palabra %s cifrada es %s.", palabra_a_cifrar, palabra_cifrada);

    return EXIT_SUCCESS;
}
