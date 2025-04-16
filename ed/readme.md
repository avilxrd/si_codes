# Estrutura de Dados

## Listas duplamente encadeadas (07/04)
- Uma lista é duplamente encadeada quando temos um encadeamento duplo, ou seja, dentro de um NÓ, temos um ponteiro que aponta para o seu PRÓXIMO e para seu ANTERIOR. </br>
- Isso nos permite navegar na lista através de 2 ponteiros. </br>
- Se temos um ponteiro para o último nó da lista, podemos percorrer a lista na ordem inversa da mesma forma que faziamos com uma lista simplesmente encadeada, porém usando um ponteiro para Lista ANTERIOR. </br>
- Para manipular listas duplamente encadeadas, precisamos ajeitar os dois ponteiros. </br>
### Estrutura da lista
```c
struct node{
  int valor;
  struct node* prox;
  struct node* ant;
};
typedef struct node Node;
```
### Função de Inserção 
```c
Node* insere_lista(Node* lista, int valor)
{
  Node* novo = (Node*)malloc(sizeof(Node));
  novo->valor = valor;
  novo->prox = lista;
  novo->ant = NULL;
  if (lista != NULL) lista->ant = novo;
  return novo;
}
```
### Função de Busca
```c
Node* busca_lista(Node* lista, int valor)
{
  Node* p;
  for (p=lista; p!=NULL; p=p->prox) if (p->info == valor) return p;
  return NULL;
}
```

### Função de Remoção
Podemos fazer uma remoção no início, meio ou fim da lista. O código terá algumas modificações dependendo de onde for feita a remoção </br>
```c
Node* remove_lista(Node* lista, int valor)
{
  Node* p = busca_lista(lista, valor);
  if (p == NULL) return lista; //não achou o elemento na lista 
  if (lista == p) lista = p->prox; //testa se é o primeiro elemento
  else p->ant->prox = p->prox;
  if (p->prox != NULL) p->prox->ant = p->ant;
  free(p); //desaloca a memoria do nó p
  return lista;
}
```
## Trabalho 01: representação de matrizes com listas encadeadas
O pdf do trabalho está no site da disciplina</br>

**[Site da Disciplina](https://sites.google.com/view/edados20251/)**.

## Listas de Tipos Estruturados
Até então, estavamos armazenando nos Nós de nossa lista, valores simples, como um Int. Porém, nada nos impede de armazenarmos mais de um dado (de tipos iguais ou diferentes).</br>
### Exemplo de Estrutura que guarda mais de um dado:
```c
struct node
{
    int numero1;
    float numero2;
    struct node* prox;
};

typedef struct node Node;
```
Caso quisermos armazenar os lados de um retângulo, por exemplo, podemos armazenar 2 floats, ou podemos armazenar outra struct do tipo Retangulo.
```c
struct retangulo
{
    float lado1;
    float lado2;
};
typedef struct retangulo Retangulo;

struct node
{
    Retangulo retangulo;
    struct node* prox;
};
typedef struct node Node;
```
Ainda temos outra possibilidade: armazenar o ponteiro para um Retangulo na nossa estrutura.
```c
struct retangulo
{
    float lado1;
    float lado2;
};
typedef struct retangulo Retangulo;

struct node
{
    Retangulo* retangulo;
    struct node* prox;
};
typedef struct node Node;
```

## Listas de Tipos Heterogêneos
São listas em que as informações diferem de Nó para Nó.</br>
Obs: as listas são homogênes, pois o Nó é sempre o mesmo, o que é heterogêneo são as informações armazenadas (tipos diferentes ou não).</br>
Para entender as listas de tipos heterogêneos, vamos criar 3 estruturas que representem formas geométricas.
```c
struct retangulo
{
    float base;
    float altura;
}
typedef struct retangulo Retangulo;

struct triangulo
{
    float base;
    float altura;
}
typedef struct triangulo Triangulo;

struct circulo
{
    float raio;
}
typedef struct circulo Circulo;

```
Para encadear essas informações, precisaremos utilizar um Ponteiro Genérico.</br>
Na nossa estrutura, precisaremos ter um identificador para saber qual o tipo de Nó.</br>

```c
struct node
{
    void* informacao;  //ponteiro genérico (sem tipo)
    int tipo;          //identificador de qual tipo é o nó
    struct node* prox; //ponteiro para o próximo elemento
}
typedef struct node Node;
```

# Pilhas

## Introdução e implementação de pilhas 16/04
Uma pilha é um container de objetos que são inseridos e retirados pelo topo.</br>
As pilhas seguem uma política de inserções e remoções denominadas LIFO (last in, first out), ou seja, a última a ser inserida é a primeira a ser retirada.</br>
Objetos podem ser inseridos em uma pilha a qualquer momento, mas somente o último objeto inserido pode ser removido da pilha imediatamente, não podemos remover um elemento do meio da pilha.</br>
As operações principais são comumente chamadas de PUSH (adicionar um elemento ao topo da pilha / empilha) e POP (remover o elemento do topo da pilha / desempilha)</br>
Podemos implementar uma pilha de duas formas: armazenando os elementos em um vetor ou em uma lista encadeada.</br>
Podemos observar que para fazer um POP a pilha nao pode estar vazia, enquanto para fazer um PUSH ela não pode estar cheia.</br>

### Implementando uma pilha com um vetor
```c
struct pilha
{
    int topo;            //índice do elemento do topo da pilha, também pode ser usado para saber quantos elementos temos na pilha
    float vetor[50];     //vetor que armazena os elementos da pilha [numero maximo de elementos da pilha]
}Pilha;
```
### Implementando uma lista com um vetor
```c
struct pilha
{
    int topo;            //índice do elemento do topo da pilha, também pode ser usado para saber quantos elementos temos na pilha
    float* lista;        //lista que armazena os elementos da pilha
}Pilha;
```

