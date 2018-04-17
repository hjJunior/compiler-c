#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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

int valida_principal(char* chave){
	(strcmp("principal", chave) == 0) ? return 1 : return 0;
}

int valida_funcao(char* chave){
	(strcmp("funcao", chave) == 0) ? return 1 : return 0;
}

// Valida palavras reservadas

int valida_leitura(char* chave){
	(strcmp("leitura", chave) == 0) ? return 1 : return 0;
}

int valida_escrita(char* chave){
	(strcmp("escrita", chave) == 0) ? return 1 : return 0;
}

int valida_se(char* chave){
	(strcmp("se", chave) == 0) ? return 1 : return 0;
}

int valida_senao(char* chave){
	(strcmp("senao", chave) == 0) ? return 1 : return 0;
}

int valida_para(char* chave){
	(strcmp("para", chave) == 0) ? return 1 : return 0;
}

// Valida tipos de dados

int valida_inteiro(char* chave){
	(strcmp("inteiro", chave) == 0) ? return 1 : return 0;
}

int valida_caractere(char* chave){
	(strcmp("caractere", chave) == 0) ? return 1 : return 0;
}

int valida_decimal(char* chave){
	(strcmp("decimal", chave) == 0) ? return 1 : return 0;
}
