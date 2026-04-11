#include "criatura.h"
#include "stdio.h"
#include <stdlib.h>

posicao_t gerar_posicao_aleatoria() {
	posicao_t posicao = {
		rand()%1000,
		rand()%600
	};
	return posicao;
}

cor_t gerar_cor_aleatoria() {
	cor_t cor = {
		rand()%255,
		rand()%255,
		rand()%255,
	};
	return cor;
}

criatura_t criar_criatura(uint16_t indice_proximo) {
	criatura_t criatura = {
		gerar_posicao_aleatoria(),
		gerar_cor_aleatoria(),
		indice_proximo
	};
	return criatura;
}

uint16_t *tamanho_maximo;
criatura_t *criaturas;
cor_t *cor;
uint16_t *pilha;
uint16_t *i_topo;

void iniciar_criaturas(uint16_t tamanho) {
	tamanho_maximo = malloc(sizeof(uint16_t));
	*tamanho_maximo = tamanho;
	criaturas = malloc(tamanho * sizeof(criatura_t));
	for (int i = 0; i < tamanho; i++) {
		criaturas[i] = criar_criatura(i + 1);
	}
	cor = malloc(sizeof(cor_t));
	*cor = gerar_cor_aleatoria();
	pilha = malloc(tamanho * sizeof(uint16_t));
	i_topo = malloc(sizeof(uint16_t));
	*i_topo = 0;
};

void processar_criaturas() {
	
}

void processar() {
	processar_criaturas();
}

criatura_t* obter_criaturas() {
	return criaturas;
}

cor_t* obter_cor_ambiente() {
	return cor;
}

void finalizar_criaturas() {
	free(criaturas);
	free(pilha);
	free(cor);
	free(tamanho_maximo);
	free(i_topo);
}