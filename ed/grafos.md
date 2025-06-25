# Grafos
Utilizamos Grafos para várias aplicações na computação, como: caminhos entre véritces, menor distância, quantos vértices podem ser alcançados de um vértice. </br>
Um grafo é um conjunto não nulo finito de de nós (vértices) </br>
Exemplos de uso de grafos: links entre págnas da web, rotas emtre cidade, roteamento de pacotes, chamadas telefonicas, etc.</br>

### Especificações
Um grafo é composto por um conjunto de vértices e um conjunto de arestas. </br>
Os grafos podem ser direcionados (dirigidos) ou não. Nos grafos direcionados, as arestas indicam o sentido em que pode ir de um vértice a outro. </br>

Representação de um grafo direcionado: V = {0,...,5), A = {(0,1), (1,2), (2,2), (2,3), (3,0), (0,3), (5,4), (1,3)} </br>
Representação de um grafo não direcionado: V = {0,...,5}, A = {(0,1), (1,2), (2,3), (3,0), (4,5), (1,3)} </br>

### Vértices adjascentes
São os vizinhos diretos, os que com uma aresta conseguimos ir de um para o outro. </br>
### Grau de um vértice
Quantidade de arestas que "tocam" em um vértice (para grafos não direcionados).</br>
Para grafos direcionados, temos: grau total (somatório das arestas que saem e das que chegam), grau de incidÊmcia (quantas chegam) e grau de saída (quantas saem). </br>
Em grafos direcionados, um vértice pode "apontar" para ele mesmo. Isso é utilizado na implementação de compiladores, por exemplo, nos reconhecedores de nomes de variáveis. (autômato de reconhecimento).</br>

### Caminhos de um grafo
Um caminho de comprimento k, de um vértice a para um vértice b é uma sequência de vértices. O comprimento é dado pelo número de arestas no caminho. Se existe um caminho de um vértice a para um vértice b, dizemos que b é alcançável de a.

### Grafos ponderados
Um grafo ponderado possui pesos associados às suas arestas. Estes pesos normalmente representam custos ou distâncias </br>

### Matrizes de adjascência
Para n vértices, teremos uma matriz n x n. </br>
Marcamos com 1 a posição na matriz que liga dois vérices. Ex: matriz[A][E] = 1 (A -> E)  </br>
Para grafos ponderados, armazenamos diretamente o custo. Ex: matriz[A][E] = 18 (A -> E, "peso" 18) </br>
Dentre as vantagens, temos: facilidade de implementeção, velocidade na obtenção das adjacências. Recomendada para grafos densos, pois pode consumir bastante espaço. </br>

### Listas de adjacência
É feita através de um vetor de adjacência, contendo uma lista para cada vértice do grafo. </br>
Mais recomendada para grafos esparços.
