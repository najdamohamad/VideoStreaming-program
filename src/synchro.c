#include "synchro.h"
#include "ensitheora.h"
#include <semaphore.h>

pthread_t thread2SDL ;
//pour le hashmap//
pthread_mutex_t lock ;

extern bool fini;

/* les variables pour la synchro, ici */
sem_t sem_taille_fenetre;
sem_t sem_signale_fenetre;

//pthread_mutex_t mutex_prod ;
pthread_mutex_t mutex_cons ;
pthread_cond_t cond_c;
pthread_cond_t cond_p;
uint32_t texture = 0 ;




/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    windowsx = buffer[0].width ;
    windowsy = buffer[0].height ;
    sem_post(&sem_taille_fenetre);
}

void attendreTailleFenetre() {
    sem_wait(&sem_taille_fenetre);
}

void signalerFenetreEtTexturePrete() {
    sem_post(&sem_signale_fenetre);
}

void attendreFenetreTexture() {
    sem_wait(&sem_signale_fenetre);
}





void debutConsommerTexture() {
    pthread_mutex_lock(&mutex_cons);
    while(texture == 0)
    {
        pthread_cond_wait(&cond_p , &mutex_cons);
    }
    texture -- ;
}

void finConsommerTexture() {
    pthread_mutex_unlock(&mutex_cons);
    pthread_cond_broadcast(&cond_c);
}


void debutDeposerTexture() {
    pthread_mutex_lock(&mutex_cons);
    while(texture == NBTEX)
        {pthread_cond_wait( &cond_c,&mutex_cons);}
    texture ++ ;
}

void finDeposerTexture() {
    pthread_mutex_unlock(&mutex_cons);
    pthread_cond_broadcast(&cond_p);
}
