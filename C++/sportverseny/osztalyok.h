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
