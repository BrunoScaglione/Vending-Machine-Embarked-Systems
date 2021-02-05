#ifndef DB_PRODUTOS_H_INCLUDED
#define DB_PRODUTOS_H_INCLUDED

extern void prod_InserirProdutos(int* produtosInseridos);

extern void prod_DeletarProduto(int produtoDeletado);

extern double prod_LerPrecoProduto(int ProdutoLido);

extern int prod_LerQuantidadeProduto(int ProdutoLido);

#endif