#include <stdio.h>
#include <stdlib.h>
#include "criatura.h"
#include "grafico.h"

int main(){
	srand(time(NULL));
	contexto_t *contexto = iniciar_criaturas();
	
	int rodadas = 100000;
	while (rodadas-- > 0){
		processar(contexto);
		atualizar_interface(contexto);
	}
	
	return 0;
}
