#include <iostream>
#include <map>
#include <chrono>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace chrono;
//Floyd Marshall Matrix
const int num_Vertices = 128;
const int INF = 99999;
void FloydMarshall_Matrix(int matrix[num_Vertices][num_Vertices], int s, int t)
{
    int path [num_Vertices][num_Vertices];
    for (int i = 0; i<num_Vertices; i++)
    {
        for (int j = 0;j<num_Vertices;j++)
        {
            if (matrix[i][j] == INF)
               path[i][j] = -1;
            else
               path[i][j] = j;
        }
    }
    
    for (int k = 0; k < num_Vertices;k++)
    {
        for (int i = 0; i <num_Vertices;i++)
        {
            for (int j = 0; j <num_Vertices;j++)
            {

                if (matrix[i][k] != INF && matrix[k][j] != INF
                    && matrix[i][j] > matrix[i][k] + matrix[k][j])
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
    
    int source = s;
    cout << "The path from Node S to Node T is:" << endl;
    
    while (source!=t)
    {
        if (path[source][t]==-1)
           break;
        cout << source << " ";
        source = path[source][t];
    }
    cout << source << endl;
    
    if (matrix[s][t] == INF)
        cout <<"There is no path between these nodes" << endl;
    else
        cout << "The weight between the two nodes is " << matrix[s][t] << endl;
    return;
};

void FloydMarshall_Adjacency(map<int,int> adjacency[],int s,int t)
{
    int matrix[num_Vertices][num_Vertices];
    
    for (int i = 0; i<num_Vertices; i++)
    {
        for (int j = 0;j<num_Vertices;j++)
        {
            if (adjacency[i].count(j) == 0)
                matrix[i][j] = INF;
            else 
                matrix[i][j] = adjacency[i].at(j);
            if (i == j)
                matrix[i][j] = 0;
        }
    }
    FloydMarshall_Matrix(matrix,s,t);
    return;
}

int main()
{
  srand(time(NULL));
  int matrix[num_Vertices][num_Vertices];
  map<int,int> adjacency[num_Vertices];
  int randInt;
  for (int i = 0; i< num_Vertices;i++)
  {
      for (int j = 0; j<num_Vertices; j++)
      {
          if (j == i)
          {
              matrix[i][j] = 0;
          }
          else  
          {
              randInt = rand() % 3+1;
              if (randInt == 0)
              {
                 matrix[i][j] = INF;
              }
              else
              {
                adjacency[i][j] = randInt;
                matrix[i][j] = randInt;
              }
          }
      }
  }
  int s = rand() % num_Vertices;
  int t = rand() % num_Vertices;
  
  cout << "Matrix" << endl;
  auto start = high_resolution_clock::now();
  FloydMarshall_Matrix(matrix,s,t);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);
  cout << "Time is " << duration.count() << endl;
  
  cout << endl << "Adjacency List" << endl;
  start = high_resolution_clock::now();
  FloydMarshall_Adjacency(adjacency,s,t);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop-start);
  cout << "Time is " << duration.count() << endl;

  return 0;
}




