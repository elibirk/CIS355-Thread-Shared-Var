#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *Counter(void *beginning);
const int threadNum = 4;
int main(){
  pthread_t tid[threadNum];//thread id for 4 threads
  int count; //thread number
  int array[4] = {0};
  //make threads
  for(count = 0; count < threadNum; count++){
  
    if(pthread_create(&tid[count], NULL, Counter, (void *)&array[0]) == -1){
	cout << "Thread error" << endl;
	exit(-1);
    }//end if for thread creation
    }//end for loop

    //wait for thread completion
    for(count = 0; count < threadNum; count++){
      if(pthread_join(tid[count], NULL) == -1){
         cout << "pthread_join error" << endl;
         exit(-1);
  }//end if
}//end for
    cout << "Adding 1 to 100,000 " << threadNum << " times results in:  " << sum << endl;
 return 0;
}//end main

void *Counter(void *beginning){
  int start =*(int*)beginning;
  cout << "Counting from " << start << " to " << start+100000 << "..." <<endl;
  for(int i = start; i <= start+100000; i++){
    pthread_mutex_lock( &mutex );
    sum = sum + i;
    pthread_mutex_unlock( &mutex );
  }//end for

  return NULL;
}//end Counter
