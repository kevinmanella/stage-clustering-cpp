#ifndef STAT_H
#define STAT_H

#include "scs.h"
#include "vectorOperations.h"

/**
	@file stat.h

	@brief Dichiarazione delle classi resCalcR e resCalcTerm, dei loro metodi e di 5 funzioni globali
**/

/**
	@brief resCalcR

	Classe resCalcR
**/
class resCalcR
{
private:
	int i;
	std::vector<double> result;

public:
	// Metodi get

	/**
		@brief Metodo getI

		Metodo che ritorna i del resCalcR

		@return I del resCalcR
	**/
	int getI() const;

	/**
		@brief Metodo getResult

		Metodo che ritorna result del resCalcR

		@return Result del resCalcR
	**/
	const std::vector<double>& getResult() const;

	// Metodi set

	/**
		@brief Metodo setI

		Metodo che setta i del resCalcR

		@param i I del resCalcR da settare
	**/
	void setI(int &i);

	/**
		@brief Metodo setResult

		Metodo che setta result del resCalcR

		@param result Result del resCalcR da settare
	**/
	void setResult(std::vector<double> &result);

	// Metodi per inserire i dati

	/**
		@brief Metodo insertDataIntoResult

		Metodo che inserisce r nel result del resCalcR

		@param r Valore double da inserire nel result del resCalcR
	**/
	void insertDataIntoResult(double &r);
};	// Fine classe resCalcR

/**
	@brief resCalcTerm

	Classe resCalcTerm
**/
class resCalcTerm
{
private:
	int term;
	double result;

public:
	// Metodi get

	/**
		@brief Metodo getTerm

		Metodo che ritorna term del resCalcTerm

		@return Term del resCalcTerm
	**/
	int getTerm() const;

	/**
		@brief Metodo getResult

		Metodo che ritorna result del resCalcTerm

		@return Result del resCalcTerm
	**/
	double getResult() const;

	// Metodi set

	/**
		@brief Metodo setTerm

		Metodo che setta term del resCalcTerm

		@param term Term del resCalcTerm da settare
	**/
	void setTerm(int &term);

	/**
		@brief Metodo setResult

		Metodo che setta result del resCalcTerm

		@param result Result del resCalcTerm da settare
	**/
	void setResult(double &result);
};	// Fine classe resCalcTerm

// Funzioni globali

/**
	@brief Funzione calcBuildR

	Funzione calcBuildR

	@param s Puntatore a sample
	@param sIndex Valore intero
	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample

	@return Puntatore a resCalcR
**/
resCalcR* calcBuildR(sample* s,int &sIndex,std::vector<sample*> &sampleX,std::vector<sample*> &sampleY);

/**
	@brief Funzione buildR

	Funzione buildR

	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample

	@return Mappa <int,vector<double>>
**/
std::map<int,std::vector<double>> buildR(std::vector<sample*> &sampleX,std::vector<sample*> &sampleY);

/**
	@brief Funzione calcUpdateR

	Funzione calcUpdateR

	@param currentR Vector di double
	@param s Puntatore a sample
	@param sIndex Valore intero
	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample

	@return Puntatore a resCalcR
**/
resCalcR* calcUpdateR(std::vector<double> &currentR,sample* s,int &sIndex,std::vector<sample*> &sampleX,std::vector<sample*> &sampleY);

/**
	@brief Funzione updateR

	Funzione updateR

	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample
	@param RHNx Mappa <int,vector<double>>
	@param RHNy Mappa <int,vector<double>>

	@return Mappa <int,vector<double>>
**/
std::map<int,std::vector<double>> updateR(std::vector<sample*> &sampleX,std::vector<sample*> &sampleY,std::map<int,std::vector<double>> &RHNx,std::map<int,std::vector<double>> &RHNy);

/**
	@brief Funzione computeTestStat

	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample
	@param RHN Mappa <int,vector<double>>

	@return Valore double
**/
double computeTestStat(std::vector<sample*> &sampleX,std::vector<sample*> &sampleY,std::map<int,std::vector<double>> &RHN);

#endif
