#pragma once

#include <bits/stdc++.h>
#include <unistd.h>
#include <chrono>
#include "tablice.hpp"

using namespace std;

enum figura { n, p, s, g, w, h, k };
enum typ { b, c };
typedef pair<figura, typ> szachownica[8][8];
class szachownica_t;
struct do_roszady;

bool czyszachowane(pair<int, int>, pair<int, int>, typ, szachownica, pair<int, int>*, do_roszady*);
pair<int, int> ruch(pair<int, int>, int*, int*, szachownica, pair<int, int>*, do_roszady*);
char lifig(figura);
pair< pair<int, int>, pair<int, int> > ruszaj(typ);
vector< pair<int, int> > apply(pair< pair<int, int>, pair<int, int> >, szachownica, pair<int, int>*, do_roszady*);
bool valid(pair< pair<int, int>, pair<int, int> >, bool);
void rysuj(bool);
void nioset(int);
void sioset(void);
bool val_fpnum(string);

inline void kopiuj(szachownica sz1, const szachownica sz2)
{

  for(int i=0;i<8;i++)
  {

    for(int j=0;j<8;j++)
    {

      sz1[i][j]=sz2[i][j];

    }

  }

}

inline void resuce_modpol(szachownica sz1, szachownica sz2, vector< pair<int, int> > *modpol)
{

  for(int i=0;i<modpol->size();i++)
  {

    sz1[ (*modpol)[i].first ][ (*modpol)[i].second ] = sz2[ (*modpol)[i].first ][ (*modpol)[i].second ];

  }

}

inline typ ntyp(typ t)
{

  if(t==b)
    return c;

  return b;

}

class szachownica_t
{

  public:

    szachownica_t( const szachownica_t&);
    szachownica_t( const szachownica&);

    szachownica_t& operator=(const szachownica_t&);
    szachownica_t& operator=(const szachownica&);
    pair<figura, typ>* operator[](int idx);

  private:

    szachownica sz_o;

};

struct do_roszady
{

  bool crkb;
  bool crwb1;
  bool crwb2;

  bool crkc;
  bool crwc1;
  bool crwc2;

  do_roszady()
  {

    crkb = 0;
    crwb1 = 0;
    crwb2 = 0;

    crkc = 0;
    crwc1 = 0;
    crwc2 = 0;

  }

};

szachownica_t::szachownica_t( const szachownica_t &obj)
{

  kopiuj(sz_o, obj.sz_o);

}

szachownica_t::szachownica_t( const szachownica &obj)
{

  kopiuj(sz_o, obj);

}

szachownica_t& szachownica_t::operator=(const szachownica_t &prawy)
{

  if( &prawy != this )
    kopiuj(sz_o, prawy.sz_o);

  return *this;

}

szachownica_t& szachownica_t::operator=(const szachownica &prawy)
{

  kopiuj(sz_o, prawy);

  return *this;

}

pair<figura, typ>* szachownica_t::operator[](int idx)
{

  return sz_o[idx];

}

szachownica gra = {

  { { w, b }, { s, b }, { g, b }, { k, b }, { h, b }, { g, b }, { s, b }, { w, b } },
  { { p, b }, { p, b }, { p, b }, { p, b }, { p, b }, { p, b }, { p, b }, { p, b } },
  { { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b } },
  { { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b } },
  { { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b } },
  { { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b }, { n, b } },
  { { p, c }, { p, c }, { p, c }, { p, c }, { p, c }, { p, c }, { p, c }, { p, c } },
  { { w, c }, { s, c }, { g, c }, { k, c }, { h, c }, { g, c }, { s, c }, { w, c } }

};

pair<int, int> main_l2m=make_pair(-1, -1);

do_roszady main_do_roszady;

bool color;

int main_status=0;
int main_status2=0;

int main_pionyb[8] = {1, 1, 1, 1, 1, 1, 1, 1}; /////////////////////////////////////////////////////////////////
int main_pionyc[8] = {1, 1, 1, 1, 1, 1, 1, 1};

double czas_na_ruch = 15;

vector<szachownica_t> lst_n_ruchy;
