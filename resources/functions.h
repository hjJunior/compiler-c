struct variaveis{
	char* tipo;
	char* variavel;
	char* valor;
};

typedef struct variaveis Variaveis;

Variaveis lista_variaveis_declaradas[10000];

FILE* file;
Lista* lista_palavras_reservadas;

char* string;
char* arquivo;
char* variavel_temporaria;
char* tipo_temporario;
char* table[100];
char* pega_palavra();
char* verifica();

char temp[10000];
char *aux_tipo_inicializacao;

int i=0; int flag=0; int c=0; int final=0;
int contTable=0;
int aux_inicializacao;
int verifica_palavras_reservadas();
int verifica_comparacao();
int verifica_lista_variaveis();
int verifica_inicializacao_inteiro();
int verifica_inicializacao_decimal();
int verifica_se_entao();

void pega_varios_leitura();
void pega_comparacao();
void inicializa_variavel();
void copia_arquivo();
void insere_palavras_reservadas();
void pega_varias_variaveis();
void pega_variavel();
void copia_tipo_variavel_temporaria();
void imprime_variaveis_declaradas();
void insere_variaveis_declaradas();
void pega_palavra_decimal();
void inicializa_struct();

void copia_arquivo(){
	if((file=fopen("../public/linguagem_valida.txt","r"))==NULL){
		printf("Impossivel abrir o arquivo informado\n");
		exit(0);
	}
	
	arquivo=string;
	int i=0;
	
	do{
		*string=getc(file);
		string++;
		i++;
	}while(!feof(file)&&i<10000);
	
	*(string-1)='\0';
	fclose(file);	
}

char* pula_espaco(){
	while(strchr(" \t",arquivo[i])){
		i++;			
	}
}

char* pega_palavra(){
	c=0;
	
	while(strchr("\n\t ,;",arquivo[i])){
		i++;			
	}
	
	while(!strchr("\n\t (),;*#%$>:^@=<",arquivo[i])){
		temp[c]=arquivo[i];
		c++;
		i++;
	}
	
	temp[c]='\0';
	c=0;
}

void insere_palavras_reservadas(){
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"principal");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"final");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"inteiro");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"decimal");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"caractere");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"leitura");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"escrita");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"se");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"entao");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"senao");
}

char* verifica(){
	c=0;
	strcpy(temp,"");
	pega_palavra();

	if(valida_variavel(temp)==0){
		if(verifica_principal(temp)==1 && flag==0){
			flag=1;
			pula_espaco();
			printf("%c\n",arquivo[i]);
			if(arquivo[i]==';'){
				printf("ERRO DE SINTAXE\n");
				exit(0);
			}
		}
				
		if(flag==1 && verifica_final(temp)==1){
			
			if(arquivo[i]==';'){
				printf("ERRO DE SINTAXE\n");
				exit(0);
			}
			printf("\n========================\n");
			printf("=  LINGUAGEM VALIDA    =\n");
			printf("========================\n");
			final=1;
			return 0;
		}
				
		if(arquivo[i]=='\0'&&final==0){
			printf("Linguagem nao finalizada\n");
			printf("Faltou 'final'\n");
		}			
				
		if(verifica_escrita(temp)==1){
			printf("escrita\n");
			pula_espaco();
			
		  	if(arquivo[i++]=='('){
		  		printf("comecou a escrever\n");
		  		pula_espaco();
		  		
				if(arquivo[i]=='"'){
					i++;
					
					while(arquivo[i++]!='"');
						
					if(!(arquivo[i++]==')')){
						printf("Erro de Balanceamento no comando escrita ')' \n");
						exit(0);
					}
				}else if(arquivo[i]=='&'){
					c=0;
					temp[c++]=arquivo[i++];
					
					while(isalnum(arquivo[i])){
						temp[c]=arquivo[i];
						c++;
						i++;
					}
					
					temp[c]='\0';
					
					if(verifica_lista_variaveis()==0){
						printf("Erro!!!!!\nVariavel %s nao declarada\n",temp);
						exit(0);
					}
					
					pula_espaco();
					
					if(!arquivo[i++]==')'){
						printf("Erro de Balanceamento no comando escrita  \n");
						exit(0);
					}
		
					c=0;
				}else {
					printf("Erro no camando escrita \n");
					exit(0);
				}
			}else{
				printf("Erro de Balanceamento no comando escrita ' ( ' \n");
				exit(0);
			}	
			
			printf("terminou de escrever\n");
			
			verifica();		
		}
		
		if(verifica_leitura(temp)==1){
			printf("leitura\n");
			pula_espaco();
			
			if(arquivo[i++]=='('){
				pega_varios_leitura();
				
				if(arquivo[i++]!=')'){
					printf("Erro de balanceamento ) \n");
					exit(0);
				}
			}else exit(0);
			
			i++;
			verifica();	
		}
	
		if(verifica_inteiro(temp)){
			printf("inteiro\n");
			 copia_tipo_variavel_temporaria();
			 pega_varias_variaveis();
			 verifica();
		}
	
		if(verifica_decimal(temp)){
			printf("decimal\n");
			copia_tipo_variavel_temporaria();
			pega_varias_variaveis();
			verifica();
		}
	
	    if(verifica_caractere(temp)){
	    	printf("caractere\n");
			copia_tipo_variavel_temporaria();
			pega_varias_variaveis();
			verifica();
		}
	
		if(verifica_se(temp)==1){
			printf("se\n");
			printf("comecou se\n");
			pula_espaco();
			
			if(arquivo[i++]!='('){
				printf("Erro no se '('\n");
				exit(0);
			}
			
			pula_espaco();
			pega_palavra();
			
			if(verifica_lista_variaveis()==1||verifica_inicializacao_inteiro()==1){
				pula_espaco();
				pega_comparacao();
				
				if(verifica_comparacao()==0){
					printf("Erro nos comparadores\n");
					exit(0);
				}
				
				pula_espaco();
				pega_palavra();
				
				if(verifica_lista_variaveis()!=1 && verifica_inicializacao_inteiro()!=1){
					printf("Erro de Comparacao\n");
					exit(0);
				}
				
				pula_espaco();
				
				if(arquivo[i++]!=')'){
					printf("Erro falta ')' no se\n");
					exit(0);
				}
				
				if(verifica_se_entao()==0){
					printf("ERRO DE SINTAXE!!\n");
					exit(0);
				}
			}

			printf("terminou se\n");
			
			verifica();
		}
		
		if(verifica_se(temp)==0&&verifica_caractere(temp)==0&&verifica_decimal(temp)==0&&verifica_inteiro(temp)==0&&verifica_leitura(temp)==0&&verifica_escrita(temp)==0&&verifica_principal(temp)==0&&verifica_final(temp)==0){	
			printf("ERRO DE SINTAXE!! VERIFIQUE AS PALAVRAS RESERVADAS\n");
			exit(0);
		}
	
	}else{
	
		if(valida_variavel(temp)==1){
			 if(verifica_lista_variaveis()==1){
			 	pula_espaco();
			 	if(arquivo[i++]=='='){
			 		pula_espaco();
			 		if(!strcmp(lista_variaveis_declaradas[aux_inicializacao].tipo,"inteiro")){
						printf("instanciou inteiro\n");						 
			 			pega_palavra();
			 			if(verifica_inicializacao_inteiro()==1){	
			 				inicializa_variavel();
						 }else{
						 	printf("Erro ao tentar inicializar a variavel '%s' com valor diferente de seu tipo\n",lista_variaveis_declaradas[aux_inicializacao].variavel);	
						 	exit(0);
						 }
					 }
			
					if(!strcmp(lista_variaveis_declaradas[aux_inicializacao].tipo,"caractere")){
						printf("instanciou caractere\n");
						int c=0;
						pula_espaco();
						
						if(arquivo[i++]=='"'){
							while(arquivo[i]!='"'){
								if(arquivo[i]=='\n'){
									printf("Erro no caractere falta de '\"'!!\n");
									exit(0);
								}
								temp[c]=arquivo[i];
								c++;
								i++;
								
							}
							temp[c]='\0';
							i++;
						}
						inicializa_variavel();
					}
				
					if(!strcmp(lista_variaveis_declaradas[aux_inicializacao].tipo,"decimal")){
						printf("%s\n",temp);
						system("pause");
						pega_palavra_decimal();
						system("cls");
						printf("%s\n",temp);
						system("pause");
						if(verifica_inicializacao_decimal()==1){
			 				inicializa_variavel();
						 }else{
						 	printf("Erro ao tentar inicializar a variavel '%s' com valor diferente de seu tipo\n",lista_variaveis_declaradas[aux_inicializacao].variavel);			 	
						 	exit(0);
						 }
					}
				} 
				
			 }else{
			printf("Variavel nao declarada %s\n",temp);
			exit(0);
		}
			 
		}
	}	
	
	if(arquivo[i]!='\0') verifica();
}

void pega_varias_variaveis(){
	c=0;
	
	while(!strchr(";",arquivo[i])){
		pega_variavel();
		insere_variaveis_declaradas(); 
	}
}

void pega_varios_leitura(){	
	while(!strchr(")",arquivo[i])){
		pula_espaco();
		if(arquivo[i]=='&'){
			temp[c++]=arquivo[i++];
					
			while(isalnum(arquivo[i])){
				temp[c++]=arquivo[i];
				i++;
			}
						
	 		temp[c]='\0'; 
		}else {
			printf("Erro ao declarar variavel '&'\n");
			exit(0);
		}
		
		if(valida_variavel(temp)==0){
			printf("Variavel de variavel errada %s\n",temp);
		}
		
		if(verifica_lista_variaveis()==0){
			printf("Variavel '%s' foi declarada \n",temp);
			exit(0);
		}
		
		pula_espaco();
		
		if(arquivo[i]!=','&&arquivo[i]!=')'){
			printf("ERRO DE SINTAXE!!\n");
			exit(0);
		}
		
		if(arquivo[i]==')') break;
		i++;
		c=0;
	}
}

void pega_variavel(){
	c=0;
	char* variavel=(char*)malloc(10000);
	pula_espaco();
	
	if(arquivo[i]=='&'){
		temp[c++]=arquivo[i++];
					
		while(isalnum(arquivo[i])){
			temp[c++]=arquivo[i];
			i++;
		}

 		temp[c]='\0'; 
	}else {
		printf("Erro ao declarar variavel '&'\n");
		exit(0);
	}
	
	pula_espaco();
	if(arquivo[i]==',') i++;
}

void imprime_variaveis_declaradas(){
	system("pause");
	system("cls");
	int i;
	
	for(i=0;i<contTable;i++){
		printf("Tipo => %s\n",lista_variaveis_declaradas[i].tipo);
		printf("Variavel => %s\n",lista_variaveis_declaradas[i].variavel);
		printf("Valor => %s\n",lista_variaveis_declaradas[i].valor);
		printf("\n");
	}
}

void copia_tipo_variavel_temporaria(){
	int y=0;
	while(temp[y]!='\0'){
		tipo_temporario[y]=temp[y];
		y++;
	}
	tipo_temporario[y]='\0';
}

void insere_variaveis_declaradas(){
	int y=0;
	if(verifica_lista_variaveis()==1){
		printf("Erro!!!\n");
		printf("Variavel %s ja foi declarada\n",temp);
		exit(0);
	}
	while(temp[y]!='\0'){
		lista_variaveis_declaradas[contTable].variavel[y]=temp[y];
		y++;
	}
	
	lista_variaveis_declaradas[contTable].variavel[y]='\0';
	strcpy(lista_variaveis_declaradas[contTable].tipo,tipo_temporario);
	strcpy(lista_variaveis_declaradas[contTable].valor,"null");
	contTable++;
}

int verifica_lista_variaveis(){
	int x;
	
	for(x=0;x<contTable;x++){
		if(strcmp(temp,lista_variaveis_declaradas[x].variavel)==0){
			strcpy(aux_tipo_inicializacao,lista_variaveis_declaradas[x].tipo);
			aux_inicializacao=x;
	 		return 1;
		}
	}
	
	return 0;
}

void pega_palavra_decimal(){
	pula_espaco();
	int c=0;
	
	while(isdigit(arquivo[i])!=0){
		temp[c]=arquivo[i];
		i++;
		c++;
	}
	
	if(arquivo[i]=='.'){
		temp[c]=arquivo[i];
		i++;
		c++;
		
		while(isdigit(arquivo[i])!=0){
			temp[c]=arquivo[i];
			i++;
			c++;
		}	
		temp[c]='\0';
		
	}else{
		pula_espaco();
			
		if(arquivo[i++]==';'){
			temp[c]='\0';
		}else{
			printf("Erro ao inicializar %s\n",lista_variaveis_declaradas[aux_inicializacao].variavel);
			exit(0);
		}
	}	
}

int verifica_inicializacao_inteiro(){
	int c=0;
	if(temp[c]!='&'){
		while(temp[c]!='\0'){
			if(isdigit(temp[c])==0){
				return 0;
			}
			
			c++;
		}
			
		return 1;	
	}
}

void inicializa_struct(){
	int x;
	aux_tipo_inicializacao=(char*) malloc(10000);
	for(x=0;x<10000;x++){
		lista_variaveis_declaradas[x].variavel=(char*)malloc(10000); 
		lista_variaveis_declaradas[x].tipo=(char*)malloc(10000);
		lista_variaveis_declaradas[x].valor=(char*)malloc(10000);
	}
}

int verifica_inicializacao_decimal(){
	int c=0;
	printf("%s\n",temp);
	
	while(isdigit(temp[c])!=0){
		c++;
	}
	printf("%c\n",temp[c]);
	
	if(temp[c]=='.'){
		c++;
		
		while(temp[c]!='\0'){
			if(isdigit(temp[c])==0){
				return 0;
			}
			c++;
		}
	}else if(temp[c]!='\0') return 0;
	
	return 1;
}

void inicializa_variavel(){
	int y=0;
	
	while(temp[y]!='\0'){
		lista_variaveis_declaradas[aux_inicializacao].valor[y]=temp[y];
		y++;
	}
	
	lista_variaveis_declaradas[aux_inicializacao].valor[y]='\0';	
}

void pega_comparacao(){
	c=0;
	while(strchr("><=",arquivo[i])){
		temp[c++]=arquivo[i++];
	}
	temp[c]='\0';
}

int verifica_comparacao(){
	if(temp[0]=='>'&&temp[1]=='=') return 1;
	if(temp[0]=='<'&&temp[1]=='=') return 1;
	if(temp[0]=='='&&temp[1]=='\0') return 1;
	if(temp[0]=='>'&&temp[1]=='\0') return 1;
	if(temp[0]=='<'&&temp[1]=='\0') return 1;
	return 0;
}

int verifica_se_entao(){
	pega_palavra();
	if(verifica_entao(temp)==0){
		printf(" ERRO NO SE 'entao'\n");
		return 0;
	}
	return 1;
}

//=====================================

int verifica_palavras_reservadas(){
	while(lista_palavras_reservadas!=NULL){
		if(strcmp(lista_palavras_reservadas->palavra,temp)==0){
			return 1;
		}
		lista_palavras_reservadas=lista_palavras_reservadas->prox;
	}
	return 0;
}

int valida_variavel(char *chave){
	int i=0;
	if(chave[i++]=='&'){
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

int verifica_principal(char* chave){
	if(strcmp("principal",chave)==0){
		return 1;
	}else{
		return 0;
	}
}

int verifica_final(char* string){
	
	if(strcmp("final",string)==0){
		return 1;
	}else{
		return 0;
	}
	
}

int verifica_inteiro(char* palavra){
	if(strcmp("inteiro",palavra)==0){
		return 1;
	}else{
		return 0;
	}
}

int verifica_decimal(char* palavra){
	if(strcmp("decimal",palavra)==0){
		return 1;
	}else{
		return 0;
	}
}

int verifica_caractere(char* palavra){
	if(strcmp("caractere",palavra)==0){
		return 1;
	}else{
		return 0;
	}
}

int verifica_leitura(char* palavra){
	return (!strcmp("leitura",palavra));
}

int verifica_escrita(char* palavra){
	return (!strcmp("escrita",palavra));
}

int verifica_se(char* palavra){
	return (!strcmp("se",palavra));
}

int verifica_entao(char* palavra){
	return (!strcmp("entao",palavra));	
}

int verifica_senao(char* palavra){
	return (!strcmp("senao",palavra));
}
