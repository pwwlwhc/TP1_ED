#ifndef CENA_H
#define CENA_H

#include "objeto.h"

typedef struct
{
    int tempo;              // tempo atual da cena
    objeto_t visiveis[100]; // vetor fixo de objetos visiveis
    int num_visiveis;       // quantidade de objetos visiveis na cena
} cena_t;

// Começa uma cena
cena_t cria_cena(int tempo);

// Adiciona um objeto visivel a cena
void adiciona_obj(objeto_t obj, cena_t *cena);

// grava a cena num arquivo de saída
void grava_cena(cena_t cena, FILE *saida);

#endif