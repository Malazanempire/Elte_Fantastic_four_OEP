#pragma once
#include <iostream>
#include<sstream>
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/maxsearch.hpp"
#include "library/linsearch.hpp"
#include "library/counting.hpp"
#include "library/selection.hpp"

//#define TESZT

//A sorban ismétlõdõ adat szerkezete
struct adat{
    std::string sportag;
    int helyezes;
    friend std::istream& operator>>(std::istream& inp, adat& e){
        inp>>e.sportag>>e.helyezes;
        return inp;
    }
};

//Ismétlõdõ adatok feldolgozásának eredménye
struct eredmeny{
    int erem;
    int indult;
    eredmeny(){}
    eredmeny(int e, int i): erem(e), indult(i) {}
};

//Egy sorban az ismétlõdõ adatok feldolgozása
class readLine: public Summation<adat,eredmeny>
{
protected:
    eredmeny func(const adat& e) const override {return eredmeny(e.helyezes<4? 1 : 0,1);}
    eredmeny neutral() const override {return eredmeny(0,0);}
    eredmeny add(const eredmeny& a, const eredmeny& b) const override {return eredmeny(a.erem+b.erem, a.indult+b.indult);}
};

//Egy sorból kinyert eredmény
struct sor{
    std::string nev;
    std::string suli;
    int erem;
    int indult;
    friend std::istream& operator>>(std::istream& inp, sor& e)
    {
        std::string line;
        getline(inp,line);
        std::stringstream ss(line);
        ss>>e.nev>>e.suli;
        StringStreamEnumerator<adat> ssenor(ss);
        readLine pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        e.erem=pr.result().erem;
        e.indult=pr.result().indult;
        return inp;
    }
};

//Megfelelt szint: maximum keresés
class Maxker : public MaxSearch<sor, int>
{
protected:
    int func(const sor& e) const override {return e.erem;}
    bool cond(const sor& e) const override {return e.indult>=3;}
};

///--------------------------------------------------------------------------------

//Kivalo szint egyedi felsorolo
//Sorok összesítésébõl kapott összegzés típusa
struct efadat{
    std::string suli;
    double arany;
    int ermek;
};

struct efadat_alap{
    int ermek;
    int diakok;
    efadat_alap(){}
    efadat_alap(int e, int d): ermek(e), diakok(d) {}
};

//Egy összesítõ tétel
class Sum : public Summation<sor, efadat_alap>
{
public:
    Sum(const std::string& suli): _suli(suli){}
protected:
    efadat_alap func(const sor& e) const override {return efadat_alap(e.erem,1);}
    efadat_alap neutral() const override {return efadat_alap(0,0);}
    efadat_alap add(const efadat_alap& a, const efadat_alap&b) const override {return efadat_alap(a.ermek+b.ermek,a.diakok+b.diakok);}
    void first() override {}
    bool whileCond(const sor& e) const override {return e.suli==_suli;}
    std::string _suli;
};

//Egyedi felsoroló, összesíti az azonos id-jû nézõket
class sajatEnumerator: public Enumerator<efadat>
{
private:
    SeqInFileEnumerator<sor>* _f;
    efadat _efadat;
    bool _end;
    //bool _empty; //ha az üres felsoroló gondot okozna
public:
    sajatEnumerator(const std::string& file) { _f = new SeqInFileEnumerator<sor>(file); }
    ~sajatEnumerator() { delete _f; }
    void first() override { _f->first(); next();}
    void next() override;
    efadat current() const override { return _efadat; }
    bool end() const override { return _end; }
};

void sajatEnumerator::next()
{
    _end=_f->end();
    if (_end) return;
    _efadat.suli = _f->current().suli;
    Sum pr(_efadat.suli);
    pr.addEnumerator(_f);
    pr.run();
    _efadat.arany = pr.result().ermek/pr.result().diakok;
    _efadat.ermek = pr.result().ermek;
}

//Kiváló szint progtétel: maxker
class Maxker_ : public MaxSearch<efadat, double>
{
protected:
    double func(const efadat& e) const override {return e.arany;}
};
