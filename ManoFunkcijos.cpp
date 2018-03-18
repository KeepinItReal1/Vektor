#include "ManoFunkcijos.h"

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

int NdIvedimas=rand() % 100 + 10;//kiek nd pazymiu bus sugeneruota

vector<node>pagr;

vector<node> vargsiukai;//balas maziau uz 50 % FeelsBadMan
vector<node> kietakai;//balas >=50 %


void ReadFromFile(){//skaito duomenis is failo, juos issaugo
ifstream inf;
node vnt;
inf.open(failas);
string line;
int i=0;
while(getline(inf, line)){
    istringstream S(line);//linija
    vector<string>elementai;//atskiri string
    string temp="";

    while (S>>temp){elementai.push_back(temp);}//perziureti veliau del exceptions
    auto dydis= elementai.size();
    vnt.pavarde=elementai[0];
    vnt.vardas=elementai[1];
    int laikinas;
    for(int l=2;l<dydis-1;l++){//pirmi du jau yra
        stringstream(elementai[l])>>laikinas;// max narys dydis-2
        vnt.int_vector.push_back(laikinas);
    }
    stringstream(elementai[dydis])>>laikinas;
    vnt.egzas=laikinas;
    pagr.push_back(vnt);
    i++;
}
inf.close();
}


void PrintOnScreen(){//spausdina nuskaitytus duomenis
int i=0;
while(pagr[i].size()!=0){
    cout<< setw(15) << pagr[i].pavarde << setw(15) << pagr[i].vardas;cout<<setw(5)<<std::fixed<<setprecision(2)<<pagr[i].Averag
    <<setw(5)<<std::fixed<<setprecision(2)<<pagr[i].median<< setw(4) << pagr[i].egzas <<endl ;
    i++;
    }
}


void SafeToFile(std::string failas1="kursiokai.txt",int ivedimas=10){// sukuria [ivedimas] random reiksmiu ir iraso jas i faila
ofstream myfile (failas1);
if(myfile.is_open()){
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt(seed);
    node vnt;
    for(int i=0;i<ivedimas;i++){
        stringstream ss;
        ss<<i;
        vnt.pavarde="vardas"+ss.str();
        vnt.vardas="pavarde"+ss.str();
        uniform_int_distribution<int> skaicius(1,10);
        vnt.egzas=skaicius(mt);
        for(int s=0;s<NdIvedimas;s++){
            vnt.int_vector.push_back(skaicius(mt));
        }
        try{
            vnt.Averag=vidurkis(vnt.int_vector);
            vnt.median=mediana(vnt.int_vector);
        }catch (std::domain_error e){cout<<e.what();}
    }pagr.push_back(vnt);

    if(vnt.Averag<5.0){
        vargsiukai.push_back(vnt);
    }
    else {//galBalas>=6.0
        kietakai.push_back(vnt);
    }

    for(int i=0;i<ivedimas;i++){
        myfile << setw(15) << pagr[i].pavarde << setw(15) << pagr[i].vardas ;
        for(int k=0;k<NdIvedimas;k++){
            myfile<< setw(5) << pagr[i].int_vector[k];
        }
        myfile << setw(5) << pagr[i].egzas <<endl ;
    }
    myfile.close();
    }else cout<<"Cannot open file."<<endl;
}


double diffclock(clock_t clock1,clock_t clock2)//skaiciuoja laika ms tarp clock1 ir clock2
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

double mediana(vector<int>&V){//grazina vektoriaus mediana
    sort(V.begin(),V.end());
    auto dydis= V.size();
    if(dydis==0){
        throw std::domain_error("Tuscio vectoriaus medianos nera.")
    }
    return dydis % 2 == 1 ? (V[dydis/2]) : (V[(dydis/2)-1]+V[dydis/2])/2;//po ? pirmas tiesa
}

double vidurkis(vector<int>&V){//grazina vektoriaus vidurki
    auto dydis= V.size();
    if(dydis==0){
        throw std::domain_error("Tuscio vectoriaus vidurkio nera.")
    }
    auto VidSum =std::accumulate(V.begin(), V.end(), 0.0);
    return static_cast<float>(VidSum)/static_cast<float>(dydis);
}


