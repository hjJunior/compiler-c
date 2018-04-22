#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct lista{
  char *chave;
  struct lista *proximo;
};

typedef struct lista Lista;

Lista* cria(void){
  return NULL;
}

Lista* insere(Lista* lista, char* chave){
  if(lista == NULL){
    Lista* listaAuxiliar = (Lista*) malloc(sizeof(Lista));
    listaAuxiliar->proximo = NULL;
    listaAuxiliar->chave = chave;
    lista = listaAuxiliar;

    return lista;
  }else{
    Lista* listaAuxiliar = (Lista*) malloc(sizeof(Lista));
    listaAuxiliar->proximo = NULL;
    listaAuxiliar->chave = chave;
    Lista* p;

    for(p = lista; p->proximo != NULL; p = p->proximo);
    p->proximo = listaAuxiliar;

    return lista;
  }
}

void imprime(Lista* lista){
  while (lista != NULL){
    printf("%s\n", lista->chave);
    lista = lista->proximo;
  }
}

void localiza_palavra_reservada(Lista* lista, char *chave){
  Lista* novaLista;

  for(novaLista = lista; novaLista != NULL; novaLista = novaLista->proximo){
    if( strcmp(novaLista->chave, chave) == 0){
        printf("Erro tentativa de declarar uma palavra reservada %s e uma palavra reservada\n", chave);           
    }  
  }       
}
