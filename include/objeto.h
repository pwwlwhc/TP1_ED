#ifndef OBJETO_H
#define OBJETO_H

#define MAX_SEGMENTOS 10

typedef struct
{
    int id;
    double x;
    double y;
    double largura;
    double inicio;
    double fim;
} objeto_t;

typedef struct
{
    double inicio;
    double fim;
} segmento_t;

// função que cria o objeto
objeto_t cria_objeto(int id, double x, double y, double largura);

// função que atualiza a posição do objeto com o tempo
void atualiza_pos_obj(objeto_t *obj, double novo_x, double novo_y);

// função que ordena os objeto com base no eixo Y
void ordena_por_y(objeto_t *vobj, int numobj);

// função que retorna segmentos visíveis
int objeto_visivel(objeto_t obj, objeto_t *visiveis, int num_visiveis, segmento_t *segmentos);

#endif