#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 3
typedef struct
{
    int valor;
    int frequencia;
} DADO;

struct FILA
{
    int valor;
    struct FILA *prox;
} typedef FILA;

void cache_LFU(DADO dados[],int tamanho_vetor_dados,int *hits,int *miss) // implementado com a logica FIFO para empates.
{
    DADO cache[TAM];
    int i=0,j=0;
    DADO aux= {0,0};
    int aux_guarda_indice=0;
    while(j<tamanho_vetor_dados)
    {
        for (i=0; i<TAM; i++)
        {
            if(cache[i].valor == dados[j].valor)//se elemento esta na cache|| incrementa hits
            {
                *hits=*hits+1;
                cache[i].frequencia++;
                break;
            }
            if(cache[i].frequencia<aux.frequencia)//se o meu auxiliar tem mais usos frequentes que o valor atual, quero que fique igual o valor atual
            {
                aux=cache[i];
                aux_guarda_indice=i;
            }
            if(cache[i].valor != dados[j].valor && i==TAM-1) //ultima interacao  nao eh igual, miss || add na cache
            {
                *miss=*miss+1;
                dados[j].frequencia++;
                cache[aux_guarda_indice]=dados[j]; //dado atual sera colocado no menos frequente
                aux.frequencia+=2;
            }
        }
        j++;
    }


}
FILA* insereInicio(FILA *PtLista, DADO Dado,int *tam)
{
    FILA *novo;
    *tam++;
    novo = (FILA*) malloc(sizeof(FILA));
    novo->valor = Dado.valor;
    novo->prox = PtLista;
    PtLista = novo;
    return PtLista;
}
int esta_cache(FILA* cache,DADO dados)//verifica se um elemento esta na cache
{
    if (cache==NULL)
        return 0;
    else
    {
        if (cache->valor ==dados.valor)
            return 1;
        esta_cache(cache->prox,dados);
    }
}
FILA* exclui_elemento(FILA *cache,DADO dados,int *tam) //exclui um elemento em qualquer posicao desde que seja passado qual o elemento
{
    FILA* ant=NULL;
    FILA *aux=cache;
    *tam--;
    while(aux->valor != dados.valor)
    {
        ant=aux;
        aux=aux->prox;
    }

    if (aux==cache)//primeiro elemento
    {
        cache=aux->prox;
        free(aux);
        return cache;
    }
    else//elemento do meio
    {
        ant->prox=aux->prox;
        free(aux);
        return cache;
    }

}
FILA* exclui_ultimo(FILA *cache,int *tam) //exclui apenas o ultimo elemento
{
    FILA* ant=NULL;
    FILA* aux=cache;
    *tam--;
    while(aux->prox != NULL)
    {
        ant=aux;
        aux=aux->prox;
    }
    if(ant==NULL)
    {
        printf("Erro ao excluir o ultimo");
        exit(1);
    }
    ant->prox=NULL;
    free(aux);
    return cache;
}
void cache_LRU(DADO dados[],int tam_vetor_dados,int *hit,int *miss)
{

    int j=0,i=0;
    FILA *cache=NULL;
    static int  tam_fila=0;
    while(i<tam_vetor_dados)
    {
        if(esta_cache(cache,dados[i]))//dado esta na cache entao tira o elemetno do lugar que esta e coloca no inicio
        {
            *hit+=1;
            cache=exclui_elemento(cache,dados[i],&tam_fila);
            cache=insereInicio(cache,dados[i],&tam_fila);
        }
        else
        {
            *miss+=1;
            if(tam_fila >= TAM)//verifica o tamanho, se necessario exclui o ultimo elemento e adiciona no inicio
            {
                cache=exclui_ultimo(cache,&tam_fila);
                cache=insereInicio(cache,dados[i],&tam_fila);
            }
            else
                cache=insereInicio(cache,dados[i],&tam_fila);
        }
        i++;
    }
}

void imprime(FILA*cache)
{
    FILA* ptaux;
    if (cache == NULL)
        puts("lista vazia");
    else
        for (ptaux=cache; ptaux!=NULL; ptaux=ptaux->prox)
            printf("%d\n",ptaux->valor);
}

int main(void)
{
    DADO a = {1, 0};
    DADO b = {2, 0};
    DADO c = {3, 0};
    DADO d = {4, 0};
    DADO e = {5, 0};
    DADO f = {6,0};
    DADO dados[8]= {a,b,c,a,a,e,d,d};
    int hit_LFU=0,miss_LFU=0;
    int hit_LRU=0,miss_LRU=0;

    printf("...Simulador Cache...\n");
    cache_LFU(dados,8,&hit_LFU,&miss_LFU);
    printf("-------LFU-------\n");
    printf("Numero de Hits=%d\nNumero de Misses=%d\n",hit_LFU,miss_LFU);
    cache_LRU(dados,8,&hit_LRU,&miss_LRU);
    printf("-------LRU-------\n");
    printf("Numero de Hits=%d\nNumero de Misses=%d\n",hit_LRU,miss_LRU);

}
