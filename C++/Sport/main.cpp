#include <iostream>
#include <fstream>
#include "osztalyok.h"
#include "library/seqinfileenumerator.hpp"

using namespace std;

void megfelelt(const string& file);
void kivalo(const string& file);

int main(int argc, char* argv[])
{
    string file;
    try{
        if(argc==2){
            file=argv[1];
;        }else{
            cout<<"Kerem a fajl nevet:"; cin>>file;
        }
        megfelelt(file);
        kivalo(file);
    }catch(SeqInFileEnumerator<sor>::Exceptions err)
    {
        if(err==SeqInFileEnumerator<sor>::OPEN_ERROR)
        {
            cout<<file<<" A file nem nyithato meg!\n";
        }
    }
    return 0;
}

void megfelelt(const string& file)
{
    SeqInFileEnumerator<sor> enor(file);
    Maxker pr;
    pr.addEnumerator(&enor);
    pr.run();
    cout<<"Megfelelt szint eredmenye:\n";
    if(pr.found())
    {
        if(pr.opt()!=0){
            cout<<"A legtobb ermes: "<<pr.optElem().nev<<" indult: "<< pr.optElem().indult << " ermek szama: " << pr.opt()<<"\n";
        }else{
            cout<<"Senki sem szerzett ermet."<<endl;
        }
    }else{
        cout<<"Nem volt olyan, akinek lenne erme a legalabb harom eremmel indulok kozul.\n";
    }
}

void kivalo(const string& file)
{
    sajatEnumerator enor(file);
    Maxker_ pr;
    pr.addEnumerator(&enor);
    pr.run();
    cout<<"Kivalo szint eredmenye:\n";
    if(pr.found())
    {
        cout<<pr.optElem().arany<<"\n";
        if(pr.optElem().arany!=0.00){
            cout<<"Aranyaiban nyertres iskola: "<<pr.optElem().suli<< " ermek szama: " <<pr.optElem().ermek <<endl;
        }else{
            cout<<"Egy iskola sem szerzett ermet."<<endl;
        }
    }else{
        cout<<"Nem volt adat.\n";
    }
}
