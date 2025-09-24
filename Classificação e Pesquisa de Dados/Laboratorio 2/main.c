#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int recursoes=0;
int trocas=0;
void gera_array(int array[],int tam);
void aloca_memoria(int **array,int tam);
int particiona_Hoare(int *array,int inicio, int fim);
void quicksort_Hoare(int  *array,int inicio,int fim);
void print_vetor(int array[],int tam);
void verifica_ordenado(int array[],int tam);
int particiona_mediana(int *array,int inicio,int fim);
void quicksort_Hoare_mediana(int  *array,int inicio,int fim);
void quicksort_Hoare_pseudo(int  *array,int inicio,int fim);
int particiona_lomuto(int *array,int inicio,int fim);
void quicksort_lomuto(int  *array,int inicio,int fim);
void quicksort_pseudolomuto(int  *array,int inicio,int fim);
void quicksort_lomutomediana(int  *array,int inicio,int fim);
int particiona_lomutomediana(int *array,int inicio,int fim);
int mediana_de_tres(int arr[], int inicio, int fim);
void trocar(int* a, int* b);
void clona_vetor(int *array,int **copia1,int **copia2,int tam);
void escreve_csv(int tam);

int main(void){

    srand(time(NULL));

    escreve_csv(10);

    return 0;

}

void print_vetor(int array[],int tam)
{
    for(int i=0;i<tam;i++)
        printf("%d ",array[i]);
    printf("\n");
}
void gera_array(int array[],int tam)
{
    for(int i=0;i<tam;i++)
        array[i]= rand() % tam+1;
}
void aloca_memoria(int **array,int tam)
{
    *array = malloc(tam * sizeof(int)); //faz a alocação dinamica do meu vetor
    if (*array == NULL)
    {
        printf("Falha na alocação de memoria\n");
        exit(1);
    }

}

int particiona_Hoare(int *array,int inicio, int fim)
{
    int pivo = array[inicio];
    int aux;
    int i=inicio,j=fim;
    while (i < j)
    {
        while(i < j && array[i] <= pivo)
        {
            i++;
        }
        while(i<j && array[j] > pivo)
        {
            j--;
        }
        if (i<j) // se nao esta olhando o mesmo valor, ele troca os valores do o menor e o maior
        {
            trocar(&array[i],&array[j]);
        }
    }
    if(array[inicio] < array[j])
    {

        trocar(&array[inicio],&array[i-1]);

    }else if(array[inicio]>array[j])
    {
        trocar(&array[inicio],&array[j]);
    }
    return  i;
}

void quicksort_Hoare(int  *array,int inicio,int fim)
{
    int pos;
    if (inicio < fim)
    {
        pos = particiona_Hoare(array,inicio,fim);
        quicksort_Hoare(array,inicio,pos-1);
        quicksort_Hoare(array,pos,fim);
    }
}

void verifica_ordenado(int array[],int tam)
{
    int flag =1;
    for(int i=0;i<tam;i++)
    {
        if (i>0 && array[i]< array[i-1])
        {
            printf("Vetor nao ordenado ! elemento %d < %d\n",i,i-1);
            flag=0;
            break;
        }
    }
    if(flag)
        printf("Vetor ordenado!\n");
}

int particiona_mediana(int *array,int inicio,int fim)
{
    int pivo = (array[inicio] + array[fim] + array[(inicio+fim)/2]) /3;
    int aux;
    int i=inicio,j=fim;
    while (i < j)
    {
        while(i < j && array[i] <= pivo)
        {
            i++;
        }
        while(i<j && array[j] > pivo)
        {
            j--;
        }

        trocar(&array[i],&array[j]);
    }

    return  i;

}

void quicksort_Hoare_mediana(int  *array,int inicio,int fim) // faz a divisao pela mediana utilizando o algoritmo de hoare
{
    int pos;
    if (inicio < fim)
    {
        pos = particiona_mediana(array,inicio,fim);
        quicksort_Hoare_mediana(array,inicio,pos-1);
        recursoes++;
        quicksort_Hoare_mediana(array,pos,fim);
        recursoes++;
    }
}

void quicksort_Hoare_pseudo(int  *array,int inicio,int fim) // faz a divisao de maneira pseudo-aleatoria utilizando o algoritmo de hoare
{
    int pos;
    if (inicio < fim)
    {
        int r = inicio + rand() % (fim - inicio + 1);
        int aux = array[r];
        array[r] = array[inicio];
        array[inicio] = aux;

        pos = particiona_Hoare(array,inicio,fim);
        quicksort_Hoare_pseudo(array,inicio,pos-1);
        recursoes++;
        quicksort_Hoare_pseudo(array,pos,fim);
        recursoes++;
    }
}

int particiona_lomuto(int *array,int inicio,int fim) // particionamento do lomuto
{
    int pivo = array[inicio];
    int i = inicio+1,j=inicio+1;
    int aux;
    while(i<=fim)
    {

        if(pivo > array[i])
        {
            trocar(&array[i],&array[j]);
            j++;
        }
        i++;
    }
    trocar(&array[inicio],&array[j-1]);

    return j;
}

void quicksort_lomuto(int  *array,int inicio,int fim) // Faz a divisao do Lomuto pegando o elemento inicial de maneira comum
{
    int pos;
    if (inicio < fim)
    {
        pos = particiona_lomuto(array,inicio,fim);
        quicksort_lomuto(array,inicio,pos-1);
        quicksort_lomuto(array,pos,fim);
    }
}

void quicksort_pseudolomuto(int  *array,int inicio,int fim)// Faz a divisao do Lomuto pegando o elemento inicial de maneira pseudo-aleatoria
{
    int pos;
    if (inicio < fim)
    {
        int r = inicio + rand() % (fim - inicio + 1);
        int aux = array[r];
        array[r] = array[inicio];
        array[inicio] = aux;

        pos = particiona_lomuto(array,inicio,fim);
        quicksort_pseudolomuto(array,inicio,pos-1);
        recursoes++;
        quicksort_pseudolomuto(array,pos,fim);
        recursoes++;
    }
}

int particiona_lomutomediana(int *array,int inicio,int fim) // particionamento do lomuto com mediana na escolha do pivo
{
    int pivo = mediana_de_tres(array,inicio,fim) ; //printf("os valores comparados sao: %d(inicio) %d(fim) %d (meio)\n pivo eh %d ",array[inicio],array[fim],array[(inicio+fim)/2],pivo);
    int i = inicio+1,j=inicio+1;
    int aux;
    while(i<fim)
    {

        if(pivo > array[i])
        {
            trocar(&array[j],&array[i]);
            j++;
        }
        i++;
    }

    trocar(&array[j-1],&array[inicio]);

    return j;
}

void quicksort_lomutomediana(int  *array,int inicio,int fim)// Faz a divisao do Lomuto pegando o elemento com a mediana
{
    int pos;
    if (inicio < fim)
    {
        pos = particiona_lomutomediana(array,inicio,fim);
        quicksort_lomutomediana(array,inicio,pos-1);
        recursoes++;
        quicksort_lomutomediana(array,pos,fim);
        recursoes++;
    }
}

int mediana_de_tres(int arr[], int inicio, int fim) {
    int meio = inicio + (fim - inicio) / 2;

    // Ordena arr[inicio], arr[meio] e arr[fim]
    if (arr[inicio] > arr[meio]) {
        trocar(&arr[inicio], &arr[meio]);
    }
    if (arr[inicio] > arr[fim]) {
        trocar(&arr[inicio], &arr[fim]);
    }
    if (arr[meio] > arr[fim]) {
        trocar(&arr[meio], &arr[fim]);
    }

    // O elemento do meio (arr[meio]) é a mediana.
    // Para o particionamento Lomuto, o pivô deve estar em fim.
    trocar(&arr[meio], &arr[inicio]);
    return arr[fim];
}

void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}
void clona_vetor(int *array,int **copia1,int **copia2,int tam)
{
     for(int i = 0;i<tam;i++)
     {
         (*copia1)[i]=array[i];
         (*copia2)[i]=array[i];
     }

}

void escreve_csv(int tam)
{
    FILE *arquivo=fopen("quicksort.csv","a");
    double tempo_total;
    clock_t partida;
    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        exit(1);

    }else
    {
        int *vetor,*copia1,*copia2;
        int control=0;
        while(control<6){
            aloca_memoria(&vetor,tam);
            aloca_memoria(&copia1,tam);
            aloca_memoria(&copia2,tam);
            gera_array(vetor,tam);
            for (int i=0;i<2;i++)
            {

                clona_vetor(vetor,&copia1,&copia2,tam);
                if(i==0)
                {
                    partida=clock();
                    quicksort_Hoare_mediana(copia1,0,tam-1);
                    tempo_total=(double)(clock() - partida)/CLOCKS_PER_SEC;
                    fprintf(arquivo,"Quicksort_Hoare_Mediana,%d,%d,%d,%f\n",tam,recursoes,trocas,tempo_total);
                    recursoes=0;
                    trocas=0;
                    verifica_ordenado(copia1,tam);

                    partida=clock();
                    quicksort_Hoare_pseudo(copia2,0,tam-1);
                    tempo_total=(double)(clock() - partida)/CLOCKS_PER_SEC;
                    fprintf(arquivo,"Quicksort_Hoare_Pseudo,%d,%d,%d,%f\n",tam,recursoes,trocas,tempo_total);
                    recursoes=0;
                    trocas=0;
                    verifica_ordenado(copia2,tam);

                }else
                {
                    partida=clock();
                    quicksort_lomutomediana(copia1,0,tam-1);
                    tempo_total=(double)(clock() - partida)/CLOCKS_PER_SEC;
                    fprintf(arquivo,"Quicksort_Lomuto_Mediana,%d,%d,%d,%f\n",tam,recursoes,trocas,tempo_total);
                    recursoes=0;
                    trocas=0;
                    verifica_ordenado(copia1,tam);

                    partida=clock();
                    quicksort_pseudolomuto(copia2,0,tam-1);
                    tempo_total=(double)(clock() - partida)/CLOCKS_PER_SEC;
                    fprintf(arquivo,"Quicksort_Lomuto_Pseudo,%d,%d,%d,%f\n",tam,recursoes,trocas,tempo_total);
                    recursoes=0;
                    trocas=0;
                    verifica_ordenado(copia2,tam);


                }
                printf("interacao %d\n\n",i);
            }
            free(vetor);
            free(copia1);
            free(copia2);
            printf("tamanho = %d\n",tam);
            tam*=10;
            control ++;
        }

        fclose(arquivo);

    }


}
