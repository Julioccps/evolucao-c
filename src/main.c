#include <stdio.h>
#include <stdlib.h>
#include "criatura.h"
#include "grafico.h"

//Funções temporárias de log, remover quando a interface estiver finalmente pronta
void mostrar_cor(cor_t cor) {
	printf("vermelho = %d \n verde = %d \n azul = %d \n", cor.r, cor.g, cor.b);
}

void mostrar_criaturas(criatura_t *criaturas, int quantidade) {
	for (int i = 0; i < quantidade; i++) {
		printf("Cor criatura %d:\n", i);
		mostrar_cor(criaturas[i].cor);
	}
}

int main(){
	iniciar_criaturas(1000);
	
	cor_t *cor_ambiente = obter_cor_ambiente(); 
	printf("Cor ambiente:\n");
	mostrar_cor(*cor_ambiente);

	int rodadas = 100000;
	while (rodadas-- > 0){
		processar();
		// Adicionar função de interface aqui. use funções de criatura.h para obter ponteiros de cor e criaturas
	}

	mostrar_criaturas(obter_criaturas(), 10);
	
	return 0;
}
