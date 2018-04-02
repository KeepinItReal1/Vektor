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
#include <sstream>//stringstream


struct node {
	std::string pavarde;
	std::string vardas;
    std::vector<int> int_vector;
	int egzas;
	double Averag;
	double median;
};

struct vektoriui {std::vector<int>vektorius;};


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

template<typename T> void plius(T &vedimas,std::string Vpavarde, std::string Vvardas,int Vegzas, std::vector<int> Ved){//prideda struktura prie duomenu laikiklio
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
        
        auto end = std::chrono::steady_clock::now();
        std::cout<<std::setw(plotis)<<std::left<<"kursiokai"+std::to_string(j)+".txt"<<std::internal<<"| "
        <<std::setw(plotis)<<std::right<<std::chrono::duration <double> (end-start).count()<<"s"<<std::endl;
    }
}


void saveToFile(std::string failas,unsigned int ivedimas, vektoriui L,int NdIvedimas){// sukuria [ ivedimas] random reiksmiu ir iraso jas i faila
    std::ofstream myfile (failas);
    if(myfile.is_open()){
        static std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> skc(1,10);
        std::uniform_int_distribution<int> NdSkc(1,10);
        if(NdIvedimas==0){
            NdIvedimas=NdSkc(mt);//kiek nd pazymiu bus sugeneruota
        }
        node vnt;
        for(unsigned int i=0;i<ivedimas;i++){//reiksmiu generavimas          
            myfile << std::setw(15) << "pavarde"+std::to_string(i)<< std::setw(15) << "vardas"+std::to_string(i);
                for(unsigned int k=0;k<NdIvedimas;k++){
                    myfile<< std::setw(5) << skc(mt);//Nd pazymiai
                }

            if(L.vektorius.size()!=0){//jei ivestas norimas pazymys
                myfile << std::setw(5) << L.vektorius.back() <<std::endl ;//egzas
                L.vektorius.pop_back();
            }else{
                myfile << std::setw(5) << skc(mt) <<std::endl ;//egzas
            }
        }myfile.close();
    }else std::cout<<"Cannot open file."<<std::endl;
}


void saveToFilePersonal(std::string failas,unsigned int ivedimas, vektoriui T,std::vector<vektoriui>L){// [ivedimas] reiksmiu, T egzamino paz,L nd paz
    std::ofstream myfile (failas);
    if(myfile.is_open()){
        static std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> skc(1,10);
        node vnt;
        for(unsigned int i=0;i<ivedimas;i++){//reiksmiu generavimas          
            myfile << std::setw(15) << "pavarde"+std::to_string(i)<< std::setw(15) << "vardas"+std::to_string(i);

            while(!L[i].vektorius.empty()){
                 myfile<< std::setw(5) << L[i].vektorius.back();//Nd pazymiai
                L[i].vektorius.pop_back();
            }

            if(T.vektorius.size()!=0){//jei ivestas norimas pazymys
                myfile << std::setw(5) << T.vektorius.back() <<std::endl ;//egzas
                T.vektorius.pop_back();
            }else{
                myfile << std::setw(5) << skc(mt) <<std::endl ;//egzas
            }
        }myfile.close();
    }else std::cout<<"Cannot open file."<<std::endl;
}



void subjectOne(){//interface'as
    auto startTime = std::chrono::steady_clock::now();

    std::cout<<"Choose your action:"<<std::endl;
    std::cout<<"0 to end the program."<<std::endl;//done
    std::cout<<"1 to create a file."<<std::endl;
    std::cout<<"2 to read a file with vector/list/deque."<<std::endl;
    std::cout<<"3 to test vector/list/deque with 5 files."<<std::endl;//done
    std::cout<<"4 to test vector/list/deque with 5 files differently(2 holders)."<<std::endl;
    std::string kumis="";std::cin>>kumis;
    if(kumis.compare("0")==0){
        std::cout<<"The end."<<std::endl;
        auto endTime = std::chrono::steady_clock::now();
        std::cout<<"The program lasted:"<<std::chrono::duration <double> (endTime-startTime).count()<<"s."<<std::endl;
    }


    else if(kumis.compare("1")==0){
        std::cout<<"Type in the chosen name for the file:"<<std::endl;//failo vardas
        std::string name;std::cin>>name;

        std::cout<<"How many entries do you want to create?"<<std::endl;//kiek irasu bus faile
        std::string zmones;std::cin>>zmones;

        std::cout<<"Do you want to generate marks randomly? [y/n]"<<std::endl;
        std::string genMarks;std::cin>>genMarks;

        if(genMarks.compare("y")==0){//generuos pazymius
            std::cout<<"How many marks do you want to generate?"<<std::endl;//kiek pazymiu irasas tures
            std::string ge;std::cin>>ge;
            std::cout<<"Do you want to generate the exam mark too? [y/n]"<<std::endl;
            std::string ge1;std::cin>>ge1;
            if(ge1.compare("y")==0){//generuos ir egzamina
                auto saveLaikas = std::chrono::steady_clock::now();
                vektoriui tuscias;
                saveToFile(name+".txt",std::stoi(zmones),tuscias,std::stoi(ge));
                auto saveLaikas1 = std::chrono::steady_clock::now();
                std::cout<<"Generated file:"<<name+".txt"<<" in "<<std::chrono::duration <double> (saveLaikas1-saveLaikas).count()<<"s."<<std::endl;
                subjectOne();
            }
            if(ge1.compare("n")==0){//leis ivest egzamina
                vektoriui v;//egzamino pazymiai v.vektorius
                while(v.vektorius.size()!=std::stoi(zmones)){
                    std::cout<<"Type in the exam mark:"<<std::endl;
                    std::string vesk;std::cin>>vesk;
                    int temp;std::stringstream(vesk)>>temp;

                    if((temp<=10) && (temp>0)){v.vektorius.push_back(temp);}
                }
                auto saveLaikas = std::chrono::steady_clock::now();
                saveToFile(name+".txt",std::stoi(zmones),v,std::stoi(ge));

                auto saveLaikas1 = std::chrono::steady_clock::now();
                std::cout<<"Generated file:"<<name+".txt"<<" in "<<std::chrono::duration <double> (saveLaikas1-saveLaikas).count()<<"s."<<std::endl;
                subjectOne();
            }else{std::cout<<"Typing in wrong here?Really?"<<std::endl;subjectOne();}
        }





        else if(genMarks.compare("n")==0){//leis pazymius vest vartotojui
            std::cout<<"Do you want to generate the exam mark? [y/n]"<<std::endl;
            std::string ge1;std::cin>>ge1;

            if(ge1.compare("y")==0){//generuos egzamina
                std::vector <vektoriui> L;
                vektoriui v;
                for(int i=0;i<std::stoi(zmones);i++){
                    std::string vesk="";
                    std::cout<<"Type in the marks, type '/' to end. Wrong symbols will be ignored."<<std::endl;
                    while(vesk.compare("/")!=0){
                        std::cin>>vesk;int temp;
                        std::stringstream(vesk)>>temp;
                        if((temp<=10) && (temp>0)){
                            v.vektorius.push_back(std::stoi(vesk));
                        }
                    }L.push_back(v);
                }
                vektoriui tuscias;
                auto saveLaikas = std::chrono::steady_clock::now();

                saveToFilePersonal(name+".txt",std::stoi(zmones),tuscias,L);

                auto saveLaikas1 = std::chrono::steady_clock::now();
                std::cout<<"Generated file:"<<name+".txt"<<" in "<<std::chrono::duration <double> (saveLaikas1-saveLaikas).count()<<"s."<<std::endl;
                subjectOne();
            }

            if(ge1.compare("n")==0){//leis ivest egzamina


                vektoriui v;
                while(v.vektorius.size()!=std::stoi(zmones)){
                    std::cout<<"Type in the exam mark:"<<std::endl;
                    std::string vesk;std::cin>>vesk;
                    int temp;std::stringstream(vesk)>>temp;

                    if((temp<=10) && (temp>0)){v.vektorius.push_back(temp);}
                }

                std::deque<vektoriui>L;
                vektoriui m;
                for(int i=0;i<std::stoi(zmones);i++){
                    std::string vesk="";
                    std::cout<<"Type in the marks, type '/' to end. Wrong symbols will be ignored."<<std::endl;
                    while(vesk.compare("/")!=0){
                        std::cin>>vesk;int temp;
                        std::stringstream(vesk)>>temp;
                        if((temp<=10) && (temp>0)){
                            m.vektorius.push_back(std::stoi(vesk));
                        }
                    }L.push_front(m);
                }


                //saveToFilePersonal(name+".txt",std::stoi(zmones),std::stoi(egzPaz),L);
                subjectOne();

            }
            else{
                std::cout<<"Wrong input returning to menu."<<std::endl;subjectOne();
            }


        }
        else{std::cout<<"Goddamit type correctly."<<std::endl;
            subjectOne();
        }
    }



    else if(kumis.compare("2")==0){

    }
    else if(kumis.compare("3")==0){
        std::cout<<"Generating files..."<<std::endl;
        //generuos 5 failus su [10^i] irasu
        for(int i=1;i<=5;i++){// ties 5 budavo crash bad_alloc kai reiksmes buvo dedamos i vienetine struktura
            auto Plaikas = std::chrono::steady_clock::now();
            vektoriui tuscias;
            saveToFile("kursiokai"+std::to_string(i)+".txt", pow(10,i),tuscias,0);//galima prideti laika per kiek sugeneruota
            auto laikas = std::chrono::steady_clock::now();
            std::cout<<"File kursiokai"+std::to_string(i)+".txt generated in "<<std::chrono::duration <double> (laikas-Plaikas).count()<<"s"<<std::endl;
        }
        
        std::cout<<"Vector"<<std::endl;
        testavimas<std::vector<node>>();
        std::cout<<"List"<<std::endl;
        testavimas<std::list<node>>();
        std::cout<<"Deque"<<std::endl;
        testavimas<std::deque<node>>();

        subjectOne();
    }
    else if(kumis.compare("4")==0){

    }
    else{
        std::cout<<"Kuzma raminkis."<<std::endl;
        subjectOne();
    }
    
}

template<typename T> void readFromFile(std::string failas, T &konteineris){//skaito duomenis is failo, juos issaugo
std::ifstream inf;
    // node vnt;
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
        // vnt.pavarde=elementai[0];// trunka daug ilgiau, kodel?
        // vnt.vardas=elementai[1];
        std::vector<int> paz;
        int laikinas;
        for(int l=2;l<dydis-1;l++){//pirmi du jau yra
            paz.push_back(std::stoi(elementai[l]));// max narys dydis-2
        }
        // vnt.egzas=std::stoi(elementai[dydis-1]);
        // vnt.Averag=vidurkis(vnt.int_vector);
        // vnt.median=mediana(vnt.int_vector);
        plius(konteineris,elementai[0],elementai[1],std::stoi(elementai[dydis-1]),paz);
        // konteineris.push_back(vnt);
    }
inf.close();
}


#endif // MANOFUNKCIJOS_H




