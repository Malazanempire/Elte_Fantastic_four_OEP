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
        //Input fajl megnyitas
        if(argc==2)
        {
            file=argv[1];
        }else{
            cout<<"Kerem a fajl nevet:"; cin>>file;
        }
        megfelelt(file);
    }catch(SeqInFileEnumerator<sor>::Exceptions err)
    {
        if(err==SeqInFileEnumerator<sor>::OPEN_ERROR)
        {
            cout<<file<<" nem elerheto!\n";
        }
    }
    return 0;
}

void megfelelt(const string& file)
{
    SeqInFileEnumerator<sor> enor(file);
    LinKer pr;
    pr.addEnumerator(&enor);
    pr.run();
    cout<<"Megfelelt szint eredmenye:\n";
    if(pr.found())
    {
        cout<<"Az elso versenyzo, aki megfelel a feltetelnek:" << pr.elem().nev << endl;
    }else{
        cout<<"Nem volt olyan versenyzo, aki a felteteleknek megfelelt.\n";
    }
}

