#include "algoritmo_de_cifrado.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "strings_lib.h"

bool includes_char(char* string, char character){

    for(int i = 0; i < strlen(string); i++){
        if(string[i] == character){
            return true;
        }
    }
    return false;
}

void remove_char(char* string, char character){

    for(int index_to_delete = 0; index_to_delete < strlen(string); index_to_delete++){
        if(string[index_to_delete] == character){
            strcpy(&string[index_to_delete], &string[index_to_delete + 1]);
        }
    }
}

char* alfabeto_sin_caracteres_de(char* clave){
    char* alfabeto = string_duplicate("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    for (int i = 0; i < strlen(clave); i++){
        remove_char(alfabeto, clave[i]);
    }

    return alfabeto;
}

char* generar_alfabeto_con_clave(char* clave){

    char* alfabeto_cifrado = string_new();
    string_append(&alfabeto_cifrado, clave);

    char* alfabeto_reducido = alfabeto_sin_caracteres_de(clave);
    string_append(&alfabeto_cifrado, alfabeto_reducido);

    return alfabeto_cifrado;
}

char** split(char* string_to_split, int cantidad_de_caracteres_a_separar){

    char** string_splitteado = malloc(cantidad_de_caracteres_a_separar * sizeof(char*));

    int indice_a_splittear = 0;
    int posible_indice = indice_a_splittear + cantidad_de_caracteres_a_separar;


    for(int i = 0; posible_indice < strlen(string_to_split); i++){
        string_splitteado[i] = calloc(1, sizeof(char*));
        char* caracteres;

        if((posible_indice + cantidad_de_caracteres_a_separar) > strlen(string_to_split)){
            caracteres = string_substring_from(string_to_split, indice_a_splittear);
        }
        else {
            caracteres = string_substring(string_to_split, indice_a_splittear, cantidad_de_caracteres_a_separar);
        }

        string_append(&string_splitteado[i], caracteres);
        indice_a_splittear += cantidad_de_caracteres_a_separar;
        posible_indice = indice_a_splittear + cantidad_de_caracteres_a_separar;
    }

    return string_splitteado;
}

NodoDigito* cargar_grupos(char* alfabeto_con_clave, int cabecera){
    char* cabecera_en_string = string_itoa(cabecera);
    int cantidad_de_caracteres_de_cabecera = strlen(cabecera_en_string);
    char** alfabeto_splitteado = split(alfabeto_con_clave, cantidad_de_caracteres_de_cabecera);

    NodoDigito* nodo_digitos = NULL;

    for (int i = 0; i < cantidad_de_caracteres_de_cabecera; i++) {
        NodoDigito* nuevo_nodo = malloc(sizeof(NodoDigito*));

        nuevo_nodo -> numero_de_grupo = cabecera_en_string[i] - '0';
        nuevo_nodo -> caracteres = string_duplicate(alfabeto_splitteado[i]);
        nuevo_nodo -> siguiente_nodo_digito = NULL;

        if (nodo_digitos == NULL){
            nodo_digitos = nuevo_nodo;
        } else{
            NodoDigito* nodo_digito_auxiliar = nodo_digitos;
            while (nodo_digito_auxiliar -> siguiente_nodo_digito != NULL){
                nodo_digito_auxiliar = nodo_digito_auxiliar -> siguiente_nodo_digito;
            }
            nodo_digito_auxiliar -> siguiente_nodo_digito = nuevo_nodo;
        }
    }

    return nodo_digitos;
}

NodoDigito* cargar_caracteres(char* clave, int cabecera){

    char* alfabeto_con_clave = generar_alfabeto_con_clave(clave);
    return cargar_grupos(alfabeto_con_clave, cabecera);
}

NodoDigito* nodo_digito_para(char caracter_a_cifrar, NodoDigito* algoritmo_de_cifrado){

    NodoDigito* nodo_digito_auxiliar = algoritmo_de_cifrado;
    NodoDigito* nodo_digito_encontrado = NULL;

    while (nodo_digito_auxiliar && nodo_digito_encontrado == NULL){

        if(includes_char(nodo_digito_auxiliar -> caracteres, caracter_a_cifrar)){
            nodo_digito_encontrado = nodo_digito_auxiliar;
        }else{
            nodo_digito_auxiliar = nodo_digito_auxiliar -> siguiente_nodo_digito;
        }
    }

    return nodo_digito_encontrado;
}

int numero_asignado_para(char caracter_a_cifrar, NodoDigito* nodo_digito){
    char* caracteres = nodo_digito -> caracteres;
    bool encontrado = false;
    int indice;

    for(int i = 0; encontrado == false; i++){
        if(caracteres[i] == caracter_a_cifrar){
            indice = i + 1; // sumamos uno porque la base del índice es 1
            encontrado = true;
        }
    }

    return indice;
}

char* encriptar(char* palabra_a_cifrar, NodoDigito* algoritmo_de_cifrado){

    char* palabra_encriptada = string_new();

    for (int i = 0; i < strlen(palabra_a_cifrar); i++) {
        char caracter_a_cifrar = palabra_a_cifrar[i];

        NodoDigito* nodo_digito = nodo_digito_para(caracter_a_cifrar, algoritmo_de_cifrado);
        int numero_asignado = numero_asignado_para(caracter_a_cifrar, nodo_digito);

        string_append(&palabra_encriptada, "(");
        string_append(&palabra_encriptada, string_itoa(nodo_digito->numero_de_grupo));
        string_append(&palabra_encriptada, ",");
        string_append(&palabra_encriptada, string_itoa(numero_asignado));
        string_append(&palabra_encriptada, ")");

        int siguiente_indice = i + 1;
        if(siguiente_indice < strlen(palabra_a_cifrar)){
            string_append(&palabra_encriptada, ",");
        }
    }

    return palabra_encriptada;
}