#ifndef MANOFUNKCIJOS_H
#define MANOFUNKCIJOS_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <list>
#include <deque>



struct node {
	std::string pavarde;
	std::string vardas;
    std::vector<int> int_vector;
	int egzas;
	double Averag;
	double median;
};


void readFromFile(std::vector<node>&,std::string failas="kursiokai.txt");//skaito duomenis is failo, juos issaugo
void printOnScreen(std::vector<node>&);//spausdina nuskaitytus duomenis
double diffclock(clock_t,clock_t);//skaiciuoja laika ms tarp clock1 ir clock2
double mediana(std::vector<int>&);//grazina vektoriaus mediana
double vidurkis(std::vector<int>&);//grazina vektoriaus vidurki
void saveToFile(std::vector<node>&,std::vector<node>&,std::vector<node>&,std::string,int);// sukuria [ivedimas] random reiksmiu ir iraso jas i faila
void readFromFileList();
void readFromFileDeque();


#endif // MANOFUNKCIJOS_H
