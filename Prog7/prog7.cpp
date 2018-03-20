#include<iostream>
#include<cstring>
using namespace std;

int crc(char *ip,char *cw,char *poly,int mode){
	strcpy(cw,ip);
	const char* zero="0";
	if(mode==0) {
		for(int j=1;j<strlen(poly);j++)
			strcat(cw,zero);
	}
	for(int i=0;i<strlen(ip);i++){
		if(cw[i]=='1'){
			for(int j=0;j<strlen(poly);j++){
				if(cw[i+j]==poly[j]){
					cw[i+j]='0';
				}
				else
					cw[i+j]='1';
			}
		}
	}

	if(mode==1){
		for(int i=strlen(cw)-strlen(poly)+1;i<strlen(cw);i++)
			if(cw[i]=='1')
				return 0;
		return 1;
	}
}

int main(){
	char ip[100],poly[100],cw[100],recv[100];
	cout<<"Enter a binary numberand the polynomial: ";
	cin>>ip;
	cout<<"Polynomial: ";
	cin>>poly;
	crc(ip,cw,poly,0);
	cout<<"Codeword sent is: "<<cw;
	cout<<"Enter received word: ";
	cin>>recv;

	int res;
	res=crc(recv,cw,poly,1);
	if(res==0) 
		cout<<"Remainder is not zero. \n";
	else
		cout<<"Remainder is zero\n";
}