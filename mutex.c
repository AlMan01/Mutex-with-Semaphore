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
	m->init_value = 0;
	m->binary_semaphore = sem_open("/sem", 0, S_IRUSR | S_IWUSR, m->init_value);
	if (m->binary_semaphore == SEM_FAILED)
	{
		perror("UNABLE TO OPEN SEMAPHORE\n");
		exit(1);
	}
}

void close_bin_sem(struct mutex* m)
{
	if (sem_close(m->binary_semaphore) == -1)
	{
		perror("UNABLE TO CLOSE SEMAPHORE\n");
		exit(1);
	}
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
