#include "importCSV.h"
#include "clustering.h"
#include <iostream>
#include <chrono>

int main()
{
	auto start=std::chrono::steady_clock::now();

	std::string filePath="small.csv";
	double d1=0.02;
	double d2=100;
	int k=10;

	std::vector<sample*> s=buildSamplesFromCSV(filePath);

	for(int i=0;i<s.size();i++)
	{
		// s[i].buildExpressedSet(d1);
		s[i]->buildExpressedSet2(d2);
	}

	std::vector<cluster> c=NJclustering(s,k);

	// Stampa dei cluster (quanti cluster ci sono e samples presenti in ogni cluster)
	std::cout<<"Size: "<<c.size()<<std::endl;

	for(std::vector<cluster>::iterator it=c.begin();it!=c.end();it++)
		std::cout<<it->string()<<std::endl;

	for(int i=0;i<s.size();i++)
	{
		delete s[i];
		s[i]=nullptr;
	}

	auto end=std::chrono::steady_clock::now();
	auto diff=end-start;
	std::cout<<std::chrono::duration<double,std::milli> (diff).count()<<" ms"<<std::endl;

	return 0;
}
