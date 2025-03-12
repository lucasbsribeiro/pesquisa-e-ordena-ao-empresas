#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

void converte_strings(int *campo_int, double *campo_double, char campo[], int campo_cont)
{
    int i = 0;
    int aspas_cont = 0;

    /* Primeiramente, retiramos as aspas de todos os campos */
    while(campo[i] != '\0')
    {
        if(campo[i] == '"' && aspas_cont == 0)
        {
            int j = 0;
            while(campo[j] != '\0')
            {
                campo[j] = campo[j + 1];
                j++;
            }
            aspas_cont++;
        } 

        if(campo[i] == '"' && aspas_cont == 1)
        {
            campo[i] = '\0';
        }

        if(campo[i] == ',') campo[i] = '.';
        i++;
    }
    /* Se o campo for relacionado ao CNPJ, natureza jurídica, qualificação do responsável, porte da empresa ou ente federativo,
    convertemos para tipo int */
    if(campo_cont != 1 && campo_cont != 4)
    {
        *campo_int = atoi(campo);
    }
    /* Se o campo relacionado ao capital, convertemos para double */
    if(campo_cont == 4)
    {
        *campo_double = atof(campo);
    }
}


void cria_empresa(Empresa empresas[], char campo[], int cont, int campo_cont)
{
    int campo_int;  /* Variável int para armazenar o campo convertido, caso seja um int */
    double campo_double;  /* Váriavel double para armazenar o campo "capital" convertido, caso seja esse o campo */

    converte_strings(&campo_int, &campo_double, campo, campo_cont);
    /* campo_cont indica qual dos campos da empresa estamos manipulando */
    switch (campo_cont)
    {
    case 0:
        empresas[cont].cnpj = campo_int;
        break;
    case 1:
        strncpy(empresas[cont].nome, campo, MAX_CAMPO_LENGHT - 1);
        break;

    case 2:
        empresas[cont].natureza_jud = campo_int;
        break;

    case 3:
        empresas[cont].qualificacao = campo_int;
        break;

    case 4:
        empresas[cont].capital_social = campo_double;
        break;

    case 5:
        empresas[cont].porte = campo_int;
        break;

    case 6:
        empresas[cont].ente_federativo = campo_double;
        break;

    default:
        break;
    }
}


void print_empresa(Empresa empresas[], int cont)
{
    printf("\n");
    printf("EMPRESA:\n");
    printf("CNPJ (8 primeiros digitos): %d\n", empresas[cont].cnpj);
    printf("NOME/RAZAO SOCIAL: %s\n", empresas[cont].nome);
    printf("COD NATUREZA JUDICIARIA: %d\n", empresas[cont].natureza_jud);
    printf("QUALIFICACAO DO RESPONSAVEL: %d\n", empresas[cont].qualificacao);
    printf("CAPITAL SOCIAL: %.2f\n", empresas[cont].capital_social);
    printf("PORTE: %d\n", empresas[cont].porte);
    if(empresas[cont].ente_federativo == 0) printf("ENTE FEDERATIVO: \n");
    else printf("ENTE FEDERATIVO: %d\n", empresas[cont].ente_federativo);
    printf("\n");
}
