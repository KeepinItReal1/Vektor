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

using namespace std;

void bubbleSort(int *A, int n);int didinimas( int *A,int skait);

int didinimas( int *A,int skait)
{
size_t added = 10;
int *B=new int[skait+added];
for(int i=0;i<skait;i++){
B[i]=A[i];
}
return *B;
}

void bubbleSort(int *A, int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)

       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
           if (A[j] > A[j+1])
              swap(A[j], A[j+1]);
}

int main(){
string vardas="";string pavarde="";
cout<<"Iveskite savo varda:";cin>>vardas;
cout<<"Iveskite savo pavarde:";cin>>pavarde;
cout<<"Jus esate:"<<vardas<<" "<<pavarde<<endl;

cout<<"Iveskite egzamino pazymi:"<<endl;
int egzas=0;
string egzas1="";
cin>>egzas1;
stringstream(egzas1)>>egzas;
cout<<"Jusu ivestas egzamino ivertinimas:"<<egzas<<endl;

cout<<"Jei norite ivertinimus generuoti atsitiktinai spauskite 't'."<<endl;
string symbol="t";
string stringas1="";cin>>stringas1;
float Vid=0;int VidSum=0;int skait=0;int maks=1;
int *A=new int[1];

if(stringas1.compare(symbol)==0)//random generacija
{
cout<<"Noredami generuoti skaiciu spauskite betkoki klavisa.Noredami baigti spauskite '/' ."<<endl;
string symbo="/";//baigimo simbolis
string stringas="";cin>>stringas;

while (stringas.compare(symbo) !=0){
if(maks<skait+1){*A=didinimas(A,skait);maks=maks+10;}
else{
cin>>stringas;
mt19937 mt(time(NULL));
uniform_int_distribution<int> skaicius(1,10);

A[skait]=skaicius(mt);
VidSum=VidSum+A[skait];
skait=skait+1;
}}
}

else {//pazymiu vedimas rankomis
cout<<"Veskite ivertinimus(neteisingi simboliai nebus imami).Noredami baigti spauskite '/' ."<<endl;
string symbo="/";//baigimo simbolis
string stringas="";

while (stringas.compare(symbo) !=0){
 if(maks<skait+1){*A=didinimas(A,skait);maks=maks+10;}
cin>>stringas;
int result=0;
stringstream(stringas)>>result;

if((result>0)&&(result<=10)){

A[skait]=result;
VidSum=VidSum+A[skait];
skait=skait+1;
}
}
}

bubbleSort(A,skait);//sortas
cout<<"Jusu ivesti pazymiai:"<<endl;
for(int i=0;i<skait;i++){
cout << A[i]<<" ";
}

if(skait%2==1)//nelyginiu skaiciu mediana
{
int mediana=0;
div_t divresult;
divresult = div (skait,2);
mediana=A[(divresult.quot)];
cout<<"\nMediana:"<<mediana;
}
if(skait%2==0)//lyginiu skaiciu mediana
{
float mediana=0;float mediana1=0;
div_t divresult;
divresult = div(skait,2);
mediana1=A[(divresult.quot)-1];
mediana=A[(divresult.quot)];
mediana=(mediana+mediana1)/2;
cout<<"\nMediana:"<<mediana;
}
Vid=VidSum/skait;
float galBalas=0.4*Vid + 0.6*egzas;
cout<<setprecision(3)<<"\nGalBalas="<<galBalas<<endl;
return 0;
}




