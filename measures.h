#ifndef MEASURES_H
#define MEASURES_H

#include "cluster.h"

/**
	@file measures.h

	@brief Dichiarazione della classe retScore, dei suoi metodi, di 2 typedef e di 11 funzioni globali
**/

/**
	@brief retScore

	Classe retScore
**/
class retScore
{
private:
	int i;
	int j;
	double score;

public:
	// Metodi get

	/**
		@brief Metodo getI

		Metodo che ritorna l'attributo i di retScore

		@return i di retScore
	**/
	int getI() const;

	/**
		@brief Metodo getJ

		Metodo che ritorna l'attributo j di retScore

		@return j di retScore
	**/
	int getJ() const;

	/**
		@brief Metodo getScore

		Metodo che ritorna l'attributo score di retScore

		@return score di retScore
	**/
	double getScore() const;

	// Metodi set

	/**
		@brief Metodo setI

		Metodo che setta l'attributo i di retScore

		@param i i del retScore da settare
	**/
	void setI(int &i);

	/**
		@brief Metodo setJ

		Metodo che setta l'attributo j di retScore

		@param j j del retScore da settare
	**/
	void setJ(int &j);

	/**
		@brief Metodo setScore

		Metodo che setta l'attributo score di retScore

		@param score score del retScore da settare
	**/
	void setScore(double &score);

	// Altri metodi

	/**
		@brief Metodo string

		Metodo che ritorna una stringa formata concatenando gli attributi di retScore nel seguente modo --> (i, j) score

		@return Stringa formata come spiegato sopra
	**/
	std::string string() const;
};	// Fine classe retScore

// Typedef di puntatori a funzione

/**
	@brief similarityFunction

	Puntatore a funzione che ha 2 vector di double e 2 interi come parametri e che ritorna un puntatore a retScore
**/
typedef retScore* (*similarityFunction) (std::vector<double> &x,std::vector<double> &y,int &xi,int &yi);

/**
	@brief clusterSimilarityFunction

	Puntatore a funzione che ha 2 puntatori a cluster e 2 interi come parametri e che ritorna un puntatore a retScore
**/
typedef retScore* (*clusterSimilarityFunction) (cluster* c1,cluster* c2,int &ci,int &cj);

// Funzioni globali

/**
	@brief Funzione cosineSimilarity

	È compatibile con similarityFunction
	https://en.wikipedia.org/wiki/Cosine_similarity

	@param x Vector di double
	@param y Vector di double
	@param xi Valore intero
	@param yi Valore intero

	@return Puntatore a retScore
**/
retScore* cosineSimilarity(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi);

/**
	@brief Funzione euclideanSimilarity

	È compatibile con similarityFunction
	https://en.wikipedia.org/wiki/Euclidean_distance

	@param x Vector di double
	@param y Vector di double
	@param xi Valore intero
	@param yi Valore intero

	@return Puntatore a retScore
**/
retScore* euclideanSimilarity(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi);

/**
	@brief Funzione minkowskiSimilarity

	È compatibile con similarityFunction
	https://en.wikipedia.org/wiki/Minkowski_distance

	@param x Vector di double
	@param y Vector di double
	@param xi Valore intero
	@param yi Valore intero

	@return Puntatore a retScore
**/
retScore* minkowskiSimilarity(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi);

/**
	@brief Funzione geneExpressed

	È compatibile con similarityFunction

	@param x Vector di double
	@param y Vector di double
	@param xi Valore intero
	@param yi Valore intero

	@return Puntatore a retScore
**/
retScore* geneExpressed(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi);

/**
	@brief Funzione avgCosine

	È compatibile con clusterSimilarityFunction

	@param c1 Puntatore a cluster
	@param c2 Puntatore a cluster
	@param ci Valore intero
	@param cj Valore intero

	@return Puntatore a retScore
**/
retScore* avgCosine(cluster* c1,cluster* c2,int &ci,int &cj);

/**
	@brief Funzione avgGenes

	È compatibile con clusterSimilarityFunction

	@param c1 Puntatore a cluster
	@param c2 Puntatore a cluster
	@param ci Valore intero
	@param cj Valore intero

	@return Puntatore a retScore
**/
retScore* avgGenes(cluster* c1,cluster* c2,int &ci,int &cj);

/**
	@brief Funzione intraSimilarity

	intraSimilarity

	@param c Puntatore a cluster
	@param sim Funzione di similarità

	@return IntraSim e IntraScore del cluster
**/
std::tuple<double,std::multimap<double,int>> intraSimilarity(cluster* c,similarityFunction sim);

/**
	@brief Funzione intraDistance

	intraDistance

	@param c Puntatore a cluster

	@return IntraSim e IntraScore del cluster
**/
std::tuple<double,std::multimap<double,int>> intraDistance(cluster* c);

/**
	@brief Funzione newCluster

	Crea un nuovo cluster

	@param cells Vector di samples
	@param indices Vector di interi (indici dei samples da inserire nel cluster)

	@return Puntatore a cluster
**/
cluster* newCluster(std::vector<sample> &cells,std::vector<int> &indices);

/**
	@brief Funzione splitCluster

	Splitta un cluster in due nuovi cluster

	@param c Puntatore a cluster
	@param cells Vector di samples
	@param ix Vector di interi (indici dei samples da inserire nel primo cluster "figlio")
	@param jx Vector di interi (indice dei samples da inserire nel secondo cluster "figlio")

	@return 2 puntatori a cluster
**/
std::tuple<cluster*,cluster*> splitCluster(cluster* c,std::vector<sample> &cells,std::vector<int> &ix,std::vector<int> &jx);

/**
	@brief Funzione fuseCluster

	Fonde due cluster in un nuovo cluster

	@param c1 Puntatore a cluster
	@param c2 Puntatore a cluster
	@param cells Vector di samples
	@param rhn Mappa <int,vector<double>> (RHN del nuovo cluster)
	@param tm Valore double (TM del nuovo cluster)

	@return Puntatore a cluster
**/
cluster* fuseCluster(cluster* c1,cluster* c2,std::vector<sample> &cells,std::map<int,std::vector<double>> &rhn,double &tm);

#endif
