#include "criatura.h"
#include "stdio.h"
#include <stdlib.h>

void processar(criatura_t criaturas[], cor_t *cor) {}

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

criatura_t criar_criatura() {
	criatura_t criatura = {
		gerar_cor_aleatoria(),
		gerar_posicao_aleatoria()
	};
	return criatura;
}

criatura_t* gerar_criaturas(uint16_t tamanho) {
	criatura_t *criaturas = malloc(tamanho * sizeof(criatura_t));
	for (int i = 0; i < tamanho; i++) {
		criatura_t criatura = criar_criatura();
		criaturas[i] = criatura;
	}
	return criaturas;
};
