#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    VENDING MACHINE
*/
//
#include "definicoes_sistema.h"
#include "atuadores.h"
#include "db_caixa_de_troco.h"
#include "db_produtos.h"
#include "display.h"
#include "sensores.h"
#include "sist_autenticacao.h"
#include "sist_recebimento_dinheiro.h"
#include "teclados.h"
#include "timer.h"

/// Painel da Vending Machine

void painelProdutosPrecos() {
  printf("Painel da Vending Machine");
  printf("Nome do Produto   | número |   Preço  ");
  printf("    Produto 1     |   1    |  0,50 R$" );
  printf("    Produto 2     |   2    |  1,50 R$");
  printf("    Produto 3     |   3    |  0,05 R$");
  printf("    Produto 4     |   4    |  0,10 R$");
  printf("    Produto 5     |   5    |  0,30 R$");
  printf("    Produto 6     |   6    |  2,50 R$");
  printf("    Produto 7     |   7    |  0,50 R$");
  printf("    Produto 8     |   8    |  0,80 R$");
  printf("    Produto 9     |   9    |  2,00 R$");
}


/***********************************************************************
 Estaticos
 ***********************************************************************/
  int codigoEvento;
  int codigoAcao;
  int estado;
  // int sensores;
  int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
  int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];

/************************************************************************
 executarAcao
 Executa uma acao
 Parametros de entrada:
    (int) codigo da acao a ser executada
 Retorno: (int) codigo do evento interno ou NENHUM_EVENTO
*************************************************************************/
// tem que colocar parametros pra acao aqui tambem
int executarAcao(int codigoAcao)
{
    int retval;

    retval = NENHUM_EVENTO;
    if (codigoAcao == NENHUMA_ACAO)
        return retval;

    switch(codigoAcao) {
    // apos usuario "dizer" que terminou de inserir o dinheiro
      case APOS_USUARIO_SUBMIT_DINHEIRO_INSERIDO:;
          // le uma lista do tipo: {valormoeda1, quantidademoeda1, valormoeda2, quantidademoeda2 ...}
          // apos o sensor ter detectado as moedas inseridas(digitadas) ele atulazou esse buffer(lista) internamente
          double *buffer = sen_LerBufferMoedasInseridas();
          // zera o buffer do sensor para que este possa guardar as moedas inseridas na proxima compra
          sen_ZerarBufferMoedasInseridas();

          // calcula o total inserido (funcao propria da maq estados)
          double totalInserido = 
            (buffer[0]*buffer[1]) + (buffer[2]*buffer[3]) + (buffer[4]*buffer[5]) + (buffer[6]*buffer[7]);

          // guarda o total inserido no sistema de recebimento de dinheiro
          rec_GuardarTotalInserido(totalInserido);
          // mostra dinheiro inserido no display para o cliente
          disp_MostrarDinheiroInserido(totalInserido);
          break;
      case APOS_USUARIO_TECLA_PRODUTO:;
          // le o produto o cliente digitou, que o teclad armazenou em seu buffer interno (de 1 a 9)
          char bufferCliente = tec_LerBufferEscolhaCliente();
          // transforma char em int
          int digit = bufferCliente - '0';
          // le a quantidade deste produto disponivel no banco de dados de produtos
          int quantidadeDisponivel = prod_LerQuantidadeProduto(digit);

          // agora serao feitas to 3 verificacoes em ordem: 
          // 1) Se o produto esta disponivel;
          // 2) se o dinheiro é suficiente; 
          // 3) Se tem troco disponivel;

          // [funcao propria da maq. de estados]
          if (quantidadeDisponivel == 0)
            // nao ha mais desse produto
            return COMPRA_INVALIDA;

          else {
            // le o dinheiro que tinhamos guardado no sistema de recebimento de dinheiro
            double valorInserido = rec_LerDinheiroInserido();
            // le o preco do produto no banco de dados de produtos
            double precoProduto = prod_LerPrecoProduto(digit);

            // [funcao propria da maq. de estados]
            if (valorInserido <= precoProduto)
              // dinheiro nao é suficiente
              return COMPRA_INVALIDA;

            else {
              // le o troco disponivel, que eh uma lista do tipo: 
              // {valormoeda1, quantidademoeda1, valormoeda2, quantidademoeda2 ...}
              double *trocoDisponivel = cxt_VerificarTrocoDisponivel();

              int moedas5centavos = trocoDisponivel[1];
              int moedas10centavos = trocoDisponivel[3];
              int moedas25centavos = trocoDisponivel[5];
              int moedas50centavos = trocoDisponivel[7];
              int moedas1real = trocoDisponivel[9];

              int trocoMoedas1real = 0;
              int trocoMoedas50centavos = 0;
              int trocoMoedas25centavos = 0;
              int trocoMoedas10centavos = 0;
              int trocoMoedas5centavos = 0;

              // valor de troco que precisamos devolver para cliente
              double trocoNecessario = valorInserido - precoProduto;

              // nossas moedas disponiveis para troco
              double moedas [10] = {
                1, moedas1real, 
                0.5, moedas50centavos, 
                0.25, moedas25centavos, 
                0.1, moedas10centavos, 
                0.05, moedas5centavos
              };
              // moedas que vamos separar para o troco
              double moedasParaTroco [10] = {
                1, trocoMoedas1real, 
                0.5, trocoMoedas50centavos, 
                0.25, trocoMoedas25centavos, 
                0.1, trocoMoedas10centavos, 
                0.05, trocoMoedas5centavos
              };

              // algoritmo que vai separando moedas para troco e define se troco é suficiente ou nao ()
              // se for possivel, vai cair em algum break
              // se nao, nao é possivel retornar troco com as moedas que temos
              // [funcao propria da maq. de estados]
              int i;
              int quociente;
              for(i=0; i <=10; i+2) {
                if (moedas[i+1] != 0)
                  quociente = trocoNecessario / moedas[i];
                    moedasParaTroco[i+1] = quociente;
                  if (i == 0 && quociente == 1)
                    break;
                  double resto = trocoNecessario - quociente*moedas[i];
                  if (resto == 0)
                    break;
                  trocoNecessario = resto;

                  return COMPRA_INVALIDA;
              
              //guarda as moedas para troco no buffer de devolucao de troco, do caixa de troco
              //se nao precisar de troco, via mandar o array incial com zeros em todas as quantidades
              cxt_SepararTrocoParaDevolver(moedasParaTroco);
              return COMPRA_VALIDA;
              }
            }
          }
      
      case APOS_COMPRA_VALIDA:;
          // retira troco do buffer que guarda o troco a ser devolvido
          double *moedasParaTroco = cxt_RetirarTrocoParaDevolver();
          // le o produto que o cliente digitou antes (de 1 a 9)
          bufferCliente = tec_LerBufferEscolhaCliente();
          // zera o buffer que guardava a escolha do cliente, o produto nesse caso
          // para que outra escolha possa ser guardada na proxima compra
          tec_ZerarBufferEscolhaCliente();
          // converte o char em int
          digit = bufferCliente - '0';
          // deleta produto do banco de dados
          prod_DeletarProduto(digit);
          // inicia timer, pois vamos mudar o estado de DERRUBANDO_PRODUTO para IDLE baseado em um certo 
          // tempo em que vamos poder assumir que o produto foi derrubado e podemos aceitar outras
          // compras ou manutencao
          tmr_iniciar(true);
          // o sistema de recebimento de dinheiro esta acima do moedeiro(internamente na maquina) 
          // e o atuador atua de forma a deslocar a base
          // e o dinheiro cair 
          at_PromoverCaidaDinheironoMoedeiroPeloDeslocamentodaBase();
          // sabendo a quantidde de cada moeda para o troco, passamos essa infromacao para o sistema de atuadores que pro-
          // moverá a atuação do atuador especifico de cada moeda baseado na quantidade especificada no array de input
          // se nao tiver troco, simplismente via desprender 0 moedas de cada
          at_DesprenderMoedasParaSeparacaoDoTroco(moedasParaTroco);
          // o troco separado ficará intenamente em um local alto, para que com o deslocamente da base, o troco caia para
          // o cliente
          at_PromoverCaidaTrocoSeparadoParaClientePeloDeslocamentoDaBase();
          // passamos a informacao do numero do produto que queremos derrubar para o sistema de atuadores que promoverá
          // a atuação do atuador especifico do produto especificado
          at_EmpurrarProduto(digit);
          break;
      case APOS_COMPRA_INVALIDA:;
          // zeramos para que o cliente possa efetuar outra escolha(cancelamento, ou esclher outro produto)
          tec_ZerarBufferEscolhaCliente();
          // mostramos em display que a compra foi invalida
          disp_MostrarErroCompraInvalida();
          break;
      case APOS_USUARIO_CANCELA_COMPRA:;
          sen_ZerarBufferMoedasInseridas();
          tec_ZerarBufferEscolhaCliente();
          // aciona atuador que promove uma alavanca mecanica que promove a devolucao das moedas inseridas, que 
          // estavam no sistema de recebimento de dinheiro
          at_AlavancaDevolucaoDinheiro();
          break;
      case APOS_TECLADO_MANUTENCAO_SUBMIT_SENHA_INSERIDA:;
          // le senha que foi teclada pela manutencao, e esa armazenada no buffer interno do
          // teclado de autenticacao
          char *bufferManutencao = tec_LerBufferSenhaManutencao();
          // zera o buffer para que proxima senha digitada seja guardada
          tec_ZerarBufferSenhaManutencao();
          int valueBufferManutencao = atoi(bufferManutencao);
          // verifica se senha digitada é a senha do sistema, pelo sistema de autenticacao
          return (aut_VerificaSenha(valueBufferManutencao)) ? SENHA_VALIDA : SENHA_INVALIDA;
      case APOS_SENHA_VALIDA:;
          // possibilita abertura da porta de manutencao 
          at_LiberarTravaPortaManutencao();
          break;
      case APOS_PORTA_DE_MANUTENCAO_FOI_FECHADA:;
          // se foi detecntado que a manutencao fechou a a porta, o travammento ocorre em seguida
          at_EmpurrarTravaPortaManutencao();
          break;
      case APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_TROCO_EFETUADO:;
          // essa acao acontece apos a manutencao ter dado submit no cadastro de mais troco
          // numeros de 1m 2m 3m 4m 5m, representarao as moedas de 0.05 centavos a 1 real em ordem

          // le o tipo de cadastro que foi escolhido pela manutencao anteriormente
          // ou seja, nesse caso (troco) tem que ter sido uma das moedas a tecla esclhida
          char *bufferTecladoInternoTipodeCadastroMoeda = tec_LerBufferTecladoInternoTipodeCadastro();
          tec_ZerarBufferTecladoInternoTipodeCadastro();

          // aqui a tranformacao para int,  ainda funciona porque a funcao atoi tranforma em int até encontrar um caracter
          // que nao seja um numero, entao: '1' e '1m' vai dar na mesma 
          int valueBufferTecladoInternoTipodeMoeda = atoi(bufferTecladoInternoTipodeCadastroMoeda);
          // quantidade da moeda que esta sendo cadastrada
          char *bufferTecladoInternoQuantidadeCadastradaMoeda = tec_LerBufferTecladoInternoQuantidadeCadastrada();
          tec_ZerarBufferTecladoInternoQuantidadeCadastrada();

          // le a quantidade cadastrada do tipo de moeda escolhido anteriormente
          int valueBufferTecladoInternoQuantidadeCadastradaMoeda = atoi(bufferTecladoInternoQuantidadeCadastradaMoeda);

          // junta as duas informacoes em um array e manda para o caixa de troco, para que seja inserido este troco
          // no banco de dados de troco disponivel da maquina
          int trocoCadastrado [2] =
            {valueBufferTecladoInternoTipodeMoeda, valueBufferTecladoInternoQuantidadeCadastradaMoeda};
          cxt_InserirTroco(trocoCadastrado);
          break;

      case APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_PRODUTO_EFETUADO:;
          // muito parecido com a acao anterior, só que vamos inserir produto ao inves de troco, no final
          char *bufferTecladoInternoTipodeCadastroProduto = tec_LerBufferTecladoInternoTipodeCadastro();
          tec_ZerarBufferTecladoInternoTipodeCadastro();
          int valueBufferTecladoInternoTipodeProduto = atoi(bufferTecladoInternoTipodeCadastroProduto);
          // quantidade da moeda que esta sendo cadastrada
          char *bufferTecladoInternoQuantidadeCadastradaProduto = tec_LerBufferTecladoInternoQuantidadeCadastrada();
          tec_ZerarBufferTecladoInternoQuantidadeCadastrada();
          int valueBufferTecladoInternoQuantidadeCadastradaProduto = atoi(bufferTecladoInternoQuantidadeCadastradaProduto);
          int produtoCadastrado [2] =
          {valueBufferTecladoInternoTipodeProduto, valueBufferTecladoInternoQuantidadeCadastradaProduto};
          // insere o produto com sua quantidade no banco de dados de produtos
          prod_InserirProdutos(produtoCadastrado);
          break;

    } // switch

    return retval;
} // executarAcao

/************************************************************************
 iniciaMaquina de Estados
 Carrega a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaMaquinaEstados() {
  int i;
  int j;

  for (i=0; i < NUM_ESTADOS; i++) {
    for (j=0; j < NUM_EVENTOS; j++) {
       acao_matrizTransicaoEstados[i][j] = NENHUMA_ACAO;
       proximo_estado_matrizTransicaoEstados[i][j] = i;
    }
  }
  proximo_estado_matrizTransicaoEstados
    [IDLE][DETECTOU_MOEDA_ENTRANDO] = COLOCANDO_MOEDAS;
  // acao_matrizTransicaoEstados
  //  [IDLE][DETECTOU_MOEDA_ENTRANDO] = NENHUMA_ACAO;

  proximo_estado_matrizTransicaoEstados
    [IDLE][TECLADO_MANUTENCAO_SUBMIT_SENHA_INSERIDA] = VERIFICANDO_SENHA_MANUTENCAO;
  acao_matrizTransicaoEstados
    [IDLE][TECLADO_MANUTENCAO_SUBMIT_SENHA_INSERIDA] = APOS_TECLADO_MANUTENCAO_SUBMIT_SENHA_INSERIDA;

  // proximo_estado_matrizTransicaoEstados
  //  [COLOCANDO_MOEDAS][DETECTOU_MOEDA_ENTRANDO] = COLOCANDO_MOEDAS;
  // acao_matrizTransicaoEstados
  //  [COLOCANDO_MOEDAS][DETECTOU_MOEDA_ENTRANDO] = NENHUMA_ACAO;

  proximo_estado_matrizTransicaoEstados
    [COLOCANDO_MOEDAS][USUARIO_SUBMIT_DINHEIRO_INSERIDO] = ESPERANDO_USUARIO_DECIDIR;
  acao_matrizTransicaoEstados
    [COLOCANDO_MOEDAS][USUARIO_SUBMIT_DINHEIRO_INSERIDO] = APOS_USUARIO_SUBMIT_DINHEIRO_INSERIDO;

  proximo_estado_matrizTransicaoEstados
    [COLOCANDO_MOEDAS][USUARIO_CANCELA_COMPRA] = IDLE;
  acao_matrizTransicaoEstados
    [COLOCANDO_MOEDAS][USUARIO_CANCELA_COMPRA] = APOS_USUARIO_CANCELA_COMPRA;

  proximo_estado_matrizTransicaoEstados
    [ESPERANDO_USUARIO_DECIDIR][USUARIO_TECLA_PRODUTO] = VERIFICANDO_POSSIBILIDADE_COMPRA;
  acao_matrizTransicaoEstados
    [ESPERANDO_USUARIO_DECIDIR][USUARIO_TECLA_PRODUTO] = APOS_USUARIO_TECLA_PRODUTO;

  proximo_estado_matrizTransicaoEstados
    [ESPERANDO_USUARIO_DECIDIR][USUARIO_CANCELA_COMPRA] = IDLE;
  acao_matrizTransicaoEstados
    [ESPERANDO_USUARIO_DECIDIR][USUARIO_CANCELA_COMPRA] = APOS_USUARIO_CANCELA_COMPRA;

  proximo_estado_matrizTransicaoEstados
    [VERIFICANDO_POSSIBILIDADE_COMPRA][COMPRA_VALIDA] = DERRUBANDO_PRODUTO;
  acao_matrizTransicaoEstados
    [VERIFICANDO_POSSIBILIDADE_COMPRA][COMPRA_VALIDA] = APOS_COMPRA_VALIDA;

  proximo_estado_matrizTransicaoEstados
    [VERIFICANDO_POSSIBILIDADE_COMPRA][COMPRA_INVALIDA] = ESPERANDO_USUARIO_DECIDIR;
  acao_matrizTransicaoEstados
    [VERIFICANDO_POSSIBILIDADE_COMPRA][COMPRA_INVALIDA] = APOS_COMPRA_INVALIDA;

  proximo_estado_matrizTransicaoEstados
      [DERRUBANDO_PRODUTO][TIMER_FINALIZADO] = IDLE;
  // acao_matrizTransicaoEstados
  //  [DERRUBANDO_PRODUTO][TIMER_FINALIZADO] = NENHUMA_ACAO;

  proximo_estado_matrizTransicaoEstados
    [VERIFICANDO_SENHA_MANUTENCAO][SENHA_VALIDA] = OCORRENDO_MANUTENCAO;
  acao_matrizTransicaoEstados
    [VERIFICANDO_SENHA_MANUTENCAO][SENHA_VALIDA] = APOS_SENHA_VALIDA;

  proximo_estado_matrizTransicaoEstados
    [VERIFICANDO_SENHA_MANUTENCAO][SENHA_INVALIDA] = IDLE;
  // acao_matrizTransicaoEstados
  //  [VERIFICANDO_SENHA_MANUTENCAO][SENHA_INVALIDA] = NENHUMA_ACAO;

  proximo_estado_matrizTransicaoEstados
    [OCORRENDO_MANUTENCAO][APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_PRODUTO_EFETUADO] = OCORRENDO_MANUTENCAO;
  acao_matrizTransicaoEstados
    [OCORRENDO_MANUTENCAO][APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_PRODUTO_EFETUADO] = 
      APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_PRODUTO_EFETUADO;

  proximo_estado_matrizTransicaoEstados
    [OCORRENDO_MANUTENCAO][APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_TROCO_EFETUADO] = OCORRENDO_MANUTENCAO;
  acao_matrizTransicaoEstados
    [OCORRENDO_MANUTENCAO][APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_TROCO_EFETUADO] = 
      APOS_TECLADO_INTERNO_SUBMIT_CADASTRO_TROCO_EFETUADO;

  proximo_estado_matrizTransicaoEstados
    [OCORRENDO_MANUTENCAO][PORTA_DE_MANUTENCAO_FOI_FECHADA] = IDLE;
  acao_matrizTransicaoEstados
    [OCORRENDO_MANUTENCAO][PORTA_DE_MANUTENCAO_FOI_FECHADA] = APOS_PORTA_DE_MANUTENCAO_FOI_FECHADA;

} // initStateMachine

/************************************************************************
 iniciaSistema
 Inicia o sistema ...
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaSistema()
{
   iniciaMaquinaEstados();
} // initSystem


/************************************************************************
 obterEvento
 Obtem um evento, que pode ser da IHM ou do alarme
 Parametros de entrada: nenhum
 Retorno: codigo do evento
*************************************************************************/

// coloquei como parametro o estadoAtual para apenas ouvirmos eventos que sao de interesse do estado
// em que estamos
int obterEvento(int estadoAtual){
  int evento = NENHUM_EVENTO;

  if (estadoAtual == IDLE || estadoAtual == COLOCANDO_MOEDAS) {
    if (sen_DetectaMoedaInserida()) 
      return DETECTOU_MOEDA_ENTRANDO;
  }
  
  if (estadoAtual == IDLE) {
    char *senhaTecladoManutencao = tec_TecladoAutenticacaoRetornaSenhaTeclada();
    int senhaTecladoManutencaoInt = atoi(senhaTecladoManutencao);
    // se usuario (manutencao) digitou alguma coisa
    if (senhaTecladoManutencao != 0)
      return TECLADO_MANUTENCAO_SUBMIT_SENHA_INSERIDA;
  }

  if (estadoAtual == COLOCANDO_MOEDAS || estadoAtual == ESPERANDO_USUARIO_DECIDIR) {
    // cliente tem 3 opcoes( cancelar, submeter, ou usar o teclado numerico para escolher o produto)
    // mas o uso do teclado numerico para escolher o produto só terá uso após ele ter submetido anteriormente
    // e se ele estiver colocando moedas, apenas cancelar tera uso para ele
    char teclaPressionadaCliente = tec_TecladoClienteRetornaTeclaPressionada();
    if (teclaPressionadaCliente == 'S')
      return USUARIO_SUBMIT_DINHEIRO_INSERIDO;
    if (teclaPressionadaCliente == 'C')
      return USUARIO_CANCELA_COMPRA;
    int digit = teclaPressionadaCliente - '0';
    if ( 1 <= digit <= 9)
      return USUARIO_TECLA_PRODUTO;
  }

  if (estadoAtual == OCORRENDO_MANUTENCAO) {
  // a manutencao pode escolher uma moeda especifica para repor
  // ou um produto especifico para repor
    char **teclasPressionadasTecladoInterno = tec_TecladoInternoRetornaTeclasPressionadas();
    // retorna array do tipo {escolha, quantidade}

    // maximo 100 moedas de cada. Fica a cargo do repositor saber quanto de cada moeda ele vai por
    // ele vai poder ver a quantidade de moedas em realacao ao espaco disponivel de cada moeda manualamente,
    // pra saber quantas ele vai colocar
    if ( 1 <= atoi(teclasPressionadasTecladoInterno[1]) <= 100) {
      if (
        strcmp(teclasPressionadasTecladoInterno[0], "1m") == 0 || 
        strcmp(teclasPressionadasTecladoInterno[0], "2m") == 0 || 
        strcmp(teclasPressionadasTecladoInterno[0], "3m") == 0 || 
        strcmp(teclasPressionadasTecladoInterno[0], "4m") == 0 || 
        strcmp(teclasPressionadasTecladoInterno[0], "5m") == 0
      )
        return TECLADO_INTERNO_SUBMIT_CADASTRO_TROCO_EFETUADO;
    }
    // maximo 9 produtos de cada. Fic a cargo de repositor saber quanto de cada produto ele vai por
    // ele vai poder ver a quantidade de produtos em realcao ao espaco disponivel para saber quantos ele vai colocar
    if ( 1 <= atoi(teclasPressionadasTecladoInterno[1]) <= 9) {
      if (
        strcmp(teclasPressionadasTecladoInterno[0], "1p") == 0 ||
        strcmp(teclasPressionadasTecladoInterno[0], "2p") == 0 ||
        strcmp(teclasPressionadasTecladoInterno[0], "3p") == 0 || 
        strcmp(teclasPressionadasTecladoInterno[0], "4p") == 0 ||
        strcmp(teclasPressionadasTecladoInterno[0], "5p") == 0 ||
        strcmp(teclasPressionadasTecladoInterno[0], "6p") == 0 ||
        strcmp(teclasPressionadasTecladoInterno[0], "7p") == 0 ||
        strcmp(teclasPressionadasTecladoInterno[0], "8p") == 0 ||
        strcmp(teclasPressionadasTecladoInterno[0], "9p") == 0
        )
        return TECLADO_INTERNO_SUBMIT_CADASTRO_PRODUTO_EFETUADO;
    }

    // manutencoa pode tambem fechar a porta para encerrar manutencao 
    if (sen_DetectaFechamentoPortaManutencao())
      return PORTA_DE_MANUTENCAO_FOI_FECHADA;
  }

  if (estadoAtual == DERRUBANDO_PRODUTO) {
    // ve se o tempo estorou
    if (tmr_timeout())
      // desliga o timer se o tempo estorou
      tmr_iniciar(false);
      return TIMER_FINALIZADO;
  }
    
     
  return evento;


} // obterEvento

/************************************************************************
 obterAcao
 Obtem uma acao da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo da acao
*************************************************************************/
int obterAcao(int estado, int codigoEvento) {
  return acao_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao


/************************************************************************
 obterProximoEstado
 Obtem o proximo estado da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo do estado
*************************************************************************/
int obterProximoEstado(int estado, int codigoEvento) {
  return proximo_estado_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao


/************************************************************************
 Main
 Loop principal de controle que executa a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
int main() {

  int codigoEvento;
  int codigoAcao;
  int estado;
  int eventoInterno;

  estado = IDLE;
  eventoInterno = NENHUM_EVENTO;

  

  iniciaSistema();
  printf ("Bem Vindo a Vending Machine\n");
  // mostra painel com tabela de: produtos, numeros dos produtos e precos 
  painelProdutosPrecos();
  while (true) {
    if (eventoInterno == NENHUM_EVENTO) {
        // modifiquei obterEvento para receber o parametro estado
        // pois nao preciso ouvir todos os eventos, só os que interessam
        // no estado que eu estou, pois por exemplo, no caso do teclado interno
        // nao é realistico a posibilidade de obter um evento sem já ter tido acesso
        // à maquina
        codigoEvento = obterEvento(estado);
    } else {
        codigoEvento = eventoInterno;
    }
    if (codigoEvento != NENHUM_EVENTO)
    {
       codigoAcao = obterAcao(estado, codigoEvento);
       estado = obterProximoEstado(estado, codigoEvento);
       eventoInterno = executarAcao(codigoAcao);
       printf("Estado: %d Evento: %d Acao:%d\n", estado, codigoEvento, codigoAcao);
    }
  } // while true
} // main
