#ifndef GRAFICO_H
#define GRAFICO_H

#include "criatura.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *janela;
    SDL_Renderer *renderizador;
} interface_t;

interface_t* inicializar_interface();

void atualizar_interface(interface_t *interface, contexto_t *contexto);

void atualizar_titulo_interface(interface_t *interface, unsigned long processamentos_por_segundo);

void finalizar_interface(interface_t *interface);

int analizar_eventos();
#endif
