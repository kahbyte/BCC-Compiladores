#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *lerNumeros(char str[], int *i, char valor[999]) {
  strcpy(valor, "");
  char num;
  char caract[99] = "";
  char numeros[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  int lenNum = sizeof(numeros) / sizeof(numeros[0]);
  char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                   'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                   's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int lenLet = sizeof(letras) / sizeof(letras[0]);
  bool ponto = false;
  int posString = 0;
  char verifica[999];
  bool letra = false;
  bool encontrou = false;
  bool fimNum = false;
  int depPonto = 0;
  bool isNum = false;
  bool invalido = false;
  for (int a = *i; a < strlen(str); a++) {
    caract[0] = str[a];
    for (int b = 0; b < lenNum; b++) {
      num = numeros[b];
      if (caract[0] == num) {
        isNum = true;
        strcat(valor, caract);
        verifica[posString] = caract[0];
        posString++;
        encontrou = true;
        if (ponto == true) {
          depPonto++;
          if (depPonto > 2) {
            invalido = true;
          }
        }
      }
    }
    if (encontrou == false) {
      if (caract[0] == '.') {
        if (ponto == true) {
          invalido = true; 
        }
        strcat(valor, caract);
        verifica[posString] = caract[0];
        posString++;
        ponto = true;
        encontrou = true;
      } else if (caract[0] == ' ') {
        if(invalido == true){
          return "Invalido\n";
        }
        else{
          if(ponto == true){
            return "Numero Flutuante\n";
          }
          return "Numero Inteiro\n";
        }
       
      } else {
        for (int d = 0; d < lenLet; d++) {
          char let = letras[d];
          if (caract[0] == let) {
            encontrou = true;
            if(isNum == true){
              invalido = true;
            }
            else{
              return "Letra\n"; 
            }
            
          }
        }
      }
    }
    if (encontrou == false) {
      if(isNum == true){
        (*i)--;
        if(invalido == true){
          return "Invalido\n";
        }
        else{ 
          if(ponto == true){
            return "Numero Flutuante\n";
          }
        return "Numero Inteiro\n";
        }
      }
      return "indeterminado\n";
    }
    encontrou = false;
    (*i)++;
  }
  if(ponto == true){
    return "Numero Flutuante\n";
  }
  return "Numero Inteiro\n";
}

int Operador(char str[], char *verifica[9999], int *posString) {
  char caract;
  int qtdCaractInd = 0;
  char caractInd[9999][99];
  bool exponenciacao = false;
  char valor[999];
  int numInt[9999];
  int qtdNumInt = 0;
  float numFlut[999];
  int qtdNumFlut = 0;
  for (int i = 0; i < strlen(str); i++) {
    caract = str[i];
    if (caract == '+') {
      verifica[*posString] = "Soma\n";
      (*posString)++;
    } else if (caract == '-') {
      verifica[*posString] = "Subtração\n";
      (*posString)++;
    } else if (caract == '*') {
      if (exponenciacao == true) {
        if (strcmp(verifica[*posString - 1], "Multiplicação\n") == 0) {
          verifica[*posString - 1] = "Potenciação\n";
          exponenciacao = false;
        } else {
          verifica[*posString] = "Multiplicação\n";
          (*posString)++;
          exponenciacao = true;
        }
      } else {
        verifica[*posString] = "Multiplicação\n";
        (*posString)++;
        exponenciacao = true;
      }

    } else if (caract == '/') {
      verifica[*posString] = "Divisão\n";
      (*posString)++;
    } else if (caract == ' ' || caract == '\n') {
      verifica[*posString] = "espaco\n";
    } else {
      verifica[*posString] = lerNumeros(str, &i, valor);
      if(strcmp(verifica[*posString], "Numero Inteiro\n") == 0){
        numInt[qtdNumInt] = atoi(valor);  
        qtdNumInt++;
      }
      else if(strcmp(verifica[*posString], "Numero Flutuante\n") == 0){
        numFlut[qtdNumFlut] = atof(valor);
        qtdNumFlut++;
      }
        (*posString)++;
    }
  }
}

int termo(char str[], int *posString){
  char *verifica[99];
  char newVerifica[99] = "";
  char numero[10];
  Operador(str, verifica, posString);
  for(int i = 0; i < *posString; i++){
    if(strcmp(verifica[i], "Invalido\n") == 0 || strcmp(verifica[i], "indeterminado\n") == 0){
      return 0;
    }
    if(strcmp(verifica[i], "Numero Inteiro\n") == 0 || strcmp(verifica[i], "Numero Flutuante\n") == 0){
      strcat(newVerifica, "Numero\n"); 
    }
    else{
      strcat(newVerifica, verifica[i]); 
    }
  }

  if(strcmp(newVerifica, "Numero\n") == 0 ||  strcmp(newVerifica, "Numero\nSoma\nNumero\n") == 0){  
    return 1;
  }

  return 0;
}

void expressao(char str[]){
  char res[99];
  int posString = 0;
  if(termo(str, &posString) == 1 || posString == 0){
    strcpy(res, "Expressão válida");
    printf("%s", res);
  }
  else{
    strcpy(res, "Expressão Inválida");
    printf("%s", res);
  }
  
}

int main(int argc, char *argv[]) {
  FILE *arq;
  char c;
  char code[9999];
  int codeIndex = 0;

  arq = fopen(argv[1], "r");
  while (c != EOF) {
    c = fgetc(arq);
    code[codeIndex] = c;
    codeIndex++;
  }
  code[codeIndex - 1] = NULL;
  fclose(arq);
  expressao(code);
  return 0;
}
