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
sites.google.com/view/edados20251 </br>

