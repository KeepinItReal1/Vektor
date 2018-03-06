#ifndef MANOFUNKCIJOS1_H
#define MANOFUNKCIJOS1_H


#include "Mano.h"
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
};

int ivedimas=0;
int skaic=10;//saraso limitas, 10 del grazumo
node *root= new node[skaic];


skaityti(){//skaito duomenis is failo, iraso juos i root
ifstream inf ( "kursiokai.txt" );
for(int i=0;i<skaic;i++){
    int temp=0;
    inf>>root[i].pavarde >>root[i].vardas;
    for(int m=0;m<5;m++)
    {
    inf>>temp;
    root[i].int_vector.push_back(temp);
    }
   inf >> root[i].egzas;}
   inf.close();
}


spausdinti(){//spausdina root esancius duomenis
for(int i=0;i<skaic;i++){//SALYGA KOL NERA TUSCIAS

    float Vid=0;int VidSum=0;
    sort(root[i].int_vector.begin(),root[i].int_vector.end());
    for(int k=0;k<5;k++){
        VidSum=VidSum+root[i].int_vector[k];
    }
    Vid=static_cast<float>(VidSum)/static_cast<float>(5);
    float galBalas=0.4*static_cast<float>(Vid) + 0.6*static_cast<float>(root[i].egzas);

    auto mediana=root[i].int_vector[2];//kadangi 5 skaiciai isrikiuoti visalaik bus vidurinis

    if((root[i].pavarde=="")&&(root[i].vardas=="")){break;}

cout<< setw(15) << root[i].pavarde << setw(15) << root[i].vardas;cout<<setw(5)<<setprecision(3)<<galBalas
<<setw(5)<<setprecision(3)<<mediana<< setw(4) << root[i].egzas <<endl ;
    }
}

issaugoti()// iraso i faila esamus root duomenis
{
    ofstream myfile ( "kursiokai.txt" );
    if (myfile.is_open())
    {
     for(int i=0;i<ivedimas;i++){//kol nera paskutinis root

    myfile << setw(15) << root[i].pavarde << setw(15) << root[i].vardas ;
    for(int k=0;k<5;k++)
    {
    myfile<< setw(4) << root[i].int_vector[k];
    }
    myfile << setw(4) << root[i].egzas <<endl ;



        }
        myfile.close();}
        else cout<<"Cannot open file."<<endl;
}

ivesti()//ivedimas i root
{cout<<"Pasirinkite kiek norite kartu ivesti duomenis(nuo 1 iki 10):";
string ivedimass="";cin>>ivedimass;stringstream(ivedimass)>>ivedimas;cout<<"Jusu pasirinktas kiekis:"<<ivedimas<<endl;
for(int i=0;i<ivedimas;i++){
cout<<"Iveskite savo pavarde:";cin>>root[i].pavarde;
cout<<"Iveskite savo varda:";cin>>root[i].vardas;
cout<<"Iveskite egzamino pazymi:";
string egzas1="";cin>>egzas1;stringstream(egzas1)>>root[i].egzas;cout<<endl;


cout<<"Jei norite ivertinimus generuoti atsitiktinai spauskite 't'."<<endl;
string symbol="t";
string stringas1="";cin>>stringas1;

if(stringas1.compare(symbol)==0)//random generacija
{
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
for(int s=0;s<5;s++){
uniform_int_distribution<int> skaicius(1,10);
root[i].int_vector.push_back(skaicius(mt));
}
}

else{
cout<<"Veskite  5 ivertinimus(neteisingi simboliai nebus imami)."<<endl;
string stringas="";
for(int h=0;h<5;h++){
cin>>stringas;
int result=0;
stringstream(stringas)>>result;
if((result>0)&&(result<=10)){
root[i].int_vector.push_back(result);
}

}
}
}
}



/*
class ManoFunkcijos
{
    public:
void skaityti();//skaito duomenis is failo, iraso juos i root
void spausdinti();//spausdina root esancius duomenis
void issaugoti();// iraso i faila esamus root duomenis
void ivesti();//duomenu ivedimas

    private:
};
*/
#endif // MANOFUNKCIJOS1_H


