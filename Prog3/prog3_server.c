#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define MSGSZ 10000

typedef struct msgbuf
{
	long mtype;
	char mtext[MSGSZ];
}message_buf;

int main()
{
	int msqid1,msqid2,f1,filesize,n;
	// int msgflg= IPC_CREAT | 0666;
	key_t key1,key2;
	message_buf buf;
	memset(&buf,0,sizeof(buf));
	size_t buf_length;
	key1=1234;
	key2=5678;

	// MESSAGE QUEUE 1 - INPUT
	if(msqid1=msgget(key1,0666)<0)
	{
		printf("SERVER: Can't open the input message queue\n");
		return 0;
	}
	else
		printf("SERVER: Input message queue opened successfully\nSERVER: Waiting for client request\n");

	// MESSAGE RECEIVE

	//MESSAGE QUEUE 2 - OUTPUT
	if(msqid2=msgget(key2,0666)<0)
	{
		printf("SERVER: Can't open the output message queue\n");
		return 0;
	}
	else
		printf("SERVER: Output message queue opened successfully\n");

	buf.mtype=2;

	// for(;;)
	// {
		
		if(msgrcv(msqid1,&buf,MSGSZ,1,0)<0)
		{
			printf("SERVER: Error on receiving reply\n");
			return 0;
		}
		else
		{
			printf("SERVER: Received message %s\n",buf.mtext);
			printf("\n\n");
		}
		// OPEN FILE AND SEND CONTENTS ON QUEUE
		if((f1=open(buf.mtext,O_RDONLY))!=-1)
		{
			printf("SERVER: Filename %s is found. Transferring its contents\n",buf.mtext);
			filesize=lseek(f1,0,2);
			lseek(f1,0,0);
			printf("SERVER: Length of the file is %d\n",filesize);
			n=read(f1,buf.mtext,filesize);
			buf_length=strlen(buf.mtext)+1;
			if(msgsnd(msqid2,&buf,buf_length,IPC_NOWAIT)<0)
			{
				printf("SERVER: Error on sending filename\n");
				return 0;
			}
			else
				printf("SERVER: File contents sent to client.\n");
			
		}
		// IF FILE NOT FOUND SEND "FILE NOT FOUND"
		else
		{
			printf("SERVER: Filename not found\n");
			strcpy(buf.mtext,"FILE NOT FOUND");
			buf_length=strlen(buf.mtext)+1;
			
			if(msgsnd(msqid2,&buf,buf_length,IPC_NOWAIT)<0)
			{
				printf("SERVER: Error on sending filename\n");
				return 0;
			}
			else
				printf("SERVER: File contents sent to client.\n");
		}
	// }
	
	return 0;
}


