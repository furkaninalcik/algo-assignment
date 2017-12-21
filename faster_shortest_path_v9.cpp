#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include<stdio.h>
#include <fstream>
#include <iostream>
#include<bits/stdc++.h>

# define INF 0x3f3f3f3f
using namespace std;
 
typedef pair<int, int> iPair;
 

class Graph
{
public:
    int V;    
 
    list< pair<int, int> > *adj;
 

    Graph(int V);  
 
    void addEdge(int u, int v, int w);
 
    void shortestPath(int s , vector<int>& dist);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}
 
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
 
void Graph::shortestPath(int src, vector<int>& dist )
{

    set< pair<int, int> > setds;
 


    setds.insert(make_pair(0, src));

    dist[src] = 0;
 

    while (!setds.empty())
    {

        pair<int, int> tmp = *(setds.begin());
        setds.erase(setds.begin());

        int u = tmp.second;
 
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
 
            if (dist[v] > dist[u] + weight)
            {
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));

                dist[v] = dist[u] + weight;

                setds.insert(make_pair(dist[v], v));
                
            }
        }
    }
 
   
  
}

int makePositive(int number){
  number = number < 0 ? 0-number : number; 
  return number;
}

void swap(int (&a)[2], int (&b)[2])
{

    int t[2] = {a[0],a[1]};
    a[0] = b[0];
    a[1] = b[1];
    //*(a+1) = *(b+1);
    b[0] = t[0];
    b[1] = t[1];
    
    //b = t;
    //*(b+1) = *(t+1);
    
}
 

int partition (int** (arr), int low, int high)
{
    int* pivot = arr[high];   
    
    int i = (low - 1);  
 

    for (int j = low; j <= high- 1; j++)
    {

        if (makePositive(arr[j][0]) <= makePositive(pivot[0]))
        {
            i++;    
            swap(arr[i], arr[j]);
            
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
 

void quickSort(int** (arr), int low, int high)
{
    if (low < high)
    {

        int pi = partition(arr, low, high);
 

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}







int main(int argc, char *argv[])
{
  
/*
----------------------

ALGORITHM:
we need to create a sorted array containing dist(w1,d_k) - dist(w2,d_k) values for every k,
then we will begin assignments from the biggest element of the array 
whose choice will make the biggest minimization in total distance 

----------------------
*/



  
  //printf("%s\n", argv[1] );

  //***********TIME**********
  std::clock_t start;
  double duration1, duration2, duration3;

  start = std::clock();
  //***********TIME**********

  ifstream input(argv[1]);
  //std::fstream input("input.txt", std::ios_base::in);

  int a;

  int num_cities;
  int num_dest;
  int wh1;
  int wh2; // warehouses
  

  

  input >> num_cities;

  //int myGraph[num_cities][num_cities];

  Graph g(num_cities);


  int** myGraph;
  myGraph = new int*[num_cities];
  for (int i = 0; i < num_cities; ++i)
  {
    myGraph[i] = new int[num_cities];
  }


  input >> num_dest;

  int* destArr;
  destArr = new int[num_dest];

  int count = 3;
  int graph_index_1 = 0;
  int graph_index_2 = 0;

  while(input >> a){
    if (count == 3 )
    {
      wh1 = a;
      count++;
    }
    else if (count == 4 )
    {
      wh2 = a;
      count++;
    }
    else if (count <= num_dest+4)
    {
      destArr[count-5] = a;
      count++;
    } else if (count > num_dest+4)
    {
      //myGraph[graph_index_1][graph_index_2] = a;
      if(a)
        g.addEdge(graph_index_1, graph_index_2, a );

      graph_index_2++;
      if (graph_index_2 == num_cities)
      {
        graph_index_1++;
        graph_index_2 = 0;
      }
    }

    //printf("%d \n", a);
  }

 
    duration1 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    //std::cout<<"Time to read the input: "<< duration1 <<'\n'; 



    int** diff;
    diff = new int*[num_dest];
    for (int i = 0; i < num_dest; ++i)
    {
      diff[i] = new int[3];
    }

    vector<int> dist1(num_cities, INF);
    vector<int> dist2(num_cities, INF);


    g.shortestPath(wh1,dist1);
    g.shortestPath(wh2,dist2);

    //list< pair<int, int> >::iterator i;


    //----TEST----------

   
    duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    //std::cout<<"Time to find the shortest paths: "<< duration2 <<'\n'; 
    

    


    for (int i = 0; i < num_dest; ++i)
    {
      diff[i][0] = dist1[destArr[i]] - dist2[destArr[i]];
      diff[i][1] = destArr[i];
      diff[i][2] = i;
    }
     quickSort(diff,0,num_dest-1);
      



    int middle = num_dest/2; // to devide the destinations equally for two warehouses num_dest/2
    int w1_counter = 0;
    int w2_counter = 0;
    bool all_to_w1 = false;
    bool all_to_w2 = false;


    int** result;
    result = new int*[num_dest];
    for (int i = 0; i < num_dest; ++i)
    {
      result[i] = new int[2];
    }

    int total = 0;




    for (int i = num_dest-1; i >= 0; --i)
      {
        if (w1_counter == middle)
        {
          all_to_w2 = true;
        }

        if (w2_counter == middle)
        {
          all_to_w1 = true;
        }
        
        if ( all_to_w1 || (diff[i][0] <= 0 && !all_to_w2))
        {
          //printf("%d %d\n", *(diff[i]+1) ,  wh1);
          result[diff[i][2]][0] = diff[i][1];
          result[diff[i][2]][1] = wh1;
          total += dist1[result[diff[i][2]][0]];

          if(!all_to_w1)
            w1_counter++;
        }
        if(all_to_w2 || (diff[i][0] > 0 &&  !all_to_w1)){
          //printf("%d %d\n", *(diff[i]+1) , wh2);
          result[diff[i][2]][0] = (diff[i][1]);
          result[diff[i][2]][1] = wh2;
          total += dist2[result[diff[i][2]][0]];

          if(!all_to_w2)
            w2_counter++;

        }
      }  

    
    printf("%d \n" , total);


    //ofstream myfile;
    //myfile.open ("output.txt");

    //myfile << "TOTAL: " << total <<  "\n";


    //quickSort(result,0,num_dest-1);

       for (int i = 0; i < num_dest; ++i)
      {

        printf("%d %d \n", (result[i][0]) , (result[i][1])  );
        //myfile << *((result[i])) << " " << *((result[i])+1)  << "\n";
      }

    //myfile.close();

   
   duration3 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    //std::cout<<"Time to prepare arrays and print: "<< duration3 <<'\n';

    return 0;
}