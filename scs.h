#ifndef SCS_H
#define SCS_H

#include <map>
#include <vector>
#include <set>

/**
	@file scs.h

	@brief Dichiarazione della classe sample, dei suoi metodi e di 2 funzioni globali
**/

/**
	@brief sample

	Classe che rappresenta un sample (ossia una cellula)
**/
class sample
{
private:
	int id;
	std::string name;
	std::map<std::string,double> mapExpression;	// Chiave: Nome del gene. Valore: RPKM del gene rispetto al sample
	std::vector<double> genesExpression;	// Tutti gli RPKM relativi al sample
	std::set<int> mostExpressed;	// Insieme che contiene gli indici dei geni più espressi

public:
	// Metodi get

	/**
		@brief Metodo getId

		Metodo che ritorna l'ID del sample

		@return ID del sample
	**/
	int getId() const;

	/**
		@brief Metodo getName

		Metodo che ritorna il nome del sample

		@return Nome del sample
	**/
	std::string getName() const;

	/**
		@brief Metodo getMapExpression

		Metodo che ritorna la MapExpression del sample

		@return MapExpression del sample
	**/
	const std::map<std::string,double>& getMapExpression() const;

	/**
		@brief Metodo getGenesExpression

		Metodo che ritorna la GenesExpression del sample

		@return GenesExpression del sample
	**/
	const std::vector<double>& getGenesExpression() const;

	/**
		@brief Metodo getMostExpressed

		Metodo che ritorna il MostExpressed del sample

		@return MostExpressed del sample
	**/
	const std::set<int>& getMostExpressed() const;

	// Metodi set

	/**
		@brief Metodo setId

		Metodo che setta l'ID del sample

		@param id ID del sample da settare
	**/
	void setId(int &id);

	/**
		@brief Metodo setName

		Metodo che setta il nome del sample

		@param name Nome del sample da settare
	**/
	void setName(std::string &name);

	/**
		@brief Metodo setMapExpression

		Metodo che setta la MapExpression del sample

		@param mapExpression MapExpression del sample da settare
	**/
	void setMapExpression(std::map<std::string,double> &mapExpression);

	/**
		@brief Metodo setGenesExpression

		Metodo che setta la GenesExpression del sample

		@param genesExpression GenesExpression del sample da settare
	**/
	void setGenesExpression(std::vector<double> &genesExpression);

	/**
		@brief Metodo setMostExpressed

		Metodo che setta il MostExpressed del sample

		@param mostExpressed MostExpressed del sample da settare
	**/
	void setMostExpressed(std::set<int> &mostExpressed);

	// Metodi per inserire i dati

	/**
		@brief Metodo insertDataIntoMapExpression

		Metodo che inserisce la coppia <geneName,rpkm> nella MapExpression del sample

		@param geneName Nome del gene
		@param rpkm RPKM del gene rispetto al sample
	**/
	void insertDataIntoMapExpression(std::string &geneName,double &rpkm);

	/**
		@brief Metodo insertDataIntoGenesExpression

		Metodo che inserisce il valore rpkm nella GenesExpression del sample

		@param rpkm RPKM relativo al sample (indipendentemente dal gene associato)
	**/
	void insertDataIntoGenesExpression(double &rpkm);

	/**
		@brief Metodo insertDataIntoMostExpressed

		Metodo che inserisce il valore index nel MostExpressed del sample

		@param index Indice del gene
	**/
	void insertDataIntoMostExpressed(int &index);

	// Metodi per costruire il MostExpressed del sample

	/**
		@brief Metodo buildExpressedSet

		Metodo che, dato un double p, costruisce l'insieme dei migliori p% geni espressi (escludendo gli zeri)

		@param p Parametro di input di tipo double
	**/
	void buildExpressedSet(double &p);

	/**
		@brief Metodo buildExpressedSet2

		Metodo che, dato un double p, costruisce l'insieme di geni che sono p volte più espressi rispetto alla mediana (escludendo gli zeri)

		@param p Parametro di input di tipo double
	**/
	void buildExpressedSet2(double &p);
};	// Fine classe sample

// Funzioni globali

/**
	@brief Operatore di stream per la classe sample

	Stampa il sample

	@param os Stream di output
	@param s Sample da stampare

	@return Riferimento allo stream di output
**/
std::ostream& operator<<(std::ostream &os, const sample &s);

/**
	@brief Funzione getMedian

	Funzione che, dato un vector di double, ne restituisce la mediana

	@param values Vector di double

	@return Mediana del vector di double
*/
double getMedian(std::vector<double> &values);

#endif
