#include<stdio.h>
int a[10][10],n,p[10],d[10];

void bellman_ford(int s){
	int u,v,i;
	for(i=0;i<n;i++){
		for(u=0;u<n;u++){
			for(v=0;v<n;v++){
				if(d[v]>d[u]+a[u][v]){
					d[v]=d[u]+a[u][v];
					p[v]=u;
				}
			}
		}
	}
	for(u=0;u<n;u++){
		for(v=0;v<n;v++){
			if(d[v]>d[u]+a[u][v]){
				printf("Negative edge");
			}
		}
	}
}

int main(){
	printf("Enter no. of vertices: ");
	scanf("%d",&n);
	printf("Enter adjacency matrix\n");
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	}
	int source;
	for(source=0;source<n;source++){
		for(i=0;i<n;i++){
			d[i]=999;
			p[i]=-1;		
		}
		d[source]=0;
		bellman_ford(source);

		printf("Router %d\n",source);

		for(i=0;i<n;i++){
			if(i!=source){
				j=i;
				while(p[j]!=-1){
					printf("%d <- ",j);
					j=p[j];
				}
			}
			printf("%d\tCost: %d\n",source,d[i]);
		}
	}
	return 1;
}