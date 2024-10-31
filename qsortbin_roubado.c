  GNU nano 6.2                                                                    sortbin.c                                                                             
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Registro{
  char logradouro[72];
  char bairro[72];
  char cidade[72];
  char uf[72];
  char sigla[2];
  char cep[8];
  char lixo[2];
}Registro;

int compara(const void *coisa1, const void *coisa2){
  return strncmp(((Registro *)coisa1)->cep,((Registro *)coisa2)->cep,sizeof(((Registro *)coisa1)->cep));
}

int main(){
  FILE *f = fopen("cep.dat","rb+");
  int n_coisas = 100;
  int tam_arquivo = n_coisas*sizeof(Registro);
  //Registro coisas[n_coisas];
  Registro *coisas = ((Registro *)malloc(tam_arquivo));
  if(n_coisas = fread(coisas,n_coisas,sizeof(Registro),f)){
    printf("LIDO!\n");
  }
  qsort(coisas,sizeof(Registro),n_coisas,compara);
  printf("ORDENADO!\n");
  FILE *saida = fopen("cep-ordenado.dat","wb");
  return 0;
}
