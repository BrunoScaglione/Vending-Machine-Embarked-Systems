#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "db_produtos.h"

// produto, quantidade, preco
static double DATA_PRODUTOS [27] = {
  PRODUTO_1, 9, PRECO_PRODUTO_1,
  PRODUTO_2, 9, PRECO_PRODUTO_2,
  PRODUTO_3, 9, PRECO_PRODUTO_3,
  PRODUTO_4, 9, PRECO_PRODUTO_4,
  PRODUTO_5, 9, PRECO_PRODUTO_5,
  PRODUTO_6, 9, PRECO_PRODUTO_6,
  PRODUTO_7, 9, PRECO_PRODUTO_7,
  PRODUTO_8, 9, PRECO_PRODUTO_8,
  PRODUTO_9, 9, PRECO_PRODUTO_9
};

int prod_LerQuantidadeProduto(int ProdutoLido) {
  // input eh o numero do produto de 1 a 9
  int index;
  // conversao para index do produto em DATA_PRODUTOS
  index = (ProdutoLido -1)*3;
  return DATA_PRODUTOS[index + 1];
}

double prod_LerPrecoProduto(int ProdutoLido) {
  // input eh o numero do produto de 1 a 9
  int index;
  // conversao para index do DATA_PRODUTOS
  index = (ProdutoLido -1)*3;
  return DATA_PRODUTOS[index + 2];
}

void prod_InserirProdutos(int* produtosInseridos) {
  // recebe input do tipo: {6, 5}
  //que significa inserir 5 produtos de número 6 
  int index;
  int numProduto = produtosInseridos[0];
  int quantidadeInserida = produtosInseridos[1];
  // conversao para index do DATA_PRODUTOS
  index = (numProduto -1)*3;
  int quantidadeAtual = DATA_PRODUTOS[index + 1];
  DATA_PRODUTOS[index + 1] = quantidadeAtual + quantidadeInserida;
}

void prod_DeletarProduto(int produtoDeletado) {
  // input eh o numero do produto de 1 a 9
  int index;
  // conversao para index do DATA_PRODUTOS
  index = (produtoDeletado -1)*3;
  int quantidade = DATA_PRODUTOS[index + 1];
  DATA_PRODUTOS[index + 1] = quantidade -1;
}



