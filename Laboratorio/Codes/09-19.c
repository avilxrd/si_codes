#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//================= Aula 19/09/2024 =================//
int lenum(){
	int d0, d1, d2;
	d0 = getchar() - '0';
	d1 = getchar() - '0';
	d2 = getchar() - '0';

	int x = d0 * 100 + d1 * 10 + d2;
	return x;
}

void impnum(int num){
	int d0, d1, d2;
	d0 = num / 100 % 10;
	d1 = num / 10 % 10;
	d2 = num / 1 % 10;
	putchar(d0 + '0');
	putchar(d1 + '0');
	putchar(d2 + '0');
	putchar('\n');
}

//================= Tarefa 19/09/2024 =================//
//02. Ignore o enter
int le_valor3(){
  int val, enter;
  int cent, dez, uni;

  printf("Digite um valor (decimal): ");
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

  printf("Valor em decimal: ");
  putchar(cent + '0');
  putchar(dez + '0');
  putchar(uni + '0');
  putchar('\n');

}

void imp_binario(int val){
  int b0, b1, b2, b3, b4, b5, b6, b7;

  b7 = val%2;
  b6 = val/2%2;
  b5 = val/4%2;
  b4 = val/8%2;
  b3 = val/16%2;
  b2 = val/32%2;
  b1 = val/64%2;
  b0 = val/128%2;

  printf("Valor em binario: ");
  putchar(b0 + '0');
  putchar(b1 + '0');
  putchar(b2 + '0');
  putchar(b3 + '0');
  putchar(b4 + '0');
  putchar(b5 + '0');
  putchar(b6 + '0');
  putchar(b7 + '0');
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
int binario_lacos(){
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
    
}