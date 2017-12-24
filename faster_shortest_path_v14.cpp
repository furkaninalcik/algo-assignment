#include <stdio.h>
//#include <limits.h>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <time.h>
#include <ctime>
//#include<bits/stdc++.h>

# define BIGnumber 0x3f333333 // representing the infinity
using namespace std;
 
typedef pair<int, int> intPair; // integer pair
 

class Graph
{ 
public:
    int num_of_vertices;    
 
    list< intPair > *adjList;
 

    Graph(int num_of_vertices);  
 
    void findShortestPaths(int s , vector<int>& distVector);

    void createEdge(int u, int v, int w);
 
};
 
Graph::Graph(int num_of_vertices)
{
    this->num_of_vertices = num_of_vertices;
    adjList = new list<intPair> [num_of_vertices];

}
 
void Graph::createEdge(int v1, int v2, int w)
{
    adjList[v1].push_back(make_pair(v2, w));
    adjList[v2].push_back(make_pair(v1, w));
}
 
void Graph::findShortestPaths(int source, vector<int>& distVector )
{

    set< intPair > dijkSet;
 


    dijkSet.insert(make_pair(0, source));

    distVector[source] = 0;
 
    
    int u,v,w;
    intPair temp;     

    while (!dijkSet.empty())
    {

        temp = *(dijkSet.begin());
        dijkSet.erase(dijkSet.begin());

        u = temp.second;
 
        list< intPair >::iterator i;
        for (i = adjList[u].begin(); i != adjList[u].end(); ++i)
        {
            v = (*i).first;
            w = (*i).second;
 
            if (distVector[v] > distVector[u] + w)
            {
                if (distVector[v] != BIGnumber)
                    dijkSet.erase(dijkSet.find(make_pair(distVector[v], v)));

                distVector[v] = distVector[u] + w;

                dijkSet.insert(make_pair(distVector[v], v));
                
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
    b[0] = t[0];
    b[1] = t[1];
    
}
 

int part (int** (arr), int l, int h)
{
    int* p = arr[h];   
    
    int i = (l - 1);  
 

    for (int j = l; j <= h- 1; j++)
    {

        if (makePositive(arr[j][0]) <= makePositive(p[0]))
        {
            i++;    
            swap(arr[i], arr[j]);
            
        }
    }
    swap(arr[i + 1], arr[h]);
    return (i + 1);
}
 

void quickS(int** (arr), int l, int h)
{
    if (l < h)
    {

        int p_1 = part(arr, l, h);
 

        quickS(arr, l, p_1 - 1);
        quickS(arr, p_1 + 1, h);
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

  Graph myG(num_cities);




  input >> num_dest;

  int* destArr;
  destArr = new int[num_dest];

  int count = 3;
  int graph_index_1 = 0;
  int graph_index_2 = 0;

  int offset = 0;

  int middle_check = 0;
  int end_of_line = 0;
  int tg = 0;

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

      printf(" %d", a );
      if(a){
        myG.createEdge(graph_index_1, graph_index_2, a );
      }

      graph_index_2++;

      if (graph_index_2 == middle_check)
      {
        int middle_line_tellg = input.tellg();
        offset = middle_line_tellg - end_of_line;
        printf(" -- offset =  %d -- " , offset );
      }



      if (graph_index_2 == num_cities)
      {

        graph_index_1++;
        //graph_index_2 = 0;
        graph_index_2 = 0;

        middle_check = graph_index_1 ;

        end_of_line = input.tellg();
        printf( " tellg %d " ,end_of_line);

        printf("\n");
        
        //offset++;
        input.seekg(end_of_line+offset);

      }
      count++;
    }

    //printf("%d \n", a);
  }

 
    duration1 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"Time to read the input: "<< duration1 <<'\n'; 



    int** diff;
    diff = new int*[num_dest];
    for (int i = 0; i < num_dest; ++i)
    {
      diff[i] = new int[3];
    }

    vector<int> dist1(num_cities, BIGnumber); //shortest paths from wh1
    vector<int> dist2(num_cities, BIGnumber); //shortest paths from wh2


    myG.findShortestPaths(wh1,dist1);
    myG.findShortestPaths(wh2,dist2);

    //list< intPair >::iterator i;


    //----TEST----------

   
    duration2 = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"Time to find the shortest paths: "<< duration2 <<'\n'; 
    

    


    for (int i = 0; i < num_dest; ++i)
    {
      diff[i][0] = dist1[destArr[i]] - dist2[destArr[i]];
      diff[i][1] = destArr[i];
      diff[i][2] = i;
    }
     quickS(diff,0,num_dest-1);
      



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

   std::cout<<"Time to prepare arrays and print: "<< duration3 <<'\n';

    return 0;
}