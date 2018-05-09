#ifndef MATH_H
#define MATH_H

#include <vector>//std::vector
#include <numeric>//std::accumulate
#include <stdexcept>//std::domain_error
#include <fstream>//stream
#include <algorithm>
#include <string>
#include <random>//std::mt19937, std::uniform_int_distribution
#include <chrono>//std::chrono 
#include <iostream>//ostream
#include <iomanip>//std::setprecision, std::setw




/**
 * @brief      skaiciuoja mediana
 *
 * @param      V     paduodamo int vector adresas
 *
 * @return     grazina medianos reiksme
 */
double mediana(std::vector<int>&V){//grazina vektoriaus mediana
    std::sort(V.begin(),V.end());
    auto dydis= V.size();
    if(dydis==0){
        throw std::domain_error("Tuscio vectoriaus medianos nera.");
    }
    return dydis % 2 == 1 ? (V[dydis/2]) : (V[(dydis/2)-1]+V[dydis/2])/2;//po ? pirmas tiesa
}

/**
 * @brief      skaiciuoja vidurki
 *
 * @param      V     paduodamo int vector adresas
 *
 * @return     grazina vidurkio reiksme
 */
double vidurkis(std::vector<int>&V){//grazina vektoriaus vidurki
    auto dydis= V.size();
    if(dydis==0){
        throw std::domain_error("Tuscio vectoriaus vidurkio nera.");
    }
    auto VidSum =std::accumulate(V.begin(), V.end(), 0.0);
    return static_cast<float>(VidSum)/static_cast<float>(dydis);
}

/**
 * @brief      Determines if file exist.
 *
 * @param[in]  fileName  The file name
 *
 * @return     True if file exist, False otherwise.(doxy pats parase, nice)
 */
bool is_file_exist(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}



/**
 * @brief      Saves to file.
 *
 * @param[in]  failas      file name
 * @param[in]  ivedimas    sukuriamu irasu skaicius
 * @param[in]  NdIvedimas  nd skaicius tenkantis irasui
 */
void saveToFile(std::string failas,unsigned int ivedimas,int NdIvedimas){// sukuria [ ivedimas] random reiksmiu ir iraso jas i faila
    std::ofstream myfile (failas);
    if(myfile.is_open()){
        static std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> skc(1,10);
        std::uniform_int_distribution<int> NdSkc(1,10);
        if(NdIvedimas==0){
            NdIvedimas=NdSkc(mt);//kiek nd pazymiu bus sugeneruota
        }
        for(unsigned int i=0;i<ivedimas;i++){//reiksmiu generavimas          
            myfile << std::setw(15) << "pavarde"+std::to_string(i)<< std::setw(15) << "vardas"+std::to_string(i);
                for(unsigned int k=0;k<NdIvedimas;k++){
                    myfile<< std::setw(5) << skc(mt);//Nd pazymiai
                }
                myfile << std::setw(5) << skc(mt) <<std::endl ;//egzas
        }myfile.close();
    }else std::cout<<"Cannot open file."<<std::endl;
}



# endif // MATH_H