#pragma once

#include "global.hpp"

pair< vector< pair< pair<int, int>, pair<int, int> > >, int > koniec_imprezy = { { { {-1, -1}, {-1, -1} }, { {-1, -1}, {-1, -1} } }, -1 };

pair< vector< pair< pair<int, int>, pair<int, int> > >, int > optymalne_ruchy(szachownica sz, pair<int, int>* l2m, do_roszady *drszd, int gleb, chrono::high_resolution_clock::time_point czas, typ t)
{

  chrono::high_resolution_clock::time_point rozp = chrono::high_resolution_clock::now();
  chrono::duration<double> cnr(czas_na_ruch - 0.25);
  chrono::duration<double> prw( rozp - czas );

  if( prw > cnr )
    return koniec_imprezy;

  szachownica sym_sz;
  kopiuj(sym_sz, sz);
  pair<int, int> sym_l2m = *l2m;
  do_roszady sym_drszd = *drszd;
  int sym_status=0;
  int sym_status2=0;

  vector< pair< pair<int, int>, pair<int, int> > > ruchy;

  int pkt = -60000;

  if( gleb < 0 )
    return { ruchy, 0 };

  for(int i=0;i<8;i++)
  {

    for(int j=0;j<8;j++)
    {

      ruch( {-1, -1}, &sym_status, &sym_status2, sym_sz, &sym_l2m, drszd );

      if( ( sym_sz[i][j].first != n ) && ( sym_sz[i][j].second == t ) )
      {

        while(true)
        {

          pair<int, int> sym_ruch = ruch( {i, j}, &sym_status, &sym_status2, sym_sz, &sym_l2m, drszd );

          if( sym_ruch.first == -1 )
            break;

          // normale bicie

          int m_pkt = wart[ sym_sz[sym_ruch.first][sym_ruch.second].first ];

          if( t == c )
          {

            m_pkt += pola[ sym_sz[sym_ruch.first][sym_ruch.second].first ][sym_ruch.first][sym_ruch.second];
            m_pkt += pola[ sym_sz[i][j].first ][sym_ruch.first][sym_ruch.second] - pola[ sym_sz[i][j].first ][i][j];

          }
          else
          {

            m_pkt += pola[ sym_sz[sym_ruch.first][sym_ruch.second].first ][7-sym_ruch.first][7-sym_ruch.second];
            m_pkt += pola[ sym_sz[i][j].first ][7-sym_ruch.first][7-sym_ruch.second] - pola[ sym_sz[i][j].first ][7-i][7-j];

          }

          if( m_pkt >= 15000 ) // Nie wymieniamy króla za króla :) k - 5 * h = 15500 > 15000
            m_pkt -= 10000;

          // bicie przelotem

          if( ( t == b ) && ( sym_sz[i][j].first == p ) )
            if( ( sym_l2m.first == sym_ruch.first-1 ) && ( sym_l2m.second == sym_ruch.second ) )
              m_pkt = 1;

          if( ( t == c ) && ( sym_sz[i][j].first == p ) )
            if( ( sym_l2m.first == sym_ruch.first+1 ) && ( sym_l2m.second == sym_ruch.second ) )
              m_pkt = 1;

          // promocja piona

          if( ( t == b ) && ( sym_sz[i][j].first == p ) )
            if( sym_ruch.first == 7 )
              m_pkt = 8;

          if( ( t == c ) && ( sym_sz[i][j].first == p ) )
            if( sym_ruch.first == 0 )
              m_pkt = 8;

          vector< pair<int, int> > modpol = apply( { { i, j }, sym_ruch }, sym_sz, &sym_l2m, &sym_drszd );

          pair< vector< pair< pair<int, int>, pair<int, int> > >, int > gen_ruch = optymalne_ruchy( sym_sz, &sym_l2m, &sym_drszd, gleb-1, czas, ntyp(t) );

          if( gen_ruch == koniec_imprezy )
            return koniec_imprezy;

          m_pkt -= gen_ruch.second;

          // int zw = optymalne_ruchy( sym_sz, &sym_l2m, gleb-1, ntyp(t) ).second;
          // if(gleb == 4)
          //   cerr << '\n' << m_pkt << " -= " << zw << "\n";
          // m_pkt -= zw;

          if( m_pkt == pkt )
            ruchy.push_back({ {i, j}, sym_ruch });

          if( m_pkt > pkt )
          {

            pkt = m_pkt;

            ruchy.clear();
            ruchy.push_back({ {i, j}, sym_ruch });

          }

          resuce_modpol(sym_sz, sz, &modpol);
          sym_l2m = *l2m;
          sym_drszd = *drszd;

        }

      }

    }

  }

  return { ruchy, pkt };

}

pair< pair<int, int>, pair<int, int> > ruszaj(szachownica sz, pair<int, int>* l2m, do_roszady *drszd, typ t)
{

  chrono::high_resolution_clock::time_point czas1 = chrono::high_resolution_clock::now();

  pair< vector< pair< pair<int, int>, pair<int, int> > >, int > ruchy;

  int gleb = 1;

  for(;;)
  {

    pair< vector< pair< pair<int, int>, pair<int, int> > >, int > zrzut = optymalne_ruchy(sz, l2m, drszd, gleb, czas1, t);

    if( zrzut == koniec_imprezy )
      break;
    else
      ruchy = zrzut;

    gleb++;

  }

  gleb--;

  vector< pair< pair<int, int>, pair<int, int> > > GTruchy;

  if( !drszd->crkb ) // tryb otwarcia
  {

    for(auto &a:ruchy.first)
    {

      if( sz[a.first.first][a.first.second].first == k )
      {

          if( ( ( a.first.second == 3 ) && ( a.second.second == 1 ) ) || ( ( a.first.second == 3 ) && ( a.second.second == 5 ) ) )
          {

            GTruchy.clear();
            GTruchy.push_back(a);
            break;

          }

      }

      if( ( sz[a.first.first][a.first.second].first == s ) || ( sz[a.first.first][a.first.second].first == g ) )
      {

        GTruchy.push_back(a);

        if( ( ( t == b ) && ( ( a.first == make_pair(0, 1) ) || ( a.first == make_pair(0, 2) ) ) ) || ( ( t == c ) && ( ( a.first == make_pair(7, 1) ) || ( a.first == make_pair(7, 2) ) ) ) )
        {

          GTruchy.push_back(a);
          GTruchy.push_back(a);
          GTruchy.push_back(a);
          GTruchy.push_back(a);
          GTruchy.push_back(a);

        }

      }
      else
      {

        GTruchy.push_back(a);

        if( sz[a.first.first][a.first.second].first != k )
          GTruchy.push_back(a);

      }

    }

  }
  else
  {

    for(auto &a:ruchy.first)
    {

      GTruchy.push_back(a);

    }

  }

  chrono::high_resolution_clock::time_point czas2 = chrono::high_resolution_clock::now();
  chrono::duration<double> roznica = czas2-czas1;

  cerr << "czas: " << roznica.count() << '\n';
  cerr << "czas na ruch: " << czas_na_ruch << '\n';
  cerr << "głębokość: " << gleb << '\n';

  if( t == b )
  {

    cerr << "tryb otwarcia: " << static_cast<int>(!drszd->crkb) << '\n';
    cerr << "tryb ataku: " << static_cast<int>(drszd->crkb) << '\n';

  }
  else
  {

    cerr << "tryb otwarcia: " << static_cast<int>(!drszd->crkc) << '\n';
    cerr << "tryb ataku: " << static_cast<int>(drszd->crkc) << '\n';

  }

  cerr << "wartosc ruchu: " << ruchy.second << '\n';
  cerr << "najlepsze ruchy: " << ruchy.first.size() << '\n';
  cerr << "GT ruchy: " << GTruchy.size() << '\n';

  if( GTruchy.size() )
    return GTruchy[ rand() % GTruchy.size() ];
  else
    return { {-1, -1}, {-1, -1} };

}
