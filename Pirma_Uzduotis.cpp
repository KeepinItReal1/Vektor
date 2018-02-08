#include <iostream>
#include <string.h>


using namespace std;
bool Lytis(char j[255]);

void PilnosEilutes(char j[255])
{
    int m = (unsigned)strlen(j);//vardo ilgis
    for (int i=0; i<(m+14);i++)
    {cout<<"*";}
    cout<<"\n";
}

void NepilnosEilutes(char j[255])
{
    int m = (unsigned)strlen(j);
    cout<<"*";
    for(int i=0;i<(m+12);i++)
    {
        cout<<" ";
    }
    cout<<"*"<<endl;
}

void Pasisveikinimas(char j[255])
{
    cout<<"* ";

    if (Lytis(j)==1)
    {
        cout<<"Sveikas, "<<j<<"! *"<<endl;
    }
    else cout<<"Sveika, "<<j<<"!  *"<<endl;

}

bool Lytis(char j[255])//vyr=1
{
    int m = (unsigned)strlen(j);
    char s=s;
    if(j[m-1]==s)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main()
{
cout<<"Type in your name:";
char k[255];
cin>>k;cout<<endl;
PilnosEilutes(k);
NepilnosEilutes(k);
Pasisveikinimas(k);
NepilnosEilutes(k);
PilnosEilutes(k);





}
