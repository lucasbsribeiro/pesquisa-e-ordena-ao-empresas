#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_LINE_LENGTH 1024
#define MAX_CAMPO_LENGHT 100  
#define MAX_FIELDS 7

typedef struct Empresa {
    int cnpj;
    char nome[50];
    int natureza_jud;
    int qualificacao;
    float capital_social;
    int porte;
    int ente_federativo;
} Empresa;

/* Funções relacionadas ao cadastro das empresas */
void converte_strings(int *campo_int, double *campo_double, char campo[], int campo_cont);
void cria_empresa(Empresa empresas[], char campo[], int cont, int campo_cont);
void print_empresa(Empresa empresas[], int cont);

/* Funções relacionadas à ordenação do vetor e às pesquisas */
int compara_cnpj(const void *a, const void *b);
int compara_nome(const void *a, const void *b);
int busca_binaria_cnpj(Empresa *empresas, int tamanho, const int cnpj);
int busca_binaria_nome(Empresa *empresas, int tamanho, const char nome[]);
void busca_binaria(Empresa *empresas, int tamanho, const int op, const int last_op);

#endif