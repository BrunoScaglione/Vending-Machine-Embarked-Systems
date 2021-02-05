#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "sist_recebimento_dinheiro.h"

double VALOR_INSERIDO;

void rec_GuardarTotalInserido(double valorInserido){
  VALOR_INSERIDO = valorInserido;
}

double rec_LerDinheiroInserido(){
  return VALOR_INSERIDO;
}
