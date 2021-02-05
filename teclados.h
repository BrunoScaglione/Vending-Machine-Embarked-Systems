#ifndef TECLADOS_H_INCLUDED
#define TECLADOS_H_INCLUDED

extern char tec_TecladoClienteRetornaTeclaPressionada();
extern char tec_LerBufferEscolhaCliente();
extern void tec_ZerarBufferEscolhaCliente();

extern char* tec_TecladoAutenticacaoRetornaSenhaTeclada();
extern char* tec_LerBufferSenhaManutencao();
extern void tec_ZerarBufferSenhaManutencao();

extern char** tec_TecladoInternoRetornaTeclasPressionadas();
extern char* tec_LerBufferTecladoInternoTipodeCadastro();
extern void tec_ZerarBufferTecladoInternoTipodeCadastro();
extern char* tec_LerBufferTecladoInternoQuantidadeCadastrada();
extern void tec_ZerarBufferTecladoInternoQuantidadeCadastrada();

#endif