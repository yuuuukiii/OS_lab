#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#define BUFSIZE 100
#define BUFNUM 4
#define KEY 1
pid_t pid[2];
int semid;
int shmid[BUFNUM];
long len;
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};
void P(int semid, int index)
{
	struct sembuf sem = {index, -1, 0};
	semop(semid, &sem, 1);
	return;
}
void V(int semid, int index)
{
	struct sembuf sem = {index, 1, 0};
	semop(semid, &sem, 1);
	return;
}
void writebuf(FILE* fp_old)//向缓冲区写
{
	int i = 0;
	char* shmaddr;
	while((len-ftell(fp_old))>BUFSIZE)
	{
		P(semid, 1);
		shmaddr = (char*)shmat(shmid[i], NULL, 0);
		fread(shmaddr, BUFSIZE, 1, fp_old);
		i = (i+1)%BUFNUM;
		V(semid, 0);
	}
	if(len!=ftell(fp_old))             //处理剩余部分
	{
		int leftsize = len - ftell(fp_old);
		P(semid, 1);
		shmaddr = (char*)shmat(shmid[i], NULL, 0);
		fread(shmaddr, leftsize, 1, fp_old);
		V(semid, 0);
	}
	exit(0);
}
void readbuf(FILE* fp_new)//从缓冲区读
{
	int i = 0;
	char* shmaddr;
	long old = 0;
	while((len - ftell(fp_new))>BUFSIZE)
	{
		P(semid, 0);
		shmaddr = (char*)shmat(shmid[i], NULL, 0);
		fwrite(shmaddr, BUFSIZE, 1, fp_new);
		i = (i+1)%BUFNUM;
		V(semid, 1);
	}
	if(len!=ftell(fp_new)) //处理剩余部分
	{
		int leftsize = len-ftell(fp_new);
		P(semid, 0);
		shmaddr = (char*)shmat(shmid[i], NULL, 0);
		fwrite(shmaddr, leftsize, 1, fp_new);
		V(semid, 1);
	}
	exit(0);
}

int main(int argc, char** argv)
{
	//open files
	FILE* fp_old, *fp_new;
	if((fp_old = fopen(argv[1], "r")) == NULL)
	{
		printf("error: open failed\n");
		return -1;
	}
	if((fp_new = fopen(argv[2], "w")) == NULL)
	{
		printf("error: open faild\n");
		return -1;
	}
	
	fseek(fp_old, 0, SEEK_END);
	len = ftell(fp_old);   //获取文件尾偏移量
	fseek(fp_old, 0, SEEK_SET);
	
	int i = 0;
	for( ; i< BUFNUM; i++)
	{
		shmid[i] = shmget(i, BUFSIZE, IPC_CREAT|0666);
		if(shmid[i] < 0)
		{
			perror("get shm ipc_id error");
			return -1;
		}
	}
	
	//设置信号量
	//semid 0: 满缓冲区的数目，初值为0
	//semid 1: 空缓冲区数目，初值为BUFNUM
	semid = semget(KEY, 2, IPC_CREAT|0666);
	if(-1 == semid)
	{
		printf("error\n");
		return -1;
	}
	union semun arg;
	arg.val = 0;
	semctl(semid, 0, SETVAL, arg); //初始化满缓冲区数目为0
	arg.val = BUFNUM;
	semctl(semid, 1, SETVAL, arg); //初始化空缓冲区数目为BUFNUM
	
	int n = 0;
	for(; n<2; n++)
	{
		if((pid[n] = fork()) == 0)
			break;
	}
	switch(n)
	{
		case 0: //子进程1
		{
			writebuf(fp_old);
			break;
		}
		case 1: //子进程2
		{
			readbuf(fp_new);
			break;
		}
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	semctl(semid, 0, IPC_RMID, arg);
	for(i = 0; i<BUFNUM; i++)
	{
		shmctl(shmid[i], IPC_RMID, NULL);
	}
	return 0;
}

