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
} Registro;

int compara_registro(const void *a, const void *b) {
  return strncmp(((Registro*)a)->cep, ((Registro*)b)->cep, 8);
}

void intercala(FILE *f1, FILE *f2){
  fseek(f1,0,SEEK_END);
  fseek(f2,0,SEEK_END);
  int tamanho1 = ftell(f1), tamanho2 = ftell(f2);
  rewind(f1); rewind(f2);
  FILE *saida = fopen("cep_ordenado_merge.dat","wb");
  Registro r1, r2;
  int qtd1 = fread(&r1,sizeof(Registro),1,f1);
  int qtd2 = fread(&r2,sizeof(Registro),1,f2);
  
  while (qtd1 > 0 && qtd2 > 0) {
    if (strncmp(r1.cep, r2.cep, 8) > 0) {
      fwrite(&r2, sizeof(Registro), 1, saida);
      qtd2 = fread(&r2, sizeof(Registro), 1, f2);
    } else {
      fwrite(&r1, sizeof(Registro), 1, saida);
      qtd1 = fread(&r1, sizeof(Registro), 1, f1);
    }
  }
  
  int tam_falta;
  if(qtd1 == 0){
    tam_falta = tamanho2 - ftell(f2);
    Registro *coisas = (Registro*)malloc(tam_falta);
    fread(coisas,sizeof(Registro),tam_falta/sizeof(Registro),f2);
    fwrite(coisas,sizeof(Registro),tam_falta/sizeof(Registro),saida);
  }else{
    tam_falta = tamanho1 - ftell(f1);
    Registro *coisas = (Registro*)malloc(tam_falta);
    fread(coisas,sizeof(Registro),tam_falta/sizeof(Registro),f1);
    fwrite(coisas,sizeof(Registro),tam_falta/sizeof(Registro),saida);
  }
}


int main() {
  FILE *fin = fopen("cep.dat", "rb");
  if (!fin) {
    perror("Erro ao abrir arquivo de entrada");
    return 1;
  }

  fseek(fin, 0, SEEK_END);
  int qtd = ftell(fin) / sizeof(Registro);
  rewind(fin);

  // Dividir o arquivo em duas metades
  int meio = qtd / 2;
  Registro *metade1 = (Registro *)malloc(sizeof(Registro) * meio);
  Registro *metade2 = (Registro *)malloc(sizeof(Registro) * (qtd - meio));

  if (!metade1 || !metade2) {
    perror("Erro na alocação de memória");
    fclose(fin);
    return 1;
  }

  // Lê a primeira metade
  fread(metade1, sizeof(Registro), meio, fin);
  // Lê a segunda metade
  fread(metade2, sizeof(Registro), qtd - meio, fin);

  // Ordena cada metade
  qsort(metade1, meio, sizeof(Registro), compara_registro);
  qsort(metade2, qtd - meio, sizeof(Registro), compara_registro);

  // Grava os arquivos ordenados
  FILE *fout_1 = fopen("cep_ordenado_1.dat", "wb");
  FILE *fout_2 = fopen("cep_ordenado_2.dat", "wb");

  if (!fout_1 || !fout_2) {
    perror("Erro ao abrir arquivo de saída");
    free(metade1);
    free(metade2);
    fclose(fin);
    return 1;
  }

  fwrite(metade1, sizeof(Registro), meio, fout_1);
  fwrite(metade2, sizeof(Registro), qtd - meio, fout_2);

  fclose(fout_1);
  fclose(fout_2);

  printf("Arquivos ordenados gravados.\n");

  free(metade1);
  free(metade2);

  // Agora intercala os dois arquivos ordenados
  fout_1 = fopen("cep_ordenado_1.dat", "rb");
  fout_2 = fopen("cep_ordenado_2.dat", "rb");

  if (!fout_1 || !fout_2) {
    perror("Erro ao abrir arquivos ordenados");
    return 1;
  }

  intercala(fout_1, fout_2);

  fclose(fout_1);
  fclose(fout_2);

  printf("Intercalação concluída. Arquivo final: cep_ordenado_merge.dat\n");

  fclose(fin);
  return 0;
}
