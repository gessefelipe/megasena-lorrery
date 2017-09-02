/*

Fazer o download do arquivo de números sorteados na Mega Sena em formato html e converter o programa para um arquivo txt.

A partir do arquivo txt criar um programa que execute as seguintes operações:

1) Determine os 6 valores que mais foram sorteados na mega sena.

2) Determine os 6 valores que menos foram sorteados na mega sena.

3) Dados 6 números determinar se estes valores ja foram sorteados em algum sorteio.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SORTEIO 1962
#define VALOR 60
#define NUM_DEZENAS 6

struct CAIXA {
	int		cont;
	int		concurso[NUM_SORTEIO];
	char	*data;
	int		dezena[NUM_SORTEIO][NUM_DEZENAS];
} MEGASENA;

void ler_resultados() {

	char string[150]; // string armazenar� a linha
	char tabulacao[] = "	"; // Caracter delimitador
	char *info; // Ponteiro para armazenar as informa��es
	MEGASENA.cont = 0;

	FILE *megasena;
	char *modo = "r";//modo de leitura "read"
	megasena = fopen("megasena.txt", modo); // Abre o arquivo

	while (fgets(string, sizeof(string) - 1, megasena) != NULL) { // Loop para ler cada linha do arquivo enquanto houver linhas

		int tamanho;
		tamanho = strlen(string);

		info = string; // info recebe a linha inteira
		info = strtok(string, tabulacao); // info recebe a primeira string antes da primeira tabula��o da primeira linha

		while (info != NULL) { // Enquanto houver linhas no arquivo
			if (tamanho > VALOR) {

				MEGASENA.concurso[MEGASENA.cont] = atoi(info);

				info = strtok(NULL, tabulacao); // Separa o id do Concurso da string
				MEGASENA.data = info; // Copia info para a variavel

				info = strtok(NULL, tabulacao);
				MEGASENA.dezena[MEGASENA.cont][0] = atoi(info);

				info = strtok(NULL, tabulacao);
				MEGASENA.dezena[MEGASENA.cont][1] = atoi(info);

				info = strtok(NULL, tabulacao);
				MEGASENA.dezena[MEGASENA.cont][2] = atoi(info);

				info = strtok(NULL, tabulacao);
				MEGASENA.dezena[MEGASENA.cont][3] = atoi(info);

				info = strtok(NULL, tabulacao);
				MEGASENA.dezena[MEGASENA.cont][4] = atoi(info);

				info = strtok(NULL, tabulacao);
				MEGASENA.dezena[MEGASENA.cont][5] = atoi(info);

				info = strtok(NULL, tabulacao); // Separa o modelo da string
				MEGASENA.cont++;
				info = NULL;
			}
			else {
				info = NULL;
			}
		}
	}
	fclose(megasena);
}

void exercicio() {
	int _dezena[NUM_DEZENAS][VALOR];
	for (int i = 0; i < NUM_DEZENAS; i++) {
		for (int j = 0; j < VALOR; j++) {
			_dezena[i][j] = 0;
		}
	}

	for (int i = 0; i < NUM_SORTEIO; i++) {
		for (int j = 0; j < NUM_DEZENAS; j++) {
			for (int k = 1; k <= VALOR; k++) {
				if (MEGASENA.dezena[i][j] == k) {
					_dezena[j][k - 1] += 1;
				}
			}
		}
	}

	int num_dezenas[VALOR];

	for (int i = 0; i < VALOR; i++) {
		num_dezenas[i] = 0;
	}

	for (int i = 0; i < NUM_DEZENAS; i++) {
		for (int j = 0; j < VALOR; j++) {
			num_dezenas[j] += _dezena[i][j];
		}
	}
	int temp;
	int vezesmaior[NUM_DEZENAS] = { 0, 0, 0, 0, 0, 0 }, numeromaior[NUM_DEZENAS] = { 0, 0, 0, 0, 0, 0 };
	int vezesmenor[NUM_DEZENAS] = { num_dezenas[0], num_dezenas[0], num_dezenas[0], num_dezenas[0], num_dezenas[0], num_dezenas[0] }, numeromenor[NUM_DEZENAS] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < NUM_DEZENAS; i++) {
		for (int j = 0; j < VALOR; j++) {

			if (num_dezenas[j] > vezesmaior[i]) {
				vezesmaior[i] = num_dezenas[j];
				numeromaior[i] = j + 1;
				temp = j;
			}

			if (j == VALOR-1) {
				num_dezenas[temp] = -1;
			}
		}


	}
	for (int i = 5; i >= 0; i--) {
		for (int j = 0; j < VALOR; j++) {
			if ((num_dezenas[j] < vezesmenor[i]) && (num_dezenas[j] > 0)) {
				vezesmenor[i] = num_dezenas[j];
				numeromenor[i] = j + 1;
				temp = j;
			}

			if (j == VALOR-1) {
				num_dezenas[temp] = -1;
			}
		}
	}

	// Apresenta��o para o usu�rios dos n�meros mais sorteados
	printf("Os 6 valores que mais foram sorteados:\n");

	// Repeti��o de 6x para apresenta��o
	for (int i = 0; i < NUM_DEZENAS; i++) {
		printf("Numero: %d - Aparecendo: %d\n", numeromaior[i], vezesmaior[i]);
	}

	printf("\nOs 6 valores que menos foram sorteados:\n");

	for (int i = 0; i < NUM_DEZENAS; i++) {
		printf("Numero: %d - Aparecendo: %d\n", numeromenor[i], vezesmenor[i]);
	}
}

int lendo_valores(int dezena[]) {
	// L� valores das dezenas que o usu�rio deseja
	printf("\n\nDigite 6 numeros (de 1 ate 60):\n");

	// Repeti��o para digitar as 6 dezenas
	for (int i = 0; i < NUM_DEZENAS; i++)
	{
		scanf("%d", &dezena[i]);
	}
}



int verificando(int dezena[]) {
	int verificacao = 0;
	for (int i = 0; i < NUM_SORTEIO; i++) {
		if (MEGASENA.dezena[i][0] == dezena[0] || MEGASENA.dezena[i][1] == dezena[0] || MEGASENA.dezena[i][2] == dezena[0] || MEGASENA.dezena[i][3] == dezena[0] || MEGASENA.dezena[i][4] == dezena[0] || MEGASENA.dezena[i][5] == dezena[0]) {
			if (MEGASENA.dezena[i][0] == dezena[1] || MEGASENA.dezena[i][1] == dezena[1] || MEGASENA.dezena[i][2] == dezena[1] || MEGASENA.dezena[i][3] == dezena[1] || MEGASENA.dezena[i][4] == dezena[1] || MEGASENA.dezena[i][5] == dezena[1]) {
				if (MEGASENA.dezena[i][0] == dezena[2] || MEGASENA.dezena[i][1] == dezena[2] || MEGASENA.dezena[i][2] == dezena[2] || MEGASENA.dezena[i][3] == dezena[2] || MEGASENA.dezena[i][4] == dezena[2] || MEGASENA.dezena[i][5] == dezena[2]) {
					if (MEGASENA.dezena[i][0] == dezena[3] || MEGASENA.dezena[i][1] == dezena[3] || MEGASENA.dezena[i][2] == dezena[3] || MEGASENA.dezena[i][3] == dezena[3] || MEGASENA.dezena[i][4] == dezena[3] || MEGASENA.dezena[i][5] == dezena[3]) {
						if (MEGASENA.dezena[i][0] == dezena[4] || MEGASENA.dezena[i][1] == dezena[4] || MEGASENA.dezena[i][2] == dezena[4] || MEGASENA.dezena[i][3] == dezena[4] || MEGASENA.dezena[i][4] == dezena[4] || MEGASENA.dezena[i][5] == dezena[4]) {
							if (MEGASENA.dezena[i][0] == dezena[5] || MEGASENA.dezena[i][1] == dezena[5] || MEGASENA.dezena[i][2] == dezena[5] || MEGASENA.dezena[i][3] == dezena[5] || MEGASENA.dezena[i][4] == dezena[5] || MEGASENA.dezena[i][5] == dezena[5]) {
								printf("\nAs dezenas %d %d %d %d %d %d ja foi sorteado no sorteio %d.\n\n", dezena[0], dezena[1], dezena[2], dezena[3], dezena[4], dezena[5], i+1);
								verificacao++;
							}
						}
					}
				}
			}
		}
	}

	if (verificacao == 0) {
		printf("\nEstas dezenas ainda nao foram sorteadas juntas.\n\n");
	}
}

int main()
{

	ler_resultados();

	exercicio();

	int dezena[NUM_DEZENAS];

	lendo_valores(dezena);

	verificando(dezena);

	return 0;

}