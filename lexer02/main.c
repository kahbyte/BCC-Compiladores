#include <stdio.h>
#include <string.h>
#include<stdbool.h>

void Operador(char str[]){
  char c;
  int posString = 0;
  char *verifica[9999];
  int qtdCaractInd = 0;
  char caractInd[9999][99];
  bool exponenciacao = false;
  for(int i = 0; i < strlen(str); i++){
    c = str[i];
    if (c == '+') {
      verifica[posString] = "Soma\n";
      posString++;
    } 
    else if(c == '-'){
      verifica[posString]= "Subtração\n";
      posString++;
    }
    else if(c == '*'){
      if(exponenciacao == true){
        if(verifica[posString-1] == "Multiplicação\n"){
        verifica[posString-1] = "Potenciação\n" ;
        exponenciacao = false;
        }
        else{
          verifica[posString]= "Multiplicação\n";
          posString++;
          exponenciacao = true; 
        }
      }
      else{
        verifica[posString]= "Multiplicação\n";
        posString++;
        exponenciacao = true; 
      }
      
    }
    else if(c == '/'){
      verifica[posString]= "Divisão\n";
      posString++;
    }
    else if(c ==' '){
      verifica[posString] = "espaco\n";
      posString++;
    }      
    else {
      sprintf(caractInd[qtdCaractInd], "indeterminado(%c)\n", c);
      verifica[posString] = caractInd[qtdCaractInd];
      posString++;
      qtdCaractInd++;
    }
  }
  printf("Operadores: \n");
  for (int i = 0; i < posString; i++) {
    printf("%s", verifica[i]);
  }
}

int main(int argc,char *argv[]) {
  FILE *arq;
  char c;
  char code[9999];
  int codeIndex = 0;
  arq = fopen(argv[1], "r");
  while(c!= EOF){
    c = fgetc(arq);
    code[codeIndex] = c;
    codeIndex++;
  }
  code[codeIndex-1] = NULL;
  fclose(arq);
  Operador(code);
  return 0;
}