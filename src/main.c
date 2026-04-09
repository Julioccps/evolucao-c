#include <stdio.h>
#include <stdlib.h>
#include "criatura.h"
#include "grafico.h"

int main(){
	cor_t *cor_ambiente = malloc(sizeof(cor_t));
	criatura_t* criaturas = gerar_criaturas(10);
	
	while (1){
		processar(criaturas, cor_ambiente);
		atualizar_interface(criaturas, cor_ambiente);
	}
	
	free(cor_ambiente);
	free(criaturas);
	return 0;
}
