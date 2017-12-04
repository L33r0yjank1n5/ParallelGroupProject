
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<string> > userItemRating; 	//List of the User's Id, Item rated ID, and rating of that item: {userID,itemID,rating}
vector<pair<string, string> > userGroup;	//List of the User's Id and what group they belong to: (userID,group)
int thread_count;

void *recItemCalc(void* rank)
{
	int start = 0;
	int end = 0;
	long id = (long) rank;
	int n = userGroup.size();

	//Spliting threads to handle a portion of the userIDs to analyze
	if(id==0)
    {
		start = 0;
		end = start+(n/thread_count)+(n%thread_count);
		//First thread takes left overs, remainders
    }
    else
    {
		//Second thread starts where the first left off, and so on and so forth
		start = id*(n/thread_count)+(n%thread_count);
		end = start+(n/thread_count);
    }

	for(int i=start; i<end; i++)
    {
		vector<string> likeUsers;						//List of Like Users
		vector<pair<string,double> > itemAverageWeight; //List of Items with their weighted rating: (itemID,weightedAverage)
		
		string id = userGroup[i].first;		//User ID of person to recomend to
		string group = userGroup[i].second;	//Group person belongs to

		//Populating list of like Users
		for (int j = 0; j < userGroup.size(); j++)
		{
			if (id == userGroup[j].first && userGroup[i].second == group)
			{
				likeUsers.push_back(userGroup[j].first);
			}
		}

		//Start the madness
		for (int j = 0; j < likeUsers.size(); j++)
		{
			string likeID = likeUsers[j];

			for (int k = 0; k < userItemRating.size(); k++)
			{
				vector<string> ratings;							//List of ratings for one similar user
				vector<string> items;							//List of items for one similar user
				double average = 0.0;
				double weightAverage = 0.0;
				double sum = 0.0;

				//Populate a list of items from similar users
				if (likeID == userItemRating[k][0]) 			//userItemRating[k][0] shows only the itemID
				{												//userItemRating[k][1] shows only the userID
					string itemNumber = userItemRating[k][1]; 	//userItemRating[k][2] shows only the rating
					
					if(items.size() == 0)
					{
						items.push_back(itemNumber);
					}
					
					if(find(items.begin(), items.end(), itemNumber) != items.end()) 
					{
						items.push_back(itemNumber);
					} 
					else 
					{
						//Do Nothing
					}	
				}
				
				//Figuring out averages
				if(items.size()!=0)
				{
					for(int l = 0; l < items.size(); l++)
					{
						//Normal Average
						double count = 0.0;
						for (int m = 0; m < userItemRating.size(); m++)
						{
							if (items[l] == userItemRating[m][1])
							{		
								int temp = atoi(userItemRating[m][2].c_str());
								sum = sum + (double)temp;
							}
						}
						average = sum/ ((double)items.size());
						
						//Weighted average
						for(int m = 0; m < userItemRating.size(); m++)
						{
							for(int n = 0; n < likeUsers.size(); n++)
							{
								if(items[l] == userItemRating[m][1] && userItemRating[m][0] == likeUsers[n])
								{
									count = count + 1.0;
								}
							}
						}
						weightAverage = average*count;									//Weighted by taking the average rating and multipling it by the number of similar users rated the item
						itemAverageWeight.push_back(make_pair(items[l],weightAverage));   //so that an item with one rating is worth less than an item with 10.
					}
				}
			}
		}
		
		//Finally, the recomendation based on largest weighted average 
		string largestItem = "";
		double largestWAver = 0.0;
		for(int j = 0; j < itemAverageWeight.size(); j++)
		{
			if(itemAverageWeight[j].second > largestWAver)
			{
				largestWAver = itemAverageWeight[j].second;
				largestItem = itemAverageWeight[j].first;
			}
		}
		cout<<endl<<"For user "<<userGroup[i].first<<", we recomend item "<<largestItem<<" because of the number of similar users and their reviews of the item."<<endl;
	}
}

int main(int argc, char** argv)
{
	string value;
	string userID, itemID, rating, useless, group;

	//Start file read
	ifstream file("New_ratings_Musical_Instruments.csv");

	while (getline(file, value))
	{
		stringstream linestream(value);

		getline(linestream, userID, ',');
		getline(linestream, itemID, ',');
		getline(linestream, rating, ',');
		getline(linestream, useless, ',');
		getline(linestream, group, ',');

		string temp[] = { userID, itemID, rating };
		vector<string> temp1(temp, temp + 3);

		userItemRating.push_back(temp1);
		userGroup.push_back(make_pair(userID, group));
	}

	file.close();

	//Start the Multi-Threaing
	long       thread;
    pthread_t* thread_handles;
    thread_count=atoi(argv[1]);
    thread_handles= (pthread_t*)malloc(thread_count*sizeof(pthread_t*));

    for(thread=0; thread<thread_count; thread++)
    {
		pthread_create(&thread_handles[thread], NULL, recItemCalc, (void*)thread);
    }

    for(thread=0; thread<thread_count; thread++)
    {
		pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

	return 0;
}

