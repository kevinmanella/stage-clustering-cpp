#include "scs.h"
#include <bits/stdc++.h>

/**
	@file scs.cpp

	@brief Definizione dei metodi della classe sample e di 2 funzioni globali
**/

// Metodi get

/**
	@brief Metodo getId

	Metodo che ritorna l'ID del sample

	@return ID del sample
**/
int sample::getId() const
{
	return id;
}

/**
	@brief Metodo getName

	Metodo che ritorna il nome del sample

	@return Nome del sample
**/
std::string sample::getName() const
{
	return name;
}

/**
	@brief Metodo getMapExpression

	Metodo che ritorna la MapExpression del sample

	@return MapExpression del sample
**/
const std::map<std::string,double>& sample::getMapExpression() const
{
	return mapExpression;
}

/**
	@brief Metodo getGenesExpression

	Metodo che ritorna la GenesExpression del sample

	@return GenesExpression del sample
**/
const std::vector<double>& sample::getGenesExpression() const
{
	return genesExpression;
}

/**
	@brief Metodo getMostExpressed

	Metodo che ritorna il MostExpressed del sample

	@return MostExpressed del sample
**/
const std::set<int>& sample::getMostExpressed() const
{
	return mostExpressed;
}

// Metodi set

/**
	@brief Metodo setId

	Metodo che setta l'ID del sample

	@param id ID del sample da settare
**/
void sample::setId(int &id)
{
	this->id=id;
}

/**
	@brief Metodo setName

	Metodo che setta il nome del sample

	@param name Nome del sample da settare
**/
void sample::setName(std::string &name)
{
	this->name=name;
}

/**
	@brief Metodo setMapExpression

	Metodo che setta la MapExpression del sample

	@param mapExpression MapExpression del sample da settare
**/
void sample::setMapExpression(std::map<std::string,double> &mapExpression)
{
	this->mapExpression=mapExpression;
}

/**
	@brief Metodo setGenesExpression

	Metodo che setta la GenesExpression del sample

	@param genesExpression GenesExpression del sample da settare
**/
void sample::setGenesExpression(std::vector<double> &genesExpression)
{
	this->genesExpression=genesExpression;
}

/**
	@brief Metodo setMostExpressed

	Metodo che setta il MostExpressed del sample

	@param mostExpressed MostExpressed del sample da settare
**/
void sample::setMostExpressed(std::set<int> &mostExpressed)
{
	this->mostExpressed=mostExpressed;
}

// Metodi per inserire i dati

/**
	@brief Metodo insertDataIntoMapExpression

	Metodo che inserisce la coppia <geneName,rpkm> nella MapExpression del sample

	@param geneName Nome del gene
	@param rpkm RPKM del gene rispetto al sample
**/
void sample::insertDataIntoMapExpression(std::string &geneName,double &rpkm)
{
	this->mapExpression[geneName]=rpkm;
}

/**
	@brief Metodo insertDataIntoGenesExpression

	Metodo che inserisce il valore rpkm nella GenesExpression del sample

	@param rpkm RPKM relativo al sample (indipendentemente dal gene associato)
**/
void sample::insertDataIntoGenesExpression(double &rpkm)
{
	this->genesExpression.push_back(rpkm);
}

/**
	@brief Metodo insertDataIntoMostExpressed

	Metodo che inserisce il valore index nel MostExpressed del sample

	@param index Indice del gene
**/
void sample::insertDataIntoMostExpressed(int &index)
{
	this->mostExpressed.insert(index);
}

// Metodi per costruire il MostExpressed del sample

/**
	@brief Metodo buildExpressedSet

	Metodo che, dato un double p, costruisce l'insieme dei migliori p% geni espressi (escludendo gli zeri)

	@param p Parametro di input di tipo double
**/
void sample::buildExpressedSet(double &p)
{
	std::multimap<double,int> tmp;

	for(std::vector<double>::const_iterator it=this->getGenesExpression().begin();it!=this->getGenesExpression().end();it++)
		tmp.insert(std::make_pair(*it,it-this->getGenesExpression().begin()));

	std::vector<int> indexes;

	for(std::multimap<double,int>::iterator it=tmp.begin();it!=tmp.end();it++)
		indexes.push_back(it->second);

	int topp=int(indexes.size()*p);

	for(int i=1;i<=topp;i++)
		this->insertDataIntoMostExpressed(indexes[indexes.size()-i]);
}

/**
	@brief Metodo buildExpressedSet2

	Metodo che, dato un double p, costruisce l'insieme di geni che sono p volte più espressi rispetto alla mediana (escludendo gli zeri)

	@param p Parametro di input di tipo double
**/
void sample::buildExpressedSet2(double &p)
{
	double tmp=p;

	std::vector<double> gen=this->getGenesExpression();
	double median=getMedian(gen);

	while(this->getMostExpressed().size()<=10)
	{
		for(int i=0;i<this->getGenesExpression().size();i++)
			if(this->getGenesExpression()[i]>tmp*median)
				this->insertDataIntoMostExpressed(i);
		
		tmp*=0.9;
	}
}

// Funzioni globali

/**
	@brief Operatore di stream per la classe sample

	Stampa il sample

	@param os Stream di output
	@param s Sample da stampare

	@return Riferimento allo stream di output
**/
std::ostream& operator<<(std::ostream &os, const sample &s)
{
	os<<"ID: "<<s.getId()<<std::endl;

	os<<"Name: "<<s.getName()<<std::endl;

	os<<"MapExpression: ";
	for(std::map<std::string,double>::const_iterator it=s.getMapExpression().begin();it!=s.getMapExpression().end();it++)
		os<<it->first<<","<<it->second<<" ";
	os<<std::endl;

	os<<"GenesExpression: ";
	for(std::vector<double>::const_iterator it=s.getGenesExpression().begin();it!=s.getGenesExpression().end();it++)
		os<<*it<<" ";
	os<<std::endl;

	os<<"MostExpressed: ";
	for(std::set<int>::const_iterator it=s.getMostExpressed().begin();it!=s.getMostExpressed().end();it++)
		os<<*it<<" ";
	os<<std::endl;

	return os;
}

/**
	@brief Funzione getMedian

	Funzione che, dato un vector di double, ne restituisce la mediana

	@param values Vector di double

	@return Mediana del vector di double
*/
double getMedian(std::vector<double> &values)
{
	std::vector<double> tmp=values;

	std::vector<double>::iterator it=tmp.begin();
	while(it!=tmp.end())
		if(*it==0)
			it=tmp.erase(it);
		else
			it++;

	sort(tmp.begin(),tmp.end());

	int middle=tmp.size()/2;

	if(tmp.size()%2==0)
		return (tmp[middle-1]+tmp[middle])/2;

	return tmp[middle];
}
