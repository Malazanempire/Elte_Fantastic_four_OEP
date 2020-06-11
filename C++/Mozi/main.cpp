#include <iostream>
#include <string>
#include "library/stringstreamenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/linsearch.hpp"
#include "library/maxsearch.hpp"


using namespace std;

struct jegy_vasarl{
    string film;
    string terem;
    string ido;
    bool csak_diak;
    int ertek;
};

struct film{
    string ido;
    bool csak_diak;
    int osszeg;
};

struct Result
{
    bool diak;
    int sum;
    Result(){}
    Result(bool d, int s): diak(d), sum(s) {}
};

class Nezo_diak : public Summation<string, Result>
{
protected:
    Result func(const string &e) const override {
        if(e.compare("g") == 0){
            return Result(false,500);
        }else if(e.compare("d") == 0){
            return Result(true,800);
        }/*else if(e.compare("f") == 0){*/
            return Result(false,1000);
        //}
    }
    Result neutral() const override { return Result(true, 0);}
    Result add(const Result& a, const Result& b) const override {
        return Result(a.diak && b.diak, a.sum + b.sum);
    }
    bool cond(const string &e) const override { return 1==e.length(); }
};

istream& operator>>(istream& inp, jegy_vasarl &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s.film >> s.terem >> s.ido;

    Nezo_diak pr;
    StringStreamEnumerator<string> enor(is);
    pr.addEnumerator(&enor);
    pr.run();

    s.csak_diak = pr.result().diak;
    s.ertek = pr.result().sum;
    return inp;
}

class FilmEnumerator : public Enumerator<film>
{
private:
    SeqInFileEnumerator<jegy_vasarl> _f;
    film _film;
    bool _end;
public:
    FilmEnumerator(const string &fname): _f(fname) {}
    void first() override { _f.first(); next();}
    void next() override;
    film current() const override { return _film; }
    bool end() const override { return _end; }
};

struct Result_v{
    bool csak_diak;
    int osszeg;
    Result_v(){}
    Result_v(bool c, int o): csak_diak(c), osszeg(o) {}
};

class Filmek : public Summation<jegy_vasarl, Result_v>
{
private:
    string ido;
public:
    Filmek(const string &i) : ido(i) {}
protected:
    Result_v func(const jegy_vasarl &e) const override { return Result_v(e.csak_diak, e.ertek); }
    Result_v neutral() const override { return Result_v(true, 0); }
    Result_v add(const Result_v &a, const Result_v &b) const override { return Result_v(a.csak_diak&&b.csak_diak, a.osszeg+b.osszeg);}
    bool whileCond(const jegy_vasarl &e) const override { return e.ido==ido; }
    void first() override {}
};

void FilmEnumerator::next()
{
    if((_end = _f.end()));
    _film.ido = _f.current().ido;
    Filmek pr(_film.ido);
    pr.addEnumerator(&_f);
    pr.run();

    _film.csak_diak = pr.result().csak_diak;
    _film.osszeg = pr.result().osszeg;
}

/*class Mozi : public Summation<jegy_vasarl, std::ostream>
{
public:
    Mozi(std::ostream* o): Summation<jegy_vasarl, std::ostream> :: Summation(o){}
protected:
    std::string func(const jegy_vasarl &e) const override {
        std::ostringstream os;
        os << "film: " << e.film << " terem: " << e.terem<< " idopont: " << e.ido<< " mind_diak: " << e.csak_diak<< " osszeg: " << e.ertek << "\n";
        return os.str();
    }
};*/

class OptLinKer : public LinSearch<jegy_vasarl, false>
{
protected:
    bool cond(const jegy_vasarl& e) const override { return e.csak_diak && e.ertek>=3000; }
};

/*class OptLinKer : public LinSearch<jegy_vasarl, true>
{
protected:
    bool cond(const jegy_vasarl& e) const override { return e.csak_diak && e.ertek<=2000; }
};*/

class BestBevetel : public MaxSearch<film,int>
{
protected:
    int func(const film &e) const override { return e.osszeg; }
    bool cond(const film &e) const override { return e.csak_diak; }
};

int main()
{
    cout << "Mozi!\n" << endl;

    SeqInFileEnumerator<jegy_vasarl> enor("in3.txt");
    OptLinKer f;
    //Mozi f(&cout);
    f.addEnumerator(&enor);
    f.run();
    if(f.found())
    {
        //cout<<" Talalt."<< f.elem().csak_diak<<" "<< f.elem().ertek <<"\n";
        cout<<" Talalt.";
    }else{
        cout<<" Nem talalt.\n";
    }

    /*FilmEnumerator enor("in7.txt");
    BestBevetel b;
    b.addEnumerator(&enor);
    b.run();
    if(!b.found()) cout << "Nincs csak diakok altal latogatott legnagyobb bevetelu film !\n";
    else cout << b.optElem().ido << " A legnagyobb bevetelu film amit csak diakok latogattak " << b.opt() << endl;;*/


    return 0;
}
