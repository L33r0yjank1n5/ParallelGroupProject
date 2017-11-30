
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <sstream>
#include <string>

using namespace std;


int thread_count;
/*
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
*/
/*
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
*/
int main(int argc, char** argv)
{;
	vector<vector<string> > userItemRating;
	vector<pair<string,string> > userGroup;
	ifstream file ("New_ratings_Musical_Instruments.csv");
	string value;
	string userID, itemID, rating, useless, group;
	
	while (getline(file, value))
	{
		stringstream linestream(value);

     	getline (linestream, userID, ',');
		getline (linestream, itemID, ',');
		getline (linestream, rating, ',');
		getline (linestream, useless, ',');
		getline (linestream, group, ',');

		string temp[] = {userID,itemID,rating};
		vector<string> temp1(temp, temp+3);

		userItemRating.push_back(temp1);
		userGroup.push_back(make_pair(userID,group));
	}

	file.close();

	for(int i = 0; i < userGroup.size(); i++)
	{
		vector<string> likeUsers;			//List of Like Users
		vector<string> items;				//List of Possible Items to recomend
		string id = userGroup[i].first;		//User ID of first person to recomend
		string group = userGroup[i].second;	//Group first person belongs to
		
		//Populating list of like Users
		for(int j = 0; j < userGroup.size(); j++)
		{
			if(id != userGroup[j].first && userGroup[i].second == group)
			{
				likeUsers.push_back(userGroup[j].first);
			}
		}
		
		//Populating list of Items based on what like users have rated, not recording ratings yet
		for(int j = 0; j < likeUsers.size(); j++)
		{
			string likeID = likeUsers[j];

			for(int k = 0; k < userItemRating.size(); k++)
			{
     			if(userItemRating[k][0] == likeID) //userItemRating[l][0] shows only the userID
				{
					string itemNumber = userItemRating[k][1]; //userItemRating[l][1] shows only the itemID

					//Making sure no items are duplicated in list
					for(int m = 0; m < items.size(); m++)
					{
						if(itemNumber == items[m])
						{
							break;
						}
					}
				}
			}
			
			//Need to get ItemRatings and weighted averages per item here.
		}
	}
	
	/*
	for(int i = 0; i < userItemRating.size(); i++) //Testing
	{
		for(int j = 0; j < userItemRating[i].size(); j++)
		{
     		cout << userItemRating[i][1] << endl;
		}
	}*/

    return 0;
}

