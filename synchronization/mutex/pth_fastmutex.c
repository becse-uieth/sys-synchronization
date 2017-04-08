#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int val,flags;
pthread_cond_t cv;

void * thread_func(){

	FILE * fd;
	pthread_mutex_lock(&mutex);
	fd=fopen("/home/ashish/linux/synchronization/mutex/ashish",flags);
	/*read*/
	/*write*/
	close(fd);
	
	 int flag=pthread_mutex_trylock(&mutex);
	  if(flag!='EBUSY'){
	 
	  printf("mutex again lock\n");
	  }
	
	pthread_mutex_unlock(&mutex);
	return NULL;
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
	printf("enter five number\n")
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


