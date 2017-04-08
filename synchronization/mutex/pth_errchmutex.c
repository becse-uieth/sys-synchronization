#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int val;


void * thread_func(){

	FILE * fd;
	pthread_lock((&mutex);
	fd=open(filename,flags);
	/*read*/
	/*write*/
	close(fd);
	/*
	 * int flag=pthread_mutex_trylock(&mutex);
	 * if(flag!=EBUSY){
	 *
	 * printf("mutex again lock\n");
	 * }
	 */
	pthread_mutex_unlock(&mutex);
	return NULL;
	}


pthread_cond_t cv;


int main(){

	pthread_t tid;
	pthread_create(tid,NULL,&thread_func,NULL);
	return 0;
}


