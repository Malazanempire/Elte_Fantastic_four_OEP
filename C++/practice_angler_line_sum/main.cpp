#include <iostream>
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
#include "../library/counting.hpp"



 using namespace std;


struct Horgasz
{
    string name;
    bool fogott;
};

//Ezen keresztül
struct Szamol
{
    string faj;
    int meret;
};
//EXTRA
istream& operator>>(istream& inp, Szamol &s)
{
    return inp>>s.faj>>s.meret;
}

//Tétel végrehajtása a köztes struct-on
class CuntHal : public Summation<Szamol, bool>
{
protected:
    bool neutral() const override {return false;};
    bool func(const Szamol& e) const override { return e.faj == "balna";};
    bool add( const bool& a, const bool& b) const override {return a || b;};
    bool cond(const Szamol& e) const override {return true;};
};

//Beolvasás
istream& operator>>(istream& inp, Horgasz &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s.name;



    CuntHal pr;
    StringStreamEnumerator<Szamol> enor(is);
    pr.addEnumerator(&enor);
    pr.run();
    s.fogott = pr.result();
    return inp;
}

//Progtétel szükség esetén, mainbe
class Balna : public LinSearch<Horgasz, false>
{
protected:
    bool cond(const Horgasz& e) const override {return e.fogott;}
};

int main(int argc, char* argv[])
{
    string fname = argc>1 ? argv[1] : "input.txt";
    Balna p;
    SeqInFileEnumerator<Horgasz> enor(fname);
    p.addEnumerator(&enor);
    p.run();
    if (p.found())
    {
        cout << p.elem().name << endl;
    }
    else
    {
        cout << "Nincs talalat" << endl;
    }

    return 0;
}
