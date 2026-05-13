#include "grafico.h"

#define TAM_QUADRADO 10
#define TAM_BORDA 2

int vetor_cinza(uint8_t vetor) {
    return (vetor >= 110 && vetor <= 146);
}

cor_t complemento_cor(cor_t cor) {
    cor_t cor_retorno;
    int cinza = vetor_cinza(cor.r) && vetor_cinza(cor.g) && vetor_cinza(cor.b);
    if (cinza) {
        cor_retorno.r = 255;
        cor_retorno.g = 255;
        cor_retorno.b = 255;
    } else {
        cor_retorno.r = 255 - cor.r;
        cor_retorno.g = 255 - cor.g;
        cor_retorno.b = 255 - cor.b;
    }
    return cor_retorno;
}

void desenharQuadrado(SDL_Renderer *renderer, criatura_t criatura) {
    int tamanho_borda = TAM_QUADRADO+TAM_BORDA;
    SDL_Rect rect_b = {
        criatura.posicao.x - tamanho_borda/2,
        criatura.posicao.y - tamanho_borda/2,
        tamanho_borda,
        tamanho_borda
    };
    cor_t cor = complemento_cor(criatura.cor);
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
    SDL_RenderFillRect(renderer, &rect_b);

    SDL_Rect rect = {
        criatura.posicao.x - TAM_QUADRADO/2,
        criatura.posicao.y - TAM_QUADRADO/2,
        TAM_QUADRADO,
        TAM_QUADRADO
    };
    cor = criatura.cor;
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

interface_t* inicializar_interface() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Quadrados",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGURA_AMBIENTE,
        ALTURA_AMBIENTE,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    interface_t *interface = malloc(sizeof(interface_t));
    interface->janela = window;
    interface->renderizador = renderer;
    return interface;
}

void atualizar_interface(interface_t *interface, contexto_t *contexto_t) {
    cor_t cor_ambiente = contexto_t->cor;
    SDL_SetRenderDrawColor(
        interface->renderizador,
        cor_ambiente.r,
        cor_ambiente.g,
        cor_ambiente.b,
        255
    );
    SDL_RenderClear(interface->renderizador);
    for (int i = 0; i < MAXIMO_CRIATURAS; i++) {
        desenharQuadrado(interface->renderizador, contexto_t->criaturas[i]);
    }
    SDL_RenderPresent(interface->renderizador);
}

int analizar_eventos() {
    SDL_Event evento;
    int rodando = 1;
    while (SDL_PollEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            rodando = 0;
        }
        if (evento.type == SDL_KEYDOWN) {
            switch (evento.key.keysym.sym) {
                case SDLK_SPACE:
                    rodando = 2;
                    break;
            }
        }
    }
    return rodando;
}

void finalizar_interface(interface_t *interface) {
    SDL_DestroyRenderer(interface->renderizador);
    SDL_DestroyWindow(interface->janela);
    SDL_Quit();
}