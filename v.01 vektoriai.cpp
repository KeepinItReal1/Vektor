#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <chrono>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
string vardas="";string pavarde="";
cout<<"Iveskite savo varda:";cin>>vardas;
cout<<"Iveskite savo pavarde:";cin>>pavarde;
cout<<"Jus esate:"<<vardas<<" "<<pavarde<<endl;

cout<<"Iveskite egzamino pazymi:"<<endl;
int egzas=0;string egzas1="";cin>>egzas1;stringstream(egzas1)>>egzas;cout<<"Jusu ivestas egzamino ivertinimas:"<<egzas<<endl;

cout<<"Jei norite ivertinimus generuoti atsitiktinai spauskite 't'."<<endl;
string symbol="t";
string stringas1="";cin>>stringas1;
float Vid=0;int VidSum=0;int skait=0;
vector<int> int_vector;

if(stringas1.compare(symbol)==0)//random generacija
{
cout<<"Noredami generuoti skaiciu spauskite betkoki klavisa.Noredami baigti spauskite '/' ."<<endl;
string symbo="/";//baigimo simbolis
string stringas="";cin>>stringas;

while (stringas.compare(symbo) !=0){
cin>>stringas;
mt19937 mt(time(NULL));
uniform_int_distribution<int> skaicius(1,10);
int_vector.push_back(skaicius(mt));
VidSum=VidSum+int_vector[skait];
skait=skait+1;
}
}

else {//pazymiu vedimas
cout<<"Veskite ivertinimus(neteisingi simboliai nebus imami).Noredami baigti spauskite '/' ."<<endl;
string symbo="/";//baigimo simbolis
string stringas="";

while (stringas.compare(symbo) !=0){
cin>>stringas;
int result=0;
stringstream(stringas)>>result;
if((result>0)&&(result<=10)){
int_vector.push_back(result);
skait=skait+1;
VidSum=VidSum+int_vector[skait];
}
}
}

sort(int_vector.begin(),int_vector.end());
cout<<"Jusu ivesti pazymiai:"<<endl;
for(int i=0;i<skait;i++){
cout << int_vector[i]<<" ";
}

if(skait%2==1)//nelyginiu skaiciu mediana
{
int mediana=0;
div_t divresult;
divresult = div (skait,2);
mediana=int_vector[(divresult.quot)];
cout<<"\nMediana:"<<mediana;
}
if(skait%2==0)//lyginiu skaiciu mediana
{
float mediana=0;float mediana1=0;
div_t divresult;
divresult = div(skait,2);
mediana1=int_vector[(divresult.quot)-1];
mediana=int_vector[(divresult.quot)];
mediana=(mediana+mediana1)/2;
cout<<"\nMediana:"<<mediana;
}
Vid=VidSum/skait;
float galBalas=0.4*Vid+0.6*egzas;
cout.precision(3);
cout<<"\nGalBalas="<<galBalas<<endl;

return 0;
}
