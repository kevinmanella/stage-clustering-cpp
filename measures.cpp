#include "measures.h"
#include <cmath>
#include <algorithm>

/**
	@file measures.cpp

	@brief Definizione dei metodi della classe retScore e di 11 funzioni globali
**/

// Metodi get

/**
	@brief Metodo getI

	Metodo che ritorna l'attributo i di retScore

	@return i di retScore
**/
int retScore::getI() const
{
	return i;
}

/**
	@brief Metodo getJ

	Metodo che ritorna l'attributo j di retScore

	@return j di retScore
**/
int retScore::getJ() const
{
	return j;
}

/**
	@brief Metodo getScore

	Metodo che ritorna l'attributo score di retScore

	@return score di retScore
**/

double retScore::getScore() const
{
	return score;
}

// Metodi set

/**
	@brief Metodo setI

	Metodo che setta l'attributo i di retScore

	@param i i del retScore da settare
**/
void retScore::setI(int &i)
{
	this->i=i;
}

/**
	@brief Metodo setJ

	Metodo che setta l'attributo j di retScore

	@param j j del retScore da settare
**/
void retScore::setJ(int &j)
{
	this->j=j;
}

/**
	@brief Metodo setScore

	Metodo che setta l'attributo score di retScore

	@param score score del retScore da settare
**/
void retScore::setScore(double &score)
{
	this->score=score;
}

// Altri metodi

/**
	@brief Metodo string

	Metodo che ritorna una stringa formata concatenando gli attributi di retScore nel seguente modo --> (i, j) score

	@return Stringa formata come spiegato sopra
**/

std::string retScore::string() const
{
	return "("+std::to_string(this->i)+", "+std::to_string(this->j)+") "+std::to_string(this->score);
}

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
retScore* cosineSimilarity(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi)
{
	retScore* ret=new retScore();
	double prod=0.0;
	double magnitude1=0.0;
	double magnitude2=0.0;

	for(int i=0;i<x.size();i++)
	{
		prod+=x[i]*y[i];
		magnitude1+=pow(x[i],2);
		magnitude2+=pow(y[i],2);
	}

	magnitude1=sqrt(magnitude1);
	magnitude2=sqrt(magnitude2);

	ret->setI(xi);
	ret->setJ(yi);
	double score=prod/(magnitude1*magnitude2);
	ret->setScore(score);

	return ret;
}

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
retScore* euclideanSimilarity(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi)
{
	retScore* ret=new retScore();
	double sum=0.0;

	for(int i=0;i<x.size();i++)
		sum+=pow(x[i]-y[i],2);

	ret->setI(xi);
	ret->setJ(yi);
	// Negativo, in quanto devo massimizzarlo, dato che lo sto usando come misura di similarità
	double score=-sqrt(sum);
	ret->setScore(score);

	return ret;
}

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
retScore* minkowskiSimilarity(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi)
{
	retScore* ret=new retScore();
	// p è hardcoded per mantenere consistenza
	// Se necessario cambiare il valore di p
	double p=3.0;
	double sum=0.0;

	for(int i=0;i<x.size();i++)
		sum+=pow(std::abs(x[i]-y[i]),p);

	ret->setI(xi);
	ret->setJ(yi);
	// Negativo, in quanto devo massimizzarlo, dato che lo sto usando come misura di similarità
	double score=-pow(sum,1.0/p);
	ret->setScore(score);

	return ret;
}

/**
	@brief Funzione geneExpressed

	È compatibile con similarityFunction

	@param x Vector di double
	@param y Vector di double
	@param xi Valore intero
	@param yi Valore intero

	@return Puntatore a retScore
**/
retScore* geneExpressed(std::vector<double> &x,std::vector<double> &y,int &xi,int &yi)
{
	retScore* ret=new retScore();
	// p è hardcoded per mantenere consistenza
	// Se necessario cambiare il valore di p
	double p=200.0;
	double sum=0.0;

	for(int i=0;i<x.size();i++)
		if(std::abs(x[i]-y[i])<=p)
			sum++;

	ret->setI(xi);
	ret->setJ(yi);
	double score=sum/x.size();
	ret->setScore(score);

	return ret;
}

/**
	@brief Funzione avgCosine

	È compatibile con clusterSimilarityFunction

	@param c1 Puntatore a cluster
	@param c2 Puntatore a cluster
	@param ci Valore intero
	@param cj Valore intero

	@return Puntatore a retScore
**/
retScore* avgCosine(cluster* c1,cluster* c2,int &ci,int &cj)
{
	retScore* ret=new retScore();
	retScore* tmp=nullptr;
	double denom=0.0;
	double avg=0.0;
	double score=0.0;
	int n=c1->len();
	int m=c2->len();
	
	for(int i=0;i<n+m;i++)
		for(int j=i+1;j<n+m;j++)
		{
			std::vector<double> ge1,ge2;

			if(i<n)
				ge1=c1->getElements()[i].getGenesExpression();
			else
				ge1=c2->getElements()[i-n].getGenesExpression();

			if(j<n)
				ge2=c1->getElements()[j].getGenesExpression();
			else
				ge2=c2->getElements()[j-n].getGenesExpression();

			tmp=cosineSimilarity(ge1,ge2,i,j);
			score=tmp->getScore();
			delete tmp;
			tmp=nullptr;
			avg+=score;
			denom++;
		}

		ret->setI(ci);
		ret->setJ(cj);
		double finalScore=avg/denom;
		ret->setScore(finalScore);

		return ret;
}

/**
	@brief Funzione avgGenes

	È compatibile con clusterSimilarityFunction

	@param c1 Puntatore a cluster
	@param c2 Puntatore a cluster
	@param ci Valore intero
	@param cj Valore intero

	@return Puntatore a retScore
**/
retScore* avgGenes(cluster* c1,cluster* c2,int &ci,int &cj)
{
	retScore* ret=new retScore();
	double denom=0.0;
	double avg=0.0;
	double score=0.0;
	int n=c1->len();
	int m=c2->len();

	for(int i=0;i<n+m;i++)
		for(int j=i+1;j<n+m;j++)
		{
			std::set<int> ge1,ge2,ge3,ge4;

			if(i<n)
				ge1=c1->getElements()[i].getMostExpressed();
			else
				ge1=c2->getElements()[i-n].getMostExpressed();

			if(j<n)
				ge2=c1->getElements()[j].getMostExpressed();
			else
				ge2=c2->getElements()[j-n].getMostExpressed();

			set_intersection(ge1.begin(),ge1.end(),ge2.begin(),ge2.end(),
							 std::inserter(ge3,ge3.begin()));
			set_union(ge1.begin(),ge1.end(),ge2.begin(),ge2.end(),
					  std::inserter(ge4,ge4.begin()));
			score=double(ge3.size())/double(ge4.size());
			avg+=score;
			denom++;
		}

		ret->setI(ci);
		ret->setJ(cj);
		double finalScore=avg/denom;
		ret->setScore(finalScore);

		return ret;
}

/**
	@brief Funzione intraSimilarity

	intraSimilarity

	@param c Puntatore a cluster
	@param sim Funzione di similarità

	@return IntraSim e IntraScore del cluster
**/
std::tuple<double,std::multimap<double,int>> intraSimilarity(cluster* c,similarityFunction sim)
{
	std::vector<double> genI;
	std::vector<double> genJ;
	double denom=0.0;
	double avg=0.0;
	double score=0.0;
	retScore* tmp=nullptr;

	std::vector<double> intraScores(c->len());

	for(int i=0;i<c->len();i++)
		for(int j=i+1;j<c->len();j++)
		{
			genI=c->getElements()[i].getGenesExpression();
			genJ=c->getElements()[j].getGenesExpression();
			tmp=sim(genI,genJ,i,j);
			score=tmp->getScore();
			delete tmp;
			tmp=nullptr;
			intraScores[i]+=score;
			intraScores[j]+=score;
			avg+=score;
			denom++;
		}

	std::multimap<double,int> s;

	for(std::vector<double>::iterator it=intraScores.begin();it!=intraScores.end();it++)
		s.insert(std::make_pair(*it,it-intraScores.begin()));

	return {avg/denom,s};
}

/**
	@brief Funzione intraDistance

	intraDistance

	@param c Puntatore a cluster

	@return IntraSim e IntraScore del cluster
**/
std::tuple<double,std::multimap<double,int>> intraDistance(cluster* c)
{
	double denom=0.0;
	double totDist=0.0;
	double score=0.0;

	std::vector<double> intraScores(c->len());

	for(int i=0;i<c->len();i++)
		for(int j=i+1;j<c->len();j++)
		{
			std::set<int> tmp1,tmp2;

			set_intersection(c->getElements()[i].getMostExpressed().begin(),c->getElements()[i].getMostExpressed().end(),
							 c->getElements()[j].getMostExpressed().begin(),c->getElements()[j].getMostExpressed().end(),
							 std::inserter(tmp1,tmp1.begin()));
			set_union(c->getElements()[i].getMostExpressed().begin(),c->getElements()[i].getMostExpressed().end(),
					  c->getElements()[j].getMostExpressed().begin(),c->getElements()[j].getMostExpressed().end(),
					  std::inserter(tmp2,tmp2.begin()));
			score=double(tmp1.size())/double(tmp2.size());
			intraScores[i]+=score;
			intraScores[j]+=score;
			totDist+=score;
			denom++;
		}

	std::multimap<double,int> s;

	for(std::vector<double>::iterator it=intraScores.begin();it!=intraScores.end();it++)
		s.insert(std::make_pair(*it,it-intraScores.begin()));

	return {totDist/denom,s};
}

/**
	@brief Funzione newCluster

	Crea un nuovo cluster

	@param cells Vector di samples
	@param indices Vector di interi (indici dei samples da inserire nel cluster)

	@return Puntatore a cluster
**/
cluster* newCluster(std::vector<sample> &cells,std::vector<int> &indices)
{
	cluster* c=new cluster;
	double tm=-1.0;
	std::vector<std::string> strindices;
	std::string id="";
	sort(indices.begin(),indices.end());
	for(std::vector<int>::iterator it=indices.begin();it!=indices.end();it++)
	{
		c->insertDataIntoElements(cells[*it]);
		c->insertDataIntoIndices(*it);
		strindices.push_back(std::to_string(*it));
	}

	c->setTm(tm);
	
	for(std::vector<std::string>::iterator it=strindices.begin();it!=strindices.end();it++)
	{
		id+=*it;
		if(it!=strindices.end()-1)
			id+=',';
	}

	c->setId(id);

	auto [intraSim,intraScore]=intraSimilarity(c,cosineSimilarity);
	//auto [intraSim,intraScore]=intraSimilarity(c,euclideanSimilarity);
	//auto [intraSim,intraScore]=intraSimilarity(c,minkowskiSimilarity);
	//auto [intraSim,intraScore]=intraSimilarity(c,geneExpressed);
	//auto [intraSim,intraScore]=intraDistance(c);
	c->setIntraSim(intraSim);
	c->setIntraScore(intraScore);

	return c;
}

/**
	@brief Funzione splitCluster

	Splitta un cluster in due nuovi cluster

	@param c Puntatore a cluster
	@param cells Vector di samples
	@param ix Vector di interi (indici dei samples da inserire nel primo cluster "figlio")
	@param jx Vector di interi (indici dei samples da inserire nel secondo cluster "figlio")

	@return 2 puntatori a cluster
**/
std::tuple<cluster*,cluster*> splitCluster(cluster* c,std::vector<sample> &cells,std::vector<int> &ix,std::vector<int> &jx)
{
	cluster* split1=newCluster(cells,ix);
	cluster* split2=newCluster(cells,jx);

	//split1->setSplittedWith(c->getSplittedWith());
	//split2->setSplittedWith(c->getSplittedWith());

	//split1->insertDataIntoSplittedWith(split1->getId());
	std::string split2ID=split2->getId();
	split1->insertDataIntoSplittedWith(split2ID);

	std::string split1ID=split1->getId();
	split2->insertDataIntoSplittedWith(split1ID);
	//split2->insertDataIntoSplittedWith(split2->getId());

	return {split1,split2};
}

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
cluster* fuseCluster(cluster* c1,cluster* c2,std::vector<sample> &cells,std::map<int,std::vector<double>> &rhn,double &tm)
{
	std::vector<int> fusedIndices;
	std::string s="";
	fusedIndices.insert(fusedIndices.end(),c1->getIndices().begin(),c1->getIndices().end());
	fusedIndices.insert(fusedIndices.end(),c2->getIndices().begin(),c2->getIndices().end());
	cluster* newClust=newCluster(cells,fusedIndices);

	for(std::set<std::string>::const_iterator it=c1->getSplittedWith().begin();it!=c1->getSplittedWith().end();it++)
	{
		s=*it;
		newClust->insertDataIntoSplittedWith(s);
	}

	for(std::set<std::string>::const_iterator it=c2->getSplittedWith().begin();it!=c2->getSplittedWith().end();it++)
	{
		s=*it;
		newClust->insertDataIntoSplittedWith(s);
	}

	newClust->setRhn(rhn);
	newClust->setTm(tm);

	auto [intraSim,intraScore]=intraSimilarity(newClust,cosineSimilarity);
	//auto [intraSim,intraScore]=intraSimilarity(newClust,euclideanSimilarity);
	//auto [intraSim,intraScore]=intraSimilarity(newClust,minkowskiSimilarity);
	//auto [intraSim,intraScore]=intraSimilarity(newClust,geneExpressed);
	//auto [intraSim,intraScore]=intraDistance(newClust);
	newClust->setIntraSim(intraSim);
	newClust->setIntraScore(intraScore);

	return newClust;
}
