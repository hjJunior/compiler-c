#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>

int valida_variavel(char *chave){
	int i = 0;

	if(chave[i++] == '#'){
		if(islower(chave[i++])){
			while(isgraph(chave[i])){
				if(!isalnum(chave[i++])){
					return 0;
				}
			}
			return 1;
		}
	}
	return 0;
}

// Valida funções e métodos

int valida_principal(char *chave){
	return (strcmp("principal", chave) == 0) ? 1 : 0;
}

int valida_funcao(char *chave){
	return (strcmp("funcao", chave) == 0) ? 1 : 0;
}

// Valida palavras reservadas

int valida_leitura(char *chave){
	return (strcmp("leitura", chave) == 0) ? 1 : 0;
}

int valida_escrita(char *chave){
	return (strcmp("escrita", chave) == 0) ? 1 : 0;
}

int valida_se(char *chave){
	return (strcmp("se", chave) == 0) ? 1 : 0;
}

int valida_senao(char *chave){
	return (strcmp("senao", chave) == 0) ? 1 : 0;
}

int valida_para(char *chave){
	return (strcmp("para", chave) == 0) ? 1 : 0;
}

// Valida tipos de dados

int valida_inteiro(char *chave){
	return (strcmp("inteiro", chave) == 0) ? 1 : 0;
}

int valida_caractere(char *chave){
	return (strcmp("caractere", chave) == 0) ? 1 : 0;
}

int valida_decimal(char *chave){
	return (strcmp("decimal", chave) == 0) ? 1 : 0;
}
