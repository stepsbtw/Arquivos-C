#include <stdio.h>
#include <string.h>

// Caio Passos Torkst Ferreira
// João Guilherme de Oliveira Ribeiro Kongevold
// Luis Inacio de Oliveira Melo

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

typedef struct _Endereco Endereco;

int buscaBinaria(Endereco e, FILE* f){
  fseek(f,0,SEEK_END);
  int qt = ftell(f)/sizeof(Endereco);
  int inicio = 0, fim = qt-1;
  int meio;
  Endereco temp;
  while(inicio <= fim){
    meio = (inicio+fim)/2;
    fseek(f,meio*sizeof(Endereco),SEEK_SET);
    fread(&temp,1,sizeof(Endereco),f);
    if(strncmp(temp.cep,e.cep,8) == 0){
      printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",temp.logradouro,temp.bairro,temp.cidade,temp.uf,temp.sigla,temp.cep);
      return meio;
    }
    else if(strncmp(temp.cep,e.cep,8) < 0){
      inicio = meio + 1;
    }
    else{
      fim = meio - 1;
    }
  }
  return -1;
}

int main(){
  FILE* f = fopen("cep_ordenado.dat","rb+");
  Endereco e;
  char cep[8];
  scanf("%s",cep);
  strcpy(e.cep,cep);
  int pos = buscaBinaria(e,f);
  if(pos == -1){
    printf("AAAAAAA nao achei");
    fclose(f);
    return 1;
  }
  printf("posicao : %d\n", pos);
  fclose(f);
  return 0;
}
