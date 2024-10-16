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