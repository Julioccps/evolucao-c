#ifndef CRIATURA_H
#define CRIATURA_H

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#define MAXIMO_CRIATURAS 16384
#define ALTURA_AMBIENTE 600
#define LARGURA_AMBIENTE 1000

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
    int8_t r;
    int8_t g;
    int8_t b;
} variacao_t;

typedef struct{
    posicao_t posicao;
    cor_t cor;
    uint8_t vivo;
} criatura_t;

typedef struct{
    criatura_t criaturas[MAXIMO_CRIATURAS];
    uint16_t limite;
    cor_t cor;
} contexto_t;

void processar(contexto_t *contexto);

contexto_t *inicializar_criaturas();

void finalizar_criaturas(contexto_t *contexto);

void gerar_nova_cor_ambiente(contexto_t *contexto);

#endif
