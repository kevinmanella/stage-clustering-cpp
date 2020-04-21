#include "sample.h"
#include "importCSV.h"
#include <iostream>

int main()
{
	// Richiamo di prova a buildSamplesFromCSV
	std::vector <sample> samples=buildSamplesFromCSV("verySmall.csv");

	// Stampa di prova del vector samples che contiene 4 samples
	std::cout<<"STAMPA DI PROVA DEL VECTOR SAMPLES"<<std::endl;
	for(int j=0;j<samples.size();j++)
	{
		std::cout<<samples[j].id<<" "<<samples[j].name<<" map[ ";

		for(std::map<std::string, double>::iterator it=samples[j].mapExpression.begin();
			it!=samples[j].mapExpression.end();it++)
				std::cout<<it->first<<":"<<it->second<<" ";

		std::cout<<"] [ ";

		for(int i=0;i<samples[j].genesExpression.size();i++)
			std::cout<<samples[j].genesExpression[i]<<" ";

		std::cout<<"]"<<std::endl;
	}

	// Richiamo di prova a buildNameToIndexFromCSV
	std::map<std::string, int> nameToIndex=buildNameToIndexFromCSV("verySmall.csv");

	// Stampa di prova di nameToIndex
	std::cout<<std::endl<<"STAMPA DI PROVA DI NAMETOINDEX"<<std::endl<<"[ ";

	for(std::map<std::string, int>::iterator it=nameToIndex.begin();
		it!=nameToIndex.end();it++)
			std::cout<<it->first<<":"<<it->second<<" ";

	std::cout<<"]"<<std::endl;

	return 0;
}
