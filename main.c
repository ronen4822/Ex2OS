#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex;
pthread_mutex_t internalCountMutex;

int internal_count;
char list[50000] = { '\0' };
int lastElement;
int finish=0;

char pop() {
	/* return the first element of the list (the element at lastElement) */
	char tmp;
	pthread_mutex_lock(&mutex);
	if (lastElement == -1) {
		pthread_mutex_unlock(&mutex);
		return '\0';
	}
	tmp = list[lastElement];
	list[lastElement] = '\0';
	lastElement--;
	pthread_mutex_unlock(&mutex);
	return tmp;
}
void push(char charToPush) {
	/*add a char to the end of the queue*/
	pthread_mutex_lock(&mutex);
	int i;
	for (i = lastElement + 1; i > 0 && i < sizeof(list)-1; --i) {
		list[i] = list[i - 1];
	}
	list[0] = charToPush;
	lastElement++;
	pthread_mutex_unlock(&mutex);
}
void myItoa()
{ /* reads the value of internal count, if 0- print 0 and return, else- read the value into a buffer and print the buffer */
	int tmp=internal_count;
	if (tmp==0)
	{
		write(1,"0\n",strlen("0\n"));
		return;
	}
	int i=0;
	char buffer[1024]={'\0'};
	while (tmp != 0)
	{
		buffer[i]=tmp%10+'0';
		i++;
		tmp/=10;
	}
	i--; // i will go 1 value over the last element because the while checks only after i++
	char tmpChar;
	int j;
	for (j=0;j<=i/2;++j)
	{
		tmpChar=buffer[i-j];
		buffer[i-j]=buffer[j];
		buffer[j]=tmpChar;
	}
	buffer[i+1]='\n';
	write(1,buffer,strlen(buffer));
}
void* threadedFunction(void* arg) { /*reads from the queue until a non null value is received and then executes the corresponding nanosleep and addition to internal_count*/
	while (1) {
                char tmp = pop();
		if (finish && tmp == '\0')
		{
			pthread_mutex_lock(&internalCountMutex);
			myItoa();
			pthread_mutex_unlock(&internalCountMutex);
			pthread_exit(NULL);
		}
		struct timespec tim;
		tim.tv_sec=0;
			if (tmp == '\0') {
                           tim.tv_nsec=0;
                           nanosleep(&tim, NULL);
                           continue;
                         }
				switch (tmp) {
				case '1':
					tim.tv_nsec=100000000L;
					nanosleep(&tim,NULL);
					pthread_mutex_lock(&internalCountMutex);
					internal_count += 1;
					pthread_mutex_unlock(&internalCountMutex);
					break;
				case '2':
					tim.tv_nsec=200000000L;
					nanosleep(&tim,NULL);
					pthread_mutex_lock(&internalCountMutex);
					internal_count += 2;
					pthread_mutex_unlock(&internalCountMutex);
					break;
				case '3':
					tim.tv_nsec=300000000L;
					nanosleep(&tim,NULL);
					pthread_mutex_lock(&internalCountMutex);
					internal_count += 3;
					pthread_mutex_unlock(&internalCountMutex);
					break;
				case '4':
					tim.tv_nsec=400000000L;
					nanosleep(&tim,NULL);
					pthread_mutex_lock(&internalCountMutex);
					internal_count += 4;
					pthread_mutex_unlock(&internalCountMutex);
					break;
				case '5':
					tim.tv_nsec=500000000L;
					nanosleep(&tim,NULL);
					pthread_mutex_lock(&internalCountMutex);
					internal_count += 5;
					pthread_mutex_unlock(&internalCountMutex);
					break;
				case '6':
					pthread_mutex_lock(&internalCountMutex);
					myItoa();
					pthread_mutex_unlock(&internalCountMutex);
					break;
				default:
					break;
				}				
	}
}
int myGetLine(char* buffer, int bufferSize) { /*wait until a new line is received, then put it into a char buffer and return the number of chars*/
	int num_chars = 0;
	int ch;
	do {
		ch = getc(stdin);
	} while (ch == '\n');

	for (; ch != EOF && ch != '\n'; ch = getc(stdin)) {
		buffer[num_chars++] = ch;
	}
	buffer[num_chars] = '\0';
	return num_chars;
}
int main(void) {
	lastElement = -1; //indicates that the list is empty
	internal_count = 0;
	char receivedVal;
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&internalCountMutex, NULL);
	pthread_t tid[5];
	int i;
	for (i = 0; i < 5; ++i) {
		if (pthread_create(&(tid[i]), NULL, threadedFunction, NULL) != 0) {
			write(1,"Failed to create thread",strlen("Failed to create thread"));
		}
	}
	char buffer[1024] = { '\0' };
	int size;
	while (1) {
		size = myGetLine(buffer, 1024);
		if (size != 1) {
			continue;
		}
		receivedVal = buffer[0];
		int queueNotEmpty = 0;
		while (queueNotEmpty == 0) {
			pthread_mutex_lock(&mutex);
			if (lastElement < 49999) {
				queueNotEmpty = 1;
			}
			else
			{
				sleep(0);
			}
			pthread_mutex_unlock(&mutex);
		}
		if (receivedVal < '1' || receivedVal > '8') {
			continue;
		}
		if (receivedVal == '7') {
			//kill all threads
			for (i=0;i<5;++i)
			{
				pthread_cancel(tid[i]);
			}
			pthread_mutex_destroy(&mutex);
			pthread_mutex_destroy(&internalCountMutex);
			myItoa();
			exit(0);
		}
		if (receivedVal == '8') {
			finish=1;
			for (i=0;i<5;++i)
			{
				pthread_join(tid[i],NULL);
			}
			pthread_mutex_destroy(&mutex);
			pthread_mutex_destroy(&internalCountMutex);
			myItoa();
			exit(0);
		}
		push(receivedVal);
	}
	return 0;

}
