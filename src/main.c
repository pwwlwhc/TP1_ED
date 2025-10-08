#include <stdio.h>
#include "objeto.h"
#include "cena.h"

void geraCena(objeto_t *vobj, int numobj, cena_t *cena)
{
    // cria cópia do objeto
        objeto_t objetos_ordenados[100];
    for (int i = 0; i < numobj; i++) {
        objetos_ordenados[i] = vobj[i];
    }
    ordena_por_y(objetos_ordenados, numobj);
    
    for (int i = 0; i < numobj; i++)
    {
        segmento_t segmentos[MAX_SEGMENTOS];
        int num_segmentos = objeto_visivel(objetos_ordenados[i], cena->visiveis, cena->num_visiveis, segmentos);
        
        for (int j = 0; j < num_segmentos; j++) {
            if (segmentos[j].inicio < segmentos[j].fim) {
                objeto_t obj_visivel = objetos_ordenados[i]; // Mantém ID correto
                obj_visivel.inicio = segmentos[j].inicio;
                obj_visivel.fim = segmentos[j].fim;
                adiciona_obj(obj_visivel, cena);
            }
        }
    }
}

int main()
{
    char tipo;
    int id, tempo;
    double x, y, largura;

    objeto_t objetos[100];
    int num_objetos = 0;

    while (scanf(" %c", &tipo) != EOF)
    {
        if (tipo == 'O') // define novo objeto
        {
            scanf("%d %lf %lf %lf", &id, &x, &y, &largura);
            objetos[num_objetos++] = cria_objeto(id, x, y, largura);
        }
        else if (tipo == 'M') // movimento
        {
            scanf("%d %d %lf %lf", &tempo, &id, &x, &y);
            for (int i = 0; i < num_objetos; i++) {
                if (objetos[i].id == id) {
                    atualiza_pos_obj(&objetos[i], x, y);
                    break;
                }
            }
        }
        else if (tipo == 'C') // geração de cena
        {
            scanf("%d", &tempo);
            cena_t cena = cria_cena(tempo);
            geraCena(objetos, num_objetos, &cena);
            grava_cena(cena, stdout);
        }
    }
    return 0;
}