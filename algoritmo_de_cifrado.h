#ifndef FINALAYED_VONWEBER_ALGORITMO_DE_CIFRADO_H
#define FINALAYED_VONWEBER_ALGORITMO_DE_CIFRADO_H

typedef struct NodoDigitoStruct{
    int numero_de_grupo;
    char* caracteres;
    struct NodoDigitoStruct* siguiente_nodo_digito;
}NodoDigito;

NodoDigito* cargar_caracteres(char* clave, int cabecera);
char* encriptar(char* palabra_a_cifrar, NodoDigito* algoritmo_de_cifrado);

#endif //FINALAYED_VONWEBER_ALGORITMO_DE_CIFRADO_H
