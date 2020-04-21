// Contiene le dichiarazioni delle due funzioni che leggono i dati dal file CSV e creano la struttura dati
#ifndef IMPORTCSV_H
#define IMPORTCSV_H

std::vector <sample> buildSamplesFromCSV(std::string filePath);

std::map<std::string, int> buildNameToIndexFromCSV(std::string filePath);

#endif
