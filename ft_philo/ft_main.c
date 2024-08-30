/* CELEBP27 */
#define _OPEN_THREADS
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void *thread(void *arg) {
      char *ret;
      printf("thread() entered with argument '%s'\n", (char *)arg);
      if ((ret = (char*) malloc(20)) == NULL) {
        perror("malloc() error");
        exit(2);
      }
      strcpy(ret, "This is a test");
      pthread_exit(ret);
}

    int main() {
      pthread_t thid[2];
      void *ret;

      int i = 0;

      while (i < 2)
      {
      if (pthread_create(&thid[i++], NULL, thread, "thread 1") != 0) {
        perror("pthread_create() error");
        exit(1);
      }
      return (1);
    }
    i = 0;
      while (i < 2)
      {
      if (pthread_join(thid[i++], &ret) != 0) {
        perror("pthread_create() error");
        exit(3);
      }
      }
    }