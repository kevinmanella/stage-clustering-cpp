#ifndef VECTOROPERATIONS_H
#define VECTOROPERATIONS_H

#include <vector>

/**
	@file vectorOperations.h

	@brief Dichiarazione di 5 funzioni globali che effettuano delle operazioni su vector di double
**/

/**
	@brief Funzione vectorSum

	Funzione che fa la somma degli elementi di due vector di double (x[i]+y[i])

	@param x Primo vector di double
	@param y Secondo vector di double

	@return Vettore somma
**/
std::vector<double> vectorSum(std::vector<double> &x,std::vector<double> &y);

/**
	@brief Funzione vectorDifference

	Funzione che fa la differenza degli elementi di due vector di double (x[i]-y[i])

	@param x Primo vector di double
	@param y Secondo vector di double

	@return Vettore differenza
**/
std::vector<double> vectorDifference(std::vector<double> &x,std::vector<double> &y);

/**
	@brief Funzione vectorMultiply

	Funzione che moltiplica tutti gli elementi di un vector di double con un valore double (x[i]*mult)

	@param x Vector di double
	@param mult Moltiplicatore

	@return Vettore prodotto
**/
std::vector<double> vectorMultiply(std::vector<double> &x,double &mult);

/**
	@brief Funzione vectorDivide

	Funzione che divide tutti gli elementi di un vector di double con un valore double (x[i]/div)

	@param x Vector di double
	@param div Divisore

	@return Vettore divisione
**/
std::vector<double> vectorDivide(std::vector<double> &x,double &div);

/**
	@brief Funzione vectorNorm

	Funzione che calcola la norma di un vector di double

	@param x Vector di double

	@return Norma del vettore
**/
double vectorNorm(std::vector<double> &x);

#endif
