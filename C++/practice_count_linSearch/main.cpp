#include <iostream>
#include <sstream>
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/enumerator.hpp"
#include "../library/summation.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
#include "../library/counting.hpp"

using namespace std;

struct Cellovolde
{
    string name;
    string vendeg;
    string nyeremeny;
    int count;
};

istream& operator>>(istream &is, Cellovolde &e)
{
    is >> e.name >> e.vendeg >> e.nyeremeny;
    return is;
}
ostream& operator<<(ostream& inp, const Cellovolde &e)
{
    inp << "név: " <<e.name << " vendég: " << e.vendeg << " nyeremeny: " << e.nyeremeny << "szám " << e.count << endl;
    return inp;
}
class MyCount : public Counting<Cellovolde>
{
private:
    string _name;
public:
    MyCount(string name) : _name(name) {}
protected:
    void first() override {}
    bool cond(const Cellovolde &e) const override
    {
        cout << "My Count: " << e;
        return e.nyeremeny=="nem_nyert";
    };
    bool whileCond(const Cellovolde &e) const override
    {
        return e.name == _name;
    }
};

class MyEnumerator : public Enumerator<Cellovolde>
{
private:
    SeqInFileEnumerator<Cellovolde> _f;
    Cellovolde _cur;
    bool _end;
public:
    MyEnumerator(const string& fn): _f(fn) { }
    void first() override
    {
        _f.first();
        next();
    }
    void next() override;
    Cellovolde current() const override
    {
        return _cur;
    }
    bool end() const override
    {
        return _end;
    }
};

class MyMaxLinSearch : public MaxSearch<Cellovolde, int, Greater<int>>
{
protected:
    int func(const Cellovolde& e) const override
    {
        cout << "Lin search: " << e;
        return e.count;
    }
};

void MyEnumerator::next()
{
    if (( _end = _f.end() ))
        return;

    _cur.name = _f.current().name;
    MyCount p(_cur.name);
    p.addEnumerator(&_f);
    p.run();

    _cur.count = p.result();
   cout << "Enum: " << _cur;
}


int main(int argc, char* argv[])
{
    string fname = argc>1 ? argv[1] : "input.txt";

    MyMaxLinSearch p;
    MyEnumerator enor(fname);
    p.addEnumerator(&enor);
    p.run();

    cout << p.optElem().name << endl;
    return 0;
}
