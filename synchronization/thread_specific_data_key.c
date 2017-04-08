#include<stdio.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>

pthread_key_t key;

void *thread_func() {
	FILE *stream;
	char filename[100];
	stream = fopen(filename, O_CREAT|S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH);
	sprintf(filename,"%s",thread_self());
	pthread_setspecific(key,stream);
	wfile(&key);
	ffunc(&key);
}

void wfile(pthread_key_t key) {
	
	FILE *stream;
	stream= (FILE *)pthread_getspecific(key);
	fprintf(stream,"This a secondary thread\n");
	fclose(stream);
}

void ffunc(pthread_key_t key) {

	FILE *stream;
	stream=(FILE *)pthread_getspecific(key);
	fflush(stream);
}

int main() {

	int i,r;
	pthread_key_create(&key,ffunc);
	pthread_t tid[5];
	for( i=0; i<5; i++) {
		r=pthread_create(&(tid[i]),NULL,&thread_func,NULL);
		if(r == -1) {
			printf("Error while creating thread\n");
			abort();
		}
		r=pthread_join(tid[i],NULL);
		if( r == -1) {
			printf("Error while joining\n");
			abort();
		}
	}
	return 0;
}

