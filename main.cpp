#include "node.h"
#include "math.h"
//#include "vektor.h"
#include <iostream>

void meniu(){//interface'as
    auto startTime = std::chrono::steady_clock::now();

    std::cout<<"Choose your action:"<<std::endl;
    std::cout<<"0 to end the program."<<std::endl;//done
    std::cout<<"1 to create a file."<<std::endl;//done
    std::cout<<"2 to read a file with vector/list/deque."<<std::endl;//done
    std::cout<<"3 to test vector/list/deque with 5 files."<<std::endl;//done
    std::cout<<"4 to test vector/list/deque with 5 files differently(2 holders)."<<std::endl;//done
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

        std::cout<<"How many marks do you want to generate per entry?"<<std::endl;//kiek pazymiu irasas tures
        std::string ge;std::cin>>ge;

        auto saveLaikas = std::chrono::steady_clock::now();
        saveToFile(name+".txt",std::stoi(zmones),std::stoi(ge));
        auto saveLaikas1 = std::chrono::steady_clock::now();
        std::cout<<"Generated file:"<<name+".txt"<<" in "<<std::chrono::duration <double> (saveLaikas1-saveLaikas).count()<<"s."<<std::endl;
        meniu();
    }

    else if(kumis.compare("2")==0){
        std::cout<<"Enter the file you want to open and read."<<std::endl;
        std::string fil;std::cin>>fil;
        if(is_file_exist(fil)==1){
            std::cout<<"Open file using vector, list or deque?[v,l,d]"<<std::endl;
            std::string vedi;std::cin>>vedi;
            if(vedi.compare("v")==0){
                std::vector<node> A;
                readNprint<std::vector<node>>(fil);
                meniu();
            }
            if(vedi.compare("l")==0){
                readNprint<std::list<node>>(fil);
                meniu();
            }
            if(vedi.compare("d")==0){
                readNprint<std::deque<node>>(fil);
                meniu();
            }
            else{
                std::cout<<"Wrong input. Returning to menu."<<std::endl;
                meniu();
            }

        }else{
            std::cout<<"File does not exist!"<<std::endl;meniu();
        }
    }
    else if(kumis.compare("3")==0){
        std::cout<<"Generating files..."<<std::endl;
        //generuos 5 failus su [10^i] irasu
        for(int i=1;i<=5;i++){// ties 5 budavo crash bad_alloc kai reiksmes buvo dedamos i vienetine struktura
            auto Plaikas = std::chrono::steady_clock::now();

            saveToFile("kursiokai"+std::to_string(i)+".txt", pow(10,i),0);//galima prideti laika per kiek sugeneruota
            auto laikas = std::chrono::steady_clock::now();
            std::cout<<"File kursiokai"+std::to_string(i)+".txt generated in "<<std::chrono::duration <double> (laikas-Plaikas).count()<<"s"<<std::endl;
        }
        
        std::cout<<"Vector"<<std::endl;
        testavimas<std::vector<node>>(5);
        std::cout<<"List"<<std::endl;
        testavimas<std::list<node>>(5);
        std::cout<<"Deque"<<std::endl;
        testavimas<std::deque<node>>(5);

        meniu();
    }
    else if(kumis.compare("4")==0){
        std::cout<<"Generating files..."<<std::endl;
        //generuos 5 failus su [10^i] irasu
        for(int i=1;i<=5;i++){// ties 5 budavo crash bad_alloc kai reiksmes buvo dedamos i vienetine struktura
            auto Plaikas = std::chrono::steady_clock::now();

            saveToFile("kursiokai"+std::to_string(i)+".txt", pow(10,i),0);//galima prideti laika per kiek sugeneruota
            auto laikas = std::chrono::steady_clock::now();
            std::cout<<"File kursiokai"+std::to_string(i)+".txt generated in "<<std::chrono::duration <double> (laikas-Plaikas).count()<<"s"<<std::endl;
        }
        
        std::cout<<"Vector"<<std::endl;
        antraStrategija<std::vector<node>>(5);
        std::cout<<"List"<<std::endl;
        antraStrategija<std::list<node>>(5);
        std::cout<<"Deque"<<std::endl;
        antraStrategija<std::deque<node>>(5);

        meniu();

    }
    else{
        std::cout<<"Kuzma raminkis."<<std::endl;
        meniu();
    }
    
}


int main(){
    meniu();
	// std::cout<<"Hello world!"<<std::endl;
	// vektor<int> v;
	// v.push_back(1);
	// v.push_back(2);
	// std::cout<<"begin "<<v.begin()<<std::endl;
	// std::cout<<"end "<<v.end()<<std::endl;
	// std::cout<<"v.back "<<v.back()<<std::endl;
	// v.pop_back();
	// std::cout<<"begin "<<v.begin()<<std::endl;
	// std::cout<<"end "<<v.end()<<std::endl;
	// return 0;
}

