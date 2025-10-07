#ifndef OBJETO_H
#define OBJETO_H

typedef struct
{
    int id;        // identificador do objeto
    float x;       // posição no eixo X
    float y;       // posição no eixo Y
    float largura; // largura total do objeto
    float inicio;  // Onde o objeto começa (x - metade da largura)
    float fim;     // Onde o objeto acaba (x + metade da largura)
} objeto_t;

// função que cria o objeto
objeto_t cria_objeto(int id, float x, float y, float largura);

// função que atualiza a posição do objeto com o tempo
void atualiza_pos_obj(objeto_t *obj, float novo_x, float novo_y);

// função que ordena os objeto com base no eixo Y
void ordena_por_y(objeto_t *vobj, int numobj);

// função que retorna se o objeto é visivel ou não
int objeto_visivel(objeto_t obj, objeto_t *visiveis, int num_visiveis, float *inicio_visivel, float *fim_visivel);

#endif