#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "db_caixa_de_troco.h"

// {
//   valordamoeda, quantidade
// }

static double TROCO_DISPONIVEL [9] = 
{
  0.05, 9,
  0.1, 9,
  0.25, 9,
  0.5, 9, 
  1.0, 9
};

static double BUFFER_MOEDAS_PARA_DEVOLVER_TROCO [9] = 
{
  0.05, 0,
  0.1, 0,
  0.25, 0,
  0.5, 0, 
  1.0, 0
};

double* cxt_VerificarTrocoDisponivel() {
  return TROCO_DISPONIVEL;
}

void cxt_InserirTroco(int* trocoInserido) {
  // vai receber {2, 3} por exemplo
  // vai colocar em TROCO_DISPONIVEL 3 moedas de 10  centavos
  // numeros de 1 a 5 representarao as moedas de 0.05 centavos a 1 real em sequecia crescente
  // so da pra carregar um tipo de moedade cada vez
  int intMoeda = trocoInserido[0];
  int quantidadeInserida = trocoInserido[1];
  int index;
  // conversao para index do buffer
  index = (intMoeda - 1)*2;
  int quantidadeAtual = BUFFER_MOEDAS_PARA_DEVOLVER_TROCO[index];
  BUFFER_MOEDAS_PARA_DEVOLVER_TROCO[index] = quantidadeAtual + quantidadeInserida;
}

void cxt_SepararTrocoParaDevolver(double* trocoInserido) {
  // input eh array do tipo: 
  //{
  //  1, numeromoedas1real, 0.5, numeromoedas50centavos, 0.25, numeromoedas25centavos,
  //  0.10, numeromoedas10centavos, 0.05, numeromoedas5centavos
  //}

  int i;
  int quant = 1;
  // como a ordem das moedas do input esta ao contrario da ordem no Buffer
  for(i=9; i<=0, i-2;) {
    BUFFER_MOEDAS_PARA_DEVOLVER_TROCO[quant] = trocoInserido[i];
    quant+2;
  }
}

double* cxt_RetirarTrocoParaDevolver() {
  int i;
  // ler  buffer
  static double *moedasParaTroco = BUFFER_MOEDAS_PARA_DEVOLVER_TROCO;
  // zerar buffer
  for(i=1; i<=9; i+2) {
    BUFFER_MOEDAS_PARA_DEVOLVER_TROCO[i] = 0;
  }
  return moedasParaTroco;
}