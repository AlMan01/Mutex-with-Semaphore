#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

struct mutex
{
	sem_t* binary_semaphore;
	int init_value;
};

void init_bin_sem(struct mutex* m)
{
	//const char* shm_name = "memory";
	//const int shm_size = 4096;
	//int shm_id;
	//char* ptr;
	//shm_id = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
	//ftruncate(shm_id, shm_size);
	m->init_value = 0;
	m->binary_semaphore = sem_open("/sem", 0, S_IRUSR | S_IWUSR, m->init_value);
	//ptr = (char*)mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
	//return ptr;
}

int lock(struct mutex* m)
{
	if(sem_wait(m->binary_semaphore) == -1)
	{
		perror("UNABLE TO DECREMENT SEMAPHORE\n");
		perror("FAILED TO LOCK THE MUTEX.\n");
		perror("IT'S ALREADY BEEN LOCKED.\n");
		return -1;
	}
	else
	{
		printf("MUTEX IS SUCCESFULLY LOCKED.\n");
		return 0;
	}
}

int unlock(struct mutex* m)
{
	if(sem_post(m->binary_semaphore) == -1)
	{
		perror("UNABLE TO INCREMENT SEMAPHORE\n");
		perror("FAILED TO UNLOCK THE MUTEX.\n");
		perror("IT'S ALREADY BEEN UNLOCKED.\n");
		return -1;
	}
	else
	{
		printf("MUTEX IS SUCCESFULLY UNLOCKED.\n");
		return 0;
	}
}

int main()
{
	return 0;
}
