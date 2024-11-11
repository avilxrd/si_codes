// Função para desenhar um tabuleiro com mini quadrados de 3x3
void desenha_tabuleiro(int tamanho, char str[tamanho]) {
    int l = (int)sqrt(tamanho);  // Lado do tabuleiro (l x l)
    int i, j, k;
    int aux = 0;  // Alternador de cor

    for (i = 0; i < l; i++) {  // Itera sobre as linhas do tabuleiro
        for (j = 0; j < 3; j++) {  // Cada célula é representada por 3 linhas

            for (k = 0; k < l; k++) {  // Itera sobre as colunas do tabuleiro
                // Determina a cor do fundo (alternando entre preto e branco)
                if ((i + k) % 2 == 0) t_cor_fundo(255, 255, 255);  // Branco
                else t_cor_fundo(0, 0, 0);  // Preto

                // Imprime a célula 3x3
                if (j == 1 && str[i * l + k] == 'Q') printf(" Q ");
                else printf("   ");
            }

            // Finaliza a linha do tabuleiro
            t_cor_normal();
            printf("\n");
        }
    }
    printf("\n\n");
}