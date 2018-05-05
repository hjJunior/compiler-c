#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>


int valida_variavel(char *chave){
	int i=0;
	if(chave[i++]=='#'){
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




// Valida funções e procedimentos

int verifica_begin(char* chave){
	
	if(strcmp("begin",chave)==0){
		return 1;
	}else{
		return 0;
	}
}



int verifica_end(char* string){
	
	if(strcmp("end",string)==0){
		return 1;
	}else{
		return 0;
	}
	
}



int verifica_int(char* palavra){
	if(strcmp("int",palavra)==0){
		return 1;
	}else{
		return 0;
	}
}

int verifica_dec(char* palavra){
	if(strcmp("dec",palavra)==0){
		return 1;
	}else{
		return 0;
	}
}

int verifica_char(char* palavra){
	if(strcmp("char",palavra)==0){
		return 1;
	}else{
		return 0;
	}
}


int verifica_read(char* palavra){
	return (!strcmp("read",palavra));
}

int verifica_write(char* palavra){
	return (!strcmp("write",palavra));
}



// Valida tipos de dados


int verifica_if(char* palavra){
	
	return (!strcmp("if",palavra));
}

int verifica_then(char* palavra){
	return (!strcmp("then",palavra));	
}

int verifica_else(char* palavra){
	
	return (!strcmp("else",palavra));
}


