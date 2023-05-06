#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int qntProdutos;
    int qntCompostos;
    float **matrizPrincipal;
    float *valores;
    float *custos;
    float *limites;
    float *lucroProduto;
    int i;
    int j;

    scanf("%d %d", &qntProdutos, &qntCompostos);

    matrizPrincipal = (float **)calloc(qntProdutos, sizeof(float *));
    for (i = 0; i < qntProdutos; i++)
        matrizPrincipal[i] = (float *)calloc(qntCompostos, sizeof(float));

    valores = (float *)calloc(qntProdutos, sizeof(float));
    custos = (float *)calloc(qntCompostos, sizeof(float));
    limites = (float *)calloc(qntCompostos, sizeof(float));
    lucroProduto = (float *)calloc(qntProdutos, sizeof(float));

    for (i = 0; i < qntProdutos; i++)
        scanf("%f", &valores[i]);
    for (i = 0; i < qntCompostos; i++)
        scanf("%f %f", &custos[i], &limites[i]);
    for (i = 0; i < qntProdutos; i++)
        for (j = 0; j < qntCompostos; j++)
            scanf("%f", &(matrizPrincipal[i][j]));

    for (i = 0; i < qntProdutos; i++)
    {
        for (j = 0; j < qntCompostos; j++)
        {
            lucroProduto[i] += custos[j] * matrizPrincipal[i][j];
        }
        lucroProduto[i] = valores[i] - lucroProduto[i];
    }

    char *equacoes;
    equacoes = (char *)malloc(qntProdutos * (qntCompostos * (6 * sizeof(char) + 1 * sizeof(int))) + 1 * sizeof(float) + 5 * sizeof(char));

    char *variavel;
    variavel = (char *)malloc(6 * sizeof(char) + 1 * sizeof(int));

    // Função objetivo
    sprintf(equacoes, "max: ");
    for (i = 0; i < qntProdutos; i++)
    {
        if (i == 0)
            sprintf(variavel, "%fx%d", lucroProduto[i], (i + 1));
        else
            sprintf(variavel, " + %fx%d", lucroProduto[i], (i + 1));
        strcat(equacoes, variavel);
    }
    strcat(equacoes,";");
    printf("%s\n",equacoes);

    // Equações limitantes
    for (i = 0; i < qntCompostos; i++)
    {
        for (j = 0; j < qntProdutos; j++)
        {
            if (j == 0)
                sprintf(equacoes, "%5fx%d", matrizPrincipal[j][i], (j + 1));
            else
            {
                sprintf(variavel, " + %5fx%d", matrizPrincipal[j][i], (j + 1));
                strcat(equacoes, variavel);
            }
        }
        sprintf(variavel, " <= %f;", limites[i]);
        strcat(equacoes, variavel);
        printf("%s\n", equacoes);
    }
}