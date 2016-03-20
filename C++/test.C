#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t cs;
int N_papers = 20;
int i = 0;

class monitor {
private:
	pthread_mutex_t crit_section;
public:
	void InitCritSect(pthread_mutex_t * crit_section) {
		pthread_mutex_init(crit_section, NULL);
	}
	void EnterCritSect(pthread_mutex_t * crit_section) {
		pthread_mutex_lock(crit_section);
	}
	void LeaveCritSect(pthread_mutex_t * crit_section) {
		pthread_mutex_unlock(crit_section);
	}
	void DestroyCritSect(pthread_mutex_t * crit_section) {
		pthread_mutex_destroy(crit_section);
	}
};

void* thread(void* args)
{
  int* n = (int*)args;
  
  while (i < N_papers)
  {
    EnterCritSect(cs);
    i = i + n[1];
	printf("thread %i take %i papers\n", n[0], n[1]);
	printf("total papers counter %i\n", i);
    sleep(1);
	LeaveCritSect(cs);
  }
  
}

main()
{
  pthread_t t1, t2, t3;
  monitor m;
  int n[] = {{1,3},
			 {2,4},
			 {3,5}};

  m.InitCritSect(cs);

  pthread_create(&t1, NULL, thread, (void*)n[0]);
  pthread_create(&t2, NULL, thread, (void*)n[1]);
  pthread_create(&t3, NULL, thread, (void*)n[2]);

  pthread_detach(t2);
  pthread_detach(t3);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  
  m.DestroyCritSect(cs);
}

