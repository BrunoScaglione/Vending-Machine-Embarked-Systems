// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "definicoes_sistema.h"
// #include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definicoes_sistema.h"
#include "timer.h"

#define TEMPO 10

int tmr_situacao;
time_t horaInicio;

/*******************************
 tmr_iniciar
 Aciona ou desaciona o timer
 entradas
   controle: TRUE:liga FALSE:desliga
 saidas
   nenhuma
********************************/
void tmr_iniciar(int controle)
{
   tmr_situacao = controle;
   if (controle)
   {
      horaInicio = time(NULL);
   }
}

/*******************************
 tmr_timeout
 Retorna se o timer esta em timeout.
 entradas
    nenhuma
 saidas
    FALSE: n�o houve estouro do temporizador
    TRUE: houve estouro do temporizador
********************************/
int tmr_timeout()
{
    time_t horaAtual;

    horaAtual = time(NULL);
    if (tmr_situacao == false)
    {
        return false;
    }
    if ((horaAtual - horaInicio) > TEMPO)
    {
        return true;
    }
    return false;
}
