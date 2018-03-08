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

const string failas("kursiokai.txt");
int NdIvedimas=100;//kiek nd bus sugeneruota
int ivedimas=10;//kiek bus asmenu ivedimas<skaic
int skaic=10;//saraso limitas, 10 del grazumo
node *root= new node[skaic];


skaityti(){//skaito duomenis is failo, iraso juos i root
//https://stackoverflow.com/questions/42982633/reading-an-input-file-line-by-line-using-string-stream cia man
ifstream inf;
inf.exceptions ( ifstream::failbit /*| ifstream::badbit*/ );
try{
inf.open(failas.c_str());
string line;
while (getline(inf, line)){
    istringstream S(line);//linija
    vector<string>elementai;//atskiri string
    string temp="";

    while (S>>temp)elementai.push_back(temp);//perziureti veliau del exceptions

    auto dydis= elementai.size();

    for(int i=0;i<skaic;i++){
    root[i].pavarde=elementai[0];
    root[i].vardas=elementai[1];
    int laikinas;
    for(int l=0;l<dydis-3;l++){//pirmi du jau yra
    stringstream(elementai[l+2])>>laikinas;
    root[i].int_vector.push_back(laikinas);
    }
    stringstream(elementai[dydis])>>laikinas;
    root[i].egzas=laikinas;
    }
inf.close();
}
}catch (const ifstream::failure e){cout << "Exception opening/reading file";}
}


spausdinti(){//spausdina root esancius duomenis
for(int i=0;i<skaic;i++){

auto dydis= root[i].int_vector.size();

if(dydis==0)
{
    cout<<"Root tuscias."<<endl;
    return 1;
}
else{
    float Vid=0;int VidSum=0;
    sort(root[i].int_vector.begin(),root[i].int_vector.end());
    for(int k=0;k<NdIvedimas;k++){
        VidSum=VidSum+root[i].int_vector[k];
    }
    Vid=static_cast<float>(VidSum)/static_cast<float>(5);
    float galBalas=0.4*static_cast<float>(Vid) + 0.6*static_cast<float>(root[i].egzas);
    float mediana=0;
if (dydis==1){ mediana=root[i].int_vector[0];}
if(dydis%2==1){//nelyginiu skaiciu mediana
 mediana=root[i].int_vector[dydis/2];
}
else//lyginiu skaiciu mediana
{
mediana=(root[i].int_vector[(dydis/2)-1]+root[i].int_vector[dydis/2])/2;
}

if((root[i].pavarde=="")&&(root[i].vardas=="")){break;}

cout<< setw(15) << root[i].pavarde << setw(15) << root[i].vardas;cout<<setw(5)<<setprecision(3)<<galBalas
<<setw(5)<<setprecision(3)<<mediana<< setw(4) << root[i].egzas <<endl ;
    }}
}

issaugoti(){// iraso i faila esamus root duomenis
    ofstream myfile ( "kursiokai.txt" );
    if (myfile.is_open())
    {
     for(int i=0;i<ivedimas;i++){//kol nera paskutinis root

    myfile << setw(15) << root[i].pavarde << setw(15) << root[i].vardas ;
    for(int k=0;k<NdIvedimas;k++)
    {
    myfile<< setw(5) << root[i].int_vector[k];
    }
    myfile << setw(5) << root[i].egzas <<endl ;

        }
        myfile.close();}
        else cout<<"Cannot open file."<<endl;
}

ivesti()//ivedimas i root
{auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
/*cout<<"Pasirinkite kiek norite kartu ivesti duomenis(nuo 1 iki 100):";
string ivedimass="";cin>>ivedimass;int IN=0;stringstream(ivedimass)>>IN;cout<<"Jusu pasirinktas kiekis:"<<IN<<endl;*/
for(int i=0;i<ivedimas;i++){
/*cout<<"Iveskite savo pavarde:";cin>>root[i].pavarde;
cout<<"Iveskite savo varda:";cin>>root[i].vardas;
cout<<"Iveskite egzamino pazymi:";
string egzas1="";cin>>egzas1;stringstream(egzas1)>>root[i].egzas;cout<<endl;*/
stringstream ss;
ss<<i;
root[i].pavarde=ss.str();

root[i].vardas=ss.str();


/*
cout<<"Jei norite ivertinimus generuoti atsitiktinai spauskite 't'."<<endl;
string symbol="t";
string stringas1="";cin>>stringas1;
if(stringas1.compare(symbol)==0)//random generacija
{
*/

uniform_int_distribution<int> skaicius(1,10);
root[i].egzas=skaicius(mt);
for(int s=0;s<NdIvedimas;s++){

root[i].int_vector.push_back(skaicius(mt));
}
}
/*
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
}*/
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


