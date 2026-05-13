#include "criatura.h"

posicao_t gerar_posicao_aleatoria() {
	posicao_t posicao = {
		rand()%LARGURA_AMBIENTE,
		rand()%ALTURA_AMBIENTE
	};
	return posicao;
}

cor_t gerar_cor_aleatoria() {
	cor_t cor = {
		rand()%256,
		rand()%256,
		rand()%256,
	};
	return cor;
}

double gerar_valor_aleatorio() {
	return (double)rand()/ (double)RAND_MAX;
}

criatura_t criar_criatura() {
	criatura_t criatura = {
		gerar_posicao_aleatoria(),
		gerar_cor_aleatoria(),
		1
	};
	return criatura;
}

contexto_t gerar_criaturas() {
	contexto_t contexto;
	contexto.cor = gerar_cor_aleatoria();
	contexto.limite = MAXIMO_CRIATURAS;
	criatura_t *criaturas = contexto.criaturas;
	for (int i = 0; i < MAXIMO_CRIATURAS; i++) {
		criaturas[i] = criar_criatura();
	}
	return contexto;
}

contexto_t *inicializar_criaturas() {
	contexto_t *contexto = malloc(sizeof(contexto_t));
	*contexto = gerar_criaturas();
	return contexto;
};

double calcular_probabilidade_morte(cor_t cor1, cor_t cor2) {
	double dr = (double)cor1.r - (double)cor2.r;
	double dg = (double)cor1.g - (double)cor2.g;
	double db = (double)cor1.b - (double)cor2.b;

	double distancia = sqrt(dr * dr + dg * dg + db * db);

	return distancia / 441.6729;
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
	int i = rand()%10;
	int valor_aleatorio;
	if (rand()%2) {
		valor_aleatorio = valores[i];
	} else {
		valor_aleatorio = -valores[i];
	}
	return valor_aleatorio;
}

criatura_t reproduzir_criatura(criatura_t criatura) {
	posicao_t posicao = criatura.posicao;
	cor_t cor = criatura.cor;
	criatura_t criatura_filho = {
		{
			clamp(posicao.x + gerar_valor_aleatorio_gaussiano()*3, 0, LARGURA_AMBIENTE-1),
			clamp(posicao.y + gerar_valor_aleatorio_gaussiano()*3, 0, ALTURA_AMBIENTE-1),
		},
		{
			clamp(cor.r + gerar_valor_aleatorio_gaussiano(), 0, 256),
			clamp(cor.g + gerar_valor_aleatorio_gaussiano(), 0, 256),
			clamp(cor.b + gerar_valor_aleatorio_gaussiano(), 0, 256)
		},
		1
	};
	return criatura_filho;
}

void remover_criaturas(contexto_t *contexto) {
	criatura_t *criaturas = contexto->criaturas;
	uint16_t limite = contexto->limite;
	for (int i = 0; i < limite; i++) {
		criatura_t *criatura = &criaturas[i];
		cor_t cor_criatura = criatura->cor;
		double probabilidade_morte = calcular_probabilidade_morte(contexto->cor, cor_criatura);
		if (gerar_valor_aleatorio() < probabilidade_morte) {
			criatura->vivo = 0;
		}
	}
	contexto->limite = limite;
}

void realocar_criaturas(contexto_t *contexto) {
	criatura_t *criaturas = contexto->criaturas;
	uint16_t limite = contexto->limite;

	uint16_t j = 0;

	for (int i = 0; i < limite; i++) {
		if (criaturas[i].vivo) {
			criaturas[j++] = criaturas[i];
		}
	}

	contexto->limite = j;
}

void reproduzir_criaturas_comum(contexto_t *contexto) {
	criatura_t *criaturas = contexto->criaturas;
	uint16_t limite = contexto->limite;
	for (int i = 0; i < limite; i++) {
		criaturas[limite + i] = reproduzir_criatura(criaturas[i]);
	}
	contexto->limite += limite;
}

void reproduzir_criaturas_reduzida(contexto_t *contexto) {
	criatura_t *criaturas = contexto->criaturas;
	uint16_t limite = contexto->limite;
	uint16_t j = rand() % limite;
	uint16_t quantidade = MAXIMO_CRIATURAS - limite;
	for (int i = 0; i < quantidade; i++) {
		criaturas[limite + i] = reproduzir_criatura(criaturas[(j + i)%limite]);
	}
	contexto->limite = MAXIMO_CRIATURAS;
}

void reproduzir_criaturas(contexto_t *contexto) {
	if ((contexto->limite * 2 <= MAXIMO_CRIATURAS)) {
		reproduzir_criaturas_comum(contexto);
	} else {
		reproduzir_criaturas_reduzida(contexto);
	}
}

void processar(contexto_t *contexto) {
	remover_criaturas(contexto);
	realocar_criaturas(contexto);
	if (contexto->limite == 0) {
		*contexto = gerar_criaturas();
		printf("Morraram\n");
	} else {
		reproduzir_criaturas(contexto);
	}
}

void finalizar_criaturas(contexto_t *contexto) {
	free(contexto);
}