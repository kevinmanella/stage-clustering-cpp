#ifndef CLUSTER_H
#define CLUSTER_H

#include "scs.h"

/**
	@file cluster.h

	@brief Dichiarazione della classe cluster, dei suoi metodi e di 1 funzione globale
**/

/**
	@brief cluster

	Classe che rappresenta un cluster (contiene un vector di samples, un vector di indici interi e altre informazioni)
**/
class cluster
{
private:
	std::string id;
	std::vector<sample*> elements;
	std::vector<int> indices;
	std::map<int,std::vector<double>> rhn;
	double tm;
	double intraSim;
	std::multimap<double,int> intraScore;
	std::set<std::string> splittedWith;

public:
	// Metodi get

	/**
		@brief Metodo getId

		Metodo che ritorna l'ID del cluster

		@return ID del cluster
	**/
	std::string getId() const;

	/**
		@brief Metodo getElements

		Metodo che ritorna gli elements del cluster

		@return Elements del cluster
	**/
	const std::vector<sample*>& getElements() const;

	/**
		@brief Metodo getIndices

		Metodo che ritorna gli indici del cluster

		@return Indici del cluster
	**/
	const std::vector<int>& getIndices() const;

	/**
		@brief Metodo getRhn

		Metodo che ritorna l'RHN del cluster

		@return RHN del cluster
	**/
	const std::map<int,std::vector<double>>& getRhn() const;

	/**
		@brief Metodo getTm

		Metodo che ritorna il TM del cluster

		@return TM del cluster
	**/
	double getTm() const;

	/**
		@brief Metodo getIntraSim

		Metodo che ritorna l'IntraSim del cluster

		@return IntraSim del cluster
	**/
	double getIntraSim() const;

	/**
		@brief Metodo getIntraScore

		Metodo che ritorna l'IntraScore del cluster

		@return IntraScore del cluster
	**/
	const std::multimap<double,int>& getIntraScore() const;

	/**
		@brief Metodo getSplittedWith

		Metodo che ritorna lo SplittedWith del cluster

		@return SplittedWith del cluster
	**/
	const std::set<std::string>& getSplittedWith() const;

	// Metodi set

	/**
		@brief Metodo setId

		Metodo che setta l'ID del cluster

		@param id ID del cluster da settare
	**/
	void setId(std::string &id);

	/**
		@brief Metodo setElements

		Metodo che setta gli elements del cluster

		@param elements Elements del cluster da settare
	**/
	void setElements(std::vector<sample*> &elements);

	/**
		@brief Metodo setIndices

		Metodo che setta gli indici del cluster

		@param indices Indici del cluster da settare
	**/
	void setIndices(std::vector<int> &indices);

	/**
		@brief Metodo setRhn

		Metodo che setta l'RHN del cluster

		@param rhn RHN del cluster da settare
	**/
	void setRhn(std::map<int,std::vector<double>> &rhn);

	/**
		@brief Metodo setTm

		Metodo che setta il TM del cluster

		@param tm TM del cluster da settare
	**/
	void setTm(double &tm);

	/**
		@brief Metodo setIntraSim

		Metodo che setta l'IntraSim del cluster

		@param intraSim IntraSim del cluster da settare
	**/
	void setIntraSim(double &intraSim);

	/**
		@brief Metodo setIntraScore

		Metodo che setta l'IntraScore del cluster

		@param intraScore IntraScore del cluster da settare
	**/
	void setIntraScore(std::multimap<double,int> &intraScore);

	/**
		@brief Metodo setSplittedWith

		Metodo che setta lo SplittedWith del cluster

		@param splittedWith SplittedWith del cluster da settare
	**/
	void setSplittedWith(std::set<std::string> &splittedWith);

	// Metodi per inserire i dati

	/**
		@brief Metodo insertDataIntoElements

		Metodo che inserisce il sample element negli elements del cluster

		@param element Sample da inserire negli elements del cluster
	**/
	void insertDataIntoElements(sample* element);

	/**
		@brief Metodo insertDataIntoIndices

		Metodo che inserisce index negli indici del cluster

		@param index Indice da inserire negli indici del cluster
	**/
	void insertDataIntoIndices(int &index);

	/**
		@brief Metodo insertDataIntoRhn

		Metodo che inserisce la coppia <i,d> nell'RHN del cluster

		@param i Valore intero
		@param d Vector di double
	**/
	void insertDataIntoRhn(int &i,std::vector<double> &d);

	/**
		@brief Metodo insertDataIntoIntraScore

		Metodo che inserisce la coppia <d,i> nell'IntraScore del cluster

		@param d Valore double
		@param i Valore intero
	**/
	void insertDataIntoIntraScore(double &d,int &i);

	/**
		@brief Metodo insertDataIntoSplittedWith

		Metodo che inserisce s nello SplittedWith del cluster

		@param s Stringa da inserire nello SplittedWith del cluster
	**/
	void insertDataIntoSplittedWith(std::string &s);

	// Altri metodi

	/**
		@brief Metodo string

		Metodo che ritorna una stringa formata concatenando i nomi dei samples presenti nel cluster.
		La stringa inizia e termina con il carattere " e i nomi dei samples sono separati dal carattere ,

		@return Stringa formata come spiegato sopra
	**/
	std::string string() const;

	/**
		@brief Metodo len

		Metodo che ritorna il numero di elements presenti nel cluster

		@return Numero di elements presenti nel cluster
	**/
	int len() const;
};	// Fine classe cluster

// Funzioni globali

/**
	@brief Operatore di stream per la classe cluster

	Stampa il cluster

	@param os Stream di output
	@param c Cluster da stampare

	@return Riferimento allo stream di output
**/
std::ostream& operator<<(std::ostream &os, const cluster &c);

#endif
