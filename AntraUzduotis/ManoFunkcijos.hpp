//#include "ManoFunkcijos.h"

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

struct node {
	std::string pavarde;
	std::string vardas;
    std::vector<int> int_vector;
	int egzas;
	double Averag;
	double median;
};

const int NdIvedimas=rand() % 100 + 10;//kiek nd pazymiu bus sugeneruota

std::vector<node>pagr;
std::deque<node>pagrD;
std::list<node>pagrL;

std::vector<node> vargsiukai;//balas maziau uz 50 % FeelsBadMan
std::vector<node> kietakai;//balas >=50 %

std::deque<node>vargsiukaiD;std::deque<node>kietakaiD;

std::list<node>vargsiukaiL;std::list<node>kietakaiL;

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

int random (int ribaIki, std::default_random_engine &dre)
{
    std::uniform_int_distribution<int> skc(1,ribaIki);
    return skc(dre);
}

void readFromFile(std::string failas="kursiokai.txt"){//skaito duomenis is failo su vektorium, juos issaugo, isrusiuoja pagal vidurki
std::ifstream inf;
node vnt;
inf.open(failas);
std::string line;
while(std::getline(inf, line)){
    std::istringstream S(line);//linija
    std::vector<std::string>elementai;//atskiri string
    std::string temp="";
    while (S>>temp){
        elementai.push_back(temp);
    }
    auto dydis=elementai.size();
    vnt.pavarde=elementai[0];
    vnt.vardas=elementai[1];
    int laikinas;
    for(int l=2;l<dydis-1;l++){//pirmi du jau yra
        std::stringstream(elementai[l])>>laikinas;// max narys dydis-2
        vnt.int_vector.push_back(laikinas);
    }
    vnt.egzas=std::stoi(elementai[dydis-1]);
    try{
        vnt.Averag=vidurkis(vnt.int_vector);
        vnt.median=mediana(vnt.int_vector);
        }catch (std::domain_error e){std::cout<<e.what();}
    pagr.push_back(vnt);
    //rusiavimas
     if(vnt.Averag<5.0){
        vargsiukai.push_back(vnt);
    }
    else {kietakai.push_back(vnt);
    }
}
inf.close();
}


void printOnScreen(std::vector<node>&V){//spausdina nuskaitytus duomenis
for(std::vector<node>::size_type i=0;i!=V.size();++i){
    std::cout<<std::setw(15) << V[i].pavarde << std::setw(15) << V[i].vardas;
    std::cout<<std::setw(5)<<std::fixed<<std::setprecision(2)<<V[i].Averag
    <<std::setw(5)<<std::fixed<<std::setprecision(2)<<V[i].median<< std::setw(4) << V[i].egzas <<std::endl ;
    }
}

void printOnScreen(std::deque<node>&V){//spausdina nuskaitytus duomenis
for(std::vector<node>::size_type i=0;i!=V.size();++i){
    std::cout<<std::setw(15) << V[i].pavarde << std::setw(15) << V[i].vardas;
    std::cout<<std::setw(5)<<std::fixed<<std::setprecision(2)<<V[i].Averag
    <<std::setw(5)<<std::fixed<<std::setprecision(2)<<V[i].median<< std::setw(4) << V[i].egzas <<std::endl ;
    }
}

void printOnScreen(std::list<node>&V){//spausdina nuskaitytus duomenis
for(std::list<node>::const_iterator iterator=V.begin();iterator!=V.end();++iterator){
//size_type i=0;i!=V.size();++i

    std::cout<<std::setw(15) << (*iterator).pavarde << std::setw(15) << (*iterator).vardas;
    std::cout<<std::setw(5)<<std::fixed<<std::setprecision(2)<<(*iterator).Averag
    <<std::setw(5)<<std::fixed<<std::setprecision(2)<<(*iterator).median<< std::setw(4) << (*iterator).egzas <<std::endl ;
    }
}



void saveToFile(std::string failas="kursiokai.txt",unsigned int ivedimas=10){// sukuria [ivedimas] random reiksmiu ir iraso jas i faila
std::ofstream myfile (failas);
if(myfile.is_open()){
    node vnt;
    std::default_random_engine dre (std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    for(int i=0;i<ivedimas;i++){
        vnt.pavarde="vardas"+std::to_string(i);
        vnt.vardas="pavarde"+std::to_string(i);
        vnt.egzas=random(10,mt);
        for(int s=0;s<NdIvedimas;s++){
            vnt.int_vector.push_back(random(10,dre));
        }
        try{
            vnt.Averag=vidurkis(vnt.int_vector);
            vnt.median=mediana(vnt.int_vector);
        }catch (std::domain_error e){std::cout<<e.what();}
        pagr.push_back(vnt);//pagr perkeltas
        }

    if(vnt.Averag<5.0){
        vargsiukai.push_back(vnt);
    }
    else {kietakai.push_back(vnt);
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




void readFromFileDeque(std::string failas="kursiokai.txt"){//panaudojus deque sintakse nesikeicia, reikia template'o
std::ifstream inf;
node vnt;
inf.open(failas);
std::string line;
while(std::getline(inf, line)){
    std::istringstream S(line);//linija
    std::deque<std::string>elementai;//atskiri string
    std::string temp="";
    while (S>>temp){
        elementai.push_back(temp);
    }
    auto dydis=elementai.size();
    vnt.pavarde=elementai[0];
    vnt.vardas=elementai[1];
    int laikinas;
    for(int l=2;l<dydis-1;l++){//pirmi du jau yra
        std::stringstream(elementai[l])>>laikinas;// max narys dydis-2
        vnt.int_vector.push_back(laikinas);
    }
    vnt.egzas=std::stoi(elementai[dydis-1]);
    try{
        vnt.Averag=vidurkis(vnt.int_vector);
        vnt.median=mediana(vnt.int_vector);
        }catch (std::domain_error e){std::cout<<e.what();}
    pagrD.push_back(vnt);
    //rusiavimas
     if(vnt.Averag<5.0){
        vargsiukai.push_back(vnt);
    }
    else {kietakai.push_back(vnt);
    }
}
}

void readFromFileList(std::string failas="kursiokai.txt"){
std::ifstream inf;
node vnt;
inf.open(failas);
std::string line;
while(std::getline(inf, line)){
    std::istringstream S(line);//linija
    std::vector<std::string>elementai;//atskiri string
    std::string temp="";
    while (S>>temp){
        elementai.push_back(temp);
    }
    auto dydis=elementai.size();
    vnt.pavarde=elementai[0];
    vnt.vardas=elementai[1];
    int laikinas;
    for(int l=2;l<dydis-1;l++){//pirmi du jau yra
        std::stringstream(elementai[l])>>laikinas;// max narys dydis-2
        vnt.int_vector.push_back(laikinas);
    }
    vnt.egzas=std::stoi(elementai[dydis-1]);
    try{
        vnt.Averag=vidurkis(vnt.int_vector);
        vnt.median=mediana(vnt.int_vector);
        }catch (std::domain_error e){std::cout<<e.what();}

    pagrL.push_back(vnt);
    //rusiavimas
     if(vnt.Averag<5.0){
        vargsiukaiL.push_back(vnt);
    }
    else {kietakaiL.push_back(vnt);
    }
}


}







