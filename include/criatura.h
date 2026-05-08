#include <stdint.h>

#ifndef CRIATURA_H
#define CRIATURA_H

#define MAXIMO_CRIATURAS 64

typedef struct {
    uint16_t x;
    uint16_t y;
} posicao_t;

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} cor_t;

typedef struct{
    posicao_t posicao;
    cor_t cor;
    uint16_t indice_proximo;
} criatura_t;

typedef struct{
    criatura_t criaturas[MAXIMO_CRIATURAS];
    uint16_t pilha[MAXIMO_CRIATURAS];
    uint16_t i_criatura_inicial;
    uint16_t i_topo;
    cor_t cor;
} contexto_t;

void processar();

contexto_t *iniciar_criaturas();

void finalizar_criaturas(contexto_t contexto);

#endif
