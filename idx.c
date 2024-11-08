// Caio Passos Torkst Ferreira
// João Guilherme de Oliveira Ribeiro Kongevold
// Luis Inácio de Oliveira Melo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Registro{
  char logradouro[72];
  char bairro[72];
  char cidade[72];
  char uf[72];
  char sigla[2];
  char cep[8];
  char lixo[2];
}Registro;

typedef struct _IdxCep{
  char cep[8];
  int pos;
}IdxCep;

int compara(const void *a, const void *b){
  return strncmp(((IdxCep*)a)->cep, ((IdxCep*)b)->cep, 8);
}


int main(){
  FILE *f, *fidx;
  f = fopen("cep.dat","rb");
  fseek(f,0,SEEK_END);
  long qtd = ftell(f) / sizeof(Registro);
  rewind(f);
  IdxCep *vet_idx = (IdxCep*)malloc(sizeof(IdxCep)*qtd);
  Registro aux;
  for(int i = 0; i < qtd; i++){
    fread(&aux, sizeof(Registro), 1, f);
    strncpy(vet_idx[i].cep, aux.cep, 8);
    vet_idx[i].pos = i;
  }
  fclose(f);
  qsort(vet_idx,qtd,sizeof(IdxCep),compara);
  fidx = fopen("cep_idx.dat","wb");
  fwrite(vet_idx,sizeof(IdxCep),qtd,fidx);
  fclose(fidx);
  free(vet_idx);
}
