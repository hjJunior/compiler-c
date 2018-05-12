#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "../resources/list.h"
#include "../resources/functions.h"

int main(){
	inicializa_struct();
	lista_palavras_reservadas=cria();
	insere_palavras_reservadas();
	string=(char*)malloc(10000);
	tipo_temporario=(char*)malloc(10000);;
	arquivo=(char*)malloc(10000);
	variavel_temporaria=(char*)malloc(10000);
	tipo_temporario=(char*)malloc(10000);
	copia_arquivo();
	verifica();
	imprime_variaveis_declaradas();
}

