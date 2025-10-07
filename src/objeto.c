#include <stdio.h>
#include "objeto.h"
#include "cena.h"

objeto_t cria_objeto(int id, float x, float y, float largura)
{
    objeto_t obj;
    obj.id = id;
    obj.x = x;
    obj.y = y;
    obj.largura = largura;
    obj.inicio = x - largura / 2.0;
    obj.fim = x + largura / 2.0;
    return obj;
}

void atualiza_pos_obj(objeto_t *obj, float novo_x, float novo_y)
{
    obj->x = novo_x;
    obj->y = novo_y;
    obj->inicio = novo_x - obj->largura / 2.0;
    obj->fim = novo_x + obj->largura / 2.0;
}

// bubble sort para ordenar os objetos no eixo y
void ordena_por_y(objeto_t *vobj, int numobj)
{
    for (int i = 0; i < numobj - 1; i++)
    {
        for (int j = 0; j < numobj - i - 1; j++)
        {
            if (vobj[j].y > vobj[j + 1].y)
            {
                objeto_t temp = vobj[j];
                vobj[j] = vobj[j + 1];
                vobj[j + 1] = temp;
            }
        }
    }
}

int objeto_visivel(objeto_t obj, objeto_t *visiveis, int num_visiveis, float *inicio_visivel, float *fim_visivel)
{
    *inicio_visivel = obj.inicio;
    *fim_visivel = obj.fim;

    if (num_visiveis == 0) {
        return 1;
    }

    for (int i = 0; i < num_visiveis; i++)
    {
        objeto_t frente = visiveis[i];

        //pula se não tem sobreposição em x
        if (obj.fim <= frente.inicio || obj.inicio >= frente.fim){
            continue;
        }

        //objeto totalmente tampado
        if (frente.inicio <= *inicio_visivel && frente.fim >= *fim_visivel){
            return 0;
        }

        //inicio sendo tampado
        if (frente.inicio <= *inicio_visivel && frente.fim > *inicio_visivel && frente.fim < *fim_visivel){
            *inicio_visivel = frente.fim;
        }

        //final sendo tampado
        if (frente.fim >= *fim_visivel && frente.inicio > *inicio_visivel && frente.inicio < *fim_visivel) {
            *fim_visivel = frente.inicio;
        }

        //VERIFICAÇÃO DE SEGURANÇA - evita valores inválidos
        if (*inicio_visivel >= *fim_visivel) {
            return 0;
        }
    }
    return 1;
}
