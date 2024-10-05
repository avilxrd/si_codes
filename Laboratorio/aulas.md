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
