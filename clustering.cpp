#include "clustering.h"
#include <algorithm>
#include <tuple>

/**
	@file clustering.cpp

	@brief Definizione dei metodi della classe stats e di 4 funzioni globali
**/

// Metodi get

/**
	@brief Metodo getTm

	Metodo che ritorna il TM di stats

	@return TM di stats
**/
double stats::getTm() const
{
	return tm;
}

/**
	@brief Metodo getRhn

	Metodo che ritorna l'RHN di stats

	@return RHN di stats
**/
const std::map<int,std::vector<double>>& stats::getRhn() const
{
	return rhn;
}

// Metodi set

/**
	@brief Metodo setTm

	Metodo che setta il TM di stats

	@param tm TM di stats da settare
**/
void stats::setTm(double &tm)
{
	this->tm=tm;
}

/**
	@brief Metodo setRhn

	Metodo che setta l'RHN di stats

	@param rhn RHN di stats da settare
**/
void stats::setRhn(std::map<int,std::vector<double>> &rhn)
{
	this->rhn=rhn;
}

// Metodi per inserire i dati

/**
	@brief Metodo insertDataIntoRhn

	Metodo che inserisce la coppia <i,d> nell'RHN di stats

	@param i Valore intero
	@param d Vector di double
**/
void stats::insertDataIntoRhn(int i,std::vector<double> &d)
{
	this->rhn[i]=d;
}

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
std::tuple<std::vector<cluster>,bool> estClustStep(std::vector<sample*> &cells,std::vector<cluster> &cs,int &thClustSize,int &thMaxFuse,clusterSimilarityFunction simMeasure)
{
	retScore* score=nullptr;
	std::vector<retScore> scores;

	//#pragma omp parallel for private(score,scores,cs)
	for(int i=0;i<cs.size();i++)
	{
		if(cs[i].len()<=thClustSize)
			for(int j=i+1;j<cs.size();j++)
				if(cs[j].len()<=thClustSize)
				{
					score=simMeasure(&cs[i],&cs[j],i,j);
					scores.push_back(*score);
					delete score;
					score=nullptr;
				}
	}

	if(scores.size()==0)
		for(int i=0;i<cs.size();i++)
			if(cs[i].len()==1)
				for(int j=0;j<cs.size();j++)
					if(i!=j)
					{
						score=simMeasure(&cs[i],&cs[j],i,j);
						scores.push_back(*score);
						delete score;
						score=nullptr;
					}

	// Ordino scores in ordine decrescente rispetto all'attributo score
	sort(scores.begin(),scores.end(),[](retScore &lhs,retScore &rhs)
	{
		return lhs.getScore()>rhs.getScore();
	});

	cluster* clus=nullptr;
	std::vector<cluster> cls;

	std::vector<int> used;
	std::vector<int>::iterator okI;
	std::vector<int>::iterator okJ;

	std::map<int,std::vector<double>> rhn;

	int fused=0;
	double tm=-1.0;
	bool singletons=false;


	for(std::vector<retScore>::iterator it=scores.begin();it!=scores.end();it++)
	{
		okI=std::find(used.begin(),used.end(),(*it).getI());
		okJ=std::find(used.begin(),used.end(),(*it).getJ());

		if(okI!=used.end() || okJ!=used.end())
		{
			// Già usato
		}
		else
		{
			// Non ancora usato
			used.push_back((*it).getI());
			used.push_back((*it).getJ());

			clus=fuseCluster(&cs[(*it).getI()],&cs[(*it).getJ()],cells,rhn,tm);
			cls.push_back(*clus);
			delete clus;
			clus=nullptr;
			fused++;
		}

		if(fused>=thMaxFuse)
			break;
	}

	for(int i=0;i<cs.size();i++)
	{
		okI=std::find(used.begin(),used.end(),i);

		if(okI!=used.end())
		{
			// Già usato
		}
		else
		{
			// Non ancora usato
			used.push_back(i);

			if(!singletons && cs[i].len()==1)
				singletons=true;

			cls.push_back(cs[i]);
		}
	}

	return {cls,singletons};
}

/**
	@brief Funzione estimateInitialClusters

	Stima i primi clusters richiamando la funzione estClustStep

	@param cells Vector di puntatori a sample

	@return Vector di clusters
**/
std::vector<cluster> estimateInitialClusters(std::vector<sample*> &cells)
{
	std::tuple<std::vector<cluster>,bool> tup;
	cluster* clus=nullptr;
	std::vector<cluster> cs;

	bool singletons=true;
	int thClustSize=3;
	int thMaxFuse=5;

	for(int i=0;i<cells.size();i++)
	{
		std::vector<int> indices{i};
		clus=newCluster(cells,indices);
		cs.push_back(*clus);
		delete clus;
		clus=nullptr;
	}

	tup=make_tuple(cs,singletons);

	while(std::get<1>(tup)==true)
	{
		tup=estClustStep(cells,std::get<0>(tup),thClustSize,thMaxFuse,avgCosine);
		// tup=estClustStep(cells,std::get<0>(tup),thClustSize,thMaxFuse,avgGenes);
	}

	return std::get<0>(tup);
}

/**
	@brief Funzione NJstep

	Effettua l'algoritmo di Neighbour Joining su currentClust

	@param cells Vector di puntatori a sample
	@param currentClust Vector di clusters
	@param memoize Mappa <string,Mappa<string,stats>>

	@return Vector di clusters
**/
std::vector<cluster> NJstep(std::vector<sample*> &cells,std::vector<cluster> &currentClust,std::map<std::string,std::map<std::string,stats>> &memoize)
{
	std::set<std::string>::iterator splitted;
	std::map<std::string,std::map<std::string,stats>>::iterator ok;
	std::map<std::string,std::map<std::string,stats>>::iterator ok1;
	std::map<std::string,stats>::iterator ok2;

	retScore* score=nullptr;
	std::vector<retScore> scores;

	cluster* c1=nullptr;
	cluster* c2=nullptr;

	std::map<int,std::vector<double>> rhn;
	double tm;
	bool memoized=false;

	//#pragma omp parallel for private(c1,c2,rhn,tm)
	for(int i=0;i<currentClust.size();i++)
		for(int j=i+1;j<currentClust.size();j++)
		{
			splitted=std::find(currentClust[i].getSplittedWith().begin(),currentClust[i].getSplittedWith().end(),currentClust[j].getId());

			if(splitted==currentClust[i].getSplittedWith().end())
			{
				c1=&currentClust[i];
				c2=&currentClust[j];

				memoized=false;

				ok1=memoize.find(c1->getId());

				if(ok1!=memoize.end())
				{
					ok2=ok1->second.find(c2->getId());

					if(ok2!=ok1->second.end())
					{
						rhn=ok2->second.getRhn();
						tm=ok2->second.getTm();
						memoized=true;
					}
				}
				else
				{
					std::map<std::string,stats> tmp;
					memoize[c1->getId()]=tmp;
				}

				if(!memoized)
				{
					ok=memoize.find(c2->getId());

					if(ok==memoize.end())
					{
						std::map<std::string,stats> tmp;
						memoize[c2->getId()]=tmp;
					}

					std::vector<sample*> samplesC1=c1->getElements();
					std::vector<sample*> samplesC2=c2->getElements();

					std::map<int,std::vector<double>> rhnC1=c1->getRhn();
					std::map<int,std::vector<double>> rhnC2=c2->getRhn();

					rhn=updateR(samplesC1,samplesC2,rhnC1,rhnC2);
					tm=computeTestStat(samplesC1,samplesC2,rhn);

					stats stat;
					stat.setRhn(rhn);
					stat.setTm(tm);

					memoize[c1->getId()][c2->getId()]=stat;
					memoize[c2->getId()][c1->getId()]=stat;
				}

				score=new retScore();
				score->setI(i);
				score->setJ(j);
				score->setScore(tm);
				scores.push_back(*score);
				delete score;
				score=nullptr;
			}
		}

	std::vector<int> used;
	std::vector<int>::iterator okI;
	std::vector<int>::iterator okJ;

	int fused=0;

	std::vector<cluster> cls;

	for(int i=0;i<scores.size();i++)
	{
		okI=std::find(used.begin(),used.end(),scores[i].getI());
		okJ=std::find(used.begin(),used.end(),scores[i].getJ());

		if(okI!=used.end() || okJ!=used.end())
		{
			// Già usato
		}
		else
		{
			// Non ancora usato
			used.push_back(scores[i].getI());
			used.push_back(scores[i].getJ());
			double score=scores[i].getScore();
			std::map<int,std::vector<double>> r=memoize[currentClust[scores[i].getI()].getId()][currentClust[scores[i].getJ()].getId()].getRhn();
			cluster* clus=fuseCluster(&currentClust[scores[i].getI()],&currentClust[scores[i].getJ()],cells,r,score);
			cls.push_back(*clus);
			delete clus;
			clus=nullptr;

			memoize.erase(currentClust[scores[i].getI()].getId());
			memoize.erase(currentClust[scores[i].getJ()].getId());
			fused++;
		}

		if(fused>=3)
			break;
	}

	for(int i=0;i<currentClust.size();i++)
	{
		okI=std::find(used.begin(),used.end(),i);

		if(okI!=used.end())
		{
			// Già usato
		}
		else
		{
			// Non ancora usato
			used.push_back(i);
			cls.push_back(currentClust[i]);
		}
	}

	return cls;
}

/**
	@brief Funzione NJclustering

	Effettua un clustering utilizzando la tecnica di Neighbour Joining

	@param cells Vector di puntatori a sample
	@param k Valore intero

	@return Vector di clusters
**/
std::vector<cluster> NJclustering(std::vector<sample*> &cells,int &k)
{
	std::vector<cluster> cls=estimateInitialClusters(cells);

	std::map<std::string,std::map<std::string,stats>> memoize;

	while(cls.size()>k)
	{
		cls=NJstep(cells,cls,memoize);

		for(int i=0;i<cls.size();i++)
			auto [tmp,avgCos]=intraDistance(&cls[i]);
	}

	return cls;
}
