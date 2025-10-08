#include <stdio.h>
#include "objeto.h"
#include "cena.h"

objeto_t cria_objeto(int id, double x, double y, double largura)
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

void atualiza_pos_obj(objeto_t *obj, double novo_x, double novo_y)
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

int objeto_visivel(objeto_t obj, objeto_t *visiveis, int num_visiveis, segmento_t *segmentos)
{
    segmento_t segmentos_temp[MAX_SEGMENTOS];
    int num_segmentos = 1;
    segmentos_temp[0].inicio = obj.inicio;
    segmentos_temp[0].fim = obj.fim;

    for (int i = 0; i < num_visiveis; i++)
    {
        objeto_t frente = visiveis[i];
        
        for (int j = 0; j < num_segmentos; j++)
        {
            // pula se não tem sobreposição
            if (segmentos_temp[j].fim <= frente.inicio || segmentos_temp[j].inicio >= frente.fim) {
                continue;
            }

            // segmento totalmente tampado
            if (frente.inicio <= segmentos_temp[j].inicio && frente.fim >= segmentos_temp[j].fim) {
                // remove esse segmento
                for (int k = j; k < num_segmentos - 1; k++) {
                    segmentos_temp[k] = segmentos_temp[k + 1];
                }
                num_segmentos--;
                j--;
                continue;
            }

            // inicio sendo tampado
            if (frente.inicio <= segmentos_temp[j].inicio && frente.fim > segmentos_temp[j].inicio && frente.fim < segmentos_temp[j].fim) {
                segmentos_temp[j].inicio = frente.fim;
            }
            // final sendo tampado
            else if (frente.fim >= segmentos_temp[j].fim && frente.inicio > segmentos_temp[j].inicio && frente.inicio < segmentos_temp[j].fim) {
                segmentos_temp[j].fim = frente.inicio;
            }
            // meio sendo tampado -> divide em dois segmentos
            else if (frente.inicio > segmentos_temp[j].inicio && frente.fim < segmentos_temp[j].fim) {
                if (num_segmentos < MAX_SEGMENTOS) {
                    // cria novo segmento para a parte direita
                    segmentos_temp[num_segmentos].inicio = frente.fim;
                    segmentos_temp[num_segmentos].fim = segmentos_temp[j].fim;
                    num_segmentos++;
                    
                    // atualiza segmento atual para a parte esquerda
                    segmentos_temp[j].fim = frente.inicio;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < num_segmentos; i++) {
    segmentos[i] = segmentos_temp[i];
    }
    return num_segmentos;
}