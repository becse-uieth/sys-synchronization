#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

#include<pthread.h>


typedef struct
{
	        pthread_mutex_t lock;
		pthread_cond_t wait;
		int value;
		int waiters;
} sema;

sema *InitSem(int count)
{       
	        sema *s;

		s = (sema *)malloc(sizeof(sema));
		if(s == NULL) {
		 return(NULL);
							        }
		s->value = count;
	        s->waiters = 0;
	        pthread_cond_init(&(s->wait),NULL);
	        pthread_mutex_init(&(s->lock),NULL);

	        return(s);
}

void P(sema *s)
{
	       pthread_mutex_lock(&(s->lock));

	       s->value--;

	       while(s->value < 0) {
               /*
		 *                  * maintain semaphore invariant
		 *                                   */
               if(s->waiters < (-1 * s->value)) {
                        s->waiters++;
                        pthread_cond_wait(&(s->wait),&(s->lock));
                        s->waiters--;
	       } else {
		       break;
	       }
        }

        pthread_mutex_unlock(&(s->lock));

        return;
}

void V(sema *s)
{

	        pthread_mutex_lock(&(s->lock));

		s->value++;

		if(s->value <= 0)
	    	{
	 		pthread_cond_signal(&(s->wait));					        }
		
		
		pthread_mutex_unlock(&(s->lock));
}