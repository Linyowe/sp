#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;//保護共享資源
#define LOOPS 100

void *atm()
{
 for (int i=0;i<LOOPS;i++){
 pthread_mutex_lock(&mutex1);
 counter++;
 pthread_mutex_unlock(&mutex1);
}
 return NULL;
};

void *withdraw()
{
  for(int i=0;i<LOOPS;i++){
  pthread_mutex_lock(&mutex1);
  counter--;
  pthread_mutex_unlock(&mutex1);
}
  return NULL;
}

int main(){
pthread_t thread1,thread2;
pthread_create(&tid1, NULL,atm, NULL);
pthread_create(&tid2, NULL,withdraw, NULL);

pthread_join(&tid1, NULL);
pthread_join(&tid2, NULL);

printf("counter=%d\n", counter);
}

