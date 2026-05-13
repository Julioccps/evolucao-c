#include <stdio.h>
#include <stdlib.h>
#include "criatura.h"
#include "grafico.h"

int main(){
	srand(time(NULL));
	contexto_t *contexto = inicializar_criaturas();
	interface_t *interface = inicializar_interface();

	int executando = 1;
	while (executando){
		processar(contexto);
		atualizar_interface(interface, contexto);
		int evento = analizar_eventos();
		if (evento == 2) {
			gerar_nova_cor_ambiente(contexto);
		}
		executando = evento > 0;
	}

	finalizar_criaturas(contexto);
	finalizar_interface(interface);
	
	return 0;
}
