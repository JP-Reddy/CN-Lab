#include<stdio.h>


unsigned short header[20];

unsigned short checksum(int type){
	printf("Enter header: ");
	int sum=0,i;
	int num;
	unsigned short x;
	num=160/type-1;
	switch(type){
		case 8: x=0x00FF;
				break;
		case 12: x=0x0FFF;
				break;
		case 16: x=0xFFFF;
				break;

	}
	for(i=0;i<num;i++){
		printf("Word %d: ",i);
		scanf("%x",&header[i]);
		sum+=(unsigned short)header[i];

		}
	while(sum>>type){
		sum=(sum & x) + (sum>>type);
	}
	sum=~(unsigned short) sum;
	return sum;
}

int main(){
	int type;
	unsigned short s_checksum,r_checksum;
	printf("Enter type 8,12 or 16: ");
	scanf("%d",&type);
	s_checksum=checksum(type);
	printf("Sender checksum: %x\n",s_checksum);
	printf("Receiver checksum");
	r_checksum=checksum(type);
	printf("Receiver checksum: %x\n",r_checksum);
	if(s_checksum==r_checksum)
		printf("No error\n");
	else
		printf("Error\n");

}