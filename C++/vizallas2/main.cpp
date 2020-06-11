#include <iostream>
#include <string>
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
    int meres
};

istream& operator>>(istream& inp, ismetlodo &s)
{
    return inp >> s.idopont >> s.meres;
}

class Meresek : public Summation<imetlodo, Result>
{
protected:
    Result func(const imetlodo &e) const override {return Result(1,e.meres<=400);}
    Result neutral() const override { return Result(0, false);}
    Result add(const Result& a, const Result& b) const override {
        return Result(a.meres_szama + b.meres_szama, a.kissebb || b.kissebb);
    }
};

istream& operator>>(istream& inp, Napi_vizallas &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s.helyszin >> s.datum;

    Meresek pr;
    StringStreamEnumerator<imetlodo> enor(is);
    pr.addEnumerator(&enor);
    pr.run();

    s.meres_szama = pr.result().meres_szama;
    s.kissebb = pr.result().kissebb;
    return inp;
}
/// Napi_vizallas-hoz vege----------------------------------------------------


class OptLinKer : public LinSearch<Napi_vizallas, false>
{
protected:
    bool cond(const Napi_vizallas& e) const override {return e.meres_szama>5 && e.kissebb;}
};

int main()
{
    cout << "Vizallas!\n" << endl;

    SeqInFileEnumerator<Napi_vizallas> enor("in.txt");
    OptLinKer k;
    k.addEnumerator(&enor);
    k.run();
    if(k.found())
    {
        cout<<" Igaz.";
    }else{
        cout<<" Nem igaz.\n";
    }

    /*felsorol f(&cout);
    f.addEnumerator(&enor);
    f.run();*/


    return 0;
}
