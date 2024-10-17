#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//================= Tarefa 26/09/2024 =================//
//Exercicio 01
int anos_dias(){
    int idade, dias;
    printf("Digite a sua idade: ");
    scanf("%d", &idade);

    dias = idade * 30 * 12;
    printf("%d", dias);
    return dias;
}

//Exercicio 02
int combustivel(){
    float preco, consumo, distancia, custo; 

    printf("Digite o preco do litro de gasolina: ");
    scanf("%f", &preco);
    printf("Digite a media de consumo do carro: ");
    scanf("%f", &consumo);
    printf("Digite a distancia a ser percorrida: ");
    scanf("%f", &distancia);

    custo = ((distancia/consumo)*preco);

    printf("Custo Final: R$ %.2f", custo);
    return custo;
}

//Exercicio 03
int carro_eletrico(){
    float valor_kwh, capacidade_bateria, autonomia, distancia, custo; 

    printf("Digite o valor do kWh: ");
    scanf("%f", &valor_kwh);
    printf("Digite a capacidade da bateria: ");
    scanf("%f", &capacidade_bateria);
    printf("Digite a autonomia do veiculo: ");
    scanf("%f", &autonomia);
    printf("Digite a distancia a ser percorrida: ");
    scanf("%f", &distancia);    

    custo = valor_kwh * (capacidade_bateria/autonomia) * distancia;

    printf("Custo Final: R$ %.2f", custo);
    return custo;
}

//Exercicio 04
int piscina(){
    float largura, comprimento, profundidade, volume;

    printf("Digite a largura da piscina: ");
    scanf("%f", &largura);
    printf("Digite o comprimento da piscina: ");
    scanf("%f", &comprimento);
    printf("Digite a profundidade da piscina: ");
    scanf("%f", &profundidade);

    volume = largura * comprimento * profundidade;
    printf("%.2f litros.\n", volume);
    return volume;
}

int main(){

}