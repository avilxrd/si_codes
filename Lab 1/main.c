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

//================= Tarefa 26/09/2024 =================//
//Exercicio 01
int anos_dias(){
    int idade, dias;
    printf("Digite a sua idade: ");
    scanf("%d", &idade);

    dias = idade * 30 * 12;
    printf("%d", dias);
    return dias;
}

//Exercicio 02
int combustivel(){
    float preco, consumo, distancia, custo; 

    printf("Digite o preco do litro de gasolina: ");
    scanf("%f", &preco);
    printf("Digite a media de consumo do carro: ");
    scanf("%f", &consumo);
    printf("Digite a distancia a ser percorrida: ");
    scanf("%f", &distancia);

    custo = ((distancia/consumo)*preco);

    printf("Custo Final: R$ %.2f", custo);
    return custo;
}

//Exercicio 03
int carro_eletrico(){
    float valor_kwh, capacidade_bateria, autonomia, distancia, custo; 

    printf("Digite o valor do kWh: ");
    scanf("%f", &valor_kwh);
    printf("Digite a capacidade da bateria: ");
    scanf("%f", &capacidade_bateria);
    printf("Digite a autonomia do veiculo: ");
    scanf("%f", &autonomia);
    printf("Digite a distancia a ser percorrida: ");
    scanf("%f", &distancia);    

    custo = valor_kwh * (capacidade_bateria/autonomia) * distancia;

    printf("Custo Final: R$ %.2f", custo);
    return custo;
}

//Exercicio 04
int piscina(){
    float largura, comprimento, profundidade, volume;

    printf("Digite a largura da piscina: ");
    scanf("%f", &largura);
    printf("Digite o comprimento da piscina: ");
    scanf("%f", &comprimento);
    printf("Digite a profundidade da piscina: ");
    scanf("%f", &profundidade);

    volume = largura * comprimento * profundidade;
    printf("%.2f litros.\n", volume);
    return volume;
}

//================= Aula 03/10/2024 =================//
bool diferenca(float gasolina, float etanol){
    float diferenca, media;
    media = (gasolina+etanol)/2;

    if(gasolina>etanol){
      diferenca = gasolina-etanol;
    }else if(gasolina<etanol){
      diferenca = etanol-gasolina;
    }else{
      return false;
    }

    if(diferenca>=media*0.05){
      printf("True");
      return true;
    }else{
      printf("False");
      return false;
    }

}

int gasolina_alcool(){
    float custo_gasolina, litro_gasolina, consumo_gasolina;
    float custo_etanol, litro_etanol, consumo_etanol;
    float distancia;

    //Gasolina
    printf("=============GASOLINA================\n");
    printf("Digite o valor do Litro da Gasolina: ");
    scanf("%f", &litro_gasolina);
    printf("Digite o consumo do carro com Gasolina (em Km/L): ");
    scanf("%f", &consumo_gasolina);
    //Etanol
    printf("\n==============ETANOL=================\n");
    printf("Digite o valor do Litro do Etanol: ");
    scanf("%f", &litro_etanol);
    printf("Digite o consumo do carro com Etanol (em Km/L): ");
    scanf("%f", &consumo_etanol);
    //Distancia
    printf("\n============DISTANCIA================\n");
    printf("Digite a distancia a ser percorrida: ");
    scanf("%f", &distancia);


    //Processamento
    custo_gasolina = (consumo_gasolina/distancia)*litro_gasolina;
    custo_etanol = (consumo_etanol/distancia)*litro_etanol;

    printf("Custo Gasolina: R$ %.2f\n", custo_gasolina);
    printf("Custo Etanol: R$ %.2f\n", custo_etanol);

    float media; 
    media = (litro_gasolina * litro_etanol)/2;
    
    if(diferenca(custo_gasolina, custo_etanol) == true){
      if(custo_gasolina>custo_etanol){
        printf("Gasolina é mais barato!");
      }else{
        printf("Etanol é mais barato!");
      }
    }else{
        printf("Tanto Faz!\n");
    }

}

int main(){
    gasolina_alcool();
}