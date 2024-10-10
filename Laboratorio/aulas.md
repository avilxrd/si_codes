# Primeira Aula [10/09]
### Introdução
Aula introdutória, explicando sobre como será o decorrer da disciplina.
* _Foi interrompida para o trote com os veteranos_

# Organização de um computador [12/09]

Um computador é formado basicamente por 3 partes fundamentais. São elas: <br>

###  Entrada e saída de dados
É a parte que interage com o usuário, por onde pode ser inserido dados através de periféricos, ou ser mostrado ao usuário através do vídeo.

### Processador
Um **processador** é composto por 2 partes: a **ULA** (unidade de lógica e aritmética) e a **UC** (unidade de controle).<br>
A ULA é responsável pela parte de lógica e aritmética, como seu nome indica. Portanto, ela que faz as contas dentro de um processador.<br>
Já a UC é a parte que controla as operações básicas do processador, recebe o código das intruções e comanda as outras unidades. Ela funciona em um ciclo de 3 passos: busca na memória o código da próxima instrução a ser executada, decodifica o código na sequência de ações a serem executadas e manda as unidades executarem as ações necessárias.

### Memória
A memória basicamente só sabe fazer duas coisas: **escrever** dados e **ler** dados. Embora seja simples, é extremamente importante para um computador.

# Primeiro programa em C [17/09]

Um programa em uma linguagem de programação é um texto, que deve ser colocado em um arquivo para que possa ser traduzido por um compilador para um programa equivalente em linguagem de máquina. <br>
Um programa é constituido por vários "programas" menores que fazem funções específicas, estes chamados de funções. Ao executar um programa em C, será rodada a função _main()_, e consequentemente as funções que a _main()_ chamar.<br>
Uma função é constituída por 4 partes: tipo, nome, argumentos e corpo.
```C
// tipo = int (inteiro), nome = main, (argumentos) = variaveis 
// que a função pode receber. 
int main(){
    // corpo da função (ou seja, o que ela faz)
}
```





# 26/09  

* Use scanf e printf. Faça uma função separada para o cálculo: a entrada e saída ficam na main, e o cálculo na função auxiliar.

1. Faça um programa que lê a idade de uma pessoa em anos e imprime a idade aproximada em dias. Use dados `int`.
2. Faça um programa que lê o preço de um litro de combustível, o consumo do veículo em km/l e a distância a percorrer, e calcula e imprime o custo em reais do combustível para percorrer essa distância. Use variáveis `float`; imprima o valor em reais com 2 casas, para representar os centavos. Informe ao usuário o que é o valor que se espera que ele digite a cada vez (para não ficar só a tela preta e o usuário tendo que conhecer a ordem em que os dados devem ser digitados).
3. Faça um programa semelhante ao anterior, para um carro elétrico, em que pergunta o valor do kWh, a capacidade da bateria em kWh, a autonomia do veículo em km com bateria cheia e a distância a percorrer em km.
4. Faça um programa que lê a largura, o comprimento e a profundidade de uma piscina em metros, e imprime sua capacidade em litros. A piscina tem o formato de um paralelepípedo._

# 03/10
### Exercícios
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

### Exercícios

1. Faça um programa que pede ao usuário o valor da base de cálculo do imposto
   de renda e imprime o valor da alíquota e da parcela a deduzir correspondentes.
2. Altere o programa anterior, de forma que tenha uma função que recebe a base
   de cálculo e retorna a alíquota, e outra que recebe a base de cálculo e
   retorna a parcela a deduzir. A impressão deve ser feita pela função
   principal.
3. Altere o programa anterior para calcular e imprimir o imposto de renda devido.

# 08/10
### Revisão do que vimos na outra aula: laços de repetição e tipo booleano
_Ao utilizar laços de repetição, é uma boa prática tentar testar primeiro os casos que já retornam o valor sem fazer muitos testes_<br>


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

### Operadores Lógicos
Existem 3 operadores lógicos em C, são eles: _AND (&&), OR (||) e NOT (!=)_<br>
Voltando ao exemplo anterior de dois e três numeros iguais, utilizando esses operadores lógicos poderíamos reescrever a função com apenas uma linha: 

```C
bool tres_iguais(float l1, float l2, float l3){
   return (a==b) && (a==c);
}
bool dois_iguais(float l1, float l2, float l3){
   return a == b || b == c || c == a;
}
//Retorna true se o valor de a for igual ao de b e de c
```
**Obs**:_os operadores & e | (apenas 1 caractere) existem e servem para outro propósito, eles fazem as operações AND e OR, porém bit-a-bit, ou seja, é uma operação diferente. É importante tomar cuidado para não errar os operadores ==, && e ||, colocando apenas um caractere._<br>

### Seleção Múltipla
Podemos utilizar os comandos de repetição para fazer uma seleção múltipla, por exemplo:
```C
if (opcao == 1){
   //Faça Algo
}else if(opcao == 2){
   //Faça algo
}//Assim por diante...
```
Como esta prática é muito comum na programação, o C tem um comando específico para seleções múltiplas, que facilita o processo:
```C
switch(opcao){
   case 'a': 
   case 'A': //Faça algo
   break;
   case 2: //Faça algo
   break;
   //...
   default: //É o caso padrão para caso nenhum dos casos foi executado. Tipo o else
   break;
}
```
O `break` é um comando não lógico, pois ele dá saltos na lógica do programas, porém o `switch case` em C foi feito de uma forma em que se o codigo entra em um caso ele vai executar todos os casos abaixo dele. <br>
Obs: após o `case` só aceita inteiros e constantes, não aceita contas e variáveis. O case sempre deve ser dado entre ' ' (aspas simples).<br>

# 10/10
Começamos a aula sendo apresentados ao "tipo de dado" NaN (not a number). Se alguma operação resultar em NaN, todas as operações conseguintes também serão. O mesmo acontece com o inf (infinito).<br>
### Laços de Repetição
A repetição é fundamental para os programas em geral. Em C, há 3 tipos de comandos de repetição. São eles: 
- While: sempre vai conferir se a condição é satisfeita antes de executar os comandos. Muito similar ao `do while`, porém com algumas diferenças.

```c
while(){//COndição
   //Instrução
}
```

- Do While: sempre vai executar uma vez antes de verificar se acondição é satisfeita. Se continuar verdadeira, o laço seguirá sendo executado.

```c
do{
   //Instrução
}
while();//Condição
```

- For: 

```c
for(;;){

}
```
### Exercicios
1. Faça um programa que lê um char e mais dois float. O programa deve então realizar uma operação sobre os dois números e imprimir o resultado dessa operação. A operação a ser realizada depende do char, se for `+`, `-`, `*` ou `/`. Se não for nenhum desses, o programa deve informar o problema e não realizar operação alguma. Use switch.  
2. Refaça o nosso primeiro programa lenum() para que ele aceite numeros sem precisar completar com zeros