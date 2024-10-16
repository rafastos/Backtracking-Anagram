#include <stdio.h>
#include <string.h>

#define TAM_MAX 100 // Tamanho máximo da string de entrada

void troca(char *x, char *y)
{
  char temp = *x;
  *x = *y;
  *y = temp;
}