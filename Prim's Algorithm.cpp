#include <iostream>
#include <map>
#include <chrono>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace chrono;

//PRIM'S Algorithm
const int INF = 99999;
const int V = 64;
void print(int cost[],int path[])
{
    for (int i = 1; i < V; i++)
    {
        if (cost[i] != INF)
        {
            cout<<"Path:" <<path[i]
             <<  " - " << i << " = Weight: "
             << cost[i] << endl;
        }
    }
}

void prim_matrix(int matrix[V][V])
{
    bool known[V];
    int cost[V];
    int path[V];
    for (int i = 0;i<V;i++)
    {   
        cost[i] = INF;
        known[i] = false;
        if (i == 0)
        {
            cost[i] = 0;
            path[i] = -1;
            known[i] = true;
        }
    }
    int key = 0;
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
    cout << "Matrix:" << endl;
    print(cost,path);
    
    
    return;
};

void prim_adjacency(map<int,int> adjacency[])
{
    bool known[V];
    int cost[V];
    int path[V];
    for (int i = 0;i<V;i++)
    {   
        cost[i] = INF;
        known[i] = false;
        if (i == 0)
        {
            cost[i] = 0;
            path[i] = -1;
            known[i] = true;
        }
    }
    int key = 0;
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
  
  cout << "Adjacency List:" << endl;
  print(cost,path);
  return;  
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
              randInt = rand() % 3 + 1;
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
  
  auto start = high_resolution_clock::now();
  prim_matrix(matrix);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);
  cout << "Time is " << duration.count() << endl;
  
  
  start = high_resolution_clock::now();
  prim_adjacency(adjacency);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop-start);
  cout << "Time is " << duration.count() << endl;
  
  
  return 0;
}








