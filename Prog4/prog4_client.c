#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


int main(int argc, char * argv[])
{
	int sockfd,n;
	char buf[1000];
	struct sockaddr_in addr;

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	addr.sin_family=AF_INET;
	addr.sin_port=htons(9515);
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.s_addr);

	memset(buf,0,sizeof(buf));
	connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	strcpy(buf,argv[1]);
	// write(sockfd,buf,sizeof(buf));
	memset(buf,0,sizeof(buf));
	n=read(sockfd,buf,sizeof(buf));
	write(1,buf,sizeof(buf));
}