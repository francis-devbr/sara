#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<conio.h>
#include <time.h>

#include "utils.h"
#include "visitante.h"

int sorteio(MapaVisitante* mapaVisitante, MapaAuditorio* mapaAuditorio);
void email();
void enviaEmailTodos(MapaVisitante* mapaVisitante);
void enviaEmail(MapaVisitante* mapaVisitante, MapaAuditorio* mapaAuditorio);
int random_number(int min_num, int max_num);
int login();
int modoDemo(MapaVisitante* mapaVisitante, MapaAuditorio* mapa);
int main();

int sorteio(MapaVisitante* mapaVisitante, MapaAuditorio* mapaAuditorio){

    char s[400];
    int idSorteado, codigo, qtd, finalizaSorteio;

    int i=1;
    int loopContinue = FALSE;
    int achou = FALSE;

    mapaAuditorio->assento.qtd_livre = countAssentos(mapaAuditorio, 'L');
    mapaAuditorio->assento.qtde_ocupado = countAssentos(mapaAuditorio, 'O');

    do{
        system("cls");
        imprimeCabecalho();
        sprintf(s,"Total de partipantes do sorteio: %d\n", mapaVisitante->total_aptos_sorteio);
        imprime(&s);

        strcpy(s,"Informe a quantidade de brindes a serem sorteados => ");
        imprime(&s);
        scanf("%d", &qtd);

        if (qtd !=0 && qtd > mapaVisitante->total_aptos_sorteio){
            red();
            strcpy(s,"Total de brindes maior do que a de Participantes");
            imprime(&s);
            reset();
            getch();
            loopContinue = TRUE;
        }else if(qtd<0){
            red();
            strcpy(s,"Quantidade de Brindes não poder ser menor que zero!!!\n");
            imprime(&s);
            reset();
            getch();
            loopContinue = TRUE;
        }else if (qtd == 0){
            red();
            strcpy(s,"Retornando ao menu anterior\n");
            imprime(&s);
            reset();
            getch();
            loopContinue = FALSE;
        }

    }while(loopContinue);

    while (i<=qtd){

        finalizaSorteio = FALSE;

        do{
            codigo = random_number(1, mapaAuditorio->assento.max_assentos);
            idSorteado = findVisitanteBy(mapaVisitante,codigo, &achou, mapaAuditorio->assento.max_assentos);

            if(achou){
                if(mapaVisitante->visitantes[idSorteado].isParticipaSorteio && !mapaVisitante->visitantes[idSorteado].isPremiado){
                    mapaVisitante->visitantes[idSorteado].isPremiado = TRUE;
                    printf("\n");
                    yellow();
                    sprintf(s,"Sorteado codigo: %d \n\n", codigo);
                    imprime(&s);
                    reset();
                    imprimeDadosVisitante(mapaVisitante,idSorteado);
                    finalizaSorteio = TRUE;
                    i++;
                }
            }else{
                finalizaSorteio = FALSE;
            }

        }while(!finalizaSorteio);
    }

    if(achou){
        printf("\n");
        green();
        sprintf(s,"Fim do sorteio\n");
        imprime(&s);
        sprintf(s,"Parabens ao ganhadores\n");
        imprime(&s);
        reset();
        getch();
    }
}

void enviaEmailTodos(MapaVisitante* mapaVisitante){

    int i = 0;
    char s[400];
    system("cls");
    imprimeCabecalho();
    mensagemEmailAgradecimento();
    for(i=0; i<mapaVisitante->total_cadastrados; i++){
        sprintf(s,"Email enviado para: %-30s \n", mapaVisitante->visitantes[i].email);
        imprime(&s);
    }

    getch();

}

void enviaEmail(MapaVisitante* mapaVisitante, MapaAuditorio* mapaAuditorio){

    char s[400];
    int codigo = 0;
    int achou = FALSE;
    int id = 0;

    system("cls");
    imprimeCabecalho();
    mensagemEmailAgradecimento();

    sprintf(s,"Informe o codigo do visitante =>");
    imprime(&s);
    scanf("%d",&codigo);

    id = findVisitanteBy(mapaVisitante,codigo, &achou, mapaAuditorio->assento.max_assentos);

    printf("\n");

    if(achou){
        sprintf(s,"Enviado para %s - Email %-30s \n", mapaVisitante->visitantes[id].nome, mapaVisitante->visitantes[id].email);
        imprime(&s);
    }else{
        red();
        printf("\n");
        sprintf(s,"Visitante nao encontrado!!!");
        imprime(&s);
        reset();
    }

    getch();

}

void email(MapaVisitante* mapaVisitante, MapaAuditorio* mapaAuditorio){

    int loopContinue = TRUE;

    int opcao;

    do{
        system("cls");
        imprimeCabecalho();
        imprimeMenuEmail();
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
              system("cls");
              enviaEmail(mapaVisitante,mapaAuditorio);
              break;

            case 2:
              system("cls");
              enviaEmailTodos(mapaVisitante);
              break;

            case 3:
              loopContinue = FALSE;
              break;
            default:
                opcaoInvalida();
                getch();
                break;
        }
    }while(loopContinue);

}

int login(){
    char s[400];
    int x=0;
    int demo = FALSE;
    char password[10];
    char passwordAdmin[10] = {"aaa"};

    int count=0;

    do{
        system("cls");
        imprimeCabecalho();
        strcpy(s,"Digite sua senha: ");
        imprime(&s);
        gets(password);

        if (strcmp(password,passwordAdmin) == 0){
            x=0;
        }else if(strcmp(password,"123") == 0){
           demo = TRUE;
           x=0;
           printf("\n");
           red();
           strcpy(s,"Modo Demo");
           imprime(&s);
           reset();
           getch();
        }else{
           x++;
           printf("\n");
           red();
           strcpy(s,"Senha invalida, tente novamente");
           imprime(&s);
           reset();
           count++;
           getch();
        }

    }while(x!=0);

    return demo;

}

int modoDemo(MapaVisitante* mapaVisitante, MapaAuditorio* mapa){

   int isOK;
    int pos = 0;

    liberaMemMapaAuditorio(mapa);
    mapa->assento.qtd_comum = 50;
    mapa->assento.qtd_especial = getAssentosEspeciais(mapa->assento.qtd_comum);
    mapa->assento.max_assentos = (mapa->assento.qtd_comum + mapa->assento.qtd_especial);
    mapa->assento.qtd_convidado = 10;
    mapa->colunas = 10;
    mapa->linhas = (getModAssento(mapa->assento.qtd_comum, mapa->colunas) + getModAssento(mapa->assento.qtd_especial, mapa->colunas));

    alocaMemMapaAuditorio(mapa);
    inicializaAuditorio(mapa);

    mapa->isStarted = TRUE;

    alocaMemVisitante(mapaVisitante, mapa->assento.max_assentos);

    pos = 0;
    mapaVisitante->visitantes[pos].codigo = 1;
    strcpy(mapaVisitante->visitantes[pos].nome, "Francis Oliveira");
    strcpy(mapaVisitante->visitantes[pos].dataNascimento, "08081980");
    strcpy(mapaVisitante->visitantes[pos].sexo, "M");
    strcpy(mapaVisitante->visitantes[pos].rg, "343065800");
    strcpy(mapaVisitante->visitantes[pos].email, "fnolivei@outlook.com");
    compraAutomatica(mapa, 'E', &mapaVisitante->visitantes[pos].linha, &mapaVisitante->visitantes[pos].coluna, &isOK);
    mapaVisitante->visitantes[pos].isParticipaSorteio = FALSE;
    mapaVisitante->visitantes[pos].isEspecial = TRUE;
    mapaVisitante->visitantes[pos].isConvidado = TRUE;
    mapaVisitante->total_cadastrados++;

    time_t now = time (0);
            strftime (mapaVisitante->visitantes[pos].dataHora, 100, "%d-%m-%Y %H:%M:%S.000", localtime (&now));

    pos=1;
    mapaVisitante->visitantes[pos].codigo = 2;
    strcpy(mapaVisitante->visitantes[pos].nome, "Fabio Oliveira");
    strcpy(mapaVisitante->visitantes[pos].dataNascimento, "08081980");
    strcpy(mapaVisitante->visitantes[pos].sexo, "M");
    strcpy(mapaVisitante->visitantes[pos].rg, "343065800");
    strcpy(mapaVisitante->visitantes[pos].email, "fabio@outlook.com");
    compraAutomatica(mapa, 'E', &mapaVisitante->visitantes[pos].linha, &mapaVisitante->visitantes[pos].coluna, &isOK);
    mapaVisitante->visitantes[pos].isParticipaSorteio = FALSE;
    mapaVisitante->visitantes[pos].isEspecial = TRUE;
    mapaVisitante->visitantes[pos].isConvidado = TRUE;
    mapaVisitante->total_cadastrados++;

    now = time (0);
    strftime (mapaVisitante->visitantes[pos].dataHora, 100, "%d-%m-%Y %H:%M:%S.000", localtime (&now));

    pos=2;
    mapaVisitante->visitantes[pos].codigo = 3;
    strcpy(mapaVisitante->visitantes[pos].nome, "Eduardo J");
    strcpy(mapaVisitante->visitantes[pos].dataNascimento, "08081980");
    strcpy(mapaVisitante->visitantes[pos].sexo, "M");
    strcpy(mapaVisitante->visitantes[pos].rg, "343065801");
    strcpy(mapaVisitante->visitantes[pos].email, "eduardo@outlook.com");
    compraAutomatica(mapa, 'L', &mapaVisitante->visitantes[pos].linha, &mapaVisitante->visitantes[pos].coluna, &isOK);
    mapaVisitante->visitantes[pos].isParticipaSorteio = TRUE;
    mapaVisitante->visitantes[pos].isEspecial = FALSE;
    mapaVisitante->visitantes[pos].isConvidado = FALSE;
    mapaVisitante->total_aptos_sorteio++;
    mapaVisitante->total_cadastrados++;

    now = time (0);
    strftime (mapaVisitante->visitantes[pos].dataHora, 100, "%d-%m-%Y %H:%M:%S.000", localtime (&now));

    pos=3;
    mapaVisitante->visitantes[pos].codigo = 4;
    strcpy(mapaVisitante->visitantes[pos].nome, "Alef ");
    strcpy(mapaVisitante->visitantes[pos].dataNascimento, "08081980");
    strcpy(mapaVisitante->visitantes[pos].sexo, "M");
    strcpy(mapaVisitante->visitantes[pos].rg, "343065802");
    strcpy(mapaVisitante->visitantes[pos].email, "alef@outlook.com");
    compraAutomatica(mapa, 'C', &mapaVisitante->visitantes[pos].linha, &mapaVisitante->visitantes[pos].coluna, &isOK);
    mapaVisitante->visitantes[pos].isParticipaSorteio = FALSE;
    mapaVisitante->visitantes[pos].isEspecial = FALSE;
    mapaVisitante->visitantes[pos].isConvidado = TRUE;
    mapaVisitante->total_cadastrados++;

    now = time (0);
    strftime (mapaVisitante->visitantes[pos].dataHora, 100, "%d-%m-%Y %H:%M:%S.000", localtime (&now));

    pos=4;
    mapaVisitante->visitantes[pos].codigo = 5;
    strcpy(mapaVisitante->visitantes[pos].nome, "Daniele J");
    strcpy(mapaVisitante->visitantes[pos].dataNascimento, "08081980");
    strcpy(mapaVisitante->visitantes[pos].sexo, "M");
    strcpy(mapaVisitante->visitantes[pos].rg, "343065801");
    strcpy(mapaVisitante->visitantes[pos].email, "daniele@outlook.com");
    compraAutomatica(mapa, 'E', &mapaVisitante->visitantes[pos].linha, &mapaVisitante->visitantes[pos].coluna, &isOK);
    mapaVisitante->visitantes[pos].isParticipaSorteio = TRUE;
    mapaVisitante->visitantes[pos].isEspecial = TRUE;
    mapaVisitante->visitantes[pos].isConvidado = FALSE;
    mapaVisitante->total_aptos_sorteio++;
    mapaVisitante->total_cadastrados++;

    now = time (0);
    strftime (mapaVisitante->visitantes[pos].dataHora, 100, "%d-%m-%Y %H:%M:%S.000", localtime (&now));


    pos=5;
    mapaVisitante->visitantes[pos].codigo = 6;
    strcpy(mapaVisitante->visitantes[pos].nome, "Jose J");
    strcpy(mapaVisitante->visitantes[pos].dataNascimento, "08081980");
    strcpy(mapaVisitante->visitantes[pos].sexo, "M");
    strcpy(mapaVisitante->visitantes[pos].rg, "343065808");
    strcpy(mapaVisitante->visitantes[pos].email, "jose@outlook.com");
    compraAutomatica(mapa, 'L', &mapaVisitante->visitantes[pos].linha, &mapaVisitante->visitantes[pos].coluna, &isOK);
    mapaVisitante->visitantes[pos].isParticipaSorteio = TRUE;
    mapaVisitante->visitantes[pos].isEspecial = FALSE;
    mapaVisitante->visitantes[pos].isConvidado = FALSE;
    mapaVisitante->total_aptos_sorteio++;
    mapaVisitante->total_cadastrados++;

    now = time (0);
    strftime (mapaVisitante->visitantes[pos].dataHora, 100, "%d-%m-%Y %H:%M:%S.000", localtime (&now));

}

int main(){

    int loopContinue = TRUE;
    int opcao = 0;

    MapaAuditorio mapaAuditorio;
    MapaVisitante mapaVisitante;

    mapaAuditorio.isStarted = FALSE;

    if (login())
        modoDemo(&mapaVisitante, &mapaAuditorio);

    do{
        system("cls");
        imprimeCabecalho();
        imprimeMenuPrincipal();
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
              if(mapaAuditorio.isStarted)
                inicializaModuloVisitante(&mapaVisitante, &mapaAuditorio);
              break;
            case 2:
              system("cls");
              if(mapaAuditorio.isStarted)
                sorteio(&mapaVisitante, &mapaAuditorio);
              break;
            case 3:

              if(mapaAuditorio.isStarted)
                email(&mapaVisitante, &mapaAuditorio);
              break;
            case 4:
                system("cls");
                inicializaModuloAuditorio(&mapaAuditorio);
                system("cls");
                imprimeMapa(&mapaAuditorio);
                break;
            case 5:
              loopContinue = FALSE;
              break;
            default:
                opcaoInvalida();
                getch();
                break;
        }
    }while(loopContinue);

  liberaMemMapaAuditorio(&mapaAuditorio);
  liberaMemVisitante(&mapaVisitante);

  return 0;
}
