#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "display.h"

void disp_MostrarDinheiroInserido(double dinheiroInserido) {
  printf("Voce inseriu %f reais", dinheiroInserido);
 

}

void disp_MostrarErroCompraInvalida() {
  printf("Compra invalida, cancele a compra ou escolha outro produto");
}