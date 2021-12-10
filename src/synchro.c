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

// #include "synchro.h"
// #include "ensitheora.h"
// #include <pthread.h>

// pthread_t thread2SDL ;
//  pthread_mutex_t lock ;


// /* les variables pour la synchro, ici */
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t taille_cond = PTHREAD_COND_INITIALIZER;
// pthread_cond_t creation_cond = PTHREAD_COND_INITIALIZER;
// bool taille_transmis = false;       //Condition pour la transmission de la taille de fenêtre par décodeur
// bool creation_fenetre = false;      //Condition pour la création de fenêtre par afficheur

// int NB_TEXTURE = 0;
// pthread_cond_t texture_cond = PTHREAD_COND_INITIALIZER; //Condition pour le prod_cons texture

// /* l'implantation des fonctions de synchro ici */
// void envoiTailleFenetre(th_ycbcr_buffer buffer) {
//         pthread_mutex_lock(&mutex);

//         //Transmission de la taille
//         windowsx = buffer[0].width;
//         windowsy = buffer[0].height;

//         //Mettre à jour la condition
//         taille_transmis = true;
//         pthread_cond_signal(&taille_cond);
//         pthread_mutex_unlock(&mutex);
// }

// void attendreTailleFenetre() {
//         pthread_mutex_lock(&mutex);
//         while(!taille_transmis){
//                 pthread_cond_wait(&taille_cond, &mutex);
//         }
//         pthread_mutex_unlock(&mutex);
// }

// void signalerFenetreEtTexturePrete() {
//         pthread_mutex_lock(&mutex);
//         creation_fenetre = true;
//         pthread_cond_signal(&creation_cond);
//         pthread_mutex_unlock(&mutex);

// }

// void attendreFenetreTexture() {
//         pthread_mutex_lock(&mutex);
//         while(!creation_fenetre){
//                 pthread_cond_wait(&creation_cond, &mutex);
//         }
//         pthread_mutex_unlock(&mutex);
// }

// void debutConsommerTexture() {
//         pthread_mutex_lock(&mutex);
//         while(NB_TEXTURE == 0){
//                 pthread_cond_wait(&texture_cond,&mutex);
//         }
// }

// void finConsommerTexture() {
//         NB_TEXTURE -= 1;
//         if(NB_TEXTURE == NBTEX - 1){
//                 pthread_cond_signal(&texture_cond);
//         }
//         pthread_mutex_unlock(&mutex);
// }


// void debutDeposerTexture() {
//         pthread_mutex_lock(&mutex);
//         while(NB_TEXTURE == NBTEX){
//                 pthread_cond_wait(&texture_cond, &mutex);
//         }
// }

// void finDeposerTexture(){
//         NB_TEXTURE += 1;
//         if(NB_TEXTURE == 1){
//                 pthread_cond_signal(&texture_cond);
//         }
//         pthread_mutex_unlock(&mutex);
// }