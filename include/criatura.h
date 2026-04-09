#include <stdint.h>

#ifndef CRIATURA_H
#define CRIATURA_H

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint16_t x;
    uint16_t y;
    uint16_t i_proximo;
} criatura_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} cor_t;

void processar(criatura_t *criaturas, cor_t *cor);

criatura_t* gerar_criaturas(uint16_t tamanho);

#endif
