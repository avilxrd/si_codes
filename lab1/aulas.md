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

# Seleção Múltipla [08/10]
### Revisão do que vimos na outra aula: laços de repetição e tipo booleano
_Ao utilizar laços de repetição, é uma boa prática tentar testar primeiro os casos que já retornam o valor sem fazer muitos testes_<br>

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

# Laços de Repetição [10/10]
Começamos a aula sendo apresentados ao "tipo de dado" NaN (not a number). Se alguma operação resultar em NaN, todas as operações conseguintes também serão. O mesmo acontece com o inf (infinito).<br>

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

# Comando For [15/10]

### Gerando numeros "aleatórios"
O C não consegue gerar numeros aleatórios do nada, todo número gerado é fruto de uma conta feita pela função `rand`. Para contornar isso, temos a função `srand()`, que, da mesma forma, gera um número baseada em um cálculo, porém esta função admite um parâmetro para começar a gerar números a partir de um certo ponto de partida. Com isso podemos usar a seguinte função e gerar números aleatórios com mais variedade.

```c
#include <time.h>
srand(time(0))
```
Utilizando o `time()`, podemos gerar um número aleatório com base no segundo em que o programa foi rodado, tornando muito difícil de gerar números repetidos, pois o programa teria que ser executado no mesmo segundo.

### Repetindo `n` vezes um laço
É comum querer repetir um trecho de código um determinado número de vezes. Com o `while` e `do while` não há meneiras de fazer um laço controlado por uma variável, por isso foi criado o comando `for`, cuja principal função é criar laços controlados por uma variável.
```c
for(int i=0; i<300; i++){ //(var_controle; crit_de_parada; incremento)
   //Comando a ser repetido
}
```
O comando `while` consegue fazer isso, porém com mais código e menos claro. Outra vantagem de utilizar o `for`, é executar o `incremento` ao utilizar o `continue`.<br>
_Exemplo_:
```c
ct = 0;
while(ct<300){
   if(i%2==1) continue;
   printf("*");
   ct = ct + 1;
}

for(int i=0; i<300; i++){
   if(i%2 ==1) continue;
   printf("*");
}
```
### Operadores de incremento
Junto com o laço `for`, é sempre muito utilizado o operador `++`(também o `--`, `+=`, `-=`, entre outras variações). Ele pode ser utilizado de 2 formas:
- b = a++: b será o valor antigo de a, e depois o a é incrementado;
- b = ++a: incrementa no a, e seu novo valor soma com o b;
Outro operador é o `+=`. É uma atribuição e depois incremento;
```c
int a = 5;
b = a++; //b=5, a=6
b = ++a; //b=6, a=6
```
# Trabalho e Revisão do Laço For [17/10]
# Vetores [22/10]
Um vetor é uma sequência de variáveis de um mesmo tipo e referenciados por um nome único. OS valores podem ser acessados pelo seu índice, tem tamanho predefinido e fixo.
