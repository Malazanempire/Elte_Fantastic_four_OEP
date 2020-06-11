#include <iostream>
#include <string>
#include "../library/enumerator.hpp"
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"

using namespace std;

struct Napi_vizallas{
    string helyszin;
    string datum;
    int meres_szama;
    bool kissebb;
};

/// Napi_vizallas-hoz --------------------------------------------------------
struct Result
{
    int meres_szama;
    bool kissebb;
    Result(){}
    Result(int s, bool m): meres_szama(s), kissebb(m) {}
};

struct ismetlodo{
    string idopont;
    int meres;
};

istream& operator>>(istream& inp, ismetlodo &s)
{
    return inp >> s.idopont >> s.meres;
}

class Meresek : public Summation<ismetlodo, Result>
{
protected:
    Result func(const ismetlodo &e) const override {return Result(1,e.meres<=400);}
    Result neutral() const override { return Result(0, true);}
    Result add(const Result& a, const Result& b) const override {
        return Result(a.meres_szama + b.meres_szama, a.kissebb && b.kissebb);
    }
};

istream& operator>>(istream& inp, Napi_vizallas &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s.helyszin >> s.datum;

    Meresek pr;
    StringStreamEnumerator<ismetlodo> enor(is);
    pr.addEnumerator(&enor);
    pr.run();

    s.meres_szama = pr.result().meres_szama;
    s.kissebb = pr.result().kissebb;
    return inp;
}
/// Napi_vizallas-hoz vege----------------------------------------------------

struct ZH_otos{
    string datum;
    int meresek_szama;
    bool kissebb;
};

struct adatok{
    int meresek_szama;
    bool kissebb;
    adatok(){}
    adatok(int m, bool k): meresek_szama(m), kissebb(k) {}
};

class MeresEnumerator : public Enumerator<ZH_otos>
{
private:
    SeqInFileEnumerator<Napi_vizallas> _f;
    ZH_otos _allas;
    bool _end;
public:
    MeresEnumerator(const string &fname): _f(fname) {}
    void first() override { _f.first(); next();}
    void next() override;
    ZH_otos current() const override { return _allas; }
    bool end() const override { return _end; }
};

class Olvas : public Summation<Napi_vizallas,adatok>
{
private:
    string _datum;
protected:
    adatok func(const Napi_vizallas &e) const override { return adatok(1,e.kissebb); }
    adatok neutral() const override { return adatok(0,true);}
    adatok add(const adatok& a, const adatok& b) const override {return adatok(a.meresek_szama+b.meresek_szama,a.kissebb&&b.kissebb);}
    bool whileCond(const Napi_vizallas &e) const override { return e.datum==_datum; }
    void first() override {}
public:
    Olvas(const string &datum): _datum(datum) {}
};

void MeresEnumerator::next()
{
    if((_end = _f.end()));
    _allas.datum =_f.current().datum;
    Olvas pr(_allas.datum);
    pr.addEnumerator(&_f);
    pr.run();
    _allas.kissebb = pr.result().kissebb;
    _allas.meresek_szama = pr.result().meresek_szama;
}


class OptLinKer : public LinSearch<Napi_vizallas, false>
{
protected:
    bool cond(const Napi_vizallas& e) const override {return e.meres_szama>5 && e.kissebb;}
};

class mini : public MaxSearch<ZH_otos,int,Less<int>>
{
protected:
    int func(const ZH_otos& e) const override {return e.meresek_szama;}
    bool  cond(const ZH_otos& e) const override { return e.kissebb;}
};

int main()
{
    cout << "Vizallas!\n" << endl;

    /*SeqInFileEnumerator<Napi_vizallas> enor("in2.txt");
    OptLinKer k;
    k.addEnumerator(&enor);
    k.run();
    if(k.found())
    {
        cout<<" Igaz.";
    }else{
        cout<<" Nem igaz.\n";
    }*/

    /*felsorol f(&cout);
    f.addEnumerator(&enor);
    f.run();*/
    MeresEnumerator enor("in1.txt");
    mini m;
    m.addEnumerator(&enor);
    m.run();
    if(m.found())
    {
        cout<<"Talalt "<<m.optElem().datum;
    }else{
        cout<<"Nem";
    }


    return 0;
}
