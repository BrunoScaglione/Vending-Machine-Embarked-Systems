#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "sensores.h"

// {
//   valordamoeda, quantidade
// }

static double BUFFER_MOEDAS_INSERIDAS [9] = 
{
  0.05, 0,
  0.1, 0,
  0.25, 0,
  0.5, 0, 
  1.0, 0
};

int sen_DetectaMoedaInserida(){
  printf("Para inserir uma moeda de 5 centavos digite '1'  e pressione enter");
  printf("Para inserir uma moeda de 10 centavos digite '2' e pressione enter");
  printf("Para inserir uma moeda de 25 centavos digite '3' e pressione enter");
  printf("Para inserir uma moeda de 50 centavos digite '4' e pressione enter");
  printf("Para inserir uma moeda de 1 real digite '5' e pressione enter");
  printf("Se voce nao quer inserir moedas digite qualquer outra coisa e pressione enter");

  char moeda;
  double valor;
  moeda = getchar( );

  int numMoeda = atoi(moeda);
  if (1 <= numMoeda <= 5) {
    int index;
    // conversao para index do buffer
    index = 2*numMoeda - 1;
    int quantidadeInseridaAtual = BUFFER_MOEDAS_INSERIDAS[index];
    BUFFER_MOEDAS_INSERIDAS[index] = quantidadeInseridaAtual + 1;
    return true;
  }
  return false;
}


double* sen_LerBufferMoedasInseridas() {
  return BUFFER_MOEDAS_INSERIDAS;
}

void sen_ZerarBufferMoedasInseridas() {
  int i;
  // zerar as quantidadades
  for(i=1; i<=9; i+2) {
    BUFFER_MOEDAS_INSERIDAS[i] = 0;
  }
}

int sen_DetectaFechamentoPortaManutencao(){
  printf("Se voce esta aqui, é porque terminou ou nao quis mais fazer manutencao (cadastro de produto ou troco)");
  printf("Digite 'X' para fechar a porta de manutencao");
  printf("Para nao fechar a porta digite qualquer outra coisa");
  char fechar;
  fechar = getchar( );
  if (fechar == 'X') 
    return true;
  return false;
}