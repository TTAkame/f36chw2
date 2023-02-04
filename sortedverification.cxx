#include<iostream>
#include<stdlib.h>
#include "json.hpp"
#include<vector>
#include<string>
#include<fstream>

using json = nlohmann::json;


int main(int argc, char** argv) {

	std::ifstream file(argv[1]);//open json as file
	nlohmann::json data = nlohmann::json::parse(file);//parse file 

//std::cout << data << std::endl<<std::endl;

	int i,a,b,count=0,tinverse = 0;//iteration and flags
	json outpt;//json for os
	
	
	
	std::string sz = data["metadata"]["arraySize"].dump();//string for arraysize

	std::string ns = data["metadata"]["numSamples"].dump();//string for numsamples
	
	
	for (auto it = data.begin(); it != std::prev(data.end(),1) ; ++it){//iterate through json object

	std::vector<int> spl = it.value().get<std::vector<int>>();//copy value to vector

	for (i=0;i<static_cast<int>(spl.size())-1;i++){//iterate through vector
	
		a = spl[i];//take 1 to temp
		b = spl[i+1];//take 2 to temp
	
//std::cout<<it.key()<<std::endl;

		if(a>b){//compare 1 and 2
			count ++;//flag raise
			outpt[it.key()]["ConsecutiveInversions"][std::to_string(i)]={a,b};//print to json for failed consecutive
//std::cout<<a<<std::endl<<b;
			
		a = 0;//empty temp
		b = 0;//empty temp
		
		
		}
	}
	if(count!=0){//if flag raise
			outpt[it.key()]["sample"]=it.value();//print to output json
		tinverse +=1;//count for inverse
	}
	count = 0;//empty flag
}
	
	outpt["metadata"]["arraySize"]=data["metadata"]["arraySize"];//print to json
	outpt["metadata"]["file"] = "SampleExample.json";//print to json
	outpt["metadata"]["numSamples"]=data["metadata"]["numSamples"];//print to json
	outpt["metadata"]["samplesWithInversions"]=tinverse;//print to json
	
	
	std::cout<< outpt <<std::endl;//print output
	
	return 1;


}
