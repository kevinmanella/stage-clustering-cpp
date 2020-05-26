#ifndef IMPORTCSV_H
#define IMPORTCSV_H

#include "scs.h"

/**
	@file importCSV.h

	@brief Dichiarazione delle 2 funzioni che leggono i dati da un file CSV
**/

/**
	@brief Funzione buildSamplesFromCSV

	Funzione che, dato il percorso di un file CSV, restituisce un vector di samples, creato leggendo i dati presenti nel file

	@param filePath Stringa contenente il percorso del file

	@return Vector di samples
**/
std::vector<sample> buildSamplesFromCSV(std::string &filePath);

/**
	@brief Funzione buildNameToIndexFromCSV

	Funzione che, dato il percorso di un file CSV, restituisce una map che ha come chiave il nome del sample e come valore l'ID del sample

	@param filePath Stringa contenente il percorso del file

	@return Map che ha come chiave il nome del sample e come valore l'ID del sample
**/
std::map<std::string,int> buildNameToIndexFromCSV(std::string &filePath);

#endif
