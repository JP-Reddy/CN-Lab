#include<stdio.h>
#include<stdlib.h>
#define INF 99

int distance[50],visited[50],a[50][50],n;

void dijkstra(int source){
	int i,j,vertex,least;
	visited[source]=1;

	for(i=0;i<n;i++){
		least=INF;
		for(j=0;j<n;j++){
			if(!visited[j] && distance[j]<least){
				least=distance[j];
				vertex=j;
			}
		}
		visited[vertex]=1;
		for(j=0;j<n;j++){
			if(!visited[j] && distance[j]>distance[vertex]+a[vertex][j])
				distance[j]=distance[vertex]+a[vertex][j];

		}		
	}
	printf("Router %d: ",source+1);
	for(i=0;i<n;i++)
		printf("%d\t",distance[i]);
	printf("\n");
}

int main(){
	int i,j,source;
	printf("No. of routers: ");
	scanf("%d",&n);
	printf("Enter distance matrix:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	for(source=0;source<n;source++){
		for(i=0;i<n;i++){
			visited[i]=0;
			distance[i]=a[source][i];
		}
		dijkstra(source);
	}

}