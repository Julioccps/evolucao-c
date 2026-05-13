#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "criatura.h"
#include "grafico.h"

int main() {
	srand(time(NULL));

	contexto_t *contexto = inicializar_criaturas();
	interface_t *interface = inicializar_interface();

	int executando = 1;

	const double intervalo = 1.0 / 60.0;
	clock_t ultimo_update = clock();

	while (executando) {
		processar(contexto);

		clock_t agora = clock();
		double tempo_passado =
			(double)(agora - ultimo_update) / CLOCKS_PER_SEC;

		if (tempo_passado >= intervalo) {

			atualizar_interface(interface, contexto);

			int evento = analizar_eventos();

			if (evento == 2) {
				gerar_nova_cor_ambiente(contexto);
			}

			executando = evento > 0;

			ultimo_update = agora;
		}
	}

	finalizar_criaturas(contexto);
	finalizar_interface(interface);

	return 0;
}