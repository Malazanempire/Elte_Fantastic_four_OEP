#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/maxsearch.hpp"
#include "library/counting.hpp"

using namespace std;

//Ide jön a végeredmény
struct Versenyzo
{
    string _name;
    string _verseny;
    int _versenyekdb;
    int _eremdb;
};

//Ezen keresztül
struct Eredmeny
{
    int _helyezes;
    string _vsz;
};

//EXTRA
istream& operator>>(istream& inp, Eredmeny &s)
{
    return inp>>s._vsz>>s._helyezes;
}

//Tétel végrehajtása a köztes struct-on BEOLVASÁSNÁL
class CountVerseny : public Counting<Eredmeny>
{
protected:
    bool cond(const Eredmeny &e) const override
    {
        return true;
    };
};


class CountErem : public Counting<Eredmeny>
{
protected:
    bool cond(const Eredmeny &e) const override
    {
        return e._helyezes>=1&&e._helyezes<=3;
    };
};

//Beolvasás
istream& operator>>(istream& inp, Versenyzo &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s._name >> s._verseny;


    CountVerseny pr;
    StringStreamEnumerator<Eredmeny> enor(is);
    pr.addEnumerator(&enor);
    pr.run();
    s._versenyekdb = pr.result();

    stringstream is2(line);
    string x,z;
    is2 >> x >> z;
    CountErem pr2;
    StringStreamEnumerator<Eredmeny> enor2(is2);
    pr2.addEnumerator(&enor2);
    pr2.run();

    s._eremdb = pr2.result();

    return inp;
}

//Progtétel szükség esetén, mainbe
class List : public MaxSearch<Versenyzo,int,Greater<int>>
{
protected:
    int func(const Versenyzo& e) const override
    {
        if(e._versenyekdb>=3)
            return e._eremdb;
            return 0;
    }

};

int main(int argc, char* argv[])
{
    string fname = argc>1 ? argv[1] : "i1.txt";
    try
    {
        List p;
        SeqInFileEnumerator<Versenyzo> enor(fname);
        p.addEnumerator(&enor);
        p.run();
        cout << p.optElem()._name <<" "<< p.optElem()._versenyekdb <<" "<< p.optElem()._eremdb<<endl;
    }
    catch(SeqInFileEnumerator<Versenyzo>::Exceptions err)
    {
        if(err==SeqInFileEnumerator<Versenyzo>::OPEN_ERROR)
            cerr << fname << " fajl nem nyithato meg!\n";
    }

    return 0;
}
