#include "stat.h"

/**
	@file stat.cpp

	@brief Definizione dei metodi delle classi resCalcR e resCalcTerm e di 5 funzioni globali
**/

// Metodi get della classe resCalcR

/**
	@brief Metodo getI

	Metodo che ritorna i del resCalcR

	@return I del resCalcR
**/
int resCalcR::getI() const
{
	return i;
}

/**
	@brief Metodo getResult

	Metodo che ritorna result del resCalcR

	@return Result del resCalcR
**/
const std::vector<double>& resCalcR::getResult() const
{
	return result;
}

// Metodi set della classe resCalcR

/**
	@brief Metodo setI

	Metodo che setta i del resCalcR

	@param i I del resCalcR da settare
**/
void resCalcR::setI(int &i)
{
	this->i=i;
}

/**
	@brief Metodo setResult

	Metodo che setta result del resCalcR

	@param result Result del resCalcR da settare
**/
void resCalcR::setResult(std::vector<double> &result)
{
	this->result=result;
}

// Metodi per inserire i dati della classe resCalcR

/**
	@brief Metodo insertDataIntoResult

	Metodo che inserisce r nel result del resCalcR

	@param r Valore double da inserire nel result del resCalcR
**/
void resCalcR::insertDataIntoResult(double &r)
{
	this->result.push_back(r);
}

// Metodi get della classe resCalcTerm

/**
	@brief Metodo getTerm

	Metodo che ritorna term del resCalcTerm

	@return Term del resCalcTerm
**/
int resCalcTerm::getTerm() const
{
	return term;
}

/**
	@brief Metodo getResult

	Metodo che ritorna result del resCalcTerm

	@return Result del resCalcTerm
**/
double resCalcTerm::getResult() const
{
	return result;
}

// Metodi set della classe resCalcTerm

/**
	@brief Metodo setTerm

	Metodo che setta term del resCalcTerm

	@param term Term del resCalcTerm da settare
**/
void resCalcTerm::setTerm(int &term)
{
	this->term=term;
}

/**
	@brief Metodo setResult

	Metodo che setta result del resCalcTerm

	@param result Result del resCalcTerm da settare
**/
void resCalcTerm::setResult(double &result)
{
	this->result=result;
}

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
resCalcR* calcBuildR(sample* s,int &sIndex,std::vector<sample*> &sampleX,std::vector<sample*> &sampleY)
{
	resCalcR* resR=new resCalcR();

	std::vector<double> R;
	std::vector<double> genS;
	std::vector<double> genSampleX;
	std::vector<double> genSampleY;
	std::vector<double> num;
	std::vector<double> summand;

	double div=0.0;
	double denom=0.0;

	int lenX=sampleX.size();
	int lenY=sampleY.size();
	int N=lenX+lenY;

	for(int i=0;i<s->getGenesExpression().size();i++)
		R.push_back(0.0);

	for(int i=0;i<N;i++)
	{
		genS=s->getGenesExpression();
		if(i<lenX)
		{
			genSampleX=sampleX[i]->getGenesExpression();
			num=vectorDifference(genS,genSampleX);
		}
		else
		{
			genSampleY=sampleY[i-lenX]->getGenesExpression();
			num=vectorDifference(genS,genSampleY);
		}

		denom=vectorNorm(num);

		if(denom!=0)
		{
			div=denom*double(N);
			summand=vectorDivide(num,div);
			R=vectorSum(R,summand);
		}
	}

	resR->setI(sIndex);
	resR->setResult(R);

	return resR;
}

/**
	@brief Funzione buildR

	Funzione buildR

	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample

	@return Mappa <int,vector<double>>
**/
std::map<int,std::vector<double>> buildR(std::vector<sample*> &sampleX,std::vector<sample*> &sampleY)
{
	resCalcR* r=nullptr;

	std::map<int,std::vector<double>> rhn;

	int lenX=sampleX.size();
	int lenY=sampleY.size();
	int N=lenX+lenY;

	//#pragma omp parallel for private(r,rhn)
	for(int i=0;i<N;i++)
	{
		if(i<lenX)
			r=calcBuildR(sampleX[i],i,sampleX,sampleY);
		else
			r=calcBuildR(sampleY[i-lenX],i,sampleX,sampleY);

		rhn[r->getI()]=r->getResult();
		delete r;
		r=nullptr;
	}

	return rhn;
}

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
resCalcR* calcUpdateR(std::vector<double> &currentR,sample* s,int &sIndex,std::vector<sample*> &sampleX,std::vector<sample*> &sampleY)
{
	resCalcR* resR=new resCalcR();

	std::vector<double> genS;
	std::vector<double> genSampleY;
	std::vector<double> num;
	std::vector<double> summand;

	double div=0.0;
	double denom=0.0;

	int lenX=sampleX.size();
	int lenY=sampleY.size();
	int N=lenX+lenY;
	double mult=double(lenX)/double(N);

	std::vector<double> R=vectorMultiply(currentR,mult);

	for(int i=0;i<lenY;i++)
	{
		genS=s->getGenesExpression();
		genSampleY=sampleY[i]->getGenesExpression();
		num=vectorDifference(genS,genSampleY);
		denom=vectorNorm(num);

		if(denom!=0)
		{
			div=denom*double(N);
			summand=vectorDivide(num,div);
			R=vectorSum(R,summand);
		}
	}

	resR->setI(sIndex);
	resR->setResult(R);

	return resR;
}

/**
	@brief Funzione updateR

	Funzione updateR

	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample
	@param RHNx Mappa <int,vector<double>>
	@param RHNy Mappa <int,vector<double>>

	@return Mappa <int,vector<double>>
**/
std::map<int,std::vector<double>> updateR(std::vector<sample*> &sampleX,std::vector<sample*> &sampleY,std::map<int,std::vector<double>> &RHNx,std::map<int,std::vector<double>> &RHNy)
{
	resCalcR* r=nullptr;

	std::map<int,std::vector<double>> rhn;

	int lenX=sampleX.size();
	int lenY=sampleY.size();
	int N=lenX+lenY;

	//#pragma omp parallel for private(r,rhn)
	for(int i=0;i<N;i++)
	{
		if(i<lenX)
			if(RHNx.size()!=0)
				r=calcUpdateR(RHNx[i],sampleX[i],i,sampleX,sampleY);
			else
				r=calcBuildR(sampleX[i],i,sampleX,sampleY);
		else
			if(RHNy.size()!=0)
				r=calcUpdateR(RHNy[i-lenX],sampleY[i-lenX],i,sampleY,sampleX);
			else
				r=calcBuildR(sampleY[i-lenX],i,sampleX,sampleY);

		rhn[r->getI()]=r->getResult();
		delete r;
		r=nullptr;
	}

	return rhn;
}

/**
	@brief Funzione computeTestStat

	Funzione computeTestStat

	@param sampleX Vector di puntatori a sample
	@param sampleY Vector di puntatori a sample
	@param RHN Mappa <int,vector<double>>

	@return Valore double
**/
double computeTestStat(std::vector<sample*> &sampleX,std::vector<sample*> &sampleY,std::map<int,std::vector<double>> &RHN)
{
	resCalcTerm* term=nullptr;
	std::vector<resCalcTerm> termVector;

	std::vector<double> r1Val;
	std::vector<double> r2Val;
	std::vector<double> diff;

	int termValue0=0;
	int termValue1=1;
	int termValue2=2;
	double norm=0.0;

	int lenX=sampleX.size();
	int lenY=sampleY.size();

	//#pragma omp parallel for private(r1Val,r2Val,RHN,diff,norm,term,termVector)
	for(int i=0;i<=lenX;i++)
		for(int j=0;j<=lenY-1;j++)
		{
			r1Val=RHN[i];
			r2Val=RHN[j+lenX];
			diff=vectorDifference(r1Val,r2Val);
			norm=vectorNorm(diff);

			term=new resCalcTerm();
			term->setTerm(termValue0);
			term->setResult(norm);

			termVector.push_back(*term);
			delete term;
			term=nullptr;
		}

	//#pragma omp parallel for private(r1Val,r2Val,RHN,diff,norm,term,termVector)
	for(int i=0;i<=lenX;i++)
		for(int j=0;j<=lenX;j++)
		{
			if(i!=j)
			{
				r1Val=RHN[i];
				r2Val=RHN[j];
				diff=vectorDifference(r1Val,r2Val);
				norm=vectorNorm(diff);

				term=new resCalcTerm();
				term->setTerm(termValue1);
				term->setResult(norm);

				termVector.push_back(*term);
				delete term;
				term=nullptr;
			}
		}

	//#pragma omp parallel for private(r1Val,r2Val,RHN,diff,norm,term,termVector)
	for(int i=0;i<=lenY-1;i++)
		for(int j=0;j<=lenY-1;j++)
		{
			if(i!=j)
			{
				r1Val=RHN[lenX+i];
				r2Val=RHN[lenX+j];
				diff=vectorDifference(r1Val,r2Val);
				norm=vectorNorm(diff);

				term=new resCalcTerm();
				term->setTerm(termValue2);
				term->setResult(norm);

				termVector.push_back(*term);
				delete term;
				term=nullptr;
			}
		}

	double intergroup=0.0;
	double intragroupX=0.0;
	double intragroupY=0.0;

	for(std::vector<resCalcTerm>::iterator it=termVector.begin();it!=termVector.end();it++)
		switch(it->getTerm())
		{
			case 0:
				intergroup+=it->getResult();
				break;
			case 1:
				intragroupX+=it->getResult();
				break;
			case 2:
				intragroupY+=it->getResult();
				break;
		}

	intergroup/=double(lenX*lenY);
	intragroupX/=double(2*lenX*lenX);
	intragroupY/=double(2*lenY*lenY);

	return double((lenX*lenY)/(lenX+lenY))*(intergroup-intragroupX-intragroupY);
}
