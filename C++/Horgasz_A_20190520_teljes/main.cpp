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
        cout<<"A legtobbet pontyot fogo horgasz: "<<pr.optElem().horgasz<<" Verseny: "<< pr.optElem().verseny << " pontyok szama: " << pr.opt()<<"\n";
    }else{
        cout<<"Nem volt olyan, aki a pontyot fogott volna.\n";
    }
}

void kivalo(const string& file)
{
    sajatEnumerator enor(file);
    linKer pr;
    pr.addEnumerator(&enor);
    pr.run();
    cout<<"Kivalo szint eredmenye:\n";
    if(pr.found())
    {
        cout<<"Volt olyan verseny, ahol nem fogtak pontyot: "<<pr.elem().verseny<<endl;
    }else{
        cout<<"Nem volt olyan verseny, ahol nem fogtak pontyot.\n";
    }
}
