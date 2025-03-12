#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main() 
{
    FILE *arquivo = fopen("K3241.K03200Y0.D40713.EMPRECSV", "r"); 
    char linha[MAX_LINE_LENGTH];  /* String que armazena cada linha do arquivo */
    char campo[MAX_CAMPO_LENGHT]; /* String que irá armazenar um campo obtido da linha lida, por ex CNPJ, nome/razao social, etc */
    int num_empresas = 0;
    int num_linhas = 0;

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    printf("Carregando o arquivo...\n");

    while(fgets(linha, sizeof(linha), arquivo)) num_linhas++;

    rewind(arquivo);  /* Movendo o ponteiro novamente para o inicio do arquivo */

    Empresa *empresas = (Empresa*) malloc(num_linhas * sizeof(Empresa));

    if(empresas == NULL) 
    {
        printf("Erro ao alocar memoria para as empresas\n");
        return -1;
    }

    printf("Carregando dados...\n\n");
    while (fgets(linha, sizeof(linha), arquivo) && num_empresas < num_linhas) /* Lê uma linha do arquivo */
    {  
        int campo_cont = 0;
        char *token = strtok(linha, ";");  /* Divide a linha em campos usando o ; como delimitador */

        while (token != NULL) 
        {
            strncpy(campo, token, MAX_CAMPO_LENGHT - 1);
            campo[MAX_CAMPO_LENGHT - 1] = '\0';
            cria_empresa(empresas, campo, num_empresas, campo_cont);
            token = strtok(NULL, ";");
            campo_cont++;
        }
        num_empresas++;
    }

    fclose(arquivo);  
    printf("Dados prontos.\n");
    srand(time(NULL));

    int op;
    int last_op = 1;
    while(1)
    {
        printf("\nSelecione uma opcao:\n");
        printf("1. Buscar empresa por CNPJ (8 primeiros digitos)\n");
        printf("2. Buscar empresa por nome empresarial/razao social\n");
        printf("3. Imprimir dados de empresa aleatoria\n");
        printf("0. Sair\n");

        if((scanf("%d", &op) != 1) || (op != 0 && op != 1 && op != 2 && op != 3)) 
        {
            printf("Entrada invalida.\n");
            getchar();
            continue;
        }
        if(op == 0) break;
        busca_binaria(empresas, num_empresas + 1, op, last_op);
        last_op = op;

        getchar();
    }
    free(empresas);
    printf("\nPrograma finalizado.\n");
    return 0;
}