#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "atuadores.h"

void at_DesprenderMoedasParaSeparacaoDoTroco(double* liberacaoMoedas)
{
    printf("Acionamento do atuador que desprende as moedas pra que sejam separadas para o troco \n");
}

void at_PromoverCaidaTrocoSeparadoParaClientePeloDeslocamentoDaBase()
{
  printf("Acionamento do atuador que promove caida das moedas separadas anterormente para o troco. \n");
  printf("Pelo deslocamento da base em que as moedas estao \n");
}

void at_PromoverCaidaDinheironoMoedeiroPeloDeslocamentodaBase() 
{
    printf("Acionamento do atuador que promove caida das moedas, que foram usadas para a compra do produto,");
    printf("no moedeiro(que é só uma caixa que guarda o dinheiro)");
}

void at_AlavancaDevolucaoDinheiro()
{
  printf("Acionamento do atuador que faz uma alavanca mecanica para que o dinheiro inserido seja devolviso");   
}

void at_EmpurrarProduto(int produto)
{
  printf("Acionamento do atuador que empurra o produto de número %d", produto);
}

void at_EmpurrarTravaPortaManutencao()
{
     printf("Acionamento do atuador que empurra empurra a trava da porta de manutencao, promovendo o travamento da porta");
}

void at_LiberarTravaPortaManutencao()
{
    printf("Acionamento do atuador que libera a tarva da porta de mmanutencao, posibilitando abertura da mesma");
}


