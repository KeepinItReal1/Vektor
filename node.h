#ifndef NODE_H
#define NODE_H

#include "math.h"

#include <iostream>//ostream
#include <string>//std::string
#include <sstream>//std::stringstream
#include <algorithm>//std::sort, std::partition
#include <iomanip>//std::setprecision, std::setw
#include <fstream>//stream
#include <chrono>//std::chrono 
#include <stdexcept>//std::domain_error
#include <vector>//std::vector
#include <deque>//std::deque
#include <list>//std::list


class node{

	public:
		template<typename T> friend void readNprint(std::string fileName);//skaito ir spausdina
		template<typename T> friend void printOnScreen(T&V);//spausdina varda, pavarde, vidurki, mediana, egzamino pazymi
		template<typename T> friend void testavimas(int skc);//skaito ir rusiuoja su deque,vector ir list
		template<typename T> friend void antraStrategija(int skc);//skaito ir rusiuoja su deque,vector ir list
		template<typename T> friend void readFromFile(std::string failas, T &konteineris);//skaito duomenis is failo, juos issaugo
		//sett'ers
		template<typename T> friend void plius(T &vedimas,std::string Vpavarde, std::string Vvardas,int Vegzas, std::vector<int> Ved);//prideda struktura prie duomenu laikiklio
        //operatoriai lygina paduotu nariu vidurkius, grazina 1 jei true
        template<typename T> friend bool operator>(T&V,T&V2);
        template<typename T> friend bool operator<(T&V,T&V2);
		//gett'ers
		inline std::string getLastName() const{return pavarde;};
		inline std::string getName() const{return vardas;};
		inline std::vector<int> getVector() const{return int_vector;};
		inline unsigned int getEgzas() const{return egzas;};
		inline double getAverag() const{return Averag;};
		inline double getMedian() const{return median;};
	private:
		std::string pavarde;
		std::string vardas;
	    std::vector<int> int_vector;
		int egzas;
		double Averag;
		double median;

};

        template<typename T> bool operator>(T&V,T&V2){
            if(V.Averag>V2.Averag){return 1;}
            else return 0;
        }
        template<typename T> bool operator<(T&V,T&V2){
            if(V.Averag<V2.Averag){return 1;}
            else return 0;
        }



/**
 * @brief      Prideda 1 studento irasa
 *
 * @param      vedimas   konteineris, i kuri rasys nauja irasa
 * @param[in]  Vpavarde  iraso pavarde
 * @param[in]  Vvardas   iraso vardas
 * @param[in]  Vegzas    iraso egzamino ivertinimas
 * @param[in]  Ved       int vector su ND ivertinimais
 *
 * @tparam     T         { template'as }
 */
template<typename T> 
void plius(T &vedimas,std::string Vpavarde, std::string Vvardas,int Vegzas, std::vector<int> Ved){//prideda struktura prie duomenu laikiklio
    node vnt;
    vnt.pavarde = Vpavarde;
    vnt.vardas = Vvardas;
    vnt.egzas = Vegzas;
    vnt.int_vector = Ved;
    try{
        vnt.Averag = vidurkis(Ved);
        vnt.median = mediana(Ved);
    }catch (std::domain_error e){std::cout<<e.what();}
    vedimas.push_back(vnt);
}


/**
 * @brief      reads from file and prints it on screen
 *
 * @param[in]  fileName  The file name
 *
 * @tparam     T         { template }
 */
template<typename T>
void readNprint(std::string fileName){//skaito ir spausdina
    T pagr;
    readFromFile(fileName,pagr);
    printOnScreen(pagr);
}



/**
 * @brief      spausdina ant ekrano
 *
 * @param      V     spausdinamo konteineriis
 *
 * @tparam     T     template'as
 */
template<typename T>
void printOnScreen(T&V){//spausdina varda, pavarde, vidurki, mediana, egzamino pazymi
std::cout<<std::setw(15) << "pavarde" << std::setw(15) << "vardas";
std::cout<<std::setw(5)<<"vid"//egzamino paz pagal vidurki
<<std::setw(5)<<"med"//egzamino paz pagal mediana
<< std::setw(4) <<"egz" <<std::endl;

    for(const auto & i:V){
        //reiktu pridet sort kad spausdintu is eiles jei paduos kitoki faila ir kas kur stulpeli
        std::cout<<std::setw(15) << i.getLastName() << std::setw(15) << i.getName();
        std::cout<<std::setw(5)<<std::fixed<<std::setprecision(2)<<static_cast<float>(i.getAverag()*0.4+0.6*i.getEgzas())//egzamino paz pagal vidurki
        <<std::setw(5)<<std::fixed<<std::setprecision(2)<<static_cast<float>(i.getMedian()*0.4+0.6*i.getEgzas())//egzamino paz pagal mediana
        << std::setw(4) <<i.getEgzas() <<std::endl;
    }
}


/**
 * @brief      pirma testavimo strategija
 *
 * @param[in]  skc   nuskaitomu failu skaicius
 *
 * @tparam     T     { template'as }
 */
template<typename T>
void testavimas(int skc){//skaito ir rusiuoja su deque,vector ir list
    const int plotis=14;
    std::cout<<std::setw(plotis)<<std::left<<"File "<<std::internal<<"| "<<std::setw(plotis)<<std::right<<"Time "<<std::endl;//ar antro setw reikia?

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
        
        auto end = std::chrono::steady_clock::now();
        std::cout<<std::setw(plotis)<<std::left<<"kursiokai"+std::to_string(j)+".txt"<<std::internal<<"| "
        <<std::setw(plotis)<<std::right<<std::chrono::duration <double> (end-start).count()<<"s"<<std::endl;
    }
}


/**
 * @brief      antra rusiavimo strategija
 *
 * @param[in]  skc   failu skaicius
 *
 * @tparam     T     template'as
 */
template<typename T>
void antraStrategija(int skc){//skaito ir rusiuoja su deque,vector ir list
    const int plotis=14;
    std::cout<<std::setw(plotis)<<std::left<<"File "<<std::internal<<"| "<<std::setw(plotis)<<std::right<<"Time "<<std::endl;//ar antro setw reikia?

    for(int j=1;j<=skc;j++){
        auto start = std::chrono::steady_clock::now();
        T pagr;
        T lievi;
        readFromFile("kursiokai"+std::to_string(j)+".txt",pagr);//nuskaito, issaugo i pagr

        for(auto k : pagr){
            if(static_cast<float>(k.Averag*0.4+0.6*k.egzas)<5.0){
                lievi.push_back(k);
                remove_if(pagr.begin(),pagr.end(),[](node &V){return (V.Averag*0.4+0.6*V.egzas)<5.0;});
            }
        }

        auto end = std::chrono::steady_clock::now();
        std::cout<<std::setw(plotis)<<std::left<<"kursiokai"+std::to_string(j)+".txt"<<std::internal<<"| "
        <<std::setw(plotis)<<std::right<<std::chrono::duration <double> (end-start).count()<<"s"<<std::endl;
    }
}




/**
 * @brief      Reads a from file.
 *
 * @param[in]  failas       failo pavadinimas
 * @param      konteineris  naudojamo konteinerio adresas
 *
 * @tparam     T            template'as
 */
template<typename T> 
void readFromFile(std::string failas, T &konteineris){//skaito duomenis is failo, juos issaugo
	std::ifstream inf;
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

        std::vector<int> paz;
        int laikinas;
        for(int l=2;l<dydis-1;l++){//pirmi du jau yra
            paz.push_back(std::stoi(elementai[l]));// max narys dydis-2
        }
        plius(konteineris,elementai[0],elementai[1],std::stoi(elementai[dydis-1]),paz);
    }
inf.close();
}




#endif //NODE_H
