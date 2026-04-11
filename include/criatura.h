#include <stdint.h>

#ifndef CRIATURA_H
#define CRIATURA_H

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

void processar();

void iniciar_criaturas(uint16_t tamanho);

criatura_t* obter_criaturas();

cor_t* obter_cor_ambiente();

void finalizar_criaturas();

#endif
