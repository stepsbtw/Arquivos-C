#include <stdio.h>
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

int comparaRegistro(const void *a, const void *b){
  return strncmp(((Registro*)a)->cep,((Registro*)b)->cep,8) // strncmp -> decide o tamanho, strings nao null terminated.
}

int main(){
  FILE *fin;
  long p, qtd;
  fin = fopen("cep.dat","rb");
  p = fseek(f,0,SEEK_END);
  qtd = ftell(p)/sizeof(Registro);

  Registro *coisas = (Registro *)malloc(sizeof(Registro)*qtd);
  rewind(f); // dei seek no final p calcular o tamanho, agora volta.
  
  if(fread(coisas,sizeof(Registro),qtd,fin) == qtd){
    printf("LIDO!");
  }

  qsort(coisas,qtd,sizeof(Registro),comparaRegistro);

  fclose(fin);
  FILE* fout = fopen("cep_ordenado.dat","wb");
  fwrite(coisas,sizeof(Registro),qtd,fout);
  fclose(fout);
  free(Registro);
}
