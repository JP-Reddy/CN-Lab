#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<fcntl.h>

int main()
{
	int sockfd,connfd,n,len,tlen,filesize,f1;
	char buf[100],contents[1000];
	struct sockaddr_in addr,client;
	addr.sin_port=htons(9515);
	addr.sin_family=AF_INET;


	sockfd=socket(AF_INET,SOCK_STREAM,0);

	bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));

	listen(sockfd,5);

	for(;;)
	{
		len=sizeof(client);
		connfd=accept(sockfd,(struct sockaddr *)&client,&len);
		n=read(connfd,buf,tlen)>0;
		if((f1=open(buf,O_RDONLY))!=-1)
		{
			printf("SERVER: Filename %s is found. Transferring its contents\n",buf);
			filesize=lseek(f1,0,2);
			lseek(f1,0,0);
			printf("SERVER: Length of the file is %d\n",filesize);
			memset(contents,0,sizeof(contents));

			n=read(f1,contents,sizeof(contents));
			write(connfd,contents,n);			
		}
		close(connfd);

	}
	close(sockfd);
}