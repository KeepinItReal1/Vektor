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

using namespace std;

struct node {
	string pavarde;
	string vardas;
    vector<int> int_vector;
	int egzas;
	double Averag;
	double median;
};

string failas("kursiokai.txt");
int NdIvedimas=rand() % 100 + 10;//kiek nd pazymiu bus sugeneruota
int ivedimas=10;//kiek bus sugeneruota asmenu (ivedimas<skaic)

vector<node>pagr;

vector<node> vargsiukai;//balas maziau uz 50 % FeelsBadMan
vector<node> kietakai;//balas >=50 %


void ReadFromFile();//skaito duomenis is failo, juos issaugo
void PrintOnScreen();//spausdina nuskaitytus duomenis
double diffclock(clock_t clock1,clock_t clock2);//skaiciuoja laika ms tarp clock1 ir clock2
double mediana(vector<int>&V);//grazina vektoriaus mediana
double vidurkis(vector<int>&V);//grazina vektoriaus vidurki
void SafeToFile(std::string failas1="kursiokai.txt",int ivedimas=10);// sukuria [ivedimas] random reiksmiu ir iraso jas i faila
#endif // MANOFUNKCIJOS_H
