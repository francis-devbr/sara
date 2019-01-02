#ifndef _VISITANTE_H_
#define _VISITANTE_H_
#endif

#include "auditorio.h"

struct Visitante    {
    int  codigo;                 /* código do visitante */
    char nome[50];               /* nome completo */
    char dataNascimento[10];     /* data de nascimento */
    char sexo[2];                /* sexo */
    char rg[10];                 /* RG */
    char email[50];              /* email */
    int  isConvidado;            /* convidado (S/N) (MAX 10) */
    int  isEspecial;             /* convidado (S/N) (MAX 03)*/
    char tipoAssento[1];            /* assento reservado*/
    int  linha;
    int  coluna;
    int  isParticipaSorteio;
    int  isPremiado;
    char dataHora[100];
};

typedef struct Visitante Visitante;

struct MapaVisitante{
    Visitante* visitantes;
    int total_aptos_sorteio;
    int total_cadastrados;
};

typedef struct MapaVisitante MapaVisitante;

int findVisitanteBy(MapaVisitante* mapaVisitante, int codigo, int *achou, int total);
void updateHeader(MapaVisitante* mapaVisitante, int pos);
void incluir(MapaVisitante* mapaVisitante, int pos, int isEspecial, int isConvidado);
void imprimeDadosVisitante(MapaVisitante* mapaVisitante, int pos);
void resetMapa(MapaVisitante* mapaVisitante, int pos);
void incluirVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapa);
void excluiVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapa);
void listarVisitantes(MapaVisitante* mapaVisitante);
void inicializaModuloVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapa);
void alocaMemVisitante(MapaVisitante* mapaVisitante, int total);
void liberaMemVisitante(MapaVisitante* mapaVisitante);
void obtemVisitantes(MapaVisitante* mapaVisitante);
void obtemVisitante(MapaVisitante* mapaVisitante, MapaAuditorio* mapaAuditorio);
