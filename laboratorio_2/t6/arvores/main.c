#include "arvores.h"

/* 
Implemente um programa que verifique, para cada uma das árvores binárias abaixo, 
se são balanceadas, perfeitamente balanceadas ou nenhum dos casos ou ambos e liste seus nós em 
(i) pré-ordem, (ii) in-ordem e (iii) pós-ordem:

a) (1 (2 (4) (5)) (3 (6) (7)));

b) (A (B (D (F)) (E)) (C (G (H))))
*/

int main()
{
    Node *arvore_1 = cria_arvore_binaria();

    insere_arvore_binaria(&arvore_1, "1");
    insere_arvore_binaria(&arvore_1->sae, "2");
    insere_arvore_binaria(&arvore_1->sae->sae, "4");
    insere_arvore_binaria(&arvore_1->sae->sad, "5");
    insere_arvore_binaria(&arvore_1->sad, "3");
    insere_arvore_binaria(&arvore_1->sad->sae, "6");
    insere_arvore_binaria(&arvore_1->sad->sad, "7");

    printf("\narvore a ser lida: \n\n");
    imprime_arvore(arvore_1, 0);
    verifica_balanceamento(arvore_1);

    printf("\nimprimindo em 'pre ordem': \n");
    pre_ordem_arvore_binaria(arvore_1);
    printf("\nimprimindo em 'in ordem': \n");
    em_ordem_arvore_binaria(arvore_1);
    printf("\nimprimindo em 'pos ordem': \n");
    pos_ordem_arvore_binaria(arvore_1);
    
    Node *arvore_2 = cria_arvore_binaria();

    insere_arvore_binaria(&arvore_2, "A");
    insere_arvore_binaria(&arvore_2->sae, "B");
    insere_arvore_binaria(&arvore_2->sae->sae, "D");
    insere_arvore_binaria(&arvore_2->sae->sae->sae, "F");
    insere_arvore_binaria(&arvore_2->sae->sad, "E");
    insere_arvore_binaria(&arvore_2->sad, "C");
    insere_arvore_binaria(&arvore_2->sad->sae, "G");
    insere_arvore_binaria(&arvore_2->sad->sae->sae, "H");

    printf("\narvore a ser lida: \n\n");
    imprime_arvore(arvore_2, 0);
    verifica_balanceamento(arvore_2);

    printf("\nimprimindo em 'pre ordem': \n");
    pre_ordem_arvore_binaria(arvore_2);
    printf("\nimprimindo em 'in ordem': \n");
    em_ordem_arvore_binaria(arvore_2);
    printf("\nimprimindo em 'pos ordem': \n");
    pos_ordem_arvore_binaria(arvore_2);
    
}