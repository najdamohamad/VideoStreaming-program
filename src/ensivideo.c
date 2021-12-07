#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <semaphore.h>
#include "synchro.h"


#include "stream_common.h"
#include "oggstream.h"






int main(int argc, char *argv[]) {
    int res;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);

    //initialisation de notre sem 
    sem_init(&sem_taille_fenetre,0,0);
    sem_init(&sem_signale_fenetre,0,0);    

    // Initialisation de la SDL

    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);
    
    // start the two stream readers
    pthread_t theora ;
    pthread_t vorbis ;
    int t,v ;
    t = pthread_create( &theora, NULL, &theoraStreamReader,  argv[1] );
    v = pthread_create( &vorbis, NULL, &vorbisStreamReader, argv[1] );

    if(t != 0) 
    {
        printf("CREATION OF THEORA THREAD FAILED ! \n") ;
        exit(-1);
    }
    if(v != 0) 
    {
        printf("CREATION OF VORBIS THREAD FAILED ! \n") ;
        exit(-1);
    }

    printf("the two threads were successfully created \n ");
    
    // wait audio thread
    pthread_join(vorbis,NULL);
    printf("WAITING FOR AUDIO : DONE ");

    // 1 seconde de garde pour le son,
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués
    pthread_cancel(theora);
    pthread_cancel(thread2SDL);
    printf("ALL THREADS DONE");
    // attendre les 2 threads videos
    pthread_join(theora,NULL);
    pthread_join(thread2SDL,NULL);


    
    exit(EXIT_SUCCESS);    
}
