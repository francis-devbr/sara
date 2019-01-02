#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ui.h"

#ifdef _WIN32
#include <Windows.h>
int GetColumnWidth(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE out;

    if (!(out = GetStdHandle(STD_OUTPUT_HANDLE)) ||
        !GetConsoleScreenBufferInfo(out, &info))
        return 80;
    return info.dwSize.X;
}//GetColumnWidth
#else
int GetColumnWidth() {return 80;}
#endif


void red() {
  printf("\033[1;31m");
}

void blue() {
  printf("\033[1;34m");
}

void green() {
  printf("\033[1;32m");
}

void yellow() {
  printf("\033[1;33m");
}

void cyan() {
  printf("\033[1;36m");
}

void reset() {
  printf("\033[0m");
}

void imprime(char *s ){

    const int total_width = GetColumnWidth();
    const int s_width = strlen(s);
    const int field_width = (total_width - s_width) / 2 + s_width;

    printf("%*s", field_width, s);

}

void imprimeCabecalho(){
    char s[80];
    printf("\n\n\n");
    strcpy(s,"*S.A.R.A*\n");
    imprime(&s);

    strcpy(s,"*Sistema Academico de Reserva de Auditorio*\n");
    imprime(&s);

    printf("\n\n");
}

void imprimePalco(int size_col){
    int i;
    char s_aux[400];
    strcat(s_aux, "|");
    for(i = 0; i < size_col; i++){
        strcat(s_aux, "_");
    }
    strcat(s_aux, "|");
    imprime(&s_aux);
    printf("\n\n");
}

void mensagemEmailAgradecimento(){
    char s[400];

    sprintf(s,"Prezado,                                        %-20s\n","");
    imprime(&s);
    sprintf(s,"Agradecemos a sua partipacao em nosso evento    %-20s\n","");
    imprime(&s);
    sprintf(s,"Sua contribuicao foi fundamental para o sucesso.%-20s\n","");
    imprime(&s);
    sprintf(s,"Segue anexo um estudo sobre o tema ministrado.  %-20s\n","");
    imprime(&s);
    sprintf(s,"Esperamos nos encontrar novamente no proximo.   %-20s\n","");
    imprime(&s);
    sprintf(s,"Obrigado!                                       %-20s\n","");
    imprime(&s);
    printf("\n");

}

void imprimeMenuPrincipal(){
         char s[80];

         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*    [1] - Visitante                                       *\n");
         imprime(&s);
         strcpy(s,"*    [2] - Realizar Sorteio                                *\n");
         imprime(&s);
         strcpy(s,"*    [3] - Enviar comunicado por e-mail                    *\n");
         imprime(&s);
         strcpy(s,"*    [4] - Configurar Auditorio                            *\n");
         imprime(&s);
         strcpy(s,"*    [5] - Sair                                            *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"Escolha uma opcao =>  ");
         imprime(&s);
}

void imprimeMenuEmail(){
         char s[80];

         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*    [1] - Escolher visitante                              *\n");
         imprime(&s);
         strcpy(s,"*    [2] - Todos os visitantes                             *\n");
         imprime(&s);
         strcpy(s,"*    [3] - Retornar ao menu inicial                        *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"Escolha uma opcao =>  ");
         imprime(&s);
}

void imprimeMenuListarVisitantes(){
         char s[80];

         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*    [1] - Escolher visitante                              *\n");
         imprime(&s);
         strcpy(s,"*    [2] - Todos os visitantes                             *\n");
         imprime(&s);
         strcpy(s,"*    [3] - Retornar ao menu inicial                        *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"Escolha uma opcao =>  ");
         imprime(&s);
}

void imprimeMenuVisitante(){
         char s[80];

         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*    [1] - Incluir visitante                               *\n");
         imprime(&s);
         strcpy(s,"*    [2] - Excluir visitante                               *\n");
         imprime(&s);
         strcpy(s,"*    [3] - Listar visitantes                               *\n");
         imprime(&s);
         strcpy(s,"*    [4] - Listar lugares                                  *\n");
         imprime(&s);
         strcpy(s,"*    [5] - Retornar ao menu inicial                        *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"*                                                          *\n");
         imprime(&s);
         strcpy(s,"************************************************************\n");
         imprime(&s);
         strcpy(s,"Escolha uma opcao =>  ");
         imprime(&s);
}

void opcaoInvalida(){
    char s[30];
    red();
    sprintf(s,"Escolha uma opcao valida\n");
    imprime(&s);
    reset();
}

