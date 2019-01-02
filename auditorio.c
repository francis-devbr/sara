#include <string.h>;
#include <stdio.h>
#include <stdlib.h>

#include "auditorio.h"

char s[400];

int getModAssento(int qtd_assento, int column){

    int mod = 0;
    int aux = qtd_assento;

    do{
        mod = aux%column;
        aux++;
    } while(!mod);

    return aux/column;
}

void getMaxAssentos(MapaAuditorio* mapa, int* isOK){

    imprimeCabecalho();
    imprimeHeaderMapa(mapa);

    strcpy(s,"Informe o total de assentos comuns =>  ");
    imprime(&s);
    scanf("%d", &mapa->assento.qtd_comum);

    if (mapa->assento.qtd_comum <= 0){
        red();
        printf("\n");
        strcpy(s,"A quantidade de assentos comuns informada e invalida!\n");
        imprime(&s);
        strcpy(s,"Por favor informe novamente...                       \n");
        imprime(&s);
        reset();
        (*isOK) = FALSE;
        getch();
    }else{
        (*isOK) = TRUE;
    }
}

void getMaxAssentosReservados(MapaAuditorio* mapa, int* isOK){

    char reservar;

    imprimeCabecalho();
    imprimeHeaderMapa(mapa);
    strcpy(s,"Deseja reservar assentos \"Sim\" ou \"Nao\" => ");
    imprime(&s);
    scanf(" %c", &reservar);

    if (toupper(reservar) == 'S'){
        strcpy(s,"Informe a quantidade de assentos a serem reservados => ");
        imprime(&s);
        scanf("%d", &mapa->assento.qtd_convidado);
    }

    if(mapa->assento.qtd_convidado > mapa->assento.qtd_comum){
        red();
        printf("\n");
        strcpy(s,"A quantidade de assentos reservados excede a quantidade de assentos disponiveis!\n");
        imprime(&s);
        strcpy(s,"Por favor informe novamente...                                                  \n");
        imprime(&s);
        reset();
        (*isOK) = FALSE;
        getch();
    }else{
        (*isOK) = TRUE;
    }

}

int getAssentosEspeciais(int qtde_assento){
    float number = qtde_assento * 0.05;
    return  (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}

void getColunas(MapaAuditorio* mapa, int* isOK){

    imprimeCabecalho();
    imprimeHeaderMapa(mapa);

    strcpy(s,"Quantidade de colunas por fileira => ");
    imprime(&s);
    scanf("%d", &mapa->colunas);

    if(mapa->colunas <= 0){
        red();
        printf("\n");
        strcpy(s,"A quantidade de colunas informada e invalida!\n");
        imprime(&s);
        strcpy(s,"Por favor informe novamente...               \n");
        imprime(&s);
        reset();
        (*isOK) = FALSE;
        getch();
    }else{
        (*isOK) = TRUE;
    }

}

void inicializaModuloAuditorio(MapaAuditorio* mapa){
    int isOK;

    do{

        liberaMemMapaAuditorio(mapa);

        do{
            system("cls");
            getMaxAssentos(mapa, &isOK);
        }while(!isOK);

        mapa->assento.qtd_especial = getAssentosEspeciais(mapa->assento.qtd_comum);
        mapa->assento.max_assentos = (mapa->assento.qtd_comum + mapa->assento.qtd_especial);

        do{
            system("cls");
            getMaxAssentosReservados(mapa, &isOK);
        }while(!isOK);

        do{
            system("cls");
            getColunas(mapa, &isOK);
        }while(!isOK);

        mapa->linhas = (getModAssento(mapa->assento.qtd_comum, mapa->colunas) + getModAssento(mapa->assento.qtd_especial, mapa->colunas));

        alocaMemMapaAuditorio(mapa);
        inicializaAuditorio(mapa);

        system("cls");
        imprimeCabecalho();
        imprimeHeaderMapa(mapa);
        strcpy(s,"Digite '1' para confirmar ou '0' para tentar novamente => ");
        imprime(&s);
        scanf("%d", &isOK);

    }while (!isOK);

    if(isOK);
        mapa->isStarted = TRUE;
}

void alocaMemMapaAuditorio(MapaAuditorio* mapa){
    mapa->matriz = malloc(sizeof(char*) * mapa->linhas);

	for(int i = 0; i < mapa->linhas; i++) {
		mapa->matriz[i] = malloc(sizeof(char) * mapa->colunas + 1);
	}
}

void liberaMemMapaAuditorio(MapaAuditorio* mapa){

    mapa->colunas = 0;
    mapa->linhas = 0;
    mapa->free_row = -1;
    mapa->free_column = -1;
    mapa->assento.qtd_comum = 0;
    mapa->assento.qtd_especial = 0;
    mapa->assento.qtd_convidado = 0;
    mapa->assento.max_assentos = 0;
    mapa->assento.qtd_livre = 0;
    mapa->assento.qtde_ocupado = 0;

	for(int i = 0; i < mapa->linhas; i++) {
		free(mapa->matriz[i]);
	}

	free(mapa->matriz);
}

void inicializaAuditorio(MapaAuditorio* mapa){

     int i,j;
     int max_especial  = 1;
     int max_reservado = 1;
     int max_comum = 1;

     for(i = 0; i < mapa->linhas; i++){
         if (max_especial <= mapa->assento.qtd_especial){
            for(j = 0; j < mapa->colunas; j++){
                if(max_especial <= mapa->assento.qtd_especial){
                    mapa->matriz[i][j] = 'E';
                }else{
                    mapa->matriz[i][j] = 'X';
                }
                max_especial++;
            }

        }else if (max_reservado <= mapa->assento.qtd_convidado){
            for(j = 0; j < mapa->colunas; j++){
                if(max_reservado <= mapa->assento.qtd_convidado){
                    max_comum++;
                    mapa->matriz[i][j] = 'R';
                }else{
                    if(max_comum <= mapa->assento.qtd_comum){
                        mapa->matriz[i][j] = 'L';
                    }else{
                        mapa->matriz[i][j] = 'X';
                    }
                    max_comum++;
                }
                max_reservado++;
            }
        }else{
            for(j = 0; j < mapa->colunas; j++){
                if(max_comum <= mapa->assento.qtd_comum){
                    mapa->matriz[i][j] = 'L';
                }else{
                     mapa->matriz[i][j] = 'X';
                }
                max_comum++;
            }
        }
     }
}

void imprimeMapa(MapaAuditorio* mapa){

      int i,j;
      char s_aux[400];
      char s_num_col[400];

      mapa->assento.qtd_livre = countAssentos(mapa, 'L');
      mapa->assento.qtde_ocupado = countAssentos(mapa, 'O');

      imprimeCabecalho();
      imprimeHeaderMapa(mapa);
      printf("\n\n");
      strcat(s_num_col, "       ");

      for(i = 0; i < mapa->colunas; i++){
        sprintf(s_aux," %02d   ",i+1);
        strcat(s_num_col, s_aux);
      }

      imprimePalco(strlen(s_num_col));

      imprime(&s_num_col);

      for(i = 0; i < mapa->linhas; i++){
         printf("\n\n");
         sprintf(s,"");
         sprintf(s_aux,"%03d",i+1);
         strcat(s, s_aux);

         for(j = 0; j < mapa->colunas; j++){
           if(mapa->matriz[i][j] != 'X'){
                sprintf(s_aux,"   [%c]",mapa->matriz[i][j]);
                strcat(s, s_aux);
           }else{
                sprintf(s_aux,"   ...",mapa->matriz[i][j]);
                strcat(s, s_aux);
           }
         }
         imprime(&s);
      }
      printf("\n\n\n");
      sprintf(s,"L-Livre  O-Ocupado  E-Especial  R-Reservado\n\n");
      imprime(&s);
      getch();
}

void imprimeHeaderMapa(MapaAuditorio* mapa){

      sprintf(s,"  Lotacao Maxima        : %03d  \n", mapa->assento.max_assentos);
      imprime(&s);
      sprintf(s,"  Assentos Especiais    : %03d  \n", mapa->assento.qtd_especial);
      imprime(&s);
      sprintf(s,"  Assentos Reservados   : %03d  \n", mapa->assento.qtd_convidado);
      imprime(&s);
      sprintf(s,"  Assentos Livres       : %03d  \n", mapa->assento.qtd_livre);
      imprime(&s);
      sprintf(s,"   Assentos Ocupados     : %03d  \n\n", mapa->assento.qtde_ocupado);
      imprime(&s);
}

int selectRow(MapaAuditorio* mapa){

   int row;

   printf("Linha: ");
   scanf("%d",&row);

   row--;

   if(row > mapa->linhas){
        printf("\t\n Esta cadeira nao existe!!! ");
   }

   return row;
}

void liberaAssento(MapaAuditorio* mapa, int linha, int coluna, char tipo){

    switch(tipo){
        case 'E':
            mapa->matriz[linha][coluna] = 'E';
            break;
        case 'C':
            mapa->matriz[linha][coluna] = 'R';
            break;
        default:
            mapa->matriz[linha][coluna] = 'L';
            break;
    }
}

int selectColumn(MapaAuditorio* mapa){

   int column;

   printf("Coluna: ");
   scanf("%d",&column);
   column --;
   if(column>mapa->colunas){
        printf("\t\n Esta cadeira nao existe!!! ");
   }
   return column;
}

void findAssentoLivre(MapaAuditorio* mapa, char tipo ){

    int i,j;
    int achou = FALSE;

    switch (tipo) {
        case 'C':
            for(i = 0; i < mapa->linhas; i++){
                for(j = 0; j < mapa->colunas; j++){
                    if (!achou){
                        if (mapa->matriz[i][j] == 'R'){
                            mapa->free_row = i;
                            mapa->free_column = j;
                            achou = TRUE;
                        }
                    }
                }
            }
            break;
        case 'E':
            for(i = 0; i < mapa->linhas; i++){
                for(j = 0; j < mapa->colunas; j++){
                    if (!achou){
                        if (mapa->matriz[i][j] == 'E'){
                            mapa->free_row = i;
                            mapa->free_column = j;
                            achou = TRUE;
                        }
                    }
                }
            }
            break;
        default:
            for(i = 0; i < mapa->linhas; i++){
                for(j = 0; j < mapa->colunas; j++){
                    if (!achou){
                        if (mapa->matriz[i][j] == 'L'){
                            mapa->free_row = i;
                            mapa->free_column = j;
                            achou = TRUE;
                        }
                    }
                }
            }
            break;
    }
}

int countAssentos(MapaAuditorio* mapa, char tipo){

    int i,j;
    int ctrl = 0;

    for(i = 0; i < mapa->linhas; i++){
        for(j = 0; j <= mapa->colunas; j++){
            if(mapa->matriz[i][j] == tipo){
                ctrl++;
            }
        }
    }

    return ctrl;

}

void compraAutomatica(MapaAuditorio* mapa, char tipo_visitante, int* linha, int* coluna, int* isOK){

    findAssentoLivre(mapa,tipo_visitante);

    if(mapa->free_row != -1 && mapa->free_column != -1){
        compraManual(mapa, tipo_visitante, isOK);
        if((*isOK)){
            (*linha) = mapa->free_row;
            (*coluna) = mapa->free_column;
        }
    }else{
        printf("\n\n    NAO EXISTE MAIS VAGAS !!\n\n");
    }

}

void compraManual(MapaAuditorio* mapa, char tipoVisitante, int* isOK){

    int row = mapa->free_row;
    int column = mapa->free_column;

   (*isOK) = FALSE;

   switch(mapa->matriz[row][column]){

       case 'L':
           mapa->matriz[row][column] = 'O';
           (*isOK) = TRUE;
           break;
       case 'O':
           printf("\n\n    CADEIRA JA OCUPADA!! ESCOLHA OUTRA !!\n\n");
           break;
       case 'R':
           if (tipoVisitante != 'C'){
                printf("\n\n    CADEIRA JA RESERVADA!! ESCOLHA OUTRA !!\n\n");
           }else{
                mapa->matriz[row][column] = 'O';
                (*isOK) = TRUE;
           }
           break;
       case 'E':
           if (tipoVisitante != 'E'){
                printf("\n\n    CADEIRA ESPECIAL!! ESCOLHA OUTRA !!\n\n");
           }else{
                mapa->matriz[row][column] = 'O';
                (*isOK) = TRUE;
           }
           break;
       default:
           printf("\n\n    CADEIRA NAO EXISTE!! ESCOLHA OUTRA !!\n\n");

   }

}


