#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int compara_cnpj(const void *a, const void *b)
{
    Empresa *empresa_a = (Empresa *)a;
    Empresa *empresa_b = (Empresa *)b;

    return (empresa_a->cnpj - empresa_b->cnpj);
}


int compara_nome(const void *a, const void *b)
{
    Empresa *empresa_a = (Empresa *)a;
    Empresa *empresa_b = (Empresa *)b;

    return strcmp(empresa_a->nome, empresa_b->nome);
}


int busca_binaria_cnpj(Empresa *empresas, int tamanho, const int cnpj)
{
    int esquerda = 0;
    int direita = tamanho - 1;
    while (esquerda <= direita) 
    {
        int meio = esquerda + (direita - esquerda) / 2;  

        if (empresas[meio].cnpj == cnpj) return meio;  

        if (empresas[meio].cnpj < cnpj) esquerda = meio + 1;    /* Passamos a ignorar a metade da esquerda do vetor */

        else direita = meio - 1;    /* Passamos a ignorar a metade da direita do vetor */
    }
    /* Elemento não encontrado */
    return -1;
}


int busca_binaria_nome(Empresa *empresas, int tamanho, const char nome[])
{
    int esquerda = 0;
    int direita = tamanho - 1;
    while (esquerda <= direita) 
    {
        int meio = esquerda + (direita - esquerda) / 2;  
        int comp;
        comp = strcmp(empresas[meio].nome, nome);

        if (comp == 0) return meio;  

        if (comp < 0) esquerda = meio + 1;    /* Passamos a ignorar a metade da esquerda do vetor */

        else direita = meio - 1;    /* Passamos a ignorar a metade da direita do vetor */
    }

    /* Elemento não encontrado */
    return -1;
}


void busca_binaria(Empresa *empresas, int tamanho, const int op, const int last_op)
{
    int indice;
    int cnpj;
    char nome[MAX_CAMPO_LENGHT];

    switch (op)
    {
    case 1:
        printf("Digite o CNPJ (8 primeiros digitos) da empresa desejada: ");
        if(scanf("%d", &cnpj) != 1) 
        {
            printf("\nEntrada invalida.\n");
            return;
        }

        if(last_op != 1) qsort(empresas, tamanho, sizeof(Empresa), compara_cnpj);
        indice = busca_binaria_cnpj(empresas, tamanho, cnpj);
        break;

    case 2:
        printf("Digite o nome empresarial/razao social da empresa desejada: ");
        scanf(" %[^\n]", nome);

        if(last_op != 2) qsort(empresas, tamanho, sizeof(Empresa), compara_nome);
        indice = busca_binaria_nome(empresas, tamanho, nome);
        break;

    case 3:
        indice = rand() % (tamanho - 1);
        break;

    default:
        return;
    }

    if(indice == -1)
    {
        printf("Empresa nao encontrada.\n");
        return;
    }
    print_empresa(empresas, indice);
}
