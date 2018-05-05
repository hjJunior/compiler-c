struct variaveis{
	char* tipo;
	char* nome;
	char* valor;
};


typedef struct variaveis Variaveis;
Variaveis lista_variaveis_declaradas[10000];

char* string;
char* arquivo;
FILE* file;
Lista* lista_palavras_reservadas;
int i=0; int flag=0; int c=0; int end=0;
char temp[10000];
char* variavel_temporaria;
char* tipo_temporario;
char* table[100];
int contTable=0;
int aux_inicializacao;
char *aux_tipo_inicializacao;

void pega_varios_read();
int verifica_palavras_reservadas();
void pega_comparacao();
int verifica_comparacao();
void inicializa_variavel();
void copia_arquivo();
void insere_palavras_reservadas();
void pega_varias_variaveis();
char* pega_Palavra();
char* verifica();
void pega_variavel();
void copia_tipo_variavel_temporaria();
void imprime_variaveis_declaradas();
void insere_variaveis_declaradas();
int verifica_lista_variaveis();
int verifica_inicializacao_int();
int verifica_inicializacao_dec();
void pega_palavra_dec();
void inicializa_struct();




void copia_arquivo(){
	
	
	if((file=fopen("../public/valido.txt","r"))==NULL){
		printf("nao foi possivel abrir o arquivo\n");
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

char* pega_Palavra(){
	c=0;
	
			while(strchr("\n\t ,;",arquivo[i])){
				i++;			
			}
		
			while(!strchr("\n\t (),;*&%$>:^@=<",arquivo[i])){
				temp[c]=arquivo[i];
				c++;
				i++;
			}
			
			temp[c]='\0';
			c=0;
}

void insere_palavras_reservadas(){
	
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"begin");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"end");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"int");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"dec");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"begin");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"char");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"read");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"write");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"if");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"then");
	lista_palavras_reservadas=insere(lista_palavras_reservadas,"else");
}

char* verifica(){
			c=0;
			strcpy(temp,"");
			pega_Palavra();	
			//printf("%s",temp);
		    //printf("%d\n",valida_variavel(temp));
		if(valida_variavel(temp)==0){
			if(verifica_begin(temp)==1 && flag==0){
				flag=1;
				pula_espaco();
				printf("%c\n",arquivo[i]);
				if(arquivo[i]==';'){
					printf("ERRO DE SINTAXE\n");
					exit(0);
				}
			}
			
			
			if(flag==1 && verifica_end(temp)==1){
				
				if(arquivo[i]==';'){
					printf("ERRO DE SINTAXE\n");
					exit(0);
				}
				printf("linguagem aceita\n");
				end=1;
				return 0;
			}
					
		
			if(arquivo[i]=='\0'&&end==0){
				printf("Linguagem nao finalizada\n");
				printf("Faltou 'end'\n");
			}
			
			
			if(verifica_write(temp)==1){
				printf("write\n");
							pula_espaco();
							  	if(arquivo[i++]=='('){
							  		printf("entrou no write\n");
							  		pula_espaco();
									if(arquivo[i]=='"'){
										i++;
										while(arquivo[i++]!='"');	
										if(!(arquivo[i++]==')')){
											printf("Erro de Balanceamento no comando Write ')' \n");
											exit(0);
										}
									}else if(arquivo[i]=='#'){
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
													printf("Erro de Balanceamento no comando Write  \n");
													exit(0);
												}
												c=0;
									}else {
											printf("Erro no camando Write \n");
											exit(0);
									}
								}else{
										printf("Erro de Balanceamento no comando Write ' ( ' \n");
										exit(0);
								}	
								
								verifica();		
				}
		
			
			if(verifica_read(temp)==1){
				printf("read\n");
				pula_espaco();
				if(arquivo[i++]=='('){
					
					pega_varios_read();
					
					if(arquivo[i++]!=')'){
									printf("Erro de balanceamento ) \n");
									exit(0);
					}
//						printf("read");
				}else exit(0);
				i++;
				verifica();	
			}
		
		
			if(verifica_int(temp)){
				printf("int\n");
				 copia_tipo_variavel_temporaria();
				 pega_varias_variaveis();
				 verifica();
			}
		
		
			if(verifica_dec(temp)){
				printf("dec\n");
				 copia_tipo_variavel_temporaria();
				 pega_varias_variaveis();
				 verifica();
			}
		
		
		    if(verifica_char(temp)){
		    	printf("char\n");
				 copia_tipo_variavel_temporaria();
				 pega_varias_variaveis();
				 verifica();
			}
		
			if(verifica_if(temp)==1){
				printf("if\n");
				pula_espaco();
				if(arquivo[i++]!='('){
					printf("Erro no if '('\n");
					exit(0);
				}
				pula_espaco();
				pega_Palavra();
				//printf("%s\n",temp);
				if(verifica_lista_variaveis()==1||verifica_inicializacao_int()==1){
					pula_espaco();
					pega_comparacao();
					if(verifica_comparacao()==0){
						printf("Erro nos comparadores\n");
						exit(0);
					}
					pula_espaco();
					pega_Palavra();
					if(verifica_lista_variaveis()!=1 && verifica_inicializacao_int()!=1){
						printf("Erro de Comparacao\n");
						exit(0);
					}
					pula_espaco();
					if(arquivo[i++]!=')'){
						printf("Erro falta ')' no if\n");
						exit(0);
					}
					if(verifica_if_then()==0){
						printf("ERRO DE SINTAXE!!\n");
						exit(0);
					}
					
				}
				verifica();
			}
					
	
	    	if(verifica_if(temp)==0&&verifica_char(temp)==0&&verifica_dec(temp)==0&&verifica_int(temp)==0&&verifica_read(temp)==0&&verifica_write(temp)==0&&verifica_begin(temp)==0&&verifica_end(temp)==0){	
	    		printf("ERRO DE SINTAXE!! VERIFIQUE AS PALAVRAS RESERVADAS\n");
	    		exit(0);
			
			}
	
		}else{
		
			if(valida_variavel(temp)==1){
				 if(verifica_lista_variaveis()==1){
				 	pula_espaco();
				 	if(arquivo[i++]==':' && arquivo[i++]=='='){
				 		pula_espaco();
				 		if(!strcmp(lista_variaveis_declaradas[aux_inicializacao].tipo,"int")){
				 			pega_Palavra();
				 			if(verifica_inicializacao_int()==1){	
				 				inicializa_variavel();
							 }else{
							 	printf("Erro ao tentar inicializar a variavel '%s' com valor diferente de seu tipo\n",lista_variaveis_declaradas[aux_inicializacao].nome);	
							 	exit(0);
							 }
						 }
				
						if(!strcmp(lista_variaveis_declaradas[aux_inicializacao].tipo,"char")){
							printf("entrou char\n");
							int c=0;
							pula_espaco();
							
							if(arquivo[i++]=='"'){
								while(arquivo[i]!='"'){
									if(arquivo[i]=='\n'){
										printf("Erro no char falta de '\"'!!\n");
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
					
						if(!strcmp(lista_variaveis_declaradas[aux_inicializacao].tipo,"dec")){
							printf("%s\n",temp);
							system("pause");
							pega_palavra_dec();
							system("cls");
							printf("%s\n",temp);
							system("pause");
							if(verifica_inicializacao_dec()==1){
				 				inicializa_variavel();
							 }else{
							 	printf("Erro ao tentar inicializar a variavel '%s' com valor diferente de seu tipo\n",lista_variaveis_declaradas[aux_inicializacao].nome);			 	
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


void pega_varios_read(){	
	
	while(!strchr(")",arquivo[i])){
		pula_espaco();
		 if(arquivo[i]=='#'){
				
						temp[c++]=arquivo[i++];
					
						while(isalnum(arquivo[i])){
							temp[c++]=arquivo[i];
							i++;
						}
						
//						printf("read");
 		temp[c]='\0'; 
		
		
	}else {
		printf("Erro ao declarar variavel '#'\n");
			exit(0);
	}
			//printf("%s\n",temp);
				if(valida_variavel(temp)==0){
								printf("Nome de variavel errada %s\n",temp);
				}
				if(verifica_lista_variaveis()==0){
								printf("variavel '%s' nao delarada \n",temp);
								exit(0);
				}
				pula_espaco();
				//printf("%c\n",arquivo[i]);
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
	char* nome=(char*)malloc(10000);
	pula_espaco();
	if(arquivo[i]=='#'){
				
						temp[c++]=arquivo[i++];
					
						while(isalnum(arquivo[i])){
							temp[c++]=arquivo[i];
							i++;
						}
						
//						printf("read");
 		temp[c]='\0'; 
		
		
	}else {
		printf("Erro ao declarar variavel '#'\n");
			exit(0);
	}
 	//printf("%s\n%s\n",nome,tipo_temporario);
	pula_espaco();
	if(arquivo[i]==',') i++;
}


void imprime_variaveis_declaradas(){
	system("pause");
	system("cls");
	int i;
	for(i=0;i<contTable;i++){
		printf("Tipo: %s\n",lista_variaveis_declaradas[i].tipo);
		printf("Nome: %s\n",lista_variaveis_declaradas[i].nome);
		printf("Valor: %s\n",lista_variaveis_declaradas[i].valor);
		printf("\n_____________________________________\n");
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
				lista_variaveis_declaradas[contTable].nome[y]=temp[y];
				y++;
	}
	lista_variaveis_declaradas[contTable].nome[y]='\0';
	strcpy(lista_variaveis_declaradas[contTable].tipo,tipo_temporario);
	
	strcpy(lista_variaveis_declaradas[contTable].valor,"null");
	contTable++;
}

int verifica_lista_variaveis(){
	int x;
	for(x=0;x<contTable;x++){
		if(strcmp(temp,lista_variaveis_declaradas[x].nome)==0){
				strcpy(aux_tipo_inicializacao,lista_variaveis_declaradas[x].tipo);
				aux_inicializacao=x;
		 		return 1;
		}
	}
	return 0;
}

void pega_palavra_dec(){
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
			printf("Erro ao inicializar %s\n",lista_variaveis_declaradas[aux_inicializacao].nome);
			exit(0);
		}
	}	
}

int verifica_inicializacao_int(){
	int c=0;
	if(temp[c]!='#'){
	
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
		lista_variaveis_declaradas[x].nome=(char*)malloc(10000); 
		lista_variaveis_declaradas[x].tipo=(char*)malloc(10000);
		lista_variaveis_declaradas[x].valor=(char*)malloc(10000);
	}
}

int verifica_inicializacao_dec(){
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

void verifica_if_then(){
	pega_Palavra();
	if(verifica_then(temp)==0){
		printf(" ERRO NO IF 'then'\n");
		exit(0);
	}
	
}

int verifica_palavras_reservadas(){
	while(lista_palavras_reservadas!=NULL){
		if(strcmp(lista_palavras_reservadas->palavra,temp)==0){
			return 1;
		}
		lista_palavras_reservadas=lista_palavras_reservadas->prox;
	}
	return 0;
}
