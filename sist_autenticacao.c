#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes_sistema.h"
#include "sist_autenticacao.h"

int SENHA = 123;

int aut_VerificaSenha(int senhaTeclada) {
 return (senhaTeclada == SENHA) ? true : false;
}