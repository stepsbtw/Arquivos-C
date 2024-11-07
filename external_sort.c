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

int compara_registro(const void *a, const void *b){
  return strncmp(((Registro*)a)->cep,((Registro*)b)->cep,8) // strncmp -> decide o tamanho, strings nao null terminated.
}

// A IDEIA AGORA É : dividir em dois arquivos, ordenar cada um, salvar, puxar denovo e intercalar.

void ordena_arquivo();

int main(){
  FILE *fin;
  long p, qtd, meio;
  fin = fopen("cep.dat","rb");
  p = fseek(f,0,SEEK_END);
  qtd = ftell(p)/sizeof(Registro);

  meio = qtd/2;
  Registro *metade = (Registro *)malloc(sizeof(Registro)*meio);
  
  rewind(fin); //fseek(fin,0,SEEK_SET);
  
  if(fread(metade,sizeof(Registro),meio,fin) == meio){
    printf("LIDO!\n");
  }
  qsort(metade,qtd,sizeof(Registro),compara_registro);
  printf("FILE 1 ORDENADO\n");
  
  if(fread(metade,sizeof(Registro),qtd-meio,fin) == qtd-meio){
    printf("LIDO!\n");
  }
  qsort(metade,qtd,sizeof(Registro),compara_registro);
  printf("FILE 2 ORDENADO\n");
  
  fclose(fin);

  FILE* fout_1 = fopen("cep_ordenado_1.dat","wb");
  fwrite(metade,sizeof(Registro),qtd,fout_1);
  fclose(fout_1);
  printf("FILE 1 SALVO\n");

  FILE* fout_2 = fopen("cep_ordenado_2.dat","wb");
  fwrite(metade,sizeof(Registro),qtd,fout_2);
  fclose(fout_2);
  printf("FILE 2 SALVO\n");

  free(metade);

  // AGORA INTERCALAR!

}
