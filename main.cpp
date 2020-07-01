#include "importCSV.h"
#include "clustering.h"
#include <iostream>
#include <fstream>

int main()
{
	int k;
	std::cout<<"Insert the number of clusters. It must be greater than 1: ";
	std::cin>>k;
	if(k<=1)
	{
		std::cout<<"The number of clusters must be greater than 1!"<<std::endl;
		exit (1);
	}

	std::string filePath;
	std::cout<<"Insert the name of the input file: ";
	std::cin>>filePath;

	double d1=0.02;
	double d2=100;

	std::vector<sample*> s=buildSamplesFromCSV(filePath);

	for(int i=0;i<s.size();i++)
	{
		// s[i].buildExpressedSet(d1);
		s[i]->buildExpressedSet2(d2);
	}

	std::vector<cluster> c=NJclustering(s,k);

	// Stampa dei cluster su console e su file (quanti cluster ci sono e samples presenti in ogni cluster)
	std::ofstream outFile;
	outFile.open("output.txt");

	if(!outFile)
	{
		std::cout<<"Non è possibile aprire il file in scrittura"<<std::endl;
		exit(1);
	}

	std::cout<<std::endl<<"Number of clusters: "<<c.size()<<std::endl;
	outFile<<"Number of clusters: "<<c.size()<<std::endl;

	for(int i=0;i<c.size();i++)
	{
		std::cout<<i<<"      "<<c[i].string()<<std::endl;
		outFile<<i<<"      "<<c[i].string()<<std::endl;
	}

	std::cout<<std::endl<<"The results are stored in the file output.txt"<<std::endl;

	outFile.close();

	for(int i=0;i<s.size();i++)
	{
		delete s[i];
		s[i]=nullptr;
	}

	return 0;
}
