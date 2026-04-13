#include "criatura.h"
#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

double gerar_valor_aleatorio() {
	return (double)rand()/ (double)RAND_MAX;
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
uint16_t *i_criatura_inicial;
cor_t *cor;
uint16_t *pilha;
uint16_t *i_topo;

void iniciar_criaturas(uint16_t tamanho) {
	srand(time(NULL));
	tamanho_maximo = malloc(sizeof(uint16_t));
	*tamanho_maximo = tamanho;
	criaturas = malloc(tamanho * sizeof(criatura_t));
	for (int i = 0; i < tamanho; i++) {
		criaturas[i] = criar_criatura(i + 1);
	}
	i_criatura_inicial = malloc(sizeof(uint16_t));
	*i_criatura_inicial = 0;
	cor = malloc(sizeof(cor_t));
	*cor = gerar_cor_aleatoria();
	pilha = malloc(tamanho * sizeof(uint16_t));
	i_topo = malloc(sizeof(uint16_t));
	*i_topo = 0;
};

double calcular_probabilidade_morte(cor_t cor1, cor_t cor2) {
	double dr = (double)cor1.r - (double)cor2.r;
	double dg = (double)cor1.g - (double)cor2.g;
	double db = (double)cor1.b - (double)cor2.b;

	double distancia = sqrt(dr * dr + dg * dg + db * db);

	return distancia / 441.6729;
}

void remover_criatura(uint16_t i, uint16_t i_anterior) {
	if (i == *i_criatura_inicial) {
		*i_criatura_inicial = criaturas[i].indice_proximo;	
	} else {
		criaturas[i_anterior].indice_proximo = criaturas[i].indice_proximo;
	}
	pilha[*i_topo++] = i;
}

int clamp(int valor, int min, int max) {
	int valor_final;
	if (valor < min) {
		valor_final = min;
	} else {
		if (valor > max) {
			valor_final = max;
		} else {
			valor_final = valor;
		}
	}
	return valor_final;
}

// Já que não posso usar float em valor de cores, vou ter que brincar aqui...
int gerar_valor_aleatorio_gaussiano() {
	int valores[10] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 2};
	int i = rand()%9;
	int valor_aleatorio;
	if (rand()%1) {
		valor_aleatorio = valores[i];
	} else {
		valor_aleatorio = -valores[i];
	}
	return valor_aleatorio;
}

void reproduzir_criatura(criatura_t criatura_pai) {
	cor_t cor_pai = criatura_pai.cor;
	posicao_t posicao_pai = criatura_pai.posicao;
	criatura_t criatura_filho = {
		{
			clamp(posicao_pai.x + gerar_valor_aleatorio_gaussiano(), 0, 1000),
			clamp(posicao_pai.y + gerar_valor_aleatorio_gaussiano(), 0, 600),
		},
		{
			clamp(cor_pai.r + gerar_valor_aleatorio_gaussiano(), 0, 255),
			clamp(cor_pai.g + gerar_valor_aleatorio_gaussiano(), 0, 255),
			clamp(cor_pai.b + gerar_valor_aleatorio_gaussiano(), 0, 255)
		},
		*i_criatura_inicial
	};
	uint16_t i_gravacao = pilha[--*i_topo];
	criaturas[i_gravacao] = criatura_filho;
	*i_criatura_inicial = i_gravacao;
}

void reproduzir_criaturas(uint16_t i_criatura) {
	if (*i_topo > 0) {
		for (int j = 0; j < (1 + rand()%2); j++) {
			reproduzir_criatura(criaturas[i_criatura]);	
		}
	}
}

void processar_criaturas() {
	uint16_t i_anterior = *i_criatura_inicial;
	uint16_t i = *i_criatura_inicial;
	while (i != *tamanho_maximo) {
		cor_t cor_criatura = criaturas[i].cor;
		double probabilidade_morte = calcular_probabilidade_morte(*cor, cor_criatura);
		printf("%f\n", gerar_valor_aleatorio());
		if (gerar_valor_aleatorio() < probabilidade_morte) {
			printf("criatura removida\n");
			remover_criatura(i, i_anterior);
		} else {
			printf("criatura reproduzida\n");
			reproduzir_criaturas(i);
		}
		i = criaturas[i].indice_proximo;
	}
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
