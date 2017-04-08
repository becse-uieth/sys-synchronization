#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int val,flags;
int thread_flag;

pthread_cond_t cv;
pthread_cond_init(&cv,NULL);

void * thread_func(){

	while(1){

		while(!thread_flag){

			pthread_mutex_lock(&mutex);
			pthread_cond_wait(&cv,&mutex);
			pthread_mutex_unlock(&mutex);
		}

	}
	
	/*do some work*/
}


void *add(void *a){

	printf("in %s\n",__func__);
	int *b;
	b=(int *)a;
	int sum=0;
	int i;
	for(i=0;i<5;i++)
		sum +=b[i];
	return (void *)sum;
}




int main(){
	
	int c,a[5],i;
	printf("enter five number\n");
	for(i=0;i<5;i++)
		scanf("%d",a[i]);

	pthread_t tid[2];
	pthread_create(tid[0],NULL,&add,NULL);
	pthread_join(tid[0],(void *)&c);
	printf("sum = %d\n",(int *)c);
	pthread_create(tid[1],NULL,&thread_func,NULL);
	pthread_join(tid[0],NULL);
	pthread_kill(tid,"SIGINT");
	return 0;
}


