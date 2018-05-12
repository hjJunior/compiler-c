#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct lista{
   char *palavra;
   struct lista *prox;
};

typedef struct lista Lista;
Lista* cria(void){
       return NULL;
}

Lista* insere(Lista* l,char* palavra){
   if(l==NULL){
   	 	Lista* aux = (Lista*) malloc(sizeof(Lista));
   		aux->prox=NULL;
   		aux->palavra=palavra;
   		l=aux;
   		return l;
   }else{
   		Lista* aux = (Lista*) malloc(sizeof(Lista));
   		aux->prox=NULL;
   		aux->palavra=palavra;
		
		Lista* p;
		
   		for(p=l;p->prox!=NULL;p=p->prox);
		p->prox=aux;
		return l;
   }
}

void imprime(Lista* l){
    while (l !=NULL){
        printf("%s\n",l->palavra);
        l = l->prox;
    }
}

void procura_palavra_reservada(Lista*l,char * palavra){
   Lista* nx;
   Lista* w;
   
   for(nx=l;nx!=NULL;nx=nx->prox){
        if( strcmp(nx->palavra,palavra)==0){
            printf("Erro tentativa de declarar uma palavra reservada %s e uma palavra reservada\n",palavra);           
        }  
    }       
}



