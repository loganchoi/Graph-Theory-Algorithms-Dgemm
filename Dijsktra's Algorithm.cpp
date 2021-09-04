#include <iostream>
#include <chrono>
#include <map>
using namespace std;
using namespace chrono;
//Dijsktra's 
const int V = 128;
const int INF = 99999;
void Dijsktra_adjacency(map<int,int> adjacency[],int Snode, int Tnode)
{
    bool known[V];
    int cost[V];
    int path[V];
    for (int i = 0;i<V;i++)
    {   
        cost[i] = INF;
        known[i] = false;
        if (i == Snode)
        {
            cost[i] = 0;
            path[i] = -1;
            known[i] = true;
        }
    }
    int key = Snode;
    for (int i = 0; i<V; i++)
    {   
        int min = INF;
        int minKey;
        for (map<int,int>::iterator j = adjacency[key].begin(); j!=adjacency[key].end();j++)
        {   
            if (known[j->first] == false)
            {
                if (j->second == 0)
                    continue;
                else if (j->second < cost[j->first])
                {
                    cost[j->first] = j->second;
                    path[j->first] = key;
                }
                if (min > j->second)
                   minKey = j->first;
            }
        }
        known[minKey] = true;
        key = minKey;
    }
    cout << "The path from "<<Snode << " to " << Tnode << endl;
    int pathKey = Tnode;
    int weight = 0;
    while (true)
    {
        if (pathKey == -1)
           break;
        cout << pathKey << " ";
        weight = weight + cost[pathKey];
        pathKey = path[pathKey];
        
    }
    cout << endl << "The weight is: " << weight << endl;
};

void Dijsktra_matrix(int matrix[V][V], int Snode, int Tnode)
{
    bool known[V];
    int cost[V];
    int path[V];
    for (int i = 0;i<V;i++)
    {   
        cost[i] = INF;
        known[i] = false;
        if (i == Snode)
        {
            cost[i] = 0;
            path[i] = -1;
            known[i] = true;
        }
    }
    int key = Snode;
    for (int i = 0; i<V; i++)
    {   
        int min = INF;
        int minKey;
        for (int j = 0; j<V;j++)
        {   
            if (known[j] == false)
            {
                if (matrix[key][j] == 0)
                    continue;
                else if (matrix[key][j] < cost[j])
                {
                    cost[j] = matrix[key][j];
                    path[j] = key;
                } 
                if (min > matrix[key][j])
                   minKey = j;
            }
        }
        known[minKey] = true;
        key = minKey;
    }
    
    cout << "The path from "<<Snode << " to " << Tnode << endl;
    int pathKey = Tnode;
    int weight = 0;
    while (pathKey != -1)
    {
        cout << pathKey << " ";
        weight = weight + cost[pathKey];
        pathKey = path[pathKey];
    }
    cout << endl << "The weight is: " << weight << endl;
};

int main()
{
  srand(time(NULL));
  map <int,int> adjacency[V];
  int matrix[V][V];
  int randInt;
  for (int i = 0; i< V;i++)
  {
      for (int j = 0; j<i; j++)
      {
          if (j == i)
          {
              matrix[i][j] = 0;
          }
          else  
          {
              randInt = rand() % 3;
              if (randInt == 0)
              {
                 matrix[i][j] = INF;
                 matrix[j][i] = INF;
              }
              else
              {
                adjacency[i][j] = randInt;
                adjacency[j][i] = randInt;
                matrix[i][j] = randInt;
                matrix[j][i] = randInt;
              }
          }
      }
  }
  int s = rand() % V;
  int t = rand() % V;
  
  
  cout << "Matrix" << endl;
  auto start = high_resolution_clock::now();
  Dijsktra_matrix(matrix,s,t);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);
  cout << "Time is " << duration.count() << endl;
  
  cout << endl << "Adjacency List" << endl;
  start = high_resolution_clock::now();
  Dijsktra_adjacency(adjacency,s,t);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop-start);
  cout << "Time is " << duration.count() << endl;
  
  return 0;
}











