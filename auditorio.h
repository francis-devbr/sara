#ifndef _AUDITORIO_H_
#define _AUDITORIO_H_
#endif

#define NULL 0
#define EOS '\0'
#define FALSE 0
#define TRUE 1

#include "ui.h"

struct Assento{
    int qtd_comum;
    int qtd_especial;
    int qtd_convidado;
    int max_assentos;
    int qtd_livre;
    int qtde_ocupado;
};

typedef struct Assento Assento;

struct MapaAuditorio{
    char** matriz;
    int linhas;
    int colunas;
    int free_row;
    int free_column;
    int isStarted;
    Assento assento;
};

typedef struct MapaAuditorio MapaAuditorio;

int getModAssento(int qtd_assento, int column);
void getMaxAssentos(MapaAuditorio* mapa, int* isOK);
void getMaxAssentosReservados(MapaAuditorio* mapa, int* isOK);
int getAssentosEspeciais(int qtde_assento);
void getColunas(MapaAuditorio* mapa, int* isOK);
void inicializaModuloAuditorio(MapaAuditorio* mapa);
void alocaMemMapaAuditorio(MapaAuditorio* mapa);
void liberaMemMapaAuditorio(MapaAuditorio* mapa);
void inicializaAuditorio(MapaAuditorio* mapa);
void imprimeMapa(MapaAuditorio* mapa);
void imprimeHeaderMapa(MapaAuditorio* mapa);
int selectRow(MapaAuditorio* mapa);
void liberaAssento(MapaAuditorio* mapa, int linha, int coluna, char tipo);
int selectColumn(MapaAuditorio* mapa);
void findAssentoLivre(MapaAuditorio* mapa, char tipo );
int countAssentos(MapaAuditorio* mapa, char tipo);
void compraAutomatica(MapaAuditorio* mapa, char tipo_visitante, int* linha, int* coluna, int* isOK);
void compraManual(MapaAuditorio* mapa, char tipoVisitante, int* isOK);

