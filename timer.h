// #ifndef TIMER_H_INCLUDED
// #define TIMER_H_INCLUDED

// extern void time_IniciarTimer();

// extern time_TimerFinalizado();

// #endif

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

/*******************************
 tmr_iniciar
 Aciona ou desaciona o timer
 entradas
   controle: TRUE:liga FALSE:desliga
 saidas
   nenhuma
********************************/
extern void tmr_iniciar(int controle);

/*******************************
 tmr_timeout
 Retorna se o timer esta em timeout.
 entradas
    nenhuma
 saidas
    FALSE: n�o houve estouro do temporizador
    TRUE: houve estouro do temporizador
********************************/
extern int tmr_timeout();

#endif // TIMER_H_INCLUDED
