#include "insertionsort.h"
#include "mergesort.h"
//#include "QuickSort.h"

#include "mergesort.h"
#include "quicksort.h"
#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>
#include"json.hpp"
#include<ctime>

int main(int argc, char** argv) {

	std::ifstream file(argv[1]);//open json file
	nlohmann::json data = nlohmann::json::parse(file);//parse and read json object


	std::cout<< "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess"<< std::endl;//print first line incsv

	for(auto it = data.begin(); it != std::prev(data.end()); ++it){//iterate through json to read sample
		
		int memaccess = 0;//initial memory access
		int comparison = 0;//initial comparison

		std::vector<int> insort = it.value().get<std::vector<int>>();//read value to vector
		std::cout<<it.key();//print the name of sample

clock_t start = clock();//start clock

		InsertionSort(&insort,memaccess,comparison);//start algorithm

clock_t end = clock();//end clock
double elatime1 = 10000.0*(end - start)/CLOCKS_PER_SEC;//read time
		std::cout<<','<<elatime1<<','<<comparison<<','<<memaccess;//output time and memory access and comparison

		memaccess = 0;//clear temp
		comparison = 0;//clear temp

		std::vector<int> mesort = it.value().get<std::vector<int>>();//initial new vector for sorting

start = clock();//start clock

		MergeSort(&mesort,memaccess,comparison);//run algorithm


end = clock();//end clock
double elatime2=10000.0*(end-start)/CLOCKS_PER_SEC;//read time
	std::cout<<','<<elatime2<<','<<comparison<<','<<memaccess;//output time and memory access and comparison
		

		memaccess=0;//clear temp
		comparison=0;//clear temp
		std::vector<int> qksort = it.value().get<std::vector<int>>();//initial new vector for sorting

start = clock();//start clock

		QuickSort(&qksort,memaccess,comparison);//run algorithm
		
end = clock();//end clock
double elatime3= 10000.0*(end-start)/CLOCKS_PER_SEC;//read time
	std::cout<<','<<elatime3<<','<<comparison<<','<<memaccess<<std::endl;//output time and memory access and comparison


	
}




	return 0;
}
