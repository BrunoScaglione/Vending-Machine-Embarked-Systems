#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "teclados.h"

static char BUFFER_ESCOLHA_CLIENTE;

static char BUFFER_SENHA_MANUTENCAO [100];

static char BUFFER_TECLADO_INTERNO_TIPO_DE_CADASTRO [4];

static char BUFFER_TECLADO_INTERNO_QUANTIDADE_CADASTRADA [100];

char tec_TecladoClienteRetornaTeclaPressionada() {
  printf("Teclado disponivel para o Cliente");
  printf("Digite 'S' e pressione enter se você quer submeter o dinheiro inserido");
  printf("Digite 'C' se voce quer cancelar a compra e obter o dinheiro de volta");
  printf("O teclado numerico tambem esta disponivel");
  printf("Atencao: Esse teclado só servira de uso apos o usuario ter submetido o dinheiro");
  printf("Digite o número do produto que deseja comprar (1-9) se voce já submeteu o dinheiro");
  char escolha;
  escolha = getchar( );
  BUFFER_ESCOLHA_CLIENTE = escolha;
  return escolha; 
}

char tec_LerBufferEscolhaCliente() {
  return BUFFER_ESCOLHA_CLIENTE;
}

void tec_ZerarBufferEscolhaCliente() {
  BUFFER_ESCOLHA_CLIENTE = 0;
}

char* tec_TecladoAutenticacaoRetornaSenhaTeclada() {
  printf("Teclado Numérico de Autenticacao Para Manutencao");
  printf("Se voce for da manutencao, digite a senha neste teclado, para abrir a porta de manutencao");
  printf("Se voce nao quer se autenticar, tecle apenas enter");
  char senha [100];
  fgets(senha, 100, stdin);
  // no fgets sempre fica um \n do enter no final
  senha[strcspn(senha, "\n")] = 0;
  strcpy(BUFFER_SENHA_MANUTENCAO, senha);
  // só pra poder colocar em uma variavel static, pois se devolvermos um
  // pointer de variaveis desse escopo, esse pointer vai ficar vazio pois
  // as variaveis do escopo da funcao sao liberadas do stack
  static char* senhastatic;
  senhastatic  = senha;
  // BUFFER_SENHA_MANUTENCAO = senha; nao pode ser feito em C, arrays can only can be assigned in initialization
  return senhastatic;
}

char* tec_LerBufferSenhaManutencao() {
  return BUFFER_SENHA_MANUTENCAO;
}

void tec_ZerarBufferSenhaManutencao() {
  strcpy(BUFFER_SENHA_MANUTENCAO, NULL);
}

char** tec_TecladoInternoRetornaTeclasPressionadas() {
  printf("Este é o teclado interno da Vending Machine");
  printf("Se voce esta aqui é porque já se autenticou e conseguiu acesso interno");
  printf("Aqui voce vai cadastrar o troco ou produtos");
  printf("Se voce já terminou todo o cadastro ou nao quer fazer o cadastro:");
  printf("--> digite qualquer outra coisa. Para que voce possa fechar a porta de manutencao"); 
  printf("Funciona da seguinte forma:");
  printf(" 1) Digita a tecla do produto especifico ou moeda especifica + enter");
  printf("2) Digita quantidade do produto/moeda escolhido anteriormente + enter");  
  printf("Teclado é composto por: Teclas das Moedas, Teclas dos Produtos e Teclado numérico");
  printf("Para cadastrar moedas:");
  printf("5 centavos => digite '1m' e pressione enter");
  printf("10 centavos => digite '2m' e pressione enter");
  printf("25 centavos => digite '3m' e pressione enter");
  printf("50 centavos => digite '4m' e pressione enter");
  printf("1 real => digite '5m' e pressione enter");
  printf("Para cadastrar troco:");
  printf("Produto 1 => digite '1p'");
  printf("Produto 2 => digite '2p'");
  printf("Produto 3 => digite '3p'");
  printf("Produto 4 => digite '4p'");
  printf("Produto 5 => digite '5p'");
  printf("Produto 6 => digite '6p'");
  printf("Produto 7 => digite '7p'");
  printf("Produto 8 => digite '8p'");
  printf("Produto 9 => digite '9p'");
  printf("Para cadastrar quantidade(de moeda ou produto especifico): utilize o teclado numerico");

  char escolha [4];
  fgets(escolha, 4, stdin);
  escolha[strcspn(escolha, "\n")] = 0;
  strcpy(BUFFER_TECLADO_INTERNO_TIPO_DE_CADASTRO, escolha);

  char quantidade [4];
  fgets(quantidade, 4, stdin);
  quantidade[strcspn(quantidade, "\n")] = 0;
  strcpy(BUFFER_TECLADO_INTERNO_QUANTIDADE_CADASTRADA, quantidade);

  // retorna array com a escolha cliente(tecla de meoda ou produto especifico)
  // e com aquantidade digitada
  // char** escolhaequantidade;
  char* escolhaequantidade [2];
  strcpy(escolhaequantidade[0], escolha);
  strcpy(escolhaequantidade[1], quantidade);

  static char** escolhaequantidadepointer;
  escolhaequantidadepointer = escolhaequantidade;

  return escolhaequantidadepointer;
}
  

char* tec_LerBufferTecladoInternoTipodeCadastro() {
  return BUFFER_TECLADO_INTERNO_TIPO_DE_CADASTRO;
}

void tec_ZerarBufferTecladoInternoTipodeCadastro() {
  strcpy(BUFFER_TECLADO_INTERNO_TIPO_DE_CADASTRO, NULL);
}

char* tec_LerBufferTecladoInternoQuantidadeCadastrada() {
  return BUFFER_TECLADO_INTERNO_QUANTIDADE_CADASTRADA;
}

void tec_ZerarBufferTecladoInternoQuantidadeCadastrada() {
  strcpy(BUFFER_TECLADO_INTERNO_QUANTIDADE_CADASTRADA, NULL);
}