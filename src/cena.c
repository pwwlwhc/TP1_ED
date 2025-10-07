#include <stdio.h>
#include "cena.h"

cena_t cria_cena(int tempo)
{
    cena_t c;
    c.tempo = tempo;
    c.num_visiveis = 0;
    return c;
}

void adiciona_obj(objeto_t obj, cena_t *cena)
{
    cena->visiveis[cena->num_visiveis] = obj;
    cena->num_visiveis++;
}


void grava_cena(cena_t cena, FILE *saida)
{
    // Ordenar visiveis por ID antes de imprimir
    for (int i = 0; i < cena.num_visiveis - 1; i++) {
        for (int j = 0; j < cena.num_visiveis - i - 1; j++) {
            if (cena.visiveis[j].id > cena.visiveis[j + 1].id) {
                objeto_t temp = cena.visiveis[j];
                cena.visiveis[j] = cena.visiveis[j + 1];
                cena.visiveis[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < cena.num_visiveis; i++)
    {
        objeto_t obj = cena.visiveis[i];
        fprintf(saida, "S %d %d %.2f %.2f\n", cena.tempo, obj.id, obj.inicio, obj.fim);
    }
}