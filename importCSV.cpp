#include "importCSV.h"
#include <fstream>
#include <iostream>
#include <sstream>

/**
	@file importCSV.cpp

	@brief Definizione delle 2 funzioni che leggono i dati da un file CSV
**/

/**
	@brief Funzione buildSamplesFromCSV

	Funzione che, dato il percorso di un file CSV, restituisce un vector di samples, creato leggendo i dati presenti nel file

	@param filePath Stringa contenente il percorso del file

	@return Vector di samples
**/
std::vector<sample> buildSamplesFromCSV(std::string &filePath)
{
	std::ifstream inFile;
	inFile.open(filePath);

	// Gestione degli errori per il file
	if(!inFile)
	{
		std::cout<<"Non è possibile aprire il file in lettura"<<std::endl;
		exit(1);
	}

	// Lettura della prima riga del file
	std::string firstLine;
	inFile>>firstLine;
	std::istringstream ss(firstLine);
	std::string token;
	std::vector<std::string> cellNames;	// Conterrà i nomi dei samples

	while(std::getline(ss,token,','))
		cellNames.push_back(token);	// Inserisco i nomi dei samples

	cellNames.erase(cellNames.begin());	// Cancello "GENES", in quanto è intestazione del file e non il nome di un sample vero e proprio

	const int size=cellNames.size();	// Rappresenta il numero di samples che vi sono nel file
	
	std::vector<sample> samples;
	sample s;

	for(int i=0;i<size;i++)
	{
		s.setId(i);
		s.setName(cellNames[i]);
		samples.push_back(s);	// Inserisco i vari samples nel vector samples
	}

	// Lettura di tutte le altre righe del file
	std::string line;

	while(inFile>>line)
	{
		std::istringstream ss2(line);
		
		std::vector<std::string> lineVector;	// Conterrà di volta in volta le varie righe del file

		while(std::getline(ss2,token,','))
			lineVector.push_back(token);	// Inserisco i RPKM

		std::string geneName=lineVector[0];	// All'inizio di ogni riga c'è il nome del gene, lo salvo
		lineVector.erase(lineVector.begin());	// Cancello il nome del gene, in quanto è intestazione del file e non un RPKM

		// Salvo i RPKM in genesExpression e inserisco i dati in mapExpression
		for(int i=0;i<size;i++)
		{
			double val=std::stod(lineVector[i]);
			samples[i].insertDataIntoMapExpression(geneName,val);
			samples[i].insertDataIntoGenesExpression(val);
		}
	}

	inFile.close();
	return samples;
}

/**
	@brief Funzione buildNameToIndexFromCSV

	Funzione che, dato il percorso di un file CSV, restituisce una map che ha come chiave il nome del sample e come valore l'ID del sample

	@param filePath Stringa contenente il percorso del file

	@return Map che ha come chiave il nome del sample e come valore l'ID del sample
**/
std::map<std::string,int> buildNameToIndexFromCSV(std::string &filePath)
{
	std::ifstream inFile;
	inFile.open(filePath);

	// Gestione degli errori per il file
	if(!inFile)
	{
		std::cout<<"Non è possibile aprire il file in lettura"<<std::endl;
		exit(1);
	}

	// Lettura della prima riga del file
	std::string firstLine;
	inFile>>firstLine;
	std::istringstream ss(firstLine);
	std::string token;
	std::vector<std::string> cellNames;	// Conterrà i nomi dei samples

	while(std::getline(ss,token,','))
		cellNames.push_back(token);	// Inserisco i nomi dei samples

	cellNames.erase(cellNames.begin());	// Cancello "GENES", in quanto è intestazione del file e non il nome di un sample vero e proprio

	std::map<std::string,int> nameToIndex;

	for(int i=0;i<cellNames.size();i++)
		nameToIndex[cellNames[i]]=i;

	inFile.close();
	return nameToIndex;
}
