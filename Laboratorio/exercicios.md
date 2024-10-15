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

# 10/10

1. Faça um programa que lê um char e mais dois float. O programa deve então realizar uma operação sobre os dois números e imprimir o resultado dessa operação. A operação a ser realizada depende do char, se for `+`, `-`, `*` ou `/`. Se não for nenhum desses, o programa deve informar o problema e não realizar operação alguma. Use switch.  
2. Refaça o nosso primeiro programa lenum() para que ele aceite numeros sem precisar completar com zeros
1. Altere o programa das médias, para que calcule duas médias, a dos valores pares e a dos ímpares.
4. Um laboratório tem duas colônias de bactérias. A primeira tem 5000 indivíduos, e a população dobra a cada hora. A segunda tem 100000 indivíduos, que têm sua população multiplicada por 1,8 a cada hora. Faça um programa, usando repetição, para calcular quantas horas serão necessárias para que a população da primeira colônia seja maior que da segunda.
8. Um dos programas acima pede para o usuário adivinhar um número secreto. Faça um programa que faz o contrário: pede para o usuário pensar em um número e depois chuta valores até acertar. Para cada chute do programa, ele imprime o chute e pede para o usuário responder se acertou ou se está acima ou abaixo do valor secreto (digitando 0, 1 ou 2). O chute do programa deve ser um valor aleatório entre os valores que ainda são possíveis a cada chute. A função abaixo pode ser de ajuda, ela retorna um valor aleatório que está entre os limites fornecidos: