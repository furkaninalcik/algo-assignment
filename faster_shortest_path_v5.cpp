#include <stdio.h>
#include <limits.h>
#include <algorithm>
/* C implementation QuickSort */
#include<stdio.h>
#include <fstream>
#include <iostream>
#include<bits/stdc++.h>

# define INF 0x3f3f3f3f
using namespace std;
 
// A utility function to swap two elements
typedef pair<int, int> iPair;
 
// This class represents a directed graph using
// adjacency list representation
class Graph
{
public:
    int V;    // No. of vertices
 
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list< pair<int, int> > *adj;
 

    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int u, int v, int w);
 
    // prints shortest path from s
    void shortestPath(int s , vector<int>& dist);
};
 
// Allocates memory for adjacency list
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
 
// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src, vector<int>& dist )
{
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
 
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    
    //vector<int> dist(V, INF);
 
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;
 
    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();
 
        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;
 
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;

                pq.push(make_pair(dist[v], v));
            }
        }
    }
 
    // Print shortest distances stored in dist[]
    /*printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
    */
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
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int** (arr), int low, int high)
{
    int* pivot = arr[high];    // pivot
    
    int i = (low - 1);  // Index of smaller element
 

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (makePositive(arr[j][0]) <= makePositive(pivot[0]))
        {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
            
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int** (arr), int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}







// Number of vertices in the graph
#define V 10
  
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree

// A utility function to print the constructed distance array
int printSolution(int dist[], int num_cities)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < num_cities; i++)
      printf("%d \t", i);
   printf("\n");
   for (int i = 0; i < num_cities; i++)
      printf("%d \t", dist[i]);
   printf("\n");

}
  
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation

  
// driver program to test above function
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



  
  printf("%s\n", argv[1] );


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

  //***********TIME**********
  std::clock_t start;
  double duration;

  start = std::clock();
  //***********TIME**********

    int** diff;
    diff = new int*[num_dest];
    for (int i = 0; i < num_dest; ++i)
    {
      diff[i] = new int[2];
    }

    vector<int> dist1(num_cities, INF);
    vector<int> dist2(num_cities, INF);


    g.shortestPath(wh1,dist1);
    g.shortestPath(wh2,dist2);

    list< pair<int, int> >::iterator i;


    //----TEST----------

    for (int i = 0; i < num_dest; ++i)
    {
      diff[i][0] = dist1[destArr[i]] - dist2[destArr[i]];
      diff[i][1] = destArr[i];
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
        
        if ( all_to_w1 || (*diff[i] < 0 && !all_to_w2))
        {
          //printf("%d %d\n", *(diff[i]+1) ,  wh1);
          result[i][0] = *(diff[i]+1);
          result[i][1] = wh1;
          if(!all_to_w1)
            w1_counter++;
        }
        if(all_to_w2 || (*diff[i] > 0 &&  !all_to_w1)){
          //printf("%d %d\n", *(diff[i]+1) , wh2);
          result[i][0] = *(diff[i]+1);
          result[i][1] = wh2;
          if(!all_to_w2)
            w2_counter++;

        }
      }  

    int total = 0;


    //ofstream myfile;
    //myfile.open ("output.txt");

    quickSort(result,0,num_dest-1);
       for (int i = 0; i < num_dest; ++i)
      {
        if (*((result[i])+1) == wh1)
        {
          total += dist1[*(result[i])];
        }
        if (*((result[i])+1) == wh2)
        {
          total += dist2[*(result[i])];
        }
        printf("%d %d \n", *((result[i])) , *((result[i])+1)  );
        //myfile << *((result[i])) << " " << *((result[i])+1)  << "\n";
      }
      printf("TOTAL: %d \n" , total);
      //myfile << "TOTAL: " << total <<  "\n";

    //myfile.close();



    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"Time: "<< duration <<'\n'; 

    return 0;
}