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

void imprimir_c(void);

#endif
