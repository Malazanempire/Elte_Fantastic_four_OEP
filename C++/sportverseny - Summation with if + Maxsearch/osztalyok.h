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

//A sorban ism�tl�d� adat szerkezete
struct adat{
    std::string sportag;
    int helyezes;
    friend std::istream& operator>>(std::istream& inp, adat& e){
        inp>>e.sportag>>e.helyezes;
        return inp;
    }
};

//Ism�tl�d� adatok feldolgoz�s�nak eredm�nye
struct eredmeny{
    int erem;
    int indult;
    eredmeny(){}
    eredmeny(int e, int i): erem(e), indult(i) {}
};

//Egy sorban az ism�tl�d� adatok feldolgoz�sa
class readLine: public Summation<adat,eredmeny>
{
protected:
    eredmeny func(const adat &e) const override {
        if(e.helyezes == 1){return eredmeny(12,1);}
        else if(e.helyezes == 2){return eredmeny(10,1);}
        else if(e.helyezes == 3){return eredmeny(8,1);}
        else if(e.helyezes == 4){return eredmeny(6,1);}
        else if(e.helyezes == 5){return eredmeny(4,1);}
        else if(e.helyezes == 6){return eredmeny(2,1);}
        else {return eredmeny(0,1);}
    }
    eredmeny neutral() const override {return eredmeny(0,0);}
    eredmeny add(const eredmeny& a, const eredmeny& b) const override {return eredmeny(a.erem+b.erem, a.indult+b.indult);}
};

//Egy sorb�l kinyert eredm�ny
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

//Megfelelt szint: maximum keres�s
class Maxker : public MaxSearch<sor, int>
{
protected:
    int func(const sor& e) const override {return e.erem;}
};
