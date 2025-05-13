# Implementando Árvores na Linguagem C

Fonte: Livro de Estrutura de Dados, André Backes

### Árvore
Por definição, uma árvore é uma abstração matemática, utilizada para representar estruturas hierárquicas não lineares dos objetos modelados.

Podemos aplicar árvores em vários casos. Basicamente, qualquer problema em que exista algum tipo de hierarquia pode ser representado como uma árvore.

Uma árvore é definida utilizando um conjunto e nós (ou vértices). Fazendo uma conexão com grafos, uma árvore é um grafo não direcionado, conexo e acíclico.

-> Conexo: porque existe exatamente um caminho entre quaisquer dois de seus nós.

-> Acíclico: porque a árvore não possui ciclos.

Em computação, uma árvore crescem de cima para baixo, ou seja, a raíz se encontra no topo e as folhas na parte mais inferior.

### Nomenclatura

* raíz: é o nó mais alto de uma árvore, ou seja, o único que não possui pai.

* pai (ou ancestral): é o nó antecessor imediato de outro nó.

* filho: é o nó sucessor imediato de outro nó.

* nó folha (terminal): é o nó que não possui filhos

* nó interno (não terminal): é qualquer nó que possui ao menos um filho.

* caminho: é uma sequência de nós que existe sempre uma aresta ligando o nó anterior com o seguinte.

### Grau do nó e subarvores

Dado um determinado nó da árvore, cada filho seu é considerado a raiz de uma nova subarvore. Ou seja, qualquer nó é a raíz de uma subarvore, consistindo dele e dos nós abaixo dele.
O grau de um nó é dado pelo número de subarvores que ele possui.

### Altura e nível da árvore

O nível de um nó é dado pelo número de nós que existem no caminho entre esse nó e a raíz (nivel 0).
Já a altura (profundidade) da árvore é o número total de níveis de uma árvore, ou seja, o comprimento do caminho mais longo da raíz até uma de suas folhas.

# Tipos de árvores

Pensando em diferentes tipos de aplicação, foram "criados" diferentes tipos de árvores.

## Árvore binária
É um tipo especial de árvore, onde cada nó pode possuir 0, 1 ou 2 (no máximo) subarvores: a da esquerda e da direita. 
Se o nó não possuir nenhuma subarvore, ele será um nó folha.
-> São muito úteis para modelar situações em que, a cada ponto do processo, é preciso tomar uma decisão entre duas direções.

A aplicação de árvores binárias é útil na implementação de banco de dados, compiladores, compressão de dados e em representações de expressões aritméticas. Também é importante na manutenção de estruturas na qual a ordem é importante.

### Tipos de Árvores Binárias
Elas podem ser divididas em 3 tipos: estritamente binária, quase completa e cheia. Elas diferem entre si pelo núumero de subarvores de um nó e posicionamento do nó na árvore.
* Estritamente binária: cada nó possui sempre nenhuma ou duas subarvores. Não existe nenhum nó interno com apenas um filho.

* Cheia (completa): é uma árvore estritamente binária, em que todos os seus nós folhas estão no mesmo nível. Nesse tipo,é possível calcular o número de nós por nível, assim como o número de nós totais na árvore. 
- Nível n possui 2^n nós. 
- Se um nível n possui m nós, o nível n+o possuirá 2*m nós.
- Uma árvore de altura H possui 2^h nós. 

* Quase completa: é uma árvore em que a diferença de altura entra as subarvores de qualquer nó , nomáximo igual a um. Ou seja, cada nó deve estar no nível D ou D-1.

### Tipos de implementação
Existem duas abordagens principais utilizadas para a implementação de árvores em um computador: usando um array (alocação estática) ou uma lista encadeada (alocação dinâmica).
Não existe uma implementação que seja melhor que a outra em todos os casos, independentemente da aplicação escolhida, é possível realizar as mesmas operações básicas necessárias, são elas: criação, inserção de um elemento, remoção de um elemento, busca por um elemento, destruição da árvore, informações com número de nós, etc.
Vamos analisar como funciona cada tpo de implementação:

### Implementação utilizando um Array (heap)
