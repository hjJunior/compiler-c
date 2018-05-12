// Compilador 2018-1
// Disciplina: Compiladores Professora: Aline Dayany Lemos
// Acad�mico: Breno Borges 	Matricula:	1410969
// Acad�mico: Jean Flores	Matricula: 	1310159

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
	tipo_temporario=(char*)malloc(10000);
	arquivo=(char*)malloc(10000);
	variavel_temporaria=(char*)malloc(10000);
	tipo_temporario=(char*)malloc(10000);
	
	copia_arquivo();
	mensagem_inicial();
	verifica();
	imprime_variaveis_declaradas();
}

