#ifndef OBJETO_H
#define OBJETO_H

typedef struct
{
    int id;        // identificador do objeto
    double x;       // posição no eixo X
    double y;       // posição no eixo Y
    double largura; // largura total do objeto
    double inicio;  // Onde o objeto começa (x - metade da largura)
    double fim;     // Onde o objeto acaba (x + metade da largura)
} objeto_t;

// função que cria o objeto
objeto_t cria_objeto(int id, double x, double y, double largura);

// função que atualiza a posição do objeto com o tempo
void atualiza_pos_obj(objeto_t *obj, double novo_x, double novo_y);

// função que ordena os objeto com base no eixo Y
void ordena_por_y(objeto_t *vobj, int numobj);

// função que retorna se o objeto é visivel ou não
int objeto_visivel(objeto_t obj, objeto_t *visiveis, int num_visiveis, double *inicio_visivel, double *fim_visivel);

#endif