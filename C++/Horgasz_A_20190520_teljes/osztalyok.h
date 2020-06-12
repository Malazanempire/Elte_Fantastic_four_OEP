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

//A sorban ismétlõdõ adat szerkezete
struct adat{
    std::string hal;
    int meret;
    friend std::istream& operator>>(std::istream& inp, adat& e){
        return inp>>e.hal>>e.meret;
    }
};

//Ismétlõdõ adatok feldolgozásának eredménye
class readLine: public Counting<adat>
{
protected:
    bool cond(const adat& e)const override {return e.hal=="Ponty";}
};

//Egy sorból kinyert eredmény
struct sor{
    std::string horgasz;
    std::string verseny;
    int ponty;
    friend std::istream& operator>>(std::istream& inp, sor& e)
    {
        std::string line;
        getline(inp,line);
        std::stringstream ss(line);
        ss>>e.horgasz>>e.verseny;
        StringStreamEnumerator<adat> ssenor(ss);
        readLine pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        e.ponty=pr.result();
        return inp;
    }
};

//Megfelelt szint: maximum keresés
class Maxker : public MaxSearch<sor, int>
{
protected:
    int func(const sor& e) const override {return e.ponty;}
};

//Kivalo szint egyedi felsorolo
//Sorok összesítésébõl kapott összegzés típusa
struct efadat{
    std::string verseny;
    bool ponty;
};

//Egy összesítõ tétel
class Sum : public Summation<sor, bool>
{
public:
    Sum(const std::string& verseny): _verseny(verseny){}
protected:
    bool func(const sor& e) const override {return e.ponty==0;}
    bool neutral() const override {return true;}
    bool add(const bool& a, const bool&b) const override {return a && b;}
    void first() override {}
    bool whileCond(const sor& e) const override {return e.verseny==_verseny;}
    std::string _verseny;
};

//Egyedi felsoroló, összesíti az azonos id-jû nézõket
class sajatEnumerator: public Enumerator<efadat>
{
private:
    SeqInFileEnumerator<sor>* _f;
    efadat _efadat;
    bool _end;
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
    _efadat.verseny = _f->current().verseny;
    Sum pr(_efadat.verseny);
    pr.addEnumerator(_f);
    pr.run();
    _efadat.ponty = pr.result();
}

//Kiváló szint progtétel: lin.ker
class linKer: public LinSearch<efadat>
{
protected:
    bool cond(const efadat& e) const override {return e.ponty;}
};
