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
#include<numeric>
#include <list>
#include <deque>



const int NdIvedimas=rand() % 100 + 10;//kiek nd pazymiu bus sugeneruota


void readFromFile(std::vector<node>&pagr,std::string failas){//skaito duomenis is failo, juos issaugo//dar reik rusiavimo su vidurkiu
std::ifstream inf;
node vnt;
inf.open(failas);
std::string line;
int i=0;
while(std::getline(inf, line)){
    std::istringstream S(line);//linija
    std::vector<std::string>elementai;//atskiri string
    std::string temp="";

    while (S>>temp){elementai.push_back(temp);}//perziureti veliau del exceptions
    auto dydis= elementai.size();
    vnt.pavarde=elementai[0];
    vnt.vardas=elementai[1];
    int laikinas;
    for(int l=2;l<dydis-1;l++){//pirmi du jau yra
        std::stringstream(elementai[l])>>laikinas;// max narys dydis-2
        vnt.int_vector.push_back(laikinas);
    }
    std::stringstream(elementai[dydis])>>laikinas;
    vnt.egzas=laikinas;
    pagr.push_back(vnt);
    i++;
}
inf.close();
}


void printOnScreen(std::vector<node>&pagr){//spausdina nuskaitytus duomenis
for(std::vector<node>::size_type i=0;i!=pagr.size()-1;i++){
    std::cout<<std::setw(15) << pagr[i].pavarde << std::setw(15) << pagr[i].vardas;
    std::cout<<std::setw(5)<<std::fixed<<std::setprecision(2)<<pagr[i].Averag
    <<std::setw(5)<<std::fixed<<std::setprecision(2)<<pagr[i].median<< std::setw(4) << pagr[i].egzas <<std::endl ;
    }
}


void saveToFile(std::vector<node>&pagr,std::vector<node>&vargsiukai,std::vector<node>&kietakai,std::string failas="kursiokai.txt",int ivedimas=10){// sukuria [ivedimas] random reiksmiu ir iraso jas i faila
std::ofstream myfile (failas);
if(myfile.is_open()){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);
    node vnt;
    for(int i=0;i<ivedimas;i++){
        vnt.pavarde="vardas"+std::to_string(i);
        vnt.vardas="pavarde"+std::to_string(i);
        std::uniform_int_distribution<int> skaicius(1,10);
        vnt.egzas=skaicius(mt);
        for(int s=0;s<NdIvedimas;s++){
            vnt.int_vector.push_back(skaicius(mt));
        }
        try{
            vnt.Averag=vidurkis(vnt.int_vector);
            vnt.median=mediana(vnt.int_vector);
        }catch (std::domain_error e){std::cout<<e.what();}
    }pagr.push_back(vnt);

    if(vnt.Averag<5.0){
        vargsiukai.push_back(vnt);
    }
    else {//galBalas>=6.0
        kietakai.push_back(vnt);
    }

    for(int i=0;i<ivedimas;i++){
        myfile << std::setw(15) << pagr[i].pavarde << std::setw(15) << pagr[i].vardas ;
        for(int k=0;k<NdIvedimas;k++){
            myfile<< std::setw(5) << pagr[i].int_vector[k];
        }
        myfile << std::setw(5) << pagr[i].egzas <<std::endl ;
    }
    myfile.close();
    }else std::cout<<"Cannot open file."<<std::endl;
}


double diffclock(clock_t clock1,clock_t clock2)//skaiciuoja laika ms tarp clock1 ir clock2
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

double mediana(std::vector<int>&V){//grazina vektoriaus mediana
    std::sort(V.begin(),V.end());
    auto dydis= V.size();
    if(dydis==0){
        throw std::domain_error("Tuscio vectoriaus medianos nera.");
    }
    return dydis % 2 == 1 ? (V[dydis/2]) : (V[(dydis/2)-1]+V[dydis/2])/2;//po ? pirmas tiesa
}

double vidurkis(std::vector<int>&V){//grazina vektoriaus vidurki
    auto dydis= V.size();
    if(dydis==0){
        throw std::domain_error("Tuscio vectoriaus vidurkio nera.");
    }
    auto VidSum =std::accumulate(V.begin(), V.end(), 0.0);
    return static_cast<float>(VidSum)/static_cast<float>(dydis);
}

void readFromFileList(){



}

void readFromFileDeque(){

}




