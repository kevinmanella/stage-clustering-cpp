#include <bits/stdc++.h>

// Funzione che, dato un vector di double, ne restituisce la mediana
double getMedian(std::vector <double> values)
{
	std::vector <double> tmp=values;

	std::vector <double>::iterator it=tmp.begin();
	while(it!=tmp.end())
	{
		if(*it==0)
			it=tmp.erase(it);
		else
			it++;
	}

	sort(tmp.begin(),tmp.end());

	int middle=tmp.size()/2;

	if(tmp.size()%2==0)
		return (tmp[middle-1]+tmp[middle])/2;

	return tmp[middle];
}
