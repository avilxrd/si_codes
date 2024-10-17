# 17/09

1. Faça um programa que pede ao usuário o valor da base de cálculo do imposto
   de renda e imprime o valor da alíquota e da parcela a deduzir correspondentes.
2. Altere o programa anterior, de forma que tenha uma função que recebe a base
   de cálculo e retorna a alíquota, e outra que recebe a base de cálculo e
   retorna a parcela a deduzir. A impressão deve ser feita pela função
   principal.
3. Altere o programa anterior para calcular e imprimir o imposto de renda devido.

# 26/09  

* Use scanf e printf. Faça uma função separada para o cálculo: a entrada e saída ficam na main, e o cálculo na função auxiliar.

1. Faça um programa que lê a idade de uma pessoa em anos e imprime a idade aproximada em dias. Use dados `int`.
2. Faça um programa que lê o preço de um litro de combustível, o consumo do veículo em km/l e a distância a percorrer, e calcula e imprime o custo em reais do combustível para percorrer essa distância. Use variáveis `float`; imprima o valor em reais com 2 casas, para representar os centavos. Informe ao usuário o que é o valor que se espera que ele digite a cada vez (para não ficar só a tela preta e o usuário tendo que conhecer a ordem em que os dados devem ser digitados).
3. Faça um programa semelhante ao anterior, para um carro elétrico, em que pergunta o valor do kWh, a capacidade da bateria em kWh, a autonomia do veículo em km com bateria cheia e a distância a percorrer em km.
4. Faça um programa que lê a largura, o comprimento e a profundidade de uma piscina em metros, e imprime sua capacidade em litros. A piscina tem o formato de um paralelepípedo._

# 03/10

Faça um programa que:
1. Lê dois números, imprime qual o maior.
1. Lê dois números, imprime "sao iguais" ou imprime qual o menor.
1. Lê um número, diz se é par ou ímpar (use o resto da divisão por 2 para decidir).
1. Lê 3 números, imprime qual o maior.
1. Lê 3 números, imprime qual o do meio.
5. Lê 2 números entre 0 e 10, que representam as notas de um aluno, e mais dois números, que representam os pesos de cada nota. Se a média ponderada das notas for pelo menos 7, informa que o aluno está aprovado. Se não for, lê mais um número, que é a nota do exame. Se a média entre o exame e a média anterior for pelo menos 5, informa que o aluno está aprovado. Senão, informa que o aluno reprovou.
6. Lê a temperatura prevista, e recomenda o usuário sobre a roupa a usar. Se a
   temperatura for inferior a 18 graus, deve sugerir casaco, senão, camiseta.
7. Altere o programa anterior para também ler a velocidade prevista do vento.
   Com vento superior a 10 km/h, a temperatura para casaco é 20°.
8. Altere o programa anterior para também ler a previsão de chuva ('S' ou 'N').
   O programa deve também responder se o usuário deve levar guarda-chuva se
   houver previsão de chuva. Também deve levar guarda-chuva se a temperatura for
   superior a 35 graus.

# 08/10

### Exercicios de Aula
1. Fazer uma funcao que diz se 3 lados sao iguais ou 2 lados sao iguais.<br>

```C
//Resolução do professor:

//3 iguais
{
   if(a != b) return false;
   if(a != c) return false;
   return true;
}
// 2 iguais
{
   if (a == b) return true;
   if (a == c) return true;
   if (b == c) return true;
   return false;
}
```
Observa-se que ele faz com uma lógica bem mais simples, exluindo as possibilidades com poucas linhas de código.<br>


# 10/10

1. Faça um programa que lê um char e mais dois float. O programa deve então realizar uma operação sobre os dois números e imprimir o resultado dessa operação. A operação a ser realizada depende do char, se for `+`, `-`, `*` ou `/`. Se não for nenhum desses, o programa deve informar o problema e não realizar operação alguma. Use switch.  
2. Refaça o nosso primeiro programa lenum() para que ele aceite numeros sem precisar completar com zeros
3. Altere o programa das médias, para que calcule duas médias, a dos valores pares e a dos ímpares.
4. Um laboratório tem duas colônias de bactérias. A primeira tem 5000 indivíduos, e a população dobra a cada hora. A segunda tem 100000 indivíduos, que têm sua população multiplicada por 1,8 a cada hora. Faça um programa, usando repetição, p'ara calcular quantas horas serão necessárias para que a população da primeira colônia seja maior que da segunda.
5. Um dos programas acima pede para o usuário adivinhar um número secreto. Faça um programa que faz o contrário: pede para o usuário pensar em um número e depois chuta valores até acertar. Para cada chute do programa, ele imprime o chute e pede para o usuário responder se acertou ou se está acima ou abaixo do valor secreto (digitando 0, 1 ou 2). O chute do programa deve ser um valor aleatório entre os valores que ainda são possíveis a cada chute. A função abaixo pode ser de ajuda, ela retorna um valor aleatório que está entre os limites fornecidos:

# 15/10

1. Faça uma função que recebe 2 argumentos: um inteiro que diz quantos caracteres se quer imprimir e um char que identifica o caractere que se quer imprimir tantas vezes. Por exemplo, se a função receber `(5, '@')`, deve imprimir `@@@@@`.
2. Faça uma função parecida, mas que além de imprimir os tantos caracteres (para o que ela deve usar a função acima), imprime também um '\n' no final.
3. O programa que segue, que usa a função do exercício anterior, deve imprimir algo parecido com o desenho abaixo quando executado. Execute o programa para conferir que faz o que é pedido.
```
*
**
***
****
```
```c
#include <stdio.h>

void funcao_do_ex_2(int n, char c)
/// corpo da função

int main()
{
  funcao_do_ex_2(1, '*');
  funcao_do_ex_2(2, '*');
  funcao_do_ex_2(3, '*');
  funcao_do_ex_2(4, '*');
}
```
4. A função `main` do programa anterior chama 4 vezes a funcao_do_ex_2. Altere para usar um laço for para realizar essa repetição.
5. Coloque o laço do exercício 4 em uma nova função, que recebe como parâmetro o número de linhas que deve desenhar. Com a função main abaixo, o programa deve fazer o mesmo desenho:
```c
int main()
{
  funcao_do_ex_5(4);
}
```
Se trocar o `4` acima por `2`, a saída deve ser:
```
*
**
```
6. Altere a função main para pedir ao usuário o número de linhas a imprimir (a altura do triângulo).
7. Faça uma nova função, semelhante à do ex. 5, mas que desenha o triângulo ao contrário. Para argumento 3:
```c
***
**
*
```
8. Faça funções para os desenhos abaixo (todos com argumento 3):
```
  *
 **
***
```
```
***
 **
  *
```
```
  *
 ***
*****
```
```
  *
 ***
*****
 ***
  *
```
```
  *
 * *
*   *
 * *
  *
```
```
*******
*** ***
** * **
* *** *
** * **
*** ***
*******
```
9. Faça uma função que imprime o calendário de um mês, como exemplificado abaixo.
A função deve receber como argumento dois inteiros. O primeiro contém o número de dias do mês (28 a 31), e o segundo o dia da semana em que cai o dia primeiro (0 a 6, 0 é domingo, 1 é segunda, 6 é sábado).
Por exemplo, se receber `(30, 4)`, deve imprimir:
```
  D  S  T  Q  Q  S  S
              1  2  3
  4  5  6  7  8  9 10
 11 12 13 14 15 16 17
 18 19 20 21 22 23 24
 25 26 27 28 29 30   
```