# t1 - desenho de figuras com ASCII

Faça um programa que permite ao usuário desenhar figuras, conforme descrito abaixo.
O programa deve ser escrito em linguagem C, levando os seguintes pontos em consideração:
- o programa deve usar funções, cada uma com objetivo claro e com nome condizente;
- deve ter um comentário antes de cada função, dizendo brevemente o que a função faz;
- o programa deve usar laços, com o comando `for` quando o número de repetições for conhecido e `while` quando não for;
- o programa deve ser bem formatado, com uso coerente de espaços (horizontais e verticais), (), {}, indentações;
- a primeira linha do programa deve ser um comentário com "t1 l124b " e o nome do aluno;
- o arquivo .c contendo o programa deve ser enviado como anexo em email para o endereço da disciplina, com "t1 l124b" no assunto.

O programa deve ler instruções sobre a figura a desenhar, depois desenhar a figura, depois voltar a pedir instruções etc, até que a instrução seja para terminar o programa.
Uma instrução para o programa é constituída de:
- um caractere que identifica o desenho a executar, uma letra de 'a' a 'h', ou 'z', que identifica o final da execução. Qualquer outro caractere não deve ser aceito, e o pedido deve ser refeito ao usuário;
- um outro caractere, que será usado para realizar o desenho. Deve ser aceito qualquer caractere imprimível ASCII (entre '!' e '~'); qualquer outro caractere não deve ser aceito e o programa deve pedir novamente ao usuário;
- um número positivo, que representa o tamanho do desenho. Número não positivo não deve sera aceito e o programa deve pedir novamente.

Caso a identificação do desenho seja 'z', o programa deve encerrar sua execução, sem pedir os demais dados de uma instrução.

As figuras estão abaixo, desenhadas como se o usuário tivesse escolhido o caractere '*' e o tamanho 3.
- figura 'a'
```
*
**
***
```
- figura 'b'
```
***
**
*
```
- figura 'c'
```
  *
 **
***
```
- figura 'd'
```
***
 **
  *
```
- figura 'e'
```
  *
 ***
*****
```
- figura 'f'
```
  *
 ***
*****
 ***
  *
```
- figura 'g'
```
  *
 * *
*   *
 * *
  *
```
- figura 'h'
```
*******
*** ***
** * **
* *** *
** * **
*** ***
*******
```