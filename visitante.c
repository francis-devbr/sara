#include <stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#include "visitante.h"

int findVisitanteBy(MapaVisitante* mapaVisitante, int codigo, int *achou, int total){

    int i = 0;
    int pos = -1;
    (*achou) = FALSE;

    if (codigo<=0){
        return pos;
    }

    for (i=0; i<total;i++){
        if (mapaVisitante->visitantes[i].codigo == codigo){
            (*achou) = TRUE;
            pos = i;
        }
    }

    return pos;
}

void updateHeader(MapaVisitante* mapaVisitante, int pos){
    system("cls");
    imprimeCabecalho();
    imprimeDadosVisitante(mapaVisitante,pos);
    printf("\n\n");
}

void incluir(MapaVisitante* mapaVisitante, int pos, int isEspecial, int isConvidado){

    char s[400];
    int codigo = pos;

    mapaVisitante->visitantes[pos].codigo = codigo+1;
    updateHeader(mapaVisitante, pos);

    mapaVisitante->visitantes[pos].isEspecial = isEspecial;
    updateHeader(mapaVisitante, pos);

    mapaVisitante->visitantes[pos].isConvidado = isConvidado;
    updateHeader(mapaVisitante, pos);

    mapaVisitante->visitantes[pos].isPremiado = FALSE;;
    updateHeader(mapaVisitante, pos);

    if(isConvidado) {
        mapaVisitante->visitantes[pos].isParticipaSorteio = FALSE;
    }else{
        mapaVisitante->visitantes[pos].isParticipaSorteio = TRUE;
    }
    updateHeader(mapaVisitante, pos);

    fflush(stdin);

    strcpy(s,"Nome completo =>  ");
    imprime(&s);
    gets(mapaVisitante->visitantes[pos].nome);
    updateHeader(mapaVisitante, pos);
    fflush(stdin);

    strcpy(s,"Data de nascimento (DDMMAAAA) =>  ");
    imprime(&s);
    gets(mapaVisitante->visitantes[pos].dataNascimento);
    updateHeader(mapaVisitante, pos);
    fflush(stdin);

    strcpy(s,"Sexo (F/M) =>  ");
    imprime(&s);
    gets(mapaVisitante->visitantes[pos].sexo);
    updateHeader(mapaVisitante, pos);
    fflush(stdin);

    strcpy(s,"RG =>  ");
    imprime(&s);
    gets(mapaVisitante->visitantes[pos].rg);
    updateHeader(mapaVisitante, pos);
    fflush(stdin);

    strcpy(s,"E-mail =>  ");
    imprime(&s);
    gets(mapaVisitante->visitantes[pos].email);
    updateHeader(mapaVisitante, pos);
    fflush(stdin);
}

void imprimeDadosVisitante(MapaVisitante* mapaVisitante, int pos){

    char s[400];

    char assento_aux[20];
    sprintf(assento_aux, "%s%d%s%d","C", mapaVisitante->visitantes[pos].coluna +1, "L", mapaVisitante->visitantes[pos].linha +1);

    sprintf(s,"Codigo               : %-30d\n", mapaVisitante->visitantes[pos].codigo);
    imprime(&s);

    sprintf(s,"Nome completo        : %-30s\n", mapaVisitante->visitantes[pos].nome);
    imprime(&s);

    sprintf(s,"Data de nascimento   : %-30s\n", mapaVisitante->visitantes[pos].dataNascimento);
    imprime(&s);

    sprintf(s,"Sexo                 : %-30s\n", mapaVisitante->visitantes[pos].sexo);
    imprime(&s);

    sprintf(s,"RG                   : %-30s\n", mapaVisitante->visitantes[pos].rg);
    imprime(&s);

    sprintf(s,"E-mail               : %-30s\n", mapaVisitante->visitantes[pos].email);
    imprime(&s);

    sprintf(s,"Assento              : %-30s\n", assento_aux);
    imprime(&s);

    sprintf(s,"Especial             : %-30s\n", mapaVisitante->visitantes[pos].isEspecial == TRUE ? "S" : "N");
    imprime(&s);

    sprintf(s,"Convidado            : %-30s\n", mapaVisitante->visitantes[pos].isConvidado == TRUE ? "S" : "N");
    imprime(&s);

    sprintf(s,"Data                 : %-30s\n", mapaVisitante->visitantes[pos].dataHora);
    imprime(&s);

}

void resetMapa(MapaVisitante* mapaVisitante, int pos){

      mapaVisitante->visitantes[pos].codigo = 0;
      mapaVisitante->visitantes[pos].isEspecial = FALSE;
      mapaVisitante->visitantes[pos].isConvidado = FALSE;
      mapaVisitante->visitantes[pos].isPremiado = FALSE;
      mapaVisitante->visitantes[pos].isParticipaSorteio = FALSE;
      strcpy(mapaVisitante->visitantes[pos].nome, "");
      strcpy(mapaVisitante->visitantes[pos].dataNascimento,"");
      strcpy(mapaVisitante->visitantes[pos].sexo,"");
      strcpy(mapaVisitante->visitantes[pos].rg,"");
      strcpy(mapaVisitante->visitantes[pos].email,"");
      mapaVisitante->visitantes[pos].linha = -1;
      mapaVisitante->visitantes[pos].coluna = -1;
      strcpy(mapaVisitante->visitantes[pos].tipoAssento,"");

}

void incluirVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapa){

    char s[400];
    int isOK, achou, isEspecial, isConvidado;

    int opcao = 1;
    int i = 0;
    char diferenciado = 'N';

    do {

        while(mapaVisitante->visitantes[i].codigo != 0){
            i++;
        }

        resetMapa(mapaVisitante,i);
        updateHeader(mapaVisitante, i);;

        strcpy(s,"Assento Especial ?(S/N) =>  ");
        imprime(&s);
        scanf(" %c", &diferenciado);
        isEspecial = toupper(diferenciado) == 'S' ? TRUE : FALSE;
        mapaVisitante->total_aptos_sorteio++;

        if (mapa->assento.qtd_convidado > 0){
            strcpy(s,"É um convidado ?(S/N) =>  ");
            imprime(&s);
            scanf(" %c",&diferenciado);
            isConvidado = toupper(diferenciado) == 'S' ? TRUE : FALSE;
            mapaVisitante->total_aptos_sorteio--;
        }

        if(isEspecial){
            strcpy(mapaVisitante->visitantes[i].tipoAssento, "E");
            compraAutomatica(mapa, mapaVisitante->visitantes[i].tipoAssento, &mapaVisitante->visitantes[i].linha, &mapaVisitante->visitantes[i].coluna, &isOK);
         }else{
            if(isConvidado){
                strcpy(mapaVisitante->visitantes[i].tipoAssento, "C");
                compraAutomatica(mapa, mapaVisitante->visitantes[i].tipoAssento, &mapaVisitante->visitantes[i].linha, &mapaVisitante->visitantes[i].coluna, &isOK);
                mapaVisitante->visitantes[i].isParticipaSorteio = FALSE;
            }else{
                strcpy(mapaVisitante->visitantes[i].tipoAssento, "L");
                compraAutomatica(mapa, mapaVisitante->visitantes[i].tipoAssento, &mapaVisitante->visitantes[i].linha, &mapaVisitante->visitantes[i].coluna, &isOK);
                mapaVisitante->visitantes[i].isParticipaSorteio = TRUE;
                mapaVisitante->total_aptos_sorteio++;
            }
        }

        if(isOK){
            incluir(mapaVisitante,i,isEspecial,isConvidado);
            mapaVisitante->total_cadastrados++;

            time_t now = time (0);
            strftime (mapaVisitante->visitantes[i].dataHora, 100, "%d-%m-%Y %H:%M:%S.000", localtime (&now));

            findVisitanteBy(mapaVisitante,mapaVisitante->visitantes[i].codigo, &achou, mapa->assento.max_assentos);
            updateHeader(mapaVisitante, i);
        }

        strcpy(s,"Digite '1' para Novo Cadastro ou '0' para sair =>  ");
        imprime(&s);
        scanf("%d",&opcao);
     }
     while (opcao==1);
}

void excluiVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapa){
    char s[400];
    char tipo;

    int codigo = 0;
    int pos = 0;
    int achou = FALSE;

    imprimeCabecalho();
    strcpy(s,"Cadastro de Clientes\n\n");
    imprime(&s);

    strcpy(s,"Informe o codigo do visitante");
    imprime(&s);
    scanf("%d",&codigo);

    system("cls");
    imprimeCabecalho();
    strcpy(s,"Cadastro de Clientes\n\n");
    imprime(&s);

    pos = findVisitanteBy(mapaVisitante,codigo, &achou, mapa->assento.max_assentos);

     if (achou){

        updateHeader(mapaVisitante,pos);

        strcpy(s,"Liberando assento...\n");
        imprime(&s);

        if(mapaVisitante->visitantes[pos].isEspecial ){
            tipo = 'E';
        }else if(mapaVisitante->visitantes[pos].isConvidado && !mapaVisitante->visitantes[pos].isEspecial){
            tipo = 'C';
        }else{
            tipo = 'L';
        }

        liberaAssento(mapa, mapaVisitante->visitantes[pos].linha, mapaVisitante->visitantes[pos].coluna, tipo);

        strcpy(s,"Excluindo visitante...\n");
        imprime(&s);
        resetMapa(mapaVisitante, pos);
        strcpy(s,"Visitante excluido...\n");
        getch();

     }
}

void obtemVisitantes(MapaVisitante* mapaVisitante){

    char s[400];
    int i;


    for (i=0;i<mapaVisitante->total_cadastrados;i++){

        if (mapaVisitante->visitantes[i].codigo > 0){
            imprimeDadosVisitante(mapaVisitante, i);
            printf("\n");
        }

        if(i>0 && i%2){
            strcpy(s,"Aperte qualquer tecla para continuar...\n\n");
            imprime(&s);
            getch();
        }
    }
    getch();

}

void obtemVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapaAuditorio){

    char s[400];
    int codigo = 0;
    int achou = FALSE;
    int id = 0;

    system("cls");
    imprimeCabecalho();

    sprintf(s,"Informe o codigo do visitante =>");
    imprime(&s);
    scanf("%d",&codigo);

    id = findVisitanteBy(mapaVisitante,codigo, &achou, mapaAuditorio->assento.max_assentos);

    printf("\n");

    if(achou){
        imprimeDadosVisitante(mapaVisitante, id);
    }else{
        red();
        printf("\n");
        sprintf(s,"Visitante nao encontrado!!!");
        imprime(&s);
        reset();
    }

    getch();

}

void menuListaVisitantes(MapaVisitante* mapaVisitante, MapaAuditorio* mapa){

    char s[400];

    int loopContinue = TRUE;

    int opcao = 0;

    do{

        system("cls");
        imprimeCabecalho();
        imprimeMenuListarVisitantes();
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                system("cls");
                imprimeCabecalho();
                strcpy(s,"Cadastro de Clientes\n\n");
                imprime(&s);

                obtemVisitante(mapaVisitante,mapa);

                break;
            case 2:
                system("cls");
                imprimeCabecalho();
                strcpy(s,"Cadastro de Clientes\n\n");
                imprime(&s);

                obtemVisitantes(mapaVisitante);
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

void inicializaModuloVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapa){

    char s[400];

    int loopContinue = TRUE;

    int opcao = 0;

    do{

        system("cls");
        imprimeCabecalho();
        imprimeMenuVisitante();
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                system("cls");
                incluirVisitante(mapaVisitante,mapa);
                break;
            case 2:
                system("cls");
                excluiVisitante(mapaVisitante,mapa);
                break;
            case 3:
                menuListaVisitantes(mapaVisitante,mapa);
                break;
            case 4:
                system("cls");
                imprimeMapa(mapa);
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

}

void alocaMemVisitante(MapaVisitante* mapaVisitante, int total) {
    mapaVisitante->total_cadastrados = 0;
    mapaVisitante->total_aptos_sorteio = 0;
	mapaVisitante->visitantes = malloc(sizeof(Visitante) * total);
}

void liberaMemVisitante(MapaVisitante* mapaVisitante){
    mapaVisitante->total_cadastrados = 0;
    mapaVisitante->total_aptos_sorteio = 0;
    free(mapaVisitante->visitantes);
}

