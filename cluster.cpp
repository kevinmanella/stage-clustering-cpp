#include "cluster.h"
#include <bits/stdc++.h>

/**
	@file cluster.cpp

	@brief Definizione dei metodi della classe cluster e di 1 funzione globale
**/

// Metodi get

/**
	@brief Metodo getId

	Metodo che ritorna l'ID del cluster

	@return ID del cluster
**/
std::string cluster::getId() const
{
	return id;
}

/**
	@brief Metodo getElements

	Metodo che ritorna gli elements del cluster

	@return Elements del cluster
**/
const std::vector<sample>& cluster::getElements() const
{
	return elements;
}

/**
	@brief Metodo getIndices

	Metodo che ritorna gli indici del cluster

	@return Indici del cluster
**/
const std::vector<int>& cluster::getIndices() const
{
	return indices;
}

/**
	@brief Metodo getRhn

	Metodo che ritorna l'RHN del cluster

	@return RHN del cluster
**/
const std::map<int,std::vector<double>>& cluster::getRhn() const
{
	return rhn;
}

/**
	@brief Metodo getTm

	Metodo che ritorna il TM del cluster

	@return TM del cluster
**/
double cluster::getTm() const
{
	return tm;
}

/**
	@brief Metodo getIntraSim

	Metodo che ritorna l'IntraSim del cluster

	@return IntraSim del cluster
**/
double cluster::getIntraSim() const
{
	return intraSim;
}

/**
	@brief Metodo getIntraScore

	Metodo che ritorna l'IntraScore del cluster

	@return IntraScore del cluster
**/
const std::multimap<double,int>& cluster::getIntraScore() const
{
	return intraScore;
}

/**
	@brief Metodo getSplittedWith

	Metodo che ritorna lo SplittedWith del cluster

	@return SplittedWith del cluster
**/
const std::set<std::string>& cluster::getSplittedWith() const
{
	return splittedWith;
}

// Metodi set

/**
	@brief Metodo setId

	Metodo che setta l'ID del cluster

	@param id ID del cluster da settare
**/
void cluster::setId(std::string &id)
{
	this->id=id;
}

/**
	@brief Metodo setElements

	Metodo che setta gli elements del cluster

	@param elements Elements del cluster da settare
**/
void cluster::setElements(std::vector<sample> &elements)
{
	this->elements=elements;
}

/**
	@brief Metodo setIndices

	Metodo che setta gli indici del cluster

	@param indices Indici del cluster da settare
**/
void cluster::setIndices(std::vector<int> &indices)
{
	this->indices=indices;
}

/**
	@brief Metodo setRhn

	Metodo che setta l'RHN del cluster

	@param rhn RHN del cluster da settare
**/
void cluster::setRhn(std::map<int,std::vector<double>> &rhn)
{
	this->rhn=rhn;
}

/**
	@brief Metodo setTm

	Metodo che setta il TM del cluster

	@param tm TM del cluster da settare
**/
void cluster::setTm(double &tm)
{
	this->tm=tm;
}

/**
	@brief Metodo setIntraSim

	Metodo che setta l'IntraSim del cluster

	@param intraSim IntraSim del cluster da settare
**/
void cluster::setIntraSim(double &intraSim)
{
	this->intraSim=intraSim;
}

/**
	@brief Metodo setIntraScore

	Metodo che setta l'IntraScore del cluster

	@param intraScore IntraScore del cluster da settare
**/
void cluster::setIntraScore(std::multimap<double,int> &intraScore)
{
	this->intraScore=intraScore;
}

/**
	@brief Metodo setSplittedWith

	Metodo che setta lo SplittedWith del cluster

	@param splittedWith SplittedWith del cluster da settare
**/
void cluster::setSplittedWith(std::set<std::string> &splittedWith)
{
	this->splittedWith=splittedWith;
}

// Metodi per inserire i dati

/**
	@brief Metodo insertDataIntoElements

	Metodo che inserisce il sample element negli elements del cluster

	@param element Sample da inserire negli elements del cluster
**/
void cluster::insertDataIntoElements(sample &element)
{
	this->elements.push_back(element);
}

/**
	@brief Metodo insertDataIntoIndices

	Metodo che inserisce index negli indici del cluster

	@param index Indice da inserire negli indici del cluster
**/
void cluster::insertDataIntoIndices(int &index)
{
	this->indices.push_back(index);
}

/**
	@brief Metodo insertDataIntoRhn

	Metodo che inserisce la coppia <i,d> nell'RHN del cluster

	@param i Valore intero
	@param d Vector di double
**/
void cluster::insertDataIntoRhn(int i,std::vector<double> &d)
{
	this->rhn[i]=d;
}

/**
	@brief Metodo insertDataIntoIntraScore

	Metodo che inserisce la coppia <d,i> nell'IntraScore del cluster

	@param d Valore double
	@param i Valore intero
**/
void cluster::insertDataIntoIntraScore(double &d,int &i)
{
	this->intraScore.insert(std::make_pair(d,i));
}

/**
	@brief Metodo insertDataIntoSplittedWith

	Metodo che inserisce s nello SplittedWith del cluster

	@param s Stringa da inserire nello SplittedWith del cluster
**/
void cluster::insertDataIntoSplittedWith(std::string &s)
{
	this->splittedWith.insert(s);
}

// Altri metodi

/**
	@brief Metodo string

	Metodo che ritorna una stringa formata concatenando i nomi dei samples presenti nel cluster.
	La stringa inizia e termina con il carattere " e i nomi dei samples sono separati dal carattere ,

	@return Stringa formata come spiegato sopra
**/
std::string cluster::string() const
{
	std::vector<std::string> elementsName;

	for(std::vector<sample>::const_iterator it=this->getElements().begin();it!=this->getElements().end();it++)
		elementsName.push_back((*it).getName());

	std::string s="";
	s+='"';

	for(std::vector<std::string>::iterator it=elementsName.begin();it!=elementsName.end();it++)
	{
		s+=*it;
		if(it!=elementsName.end()-1)
			s+=',';
	}

	s+='"';

	return s;
}

/**
	@brief Metodo len

	Metodo che ritorna il numero di elements presenti nel cluster

	@return Numero di elements presenti nel cluster
**/
int cluster::len() const
{
	return this->elements.size();
}

// Funzioni globali

/**
	@brief Operatore di stream per la classe cluster

	Stampa il cluster

	@param os Stream di output
	@param c Cluster da stampare

	@return Riferimento allo stream di output
**/
std::ostream& operator<<(std::ostream &os, const cluster &c)
{
	os<<"ID: "<<c.getId()<<std::endl;

	os<<"Quantità di Elements: "<<c.getElements().size()<<std::endl;
	/*for(std::vector<sample>::const_iterator it=c.getElements().begin();it!=c.getElements().end();it++)
		os<<*it<<std::endl;*/

	os<<"Indices: ";
	for(std::vector<int>::const_iterator it=c.getIndices().begin();it!=c.getIndices().end();it++)
		os<<*it<<" ";
	os<<std::endl;

	os<<"RHN:"<<std::endl;
	for(std::map<int,std::vector<double>>::const_iterator it=c.getRhn().begin();it!=c.getRhn().end();it++)
	{
		os<<it->first<<",[";
		for(std::vector<double>::const_iterator it2=it->second.begin();it2!=it->second.end();it2++)
			os<<*it2<<" ";
		os<<"]"<<std::endl;
	}
	os<<std::endl;

	os<<"TM: "<<c.getTm()<<std::endl;

	os<<"IntraSim: "<<c.getIntraSim()<<std::endl;

	os<<"IntraScore: "<<std::endl;
	for(std::multimap<double,int>::const_iterator it=c.getIntraScore().begin();it!=c.getIntraScore().end();it++)
		os<<it->first<<","<<it->second<<" ";
	os<<std::endl;

	os<<"SplittedWith: ";
	for(std::set<std::string>::const_iterator it=c.getSplittedWith().begin();it!=c.getSplittedWith().end();it++)
		os<<*it<<" ";
	os<<std::endl;

	return os;
}
