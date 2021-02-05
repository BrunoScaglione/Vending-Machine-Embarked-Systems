#ifndef DB_CAIXA_DE_TROCO_H_INCLUDED
#define DB_CAIXA_DE_TROCO_H_INCLUDED

extern double* cxt_VerificarTrocoDisponivel();

extern void cxt_InserirTroco(int* trocoInserido);

extern void cxt_SepararTrocoParaDevolver(double* trocoInserido);

extern double* cxt_RetirarTrocoParaDevolver();


#endif