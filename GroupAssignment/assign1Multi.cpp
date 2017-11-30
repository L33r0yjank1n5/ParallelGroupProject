
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

typedef vector<vector<int> > AdjacencyMatrix;
AdjacencyMatrix adjMatrix;
AdjacencyMatrix comFriends;
int thread_count;

void *comFriendsCalc(void* rank)
{
    long id = (long) rank;
    int start=0;
    int end=0;
    int n = adjMatrix.size();

    if(id==0)
    {
	start = 0;
	end = start+(n/thread_count)+(n%thread_count);
    }
    else
    {
	start = id*(n/thread_count)+(n%thread_count);
	end = start+(n/thread_count);
    }

    for(int i=start; i<end; i++)
    {
	for(int j=0; j<adjMatrix[i].size(); j++)
	{
		int count=0;
		if(i!=j && adjMatrix[i][j]==1)
		{
			for(int h=0; h<adjMatrix[j].size(); h++)
			{
				if(adjMatrix[i][j]==1 && adjMatrix[j][h]==1)
				{
					count++;
				}
			}
		}
		comFriends[i][j]=count;
	}
    }

    return NULL;
}

void printMatrix(AdjacencyMatrix adjMatrix)
{
    for (int i=0; i<adjMatrix.size(); i++)
    {
        for (int j=0; j<adjMatrix[i].size(); j++)
	{
		cout<<adjMatrix[i][j]<<" ";
        	cout<<endl;
	}
    }
}

int main(int argc, char** argv)
{
    if(argc<4)
    {
        cout<<"To run: ./assign1Serial filename k #ofthreads"<<endl;
        cout<<"./assign1Serial networkDatasets/toyGraph1.txt 2 2"<<endl;
	return 0;
    }

    fstream myfile(argv[1],std::ios_base::in);
    int k = atoi(argv[2]);
    int u,v;
    int maxNode = 0;
    vector<pair<int,int> > allEdges;
    while(myfile >> u >> v)
    {
        allEdges.push_back(make_pair(u,v));
        if(u > maxNode)
        {
		maxNode = u;
	}

        if(v > maxNode)
	{
        	maxNode = v;
	}
    }

    int n = maxNode +1;

    adjMatrix = AdjacencyMatrix(n,vector<int>(n));

    for(int i=0; i<allEdges.size(); i++)
    {
        u = allEdges[i].first;
        v = allEdges[i].second;
        adjMatrix[u][v] = 1;
	adjMatrix[v][u] = 1;
    }

/*  //Testing
    if(n<=10)
    {
	printMatrix(adjMatrix);
    }
*/

    comFriends = AdjacencyMatrix(n,vector<int>(n));

    long       thread;
    pthread_t* thread_handles;
    thread_count=atoi(argv[3]);
    thread_handles= (pthread_t*)malloc(thread_count*sizeof(pthread_t*));

    for(thread=0; thread<thread_count; thread++)
    {
	pthread_create(&thread_handles[thread], NULL, comFriendsCalc, (void*)thread);
    }

    for(thread=0; thread<thread_count; thread++)
    {
	pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

/*  //Testing
    printMatrix(comFriends);
*/

    for(int i=0; i<comFriends.size(); i++)
    {
	for(int h=0; h<k; h++)
	{
		int rec = 0;
		int recNum = 0;

		for(int j=0; j<comFriends.size();j++)
		{
			if(i!=j && comFriends[i][j] > recNum)
			{
				recNum = comFriends[i][j];
				rec = j;
			}
		}

		comFriends[i][rec]=0;
		cout<<"Person " << i << " is recomended to be friends with " << rec << " because they share " << recNum << " friends in common." << endl;
	}
    }

    return 0;
}

