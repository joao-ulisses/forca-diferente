#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct no
{
    char *valor;
    int acertou;
    struct no *proximo;
} No;

typedef struct
{
    No *inicio;
    int tam;
} Lista;

void criar_lista(Lista *lista)
{
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_no_fim(Lista *lista, char *num)
{
    No *aux, *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = *num;
        novo->proximo = NULL;
        novo->acertou = 0;

        if (lista->inicio == NULL)
            lista->inicio = novo;
        else
        {
            aux = lista->inicio;
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }
        lista->tam++;
    }
    else
        printf("Erro ao alocar memoria!\n");
}

No *remover(No **lista, char num)
{
    No *aux, *remover = NULL;

    if (*lista)
    {
        if ((*lista)->valor == num)
        {
            remover = *lista;
            *lista = remover->proximo;
        }
        else
        {
            aux = *lista;
            while (aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if (aux->proximo)
            {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
            }
        }
    }
    return remover;
}

void checaPalavra(char palavraCerta[5], No *palavraDigitada)
{
    for (int i = 0; i < 5; i++)
    {
        if (palavraCerta[i] == palavraDigitada->valor)
        {
            palavraDigitada->acertou = 1;
        }
        palavraDigitada = palavraDigitada->proximo;
    }
}

void checaLetras(char letraCerta[5], No *palavraDigitada)
{
    printf("\n\tLetras certas: ");
    while (palavraDigitada)
    {
        for (int i = 0; i < 5; i++)
        {
            if (palavraDigitada->valor == letraCerta[i])
            {
                printf("%c ", palavraDigitada->valor);
            }
        }
        palavraDigitada = palavraDigitada->proximo;
    }
    printf("\n\t");
    system("PAUSE");
}

void imprimeAcerto(No *no, char palavraCerta[5])
{
    printf("\n\tLetras Acertadas: ");
    int contLista = 0;
    while (no)
    {
        if (no->acertou == 1)
        {
            printf("%c ", palavraCerta[contLista]);
        }
        else
        {
            printf("_ ");
        }
        no = no->proximo;
        contLista++;
    }
    printf("\n\n");
}

void imprimeDigitadas(No *no)
{
    printf("\n\tLetras Digitadas: ");
    while (no)
    {
        printf("%c ", no->valor);
        no = no->proximo;
    }
    printf("\n\n");
}

void escolhePalavra(char *palavraEscolhida[])
{
    FILE *f;

    f = fopen("palavras.txt", "r");
    if (f == 0)
    {
        printf("Banco de dados de palavras n�o dispon�vel\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for (int i = 0; i <= randomico; i++)
    {
        fscanf(f, "%s", palavraEscolhida);
    }

    fclose(f);
}

int main()
{
    for (;;)
    {
        srand(time(NULL));
        int sorteado = rand() % 3;
        sorteado++;

        char palavraEscolhida[5];
        escolhePalavra(&palavraEscolhida);

        int opcao;
        char valor;
        int cont = 0;

        No *removido;
        Lista *lista = NULL;

        criar_lista(&lista);

        do
        {
            system("cls");
            printf("\n\tAdivinhe a palavra de 5 letras: \n\n\t");
            imprimeAcerto(lista, palavraEscolhida);
            imprimeDigitadas(lista);
            printf("\n\n\n\t1 - Inserir letra\t2 - Remover\t3 - Confere\t0- Reinicia\n\n\t");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                if (cont < 5)
                {
                    printf("\n\tDigite um valor: ");
                    fflush(stdin);
                    scanf("%c", &valor);
                    inserir_no_fim(&lista, &valor);
                    cont++;
                }
                else
                {
                    printf("\tVoce nao pode digitar mais letras!\n\t");
                    system("PAUSE");
                }
                break;
            case 2:
                printf("Digite um valor a ser removido (ele remove da esquerda para a direita): ");
                fflush(stdin);
                scanf("%c", &valor);
                removido = remover(&lista, valor);
                if (removido)
                {
                    printf("Elemento a ser removido: %d\n", removido->valor);
                    free(removido);
                    cont--;
                }
                else
                {
                    printf("Elemento inexistente!\n");
                }
                break;
            case 3:
                if (cont == 5)
                {
                    checaPalavra(palavraEscolhida, lista);
                    checaLetras(palavraEscolhida, lista);
                }
                else
                {
                    printf("Insira 5 letras para conferir, letras digitadas: %d\n", cont);
                    system("PAUSE");
                }
                break;
            default:
                if (opcao != 0)
                    printf("Opcao invalida!\n");
            }
        } while (opcao != 0);
    }

    return 0;
}
