#ifndef MANOFUNKCIJOS_H
#define MANOFUNKCIJOS_H



#include <iostream>//ostream
#include <string>//std::string
#include <sstream>//std::stringstream
#include <stdlib.h>//rand
#include <random>//std::mt19937, std::uniform_int_distribution
#include <algorithm>//std::sort
#include <iomanip>//std::setprecision, std::setw
#include <fstream>//stream
#include <chrono>//std::chrono 
#include <stdexcept>//std::domain_error
#include <numeric>//std::accumulate
#include <vector>//std::vector
#include <deque>//std::deque
#include <list>//std::list
#include <math.h>//pow


struct node {
	std::string pavarde;
	std::string vardas;
    std::vector<int> int_vector;
	int egzas;
	double Averag;
	double median;
};


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


template<typename T>void printOnScreen(T&V){//spausdina varda, pavarde, vidurki, mediana, egzamino pazymi
    for(const auto & i:V){
        //reiktu pridet sort kad spausdintu is eiles jei paduos kitoki faila ir kas kur stulpeli
        std::cout<<std::setw(15) << i.pavarde << std::setw(15) << i.vardas;
        std::cout<<std::setw(5)<<std::fixed<<std::setprecision(2)<<static_cast<float>(i.Averag*0.4+0.6*i.egzas)//egzamino paz pagal vidurki
        <<std::setw(5)<<std::fixed<<std::setprecision(2)<<static_cast<float>(i.median*0.4+0.6*i.egzas)//egzamino paz pagal mediana
        << std::setw(4) <<i.egzas <<std::endl;
    }
}

template<typename T>void testavimas(int skc=5){//skaito ir rusiuoja su deque,vector ir list
    const int plotis=10;
    std::cout<<std::setw(plotis)<<std::left<<"Failas "<<std::internal<<"| "<<std::setw(plotis)<<std::right<<"Laikas "<<std::endl;//ar antro setw reikia?

    for(int j=1;j<=skc;j++){
        auto start = std::chrono::steady_clock::now();
        T pagr;
        T lievi;
        T geri;
        readFromFile("kursiokai"+std::to_string(j)+".txt",pagr);//nuskaito, issaugo i pagr

        //rusiavimas
        for(const auto & i:pagr){//kaip ir printOnScreen iteratorius
            if(static_cast<float>(i.Averag*0.4+0.6*i.egzas)>=5.0){
                geri.push_back(i);
            }
            else {lievi.push_back(i);
            }

        }
        std::cout<<"pagr "<<pagr.size()<<std::endl;  
        std::cout<<"lievi "<<lievi.size()<<std::endl;
        std::cout<<"geri "<<geri.size()<<std::endl;
        
 
        auto end = std::chrono::steady_clock::now();
        std::cout<<std::setw(plotis)<<std::left<<"kursiokai"+std::to_string(j)+".txt"<<std::internal<<"| "
        <<std::setw(plotis)<<std::right<<std::chrono::duration <double> (end-start).count()<<std::endl;
    }
}


void saveToFile(std::string failas,unsigned int ivedimas){// sukuria [ ivedimas] random reiksmiu ir iraso jas i faila
    std::ofstream myfile (failas);
    if(myfile.is_open()){
        static std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> skc(1,10);
        std::uniform_int_distribution<int> NdSkc(1,10);
        auto NdIvedimas=NdSkc(mt);//kiek nd pazymiu bus sugeneruota
        node vnt;
        for(unsigned int i=0;i<ivedimas;i++){//reiksmiu generavimas          
            myfile << std::setw(15) << "pavarde"+std::to_string(i)<< std::setw(15) << "vardas"+std::to_string(i);
            for(unsigned int k=0;k<NdIvedimas;k++){
                myfile<< std::setw(5) << skc(mt);//Nd pazymiai
            }
            myfile << std::setw(5) << skc(mt) <<std::endl ;//egzas
        }myfile.close();
    }else std::cout<<"Cannot open file."<<std::endl;
}




void subjectOne(){//interface'as
    std::cout<<"Do you want to generate and compare files automatically ? [y/n]"<<std::endl;
    std::string trash="";std::cin>>trash;
    if(trash.compare("y")==0){

        std::cout<<"Generuojami failai..."<<std::endl;
        //generuos 5 failus su [10^i] irasu
        for(int i=1;i<=5;i++){// ties 5 budavo crash bad_alloc kai reiksmes buvo dedamos i vienetine struktura
            auto Plaikas = std::chrono::steady_clock::now();
            saveToFile("kursiokai"+std::to_string(i)+".txt", pow(10,i));//galima prideti laika per kiek sugeneruota
            auto laikas = std::chrono::steady_clock::now();
            std::cout<<"Failas kursiokai"+std::to_string(i)+".txt sugeneruotas per "<<std::chrono::duration <double> (laikas-Plaikas).count()<<"s"<<std::endl;
        }
        
        testavimas<std::vector<node>>();

        std::terminate();
    }
    else if(trash.compare("n")==0){//leis irasyti i failus paciam
        //kodas
    }else{std::cout<<"Wrong input, exiting."<<std::endl;
        std::terminate();
    }
    
}

template<typename T> void readFromFile(std::string failas, T &konteineris){//skaito duomenis is failo, juos issaugo
std::ifstream inf;
node vnt;
inf.open(failas);
std::string line;
try{
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
            vnt.int_vector.push_back(std::stoi(elementai[l]));// max narys dydis-2
        }
        vnt.egzas=std::stoi(elementai[dydis-1]);
                vnt.Averag=vidurkis(vnt.int_vector);
            vnt.median=mediana(vnt.int_vector);
            
        konteineris.push_back(vnt);
    }
}catch (std::domain_error e){std::cout<<e.what();}
inf.close();
}


#endif // MANOFUNKCIJOS_H




