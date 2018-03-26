#ifndef MANOFUNKCIJOS_H
#define MANOFUNKCIJOS_H



#include <iostream>//ostream
#include <string>//std::string
#include <sstream>//std::stringstream
#include <stdlib.h>//rand
#include <random>//std::mt19937, std::uniform_int_distribution
//#include <time.h>//?
//#include <functional> //?
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

// double timing(,){
// return std::chrono::duration <double> (end-start).count();//grazins laika s
// }



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


template<typename T>void printOnScreen(T&V){
    for(const auto & i:V){
        //reiktu pridet sort kad spausdintu is eiles jei paduos kitoki faila
        i.Averag=vidurkis(i.int_vector);
        i.median=mediana(i.int_vector);
        std::cout<<std::setw(15) << i.pavarde << std::setw(15) << i.vardas;
        std::cout<<std::setw(5)<<std::fixed<<std::setprecision(2)<<i.Averag
        <<std::setw(5)<<std::fixed<<std::setprecision(2)<<i.median<< std::setw(4) <<i.egzas <<std::endl ;
    }
}


void saveToFile(std::string failas,unsigned int ivedimas){// sukuria [ ivedimas] random reiksmiu ir iraso jas i faila
    std::ofstream myfile (failas);
    if(myfile.is_open()){
        static std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> skc(1,10);
        std::uniform_int_distribution<int> NdSkc(10,100);
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
    if(trash.compare("y")==0){//generuos 5 failus su [10^i] irasu
        saveToFile("kursiokai.txt", pow(10,1));
        for(int i=2;i<=4;i++){//vietoj 4 turi buti 5, ties 5 crash bad_alloc
            std::cout<<i<<std::endl;
            saveToFile("kursiokai"+std::to_string(i)+".txt", pow(10,i));
            // auto start= std::chrono::steady_clock::now();
            // //lyginimas su template'ais
            // auto end= std::chrono::steady_clock::now();
            // std::cout<<timing(start,end);//grazins laika s
        }std::cout<<6<<std::endl;
        std::terminate();
    }
    else if(trash.compare("n")==0){//leis irasyti i failus paciam
        //kodas
    }
    else{std::cout<<"Wrong input, exiting."<<std::endl;
        std::terminate();
    }
}


#endif // MANOFUNKCIJOS_H
