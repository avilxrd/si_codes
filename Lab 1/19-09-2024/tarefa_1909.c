#include <stdio.h>

//02. Ignore o enter
int le_valor3(){
  int val, enter;
  int cent, dez, uni;

  cent = getchar() - '0';
  dez = getchar() - '0';
  uni = getchar() - '0';
  enter = getchar();

  val = cent*100 + dez*10 + uni;
  return val;
}


//04.Quebrar linha ao final
void imp_valor(int val){
  int cent, dez, uni;

  uni = val%10;
  dez = val/10%10;
  cent = val/100%10;

  putchar(cent + '0');
  putchar(dez + '0');
  putchar(uni + '0');
  putchar('\n');
}

//01. Media de 3 numeros de 3 digitos
int media_3(){
  int num1, num2, num3, media;
  
  num1 = le_valor3();
  num2 = le_valor3();
  num3 = le_valor3();

  media = (num1 + num2 + num3) / 3;
  
  printf("Media --> ");
  imp_valor(media);
  putchar('\n');

  return 0;
}

//03. Leia 1 numero -> Imprima dobro e quadrado
int dobro_quadrado(){
  int num, dobro, quadrado;
  num = le_valor3();

  dobro = num*2;
  quadrado = num*num;

  imp_valor(dobro);
  imp_valor(quadrado);
}

//05. 
int binario(){
  int numero;
  int binario[8];
  int i = 7;

  numero = le_valor3();

  while(numero>0 && i>=0){
    binario[i] = numero%2;
    numero/=2;
    i--;
  }
  while(i>=0){
    binario[i] = 0;
    i--;
  }
  for (i = 0; i < 8; i++){
        putchar(binario[i] + '0');
    }
    putchar('\n');
}


int main(){
  binario();
}
