#include <iostream>
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
#include "../library/counting.hpp"



using namespace std;


//Ide jön a végeredmény
struct Horgasz
{
    string _name;
    string _maxfaj;
    int _halmeret;
};



//Ezen keresztül
struct LegnagyobbHal
{
    string _faj;
    int _meret;
};
//EXTRA
istream& operator>>(istream& inp, LegnagyobbHal &s)
{
    return inp>>s._faj>>s._meret;
}
//Tétel végrehajtása a köztes struct-on
class MaxHal : public MaxSearch<LegnagyobbHal,int,Greater<int>>
{
protected:
    int func(const LegnagyobbHal& e) const override
    {
        return e._meret;
    }
};



//Beolvasás
istream& operator>>(istream& inp, Horgasz &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s._name;



    MaxHal pr;
    StringStreamEnumerator<LegnagyobbHal> enor(is);
    pr.addEnumerator(&enor);
    pr.run();
    if(pr.found())
    {
        s._maxfaj = pr.optElem()._faj;
        s._halmeret = pr.optElem()._meret;
    }
    return inp;
}



//Progtétel szükség esetén, mainbe
class List : public Summation<Horgasz,std::ostream>
{
protected:
    std::string func(const Horgasz &e) const override {
        std::ostringstream os;
        os << e._name << " " <<e._maxfaj << " " << e._halmeret << "\n";
        return os.str();
    }
public:
    List(std::ostream* o): Summation<Horgasz, std::ostream> :: Summation(o) {}
};



int main(int argc, char* argv[])
{
    string fname = argc>1 ? argv[1] : "input.txt";
    List p(&cout);
    SeqInFileEnumerator<Horgasz> enor(fname);
    p.addEnumerator(&enor);
    p.run();



    return 0;
}
