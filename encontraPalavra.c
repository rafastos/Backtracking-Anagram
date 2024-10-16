#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX 100
#define TAM_DIC 245367

int buscaBinaria(char *str, char **dicionario, int tamDic)
{
  int inicio = 0;
  int fim = tamDic - 1;

  while (inicio <= fim)
  {
    int meio = (inicio + fim) / 2;

    if (strcmp(str, dicionario[meio]) == 0)
      return meio; // anagrama encontrado
    else if (strcmp(str, dicionario[meio]) < 0)
      fim = meio - 1; // anagrama está na metade esquerda
    else
      inicio = meio + 1; // anagrama está na metade direita
  }

  return -1; // anagrama não encontrado
}

void carregaDicionario(char *txt, char **dicionario, int *tamanho)
{
  FILE *arq = fopen(txt, "r");
  if (arq == NULL)
  {
    printf("Erro abrindo arquivo\n");
    return;
  }

  *tamanho = 0;
  char linha[TAM_MAX];
  while (fgets(linha, sizeof(linha), arq))
  {
    if (*tamanho >= TAM_DIC)
    {
      printf("Dicionario muito grande! Limite maximo de %d palavras alcancado.\n", TAM_DIC);
      break;
    }

    linha[strcspn(linha, "\n")] = 0;
    dicionario[(*tamanho)++] = strdup(linha);
    if (dicionario[*tamanho - 1] == NULL)
    {
      printf("Erro ao alocar memoria para a palavra '%s'\n", linha);
      exit(1);
    }
  }
  fclose(arq);
}

void troca(char *x, char *y)
{
  char temp = *x;
  *x = *y;
  *y = temp;
}

void processaSolucao(char *str, char **dicionario, int tamDic)
{
  int indice = buscaBinaria(str, dicionario, tamDic);

  if (indice != -1)
    printf("Anagrama encontrado: %s\n", str);
}

int geraCandidatos(char *str, int inicio, int fim, int *candidatos)
{
  int cont = 0;
  for (int i = fim; i >= inicio; i--)
  {
    int deveTrocar = 1;
    for (int j = inicio; j < i; j++)
      if (str[j] == str[i])
      {
        deveTrocar = 0;
        break;
      }
    if (deveTrocar)
      candidatos[cont++] = i;
  }
  return cont;
}

void backtracking(char *str, int inicio, int fim, char **dicionario, int tamDic)
{
  if (inicio == fim)
    processaSolucao(str, dicionario, tamDic);
  else
  {
    int candidatos[TAM_MAX];
    int numCandidatos = geraCandidatos(str, inicio, fim, candidatos);

    for (int i = 0; i < numCandidatos; i++)
    {
      troca(&str[inicio], &str[candidatos[i]]);
      backtracking(str, inicio + 1, fim, dicionario, tamDic);
      troca(&str[inicio], &str[candidatos[i]]);
    }
  }
}