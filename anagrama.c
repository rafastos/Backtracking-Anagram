#include <stdio.h>
#include <string.h>

#define TAM_MAX 100 // Tamanho máximo da string de entrada

void troca(char *x, char *y)
{
  char temp = *x;
  *x = *y;
  *y = temp;
}

void processaSolucao(char *str)
{
  printf("%s\n", str);
}

int geraCandidatos(char *str, int inicio, int fim, int *candidatos)
{
  int cont = 0;
  int deveTrocar;
  for (int i = fim; i >= inicio; i--)
  {
    deveTrocar = 1;
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

void backtracking(char *str, int inicio, int fim)
{
  if (inicio == fim)
    processaSolucao(str);
  else
  {
    int candidatos[TAM_MAX];
    int numCandidatos = geraCandidatos(str, inicio, fim, candidatos);

    for (int i = 0; i < numCandidatos; i++)
    {
      troca(&str[inicio], &str[candidatos[i]]);
      backtracking(str, inicio + 1, fim);
      troca(&str[inicio], &str[candidatos[i]]);
    }
  }
}

int main()
{
  char str[TAM_MAX];
  printf("Digite uma palavra: ");
  scanf("%s", str);
  int n = strlen(str);
  backtracking(str, 0, n - 1);
  return 0;
}