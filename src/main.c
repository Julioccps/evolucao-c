#include <stdio.h>
#include <stdlib.h>
#include "criatura.h"
#include "grafico.h"

int main(){
	iniciar_criaturas(10);
	
	while (1){
		processar();
		atualizar_interface(
			obter_criaturas(),
			obter_cor_ambiente()
		);
	}
	
	finalizar_criaturas();
	return 0;
}
