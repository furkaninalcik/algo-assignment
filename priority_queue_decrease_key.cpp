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


int main(int argc, char const *argv[])
{

	int item = 5;
	int item1 = 7;
	int item2 = 1;
	int item3 = 19;

	std::vector<int> vec;
	vec.push_back(item);
	vec.push_back(item1);
	vec.push_back(item2);
	vec.push_back(item3);
	
	//std::push_heap(vec.begin(), vec.end());

	std::make_heap(vec.begin(), vec.end());

	//int a = vec.front();



	std::pop_heap(vec.begin(), vec.end());
	vec.pop_back();
	vec.pop_back();
	

	std::make_heap(vec.begin(), vec.end());
	for (int i = 0; i < 4; ++i)
	{
		printf("%d \n", vec[i] );
	}

	return 0;
}