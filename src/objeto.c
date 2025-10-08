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
    int num_segmentos = 1;
    segmentos[0].inicio = obj.inicio;
    segmentos[0].fim = obj.fim;

    for (int i = 0; i < num_visiveis; i++)
    {
        objeto_t frente = visiveis[i];
        
        for (int j = 0; j < num_segmentos; j++)
        {
            // Pula se não há sobreposição
            if (segmentos[j].fim <= frente.inicio || segmentos[j].inicio >= frente.fim) {
                continue;
            }

            // Segmento totalmente tampado
            if (frente.inicio <= segmentos[j].inicio && frente.fim >= segmentos[j].fim) {
                // Remove este segmento
                for (int k = j; k < num_segmentos - 1; k++) {
                    segmentos[k] = segmentos[k + 1];
                }
                num_segmentos--;
                j--;
                continue;
            }

            // Início sendo tampado
            if (frente.inicio <= segmentos[j].inicio && frente.fim > segmentos[j].inicio && frente.fim < segmentos[j].fim) {
                segmentos[j].inicio = frente.fim;
            }
            // Final sendo tampado
            else if (frente.fim >= segmentos[j].fim && frente.inicio > segmentos[j].inicio && frente.inicio < segmentos[j].fim) {
                segmentos[j].fim = frente.inicio;
            }
            // Meio sendo tampado - divide em dois segmentos
            else if (frente.inicio > segmentos[j].inicio && frente.fim < segmentos[j].fim) {
                if (num_segmentos < MAX_SEGMENTOS) {
                    // Cria novo segmento para a parte direita
                    segmentos[num_segmentos].inicio = frente.fim;
                    segmentos[num_segmentos].fim = segmentos[j].fim;
                    num_segmentos++;
                    
                    // Atualiza segmento atual para a parte esquerda
                    segmentos[j].fim = frente.inicio;
                }
            }
        }
    }
    return num_segmentos;
}