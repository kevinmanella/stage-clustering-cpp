#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "measures.h"
#include "stat.h"

/**
	@file clustering.h

	@brief Dichiarazione della classe stats, dei suoi metodi e di 4 funzioni globali
**/

/**
	@brief stats

	Classe stats
**/
class stats
{
private:
	double tm;
	std::map<int,std::vector<double>> rhn;
public:
	// Metodi get

	/**
		@brief Metodo getTm

		Metodo che ritorna il TM di stats

		@return TM di stats
	**/
	double getTm() const;

	/**
		@brief Metodo getRhn

		Metodo che ritorna l'RHN di stats

		@return RHN di stats
	**/
	const std::map<int,std::vector<double>>& getRhn() const;

	// Metodi set

	/**
		@brief Metodo setTm

		Metodo che setta il TM di stats

		@param tm TM di stats da settare
	**/
	void setTm(double &tm);

	/**
		@brief Metodo setRhn

		Metodo che setta l'RHN di stats

		@param rhn RHN di stats da settare
	**/
	void setRhn(std::map<int,std::vector<double>> &rhn);

	// Metodi per inserire i dati

	/**
		@brief Metodo insertDataIntoRhn

		Metodo che inserisce la coppia <i,d> nell'RHN di stats

		@param i Valore intero
		@param d Vector di double
	**/
	void insertDataIntoRhn(int i,std::vector<double> &d);
};	// Fine classe stats

// Funzioni globali

/**
	@brief Funzione estClustStep

	Stima i primi clusters usando simMeasure come funzione di similarità.
	Ad ogni step un totale di thMaxFuse insiemi vengono fusi con un numero massimo di thClustSize elementi

	@param cells Vector di puntatori a sample
	@param cs Vector di clusters
	@param thClustSize Valore intero
	@param thMaxFuse Valore intero
	@param simMeasure Funzione di similarità

	@return Tupla contenente un vector di clusters e un valore booleano
**/
std::tuple<std::vector<cluster>,bool> estClustStep(std::vector<sample*> &cells,std::vector<cluster> &cs,int &thClustSize,int &thMaxFuse,clusterSimilarityFunction simMeasure);

/**
	@brief Funzione estimateInitialClusters

	Stima i primi clusters richiamando la funzione estClustStep

	@param cells Vector di puntatori a sample

	@return Vector di clusters
**/
std::vector<cluster> estimateInitialClusters(std::vector<sample*> &cells);

/**
	@brief Funzione NJstep

	Effettua l'algoritmo di Neighbour Joining su currentClust

	@param cells Vector di puntatori a sample
	@param currentClust Vector di clusters
	@param memoize Mappa <string,Mappa<string,stats>>

	@return Vector di clusters
**/
std::vector<cluster> NJstep(std::vector<sample*> &cells,std::vector<cluster> &currentClust,std::map<std::string,std::map<std::string,stats>> &memoize);

/**
	@brief Funzione NJclustering

	Effettua un clustering utilizzando la tecnica di Neighbour Joining

	@param cells Vector di puntatori a sample
	@param k Valore intero

	@return Vector di clusters
**/
std::vector<cluster> NJclustering(std::vector<sample*> &cells,int &k);

#endif
