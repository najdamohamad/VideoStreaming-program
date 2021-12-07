#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdbool.h>
#include "ensitheora.h"
#include <semaphore.h>

extern pthread_t thread2SDL ;
extern pthread_mutex_t lock ;
extern sem_t sem_taille_fenetre;
extern sem_t sem_signale_fenetre;
extern bool fini;
extern pthread_mutex_t mutex_cons ;
//extern pthread_mutex_t mutex_prod ;


/* Les extern des variables pour la synchro ici */


/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

#endif
