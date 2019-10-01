#pragma once

#include "global.hpp"

pair<int, int> ruch(pair<int, int> pole, int *status, int *status2, szachownica sz, pair<int, int> *l2m, do_roszady *drszd)
{

  //cerr << "\nruch { " << pole.first << ", " << pole.second << " }\n";

  if( pole.first == -1 ) // reset
  {

    //cerr << "reset: 1\n";

    *status=0;
    *status2=0;
    return {-1, -1};

  }

  //cerr << "reset: 0\n";

  if( sz[pole.first][pole.second].first == n )
    return {-1, -1};

  //cerr << "if( sz[pole.first][pole.second].first == n ): 1\n";

  if( sz[pole.first][pole.second].first == p )
  {

    //cerr << "pion: 1\n";

    if( ( ( pole.first == 1 ) && ( sz[pole.first][pole.second].second == b ) ) || ( ( pole.first == 6 ) && ( sz[pole.first][pole.second].second == c ) ) )
    {

      switch(*status)
      {

        case 0:
          if( sz[pole.first][pole.second].second == b )
          {

            if( sz[pole.first+1][pole.second].first == n )
            {

              *status=1;
              return { pole.first+1, pole.second };

            }

          }

          if( sz[pole.first][pole.second].second == c )
          {

            if( sz[pole.first-1][pole.second].first == n )
            {

              *status=1;
              return { pole.first-1, pole.second };

            }

          }

        case 1:
          if( sz[pole.first][pole.second].second == b )
          {

            if( ( sz[pole.first+1][pole.second].first == n ) && ( sz[pole.first+2][pole.second].first == n ) )
            {

              *status=2;
              return { pole.first+2, pole.second };

            }

          }

          if( sz[pole.first][pole.second].second == c )
          {

            if( ( sz[pole.first-1][pole.second].first == n ) && ( sz[pole.first-2][pole.second].first == n ) )
            {

              *status=2;
              return { pole.first-2, pole.second };

            }

          }

        case 2:
          if( ( pole.second < 7 ) && ( sz[pole.first][pole.second].second == b ) )
          {

            if( ( sz[pole.first+1][pole.second+1].first != n ) && ( sz[pole.first+1][pole.second+1].second == c ) )
            {

              *status=3;
              return { pole.first+1, pole.second+1 };

            }

          }

          if( ( pole.second > 0 ) && ( sz[pole.first][pole.second].second == c ) )
          {

            if( ( sz[pole.first-1][pole.second-1].first != n ) && ( sz[pole.first-1][pole.second-1].second == b ) )
            {

              *status=3;
              return { pole.first-1, pole.second-1 };

            }

          }

        case 3:
          if( ( pole.second > 0 ) && ( sz[pole.first][pole.second].second == b ) )
          {

            if( ( sz[pole.first+1][pole.second-1].first != n ) && ( sz[pole.first+1][pole.second-1].second == c ) )
            {

              *status=4;
              return { pole.first+1, pole.second-1 };

            }

          }

          if( ( pole.second < 7 ) && ( sz[pole.first][pole.second].second == c ) )
          {

            if( ( sz[pole.first-1][pole.second+1].first != n ) && ( sz[pole.first-1][pole.second+1].second == b ) )
            {

              *status=4;
              return { pole.first-1, pole.second+1 };

            }

          }

        default:
          *status=0;
          *status2=0;
          return { -1, -1 };


      }

    }
    else
    {

        switch(*status)
        {

          case 0:
            if( ( sz[pole.first][pole.second].second == b ) && ( pole.first < 7 ) )
            {

              if( sz[pole.first+1][pole.second].first == n )
              {

                *status=1;
                return { pole.first+1, pole.second };

              }

            }

            if( ( sz[pole.first][pole.second].second == c ) && ( pole.first > 0 ) )
            {

              if( sz[pole.first-1][pole.second].first == n )
              {

                *status=1;
                return { pole.first-1, pole.second };

              }

            }

          case 1:
            if( ( pole.first < 7 ) && ( pole.second < 7 ) && ( sz[pole.first][pole.second].second == b ) )
            {

              if( ( ( sz[pole.first+1][pole.second+1].first != n ) && ( sz[pole.first+1][pole.second+1].second == c ) ) || ( *l2m == make_pair(pole.first, pole.second+1) ) )
              {

                *status=2;
                return { pole.first+1, pole.second+1 };

              }

            }

            if( ( pole.first > 0 ) && ( pole.second > 0 ) && ( sz[pole.first][pole.second].second == c ) )
            {

              if( ( ( sz[pole.first-1][pole.second-1].first != n ) && ( sz[pole.first-1][pole.second-1].second == b ) ) || ( *l2m == make_pair(pole.first, pole.second-1) ) )
              {

                *status=2;
                return { pole.first-1, pole.second-1 };

              }

            }

          case 2:
            if( ( pole.first < 7 ) && ( pole.second > 0 ) && ( sz[pole.first][pole.second].second == b ) )
            {

              if( ( ( sz[pole.first+1][pole.second-1].first != n ) && ( sz[pole.first+1][pole.second-1].second == c ) ) || ( ( *l2m == make_pair(pole.first, pole.second-1) ) && ( ( sz[l2m->first][l2m->second].first != n ) && ( sz[l2m->first][l2m->second].second == c ) ) ) )
              {

                *status=3;
                return { pole.first+1, pole.second-1 };

              }

            }

            if( ( pole.first > 0 ) && ( pole.second < 7 ) && ( sz[pole.first][pole.second].second == c ) )
            {

              if( ( ( sz[pole.first-1][pole.second+1].first != n ) && ( sz[pole.first-1][pole.second+1].second == b ) ) || ( ( *l2m == make_pair(pole.first, pole.second+1) ) && ( ( sz[l2m->first][l2m->second].first != n ) && ( sz[l2m->first][l2m->second].second == b ) ) ) )
              {

                *status=3;
                return { pole.first-1, pole.second+1 };

              }

            }

          default:
            *status=0;
            *status2=0;
            return { -1, -1 };


        }

    }

  }

  //cerr << "pion: 0\n";

  if( sz[pole.first][pole.second].first == s )
  {

    //cerr << "skoczek: 1\n";

    switch(*status)
    {

      case 0:
        if( ( pole.first > 1 ) && ( pole.second < 7 ) )
        {

          if( ( sz[pole.first-2][pole.second+1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first-2][pole.second+1].second ) )
          {

            *status=1;
            return {pole.first-2, pole.second+1};

          }

        }

      case 1:
        if( ( pole.first > 0 ) && ( pole.second < 6 ) )
        {

          if( ( sz[pole.first-1][pole.second+2].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first-1][pole.second+2].second ) )
          {

            *status=2;
            return {pole.first-1, pole.second+2};

          }

        }

      case 2:
        if( ( pole.first < 7 ) && ( pole.second < 6 ) )
        {

          if( ( sz[pole.first+1][pole.second+2].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first+1][pole.second+2].second ) )
          {

            *status=3;
            return {pole.first+1, pole.second+2};

          }

        }

      case 3:
        if( ( pole.first < 6 ) && ( pole.second < 7 ) )
        {

          if( ( sz[pole.first+2][pole.second+1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first+2][pole.second+1].second ) )
          {

            *status=4;
            return {pole.first+2, pole.second+1};

          }

        }

      case 4:
        if( ( pole.first < 6 ) && ( pole.second > 0 ) )
        {

          if( ( sz[pole.first+2][pole.second-1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first+2][pole.second-1].second ) )
          {

            *status=5;
            return {pole.first+2, pole.second-1};

          }

        }

      case 5:
        if( ( pole.first < 7 ) && ( pole.second > 1 ) )
        {

          if( ( sz[pole.first+1][pole.second-2].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first+1][pole.second-2].second ) )
          {

            *status=6;
            return {pole.first+1, pole.second-2};

          }

        }

      case 6:
        if( ( pole.first > 0 ) && ( pole.second > 1 ) )
        {

          if( ( sz[pole.first-1][pole.second-2].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first-1][pole.second-2].second ) )
          {

            *status=7;
            return {pole.first-1, pole.second-2};

          }

        }

      case 7:
        if( ( pole.first > 1 ) && ( pole.second > 0 ) )
        {

          if( ( sz[pole.first-2][pole.second-1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first-2][pole.second-1].second ) )
          {

            *status=8;
            return {pole.first-2, pole.second-1};

          }

        }

      default:
        *status=0;
        *status2=0;
        return {-1, -1};

    }

  }

  //cerr << "skoczek: 0\n";

  if( sz[pole.first][pole.second].first == k )
  {

    //cerr << "król: 1\n";

    switch(*status)
    {

      case 0:
        if( pole.first > 0 )
        {

          if( ( ( sz[pole.first-1][pole.second].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first-1][pole.second].second ) ) && !czyszachowane(pole, {pole.first-1, pole.second}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=1;
            return {pole.first-1, pole.second};

          }

        }

      case 1:
        if( ( pole.first > 0 ) && ( pole.second < 7 ) )
        {

          if( ( ( sz[pole.first-1][pole.second+1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first-1][pole.second+1].second ) ) && !czyszachowane(pole, {pole.first-1, pole.second+1}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=2;
            return {pole.first-1, pole.second+1};

          }

        }

      case 2:
        if( pole.second < 7 )
        {

          if( ( ( sz[pole.first][pole.second+1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first][pole.second+1].second ) ) && !czyszachowane(pole, {pole.first, pole.second+1}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=3;
            return {pole.first, pole.second+1};

          }

        }

      case 3:
        if( ( pole.first < 7 ) && ( pole.second < 7 ) )
        {

          if( ( ( sz[pole.first+1][pole.second+1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first+1][pole.second+1].second ) ) && !czyszachowane(pole, {pole.first+1, pole.second+1}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=4;
            return {pole.first+1, pole.second+1};

          }

        }

      case 4:
        if( pole.first < 7 )
        {

          if( ( ( sz[pole.first+1][pole.second].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first+1][pole.second].second ) ) && !czyszachowane(pole, {pole.first+1, pole.second}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=5;
            return {pole.first+1, pole.second};

          }

        }

      case 5:
        if( ( pole.first < 7 ) && ( pole.second > 0 ) )
        {

          if( ( ( sz[pole.first+1][pole.second-1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first+1][pole.second-1].second ) ) && !czyszachowane(pole, {pole.first+1, pole.second-1}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=6;
            return {pole.first+1, pole.second-1};

          }

        }

      case 6:
        if( pole.second > 0 )
        {

          if( ( ( sz[pole.first][pole.second-1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first][pole.second-1].second ) ) && !czyszachowane(pole, {pole.first, pole.second-1}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=7;
            return {pole.first, pole.second-1};

          }

        }

      case 7:
        if( ( pole.first > 0 ) && ( pole.second > 0 ) )
        {

          if( ( ( sz[pole.first-1][pole.second-1].first == n ) || ( sz[pole.first][pole.second].second != sz[pole.first-1][pole.second-1].second ) ) && !czyszachowane(pole, {pole.first-1, pole.second-1}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
          {

            *status=8;
            return {pole.first-1, pole.second-1};

          }

        }

      case 8: // mała roszada
        if( ( ( sz[pole.first][pole.second].second == b ) && !drszd->crkb && !drszd->crwb1 ) || ( ( sz[pole.first][pole.second].second == c ) && !drszd->crkc && !drszd->crwc1 ) ) // król się nie ruszał
        {

          if( ( sz[pole.first][pole.second-1].first == n ) && ( sz[pole.first][pole.second-2].first == n ) )
          {

            if( !czyszachowane(pole, pole, sz[pole.first][pole.second].second, sz, l2m, drszd) && !czyszachowane(pole, {pole.first, pole.second-1}, sz[pole.first][pole.second].second, sz, l2m, drszd) && !czyszachowane(pole, {pole.first, pole.second-2}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
            {

              *status=9;
              return {pole.first, pole.second-2};

            }

          }

        }

      case 9: // wielka roszada
        if( ( ( sz[pole.first][pole.second].second == b ) && !drszd->crkb && !drszd->crwb2 ) || ( ( sz[pole.first][pole.second].second == c ) && !drszd->crkc && !drszd->crwc2 ) ) // król i wieża 1 ruch
        {

          if( ( sz[pole.first][pole.second+1].first == n ) && ( sz[pole.first][pole.second+2].first == n ) && ( sz[pole.first][pole.second+3].first == n ) )
          {

            if( !czyszachowane(pole, pole, sz[pole.first][pole.second].second, sz, l2m, drszd) && !czyszachowane(pole, {pole.first, pole.second+1}, sz[pole.first][pole.second].second, sz, l2m, drszd) && !czyszachowane(pole, {pole.first, pole.second+2}, sz[pole.first][pole.second].second, sz, l2m, drszd) )
            {

              *status=10;
              return {pole.first, pole.second+2};

            }

          }

        }

      default:
        *status=0;
        *status2=0;
        return {-1, -1};

    }

  }

  //cerr << "król: 0\n";

  if( sz[pole.first][pole.second].first == w )
  {

    //cerr << "wieża: 1\n";

    *status2 = *status2 + 1;

    switch(*status)
    {

      case 0:
        if( pole.first-*status2 >=0 )
        {

          if( sz[pole.first-*status2][pole.second].first == n )
            return {pole.first-*status2, pole.second};

          if( sz[pole.first-*status2][pole.second].second != sz[pole.first][pole.second].second )
          {

            pole.first-=*status2;

            *status=1;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=1;
        *status2=1;

      case 1:
        if( pole.second+*status2 <=7 )
        {

          if( sz[pole.first][pole.second+*status2].first == n )
            return {pole.first, pole.second+*status2};

          if( sz[pole.first][pole.second+*status2].second != sz[pole.first][pole.second].second )
          {

            pole.second+=*status2;

            *status=2;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=2;
        *status2=1;

      case 2:
        if( pole.first+*status2 <=7 )
        {

          if( sz[pole.first+*status2][pole.second].first == n )
            return {pole.first+*status2, pole.second};

          if( sz[pole.first+*status2][pole.second].second != sz[pole.first][pole.second].second )
          {

            //cerr << "return " << pole.first+*status2 << ' ' << pole.second << ' ';

            pole.first+=*status2;

            *status=3;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=3;
        *status2=1;

      case 3:
        if( pole.second-*status2 >=0 )
        {

          if( sz[pole.first][pole.second-*status2].first == n )
            return {pole.first, pole.second-*status2};

          if( sz[pole.first][pole.second-*status2].second != sz[pole.first][pole.second].second )
          {

            pole.second-=*status2;

            *status=4;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=4;
        *status2=1;

      default:
        *status=0;
        *status2=0;
        return {-1, -1};

    }

  }

  //cerr << "wieża: 0\n";

  if( sz[pole.first][pole.second].first == g )
  {

    //cerr << "goniec: 1\n";

    *status2 = *status2 + 1;

    switch(*status)
    {

      case 0:
        if( ( pole.first-*status2 >=0 ) && ( pole.second+*status2 <=7 ) )
        {

          if( sz[pole.first-*status2][pole.second+*status2].first == n )
            return {pole.first-*status2, pole.second+*status2};

          if( sz[pole.first-*status2][pole.second+*status2].second != sz[pole.first][pole.second].second )
          {

            pole.first-=*status2;
            pole.second+=*status2;

            *status=1;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=1;
        *status2=1;

      case 1:
        if( ( pole.first+*status2 <=7 ) && ( pole.second+*status2 <=7 ) )
        {

          if( sz[pole.first+*status2][pole.second+*status2].first == n )
            return {pole.first+*status2, pole.second+*status2};

          if( sz[pole.first+*status2][pole.second+*status2].second != sz[pole.first][pole.second].second )
          {

            pole.first+=*status2;
            pole.second+=*status2;

            *status=2;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=2;
        *status2=1;

      case 2:
        if( ( pole.first+*status2 <=7 ) && ( pole.second-*status2 >=0 ) )
        {

          if( sz[pole.first+*status2][pole.second-*status2].first == n )
            return {pole.first+*status2, pole.second-*status2};

          if( sz[pole.first+*status2][pole.second-*status2].second != sz[pole.first][pole.second].second )
          {

            //cerr << "return " << pole.first+*status2 << ' ' << pole.second << ' ';

            pole.first+=*status2;
            pole.second-=*status2;

            *status=3;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=3;
        *status2=1;

      case 3:
        if( ( pole.first-*status2 >=0 ) && ( pole.second-*status2 >=0 ) )
        {

          if( sz[pole.first-*status2][pole.second-*status2].first == n )
            return {pole.first-*status2, pole.second-*status2};

          if( sz[pole.first-*status2][pole.second-*status2].second != sz[pole.first][pole.second].second )
          {

            pole.first-=*status2;
            pole.second-=*status2;

            *status=4;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=4;
        *status2=1;

      default:
        *status=0;
        *status2=0;
        return {-1, -1};

    }

  }

  //cerr << "goniec: 0\n";

  if( sz[pole.first][pole.second].first == h )
  {

    //cerr << "hetman: 1\n";

    *status2 = *status2 + 1;

    switch(*status)
    {

      case 0:
        if( pole.first-*status2 >=0 )
        {

          if( sz[pole.first-*status2][pole.second].first == n )
            return {pole.first-*status2, pole.second};

          if( sz[pole.first-*status2][pole.second].second != sz[pole.first][pole.second].second )
          {

            pole.first-=*status2;

            *status=1;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=1;
        *status2=1;

      case 1:
        if( pole.second+*status2 <=7 )
        {

          if( sz[pole.first][pole.second+*status2].first == n )
            return {pole.first, pole.second+*status2};

          if( sz[pole.first][pole.second+*status2].second != sz[pole.first][pole.second].second )
          {

            pole.second+=*status2;

            *status=2;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=2;
        *status2=1;

      case 2:
        if( pole.first+*status2 <=7 )
        {

          if( sz[pole.first+*status2][pole.second].first == n )
            return {pole.first+*status2, pole.second};

          if( sz[pole.first+*status2][pole.second].second != sz[pole.first][pole.second].second )
          {

            //cerr << "return " << pole.first+*status2 << ' ' << pole.second << ' ';

            pole.first+=*status2;

            *status=3;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=3;
        *status2=1;

      case 3:
        if( pole.second-*status2 >=0 )
        {

          if( sz[pole.first][pole.second-*status2].first == n )
            return {pole.first, pole.second-*status2};

          if( sz[pole.first][pole.second-*status2].second != sz[pole.first][pole.second].second )
          {

            pole.second-=*status2;

            *status=4;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=4;
        *status2=1;

      case 4:
        if( ( pole.first-*status2 >=0 ) && ( pole.second+*status2 <=7 ) )
        {

          if( sz[pole.first-*status2][pole.second+*status2].first == n )
            return {pole.first-*status2, pole.second+*status2};

          if( sz[pole.first-*status2][pole.second+*status2].second != sz[pole.first][pole.second].second )
          {

            pole.first-=*status2;
            pole.second+=*status2;

            *status=5;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=5;
        *status2=1;

      case 5:
        if( ( pole.first+*status2 <=7 ) && ( pole.second+*status2 <=7 ) )
        {

          if( sz[pole.first+*status2][pole.second+*status2].first == n )
            return {pole.first+*status2, pole.second+*status2};

          if( sz[pole.first+*status2][pole.second+*status2].second != sz[pole.first][pole.second].second )
          {

            pole.first+=*status2;
            pole.second+=*status2;

            *status=6;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=6;
        *status2=1;

      case 6:
        if( ( pole.first+*status2 <=7 ) && ( pole.second-*status2 >=0 ) )
        {

          if( sz[pole.first+*status2][pole.second-*status2].first == n )
            return {pole.first+*status2, pole.second-*status2};

          if( sz[pole.first+*status2][pole.second-*status2].second != sz[pole.first][pole.second].second )
          {

            //cerr << "return " << pole.first+*status2 << ' ' << pole.second << ' ';

            pole.first+=*status2;
            pole.second-=*status2;

            *status=7;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=7;
        *status2=1;

      case 7:
        if( ( pole.first-*status2 >=0 ) && ( pole.second-*status2 >=0 ) )
        {

          if( sz[pole.first-*status2][pole.second-*status2].first == n )
            return {pole.first-*status2, pole.second-*status2};

          if( sz[pole.first-*status2][pole.second-*status2].second != sz[pole.first][pole.second].second )
          {

            pole.first-=*status2;
            pole.second-=*status2;

            *status=8;
            *status2=0;
            return {pole.first, pole.second};

          }

        }

        *status=8;
        *status2=1;

      default:
        *status=0;
        *status2=0;
        return {-1, -1};

    }

  }

  //cerr << "hetman: 0\n";

  return { -1, -1 };

}
