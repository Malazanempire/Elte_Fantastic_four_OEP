
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
    bool balna;
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
class CuntHal : public LinSearch<Szamol, true>
{
protected:
    bool cond(const Szamol& e) const override {return e.faj == "balna";};


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
    s.balna = pr.found();
    return inp;
}

//Progtétel szükség esetén, mainbe
class Balna : public Counting<Horgasz>
{
protected:
    void first() override {};
    bool cond(const Horgasz &e) const override {return e.balna;};
};

int main(int argc, char* argv[])
{
    string fname = argc>1 ? argv[1] : "input.txt";
    Balna p;
    SeqInFileEnumerator<Horgasz> enor(fname);
    p.addEnumerator(&enor);
    p.run();
    cout << p.result() << endl;


    return 0;
}

