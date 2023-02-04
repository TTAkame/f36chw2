#include<iostream>
#include<stdlib.h>
#include "json.hpp"
#include<vector>
#include<string>
#include<fstream>

int main(int argc, char** argv) {

	std::ifstream file1(argv[1]);
	std::ifstream file2(argv[2]);
	int i,j;
	std::vector<std::string> v1,v2;
	nlohmann::json oupt;
	
//	vector<int> iv1,iv2;
	
	nlohmann::json data1 = nlohmann::json::parse(file1);
	nlohmann::json data2 = nlohmann::json::parse(file2);

	std::string s = data1["metadata"]["arraySize"].dump();

	std::string n = data1["metadata"]["numSamples"].dump();

	int sz=stoi(s);
	int ns=stoi(n);
	int count = 0,c=0;
	

	for(auto it = data1.begin();it != std::prev(data1.end());++it){
		v1.push_back(it.key());
	}
	for(auto it = data2.begin();it != std::prev(data2.end());++it){
		v2.push_back(it.key());
	}
	for(i=0;i<ns;i++){
		for(j=0;j<sz;j++){
			oupt[v1.at(i)][argv[1]]=data1[v1.at(i)];
			oupt[v2.at(i)][argv[2]]=data2[v2.at(i)];

			if(data1[v1.at(i)][j]!=data2[v2.at(i)][j]){
				oupt[v2.at(i)]["Mismatches"][std::to_string(j)]={data1[v1.at(i)][j],data2[v2.at(i)][j]};
				count++;
			}	
		}
		if(count!=0){
			c++;
			count=0;
		}
	}
	oupt["metadata"]["File1"]["arraySize"]=data1["metadata"]["arraySize"];
	oupt["metadata"]["File1"]["numSamples"]=data1["metadata"]["numSamples"];
	oupt["metadata"]["File1"]["name"]=argv[1];


	oupt["metadata"]["File2"]["arraySize"]=data2["metadata"]["arraySize"];
	oupt["metadata"]["File2"]["numSamples"]=data2["metadata"]["numSamples"];
	oupt["metadata"]["File2"]["name"]=argv[2];
	
	oupt["metadata"]["samplesWithConflictingResults"]=c;
	
	
	
	
	std::cout<<oupt<<std::endl;

}
