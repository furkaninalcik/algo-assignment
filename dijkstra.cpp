// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
  
#include <stdio.h>
#include <limits.h>
#include <algorithm>
/* C implementation QuickSort */
#include<stdio.h>
 
// A utility function to swap two elements

int makePositive(int number){
  number = number < 0 ? 0-number : number; 
  return number;
}

void swap(int (&a)[2], int (&b)[2])
{
    printf("SWAPPING\n");

    int t[2] = {a[0],a[1]};
    a[0] = b[0];
    a[1] = b[1];
    //*(a+1) = *(b+1);
    b[0] = t[0];
    b[1] = t[1];
    
    //b = t;
    //*(b+1) = *(t+1);
    printf("a %d %d \n", a[0], a[1]);
    printf("b %d %d \n", b[0], b[1]);
    printf("t %d %d \n", t[0], t[1]);
    
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int (&arr)[4][2], int low, int high)
{
    int* pivot = arr[high];    // pivot
    printf("pivot: %d %d %d \n", high , arr[high][0], arr[high][1] );
    
    int i = (low - 1);  // Index of smaller element
 
    printf("i: %d %d %d \n", i , arr[i][0], arr[i][1] );

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        printf("----> %d %d \n", arr[j][0], pivot[0] );
        if (makePositive(arr[j][0]) <= makePositive(pivot[0]))
        {
            i++;    // increment index of smaller element
            printf("%d %d %d \n", i , arr[i][0], arr[i][1]);
            printf("%d %d %d \n", j , arr[j][0], arr[j][1]);
            swap(arr[i], arr[j]);
            
        }
    }
    printf("indexes %d %d \n", i+1, high);
    swap(arr[i + 1], arr[high]);
    printf("swapped %d %d  \n", arr[i+1][0] , arr[high][0] );
    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int (&arr)[4][2], int low, int high)
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
int minDistance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}
  
// A utility function to print the constructed distance array
int printSolution(int dist[], int n, int dest)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
      printf("%d \t", i);
   printf("\n");
   for (int i = 0; i < V; i++)
      printf("%d \t", dist[i]);
   printf("\n");

}
  
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int dist[V], int src, int dest)
{
     //int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i
  
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
  
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
  
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
  
     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
  
       // Mark the picked vertex as processed
       sptSet[u] = true;
  
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)
  
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
  
     // print the constructed distance array
     printSolution(dist, V, dest);
}
  
// driver program to test above function
int main(char *argv[])
{
   /* Let us create the example graph discussed above */
    /*
   int n; //total number of cities 
   int dest; //total number of destinations
   int index1, index2;//the indexes for two warehouses
   cin >> n;
   cin >> dest;
*/

/*
----------------------

ALGORITHM:
we need to create a sorted array containing dist(w1,d_k) - dist(w2,d_k) values for every k,
then we will begin assignments from the biggest element of the array 
whose choice will make the biggest minimization in total distance 

----------------------
*/
   int graph[V][V] = {{0, 43, 0, 46, 15, 0, 0, 0, 0, 0},
                      {43, 0, 0, 50, 0, 36, 43, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 49, 13, 0},
                      {46, 50, 0, 0, 0, 0, 0, 0, 0, 0},
                      {15, 0, 0, 0, 0, 0, 0, 0, 46, 45},
                      {0, 36, 0, 0, 0, 0, 20, 0, 0, 0},
                      {0, 43, 0, 0, 0, 20, 0, 0, 0, 0},
                      {0, 0, 49, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 13, 0, 46, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 45, 0, 0, 0, 0, 0},
                     };
    int dist1[V]; 
    int dist2[V]; 
    int diff[4][2];

    int destArray[4] = {1,4,6,8};

    int w1 = 5;
    int w2 = 7;

    dijkstra(graph, dist1, w1, 1);
    dijkstra(graph, dist2, w2, 1);
    printf("DIFF:\n");
    for (int i = 0; i < 4; ++i)
    {
      diff[i][0] = dist1[destArray[i]] - dist2[destArray[i]];
      diff[i][1] = destArray[i];
    }
      quickSort(diff,0,3);
      
      for (int i = 0; i < 4; ++i)
      {
        printf("%d \t ", *((diff[i])) );
      }
    printf("\n");


    printf("*****************\n");
    int temp[4][2] = {{-41,1},{23,4},{77,6},{11,8}};
 
    quickSort(temp,0,3);
    for (int i = 0; i < 4; ++i)
      {
        printf("%d %d \t ", *((temp[i])) , *((temp[i])+1)  );
      }

    printf("Warehouse - Destination ASSIGMENTS:\n");
    int middle = 2; // to devide the destinations equally for two warehouses 4/2 = 2
    int w1_counter = 0;
    int w2_counter = 0;
    bool all_to_w1 = false;
    bool all_to_w2 = false;

    int result[4][2] {{-41,1},{23,4},{77,6},{11,8}};;

    for (int i = 3; i >= 0; --i)
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
          printf("%d %d\n", *(diff[i]+1) ,  w1);
          result[i][0] = *(diff[i]+1);
          result[i][1] = w1;
          if(!all_to_w1)
            w1_counter++;
        }
        if(all_to_w2 || (*diff[i] > 0 &&  !all_to_w1)){
          printf("%d %d\n", *(diff[i]+1) , w2);
          result[i][0] = *(diff[i]+1);
          result[i][1] = w2;
          if(!all_to_w2)
            w2_counter++;

        }
      }  

    int total = 0;


    quickSort(result,0,3);
       for (int i = 0; i < 4; ++i)
      {
        if (*((result[i])+1) == w1)
        {
          total += dist1[*(result[i])];
        }
        if (*((result[i])+1) == w2)
        {
          total += dist2[*(result[i])];
        }
        printf("%d %d \n", *((result[i])) , *((result[i])+1)  );
      }
      printf("TOTAL: %d \n" , total);


    return 0;
}