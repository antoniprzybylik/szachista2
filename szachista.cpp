#include "global.hpp"
#include "ruch.hpp"
#include "optymalny_ruch.hpp"

#include "szachistaConfig.h"

#include "termios.h"

static struct termios str_termios, trz_termios;

void nioset(int echo)
{

  tcgetattr(0, &str_termios);
  trz_termios = str_termios;
  trz_termios.c_lflag &= ~ICANON;

  if(echo)
    trz_termios.c_lflag |= ECHO;
  else
    trz_termios.c_lflag &= ~ECHO;

  tcsetattr(0, TCSANOW, &trz_termios);

}

void sioset(void)
{

  tcsetattr(0, TCSANOW, &str_termios);

}

bool czyszachowane(pair<int, int> prepole, pair<int, int> pole, typ t, szachownica sz, pair<int, int> *l2m, do_roszady *drszd)
{

  ////cerr << "\nczyszachowane " << pole.first << ", " << pole.second << ", " << int(t) << '\n';

  pair<figura, typ> pcb=sz[prepole.first][prepole.second];
  sz[prepole.first][prepole.second]={n, t};

  pair<figura, typ> cb=sz[pole.first][pole.second];
  sz[pole.first][pole.second]={k, t};

  for(int i=0;i<8;i++)
  {

    for(int j=0;j<8;j++)
    {

      if( ( sz[i][j].second != t ) && ( sz[i][j].first != n ) && ( sz[i][j].first != k ) )
      {

        int local_status = 0;
        int local_status2 = 0;

        ruch({-1, -1}, &local_status, &local_status2, sz, l2m, drszd);

        while(true)
        {

          pair<int, int> r=ruch({i, j}, &local_status, &local_status2, sz, l2m, drszd);

          if( r.first == -1 )
            break;

          if( r == pole )
          {

            sz[pole.first][pole.second]=cb;
            sz[prepole.first][prepole.second]=pcb;
            return true;

          }

        }

      }

    }

  }

  sz[pole.first][pole.second]=cb;
  sz[prepole.first][prepole.second]=pcb;

  if( ( pole.first < 7 ) && ( pole.second > 0 ) )
    if( ( sz[pole.first+1][pole.second-1] == make_pair(k, ntyp(t)) ) )
      return true;

  if( pole.first < 7 )
    if( ( sz[pole.first+1][pole.second] == make_pair(k, ntyp(t)) ) )
      return true;

  if( ( pole.first < 7 ) && ( pole.second < 7 ) )
    if( ( sz[pole.first+1][pole.second+1] == make_pair(k, ntyp(t)) ) )
      return true;

  if( pole.second < 7 )
    if( ( sz[pole.first][pole.second+1] == make_pair(k, ntyp(t)) ) )
      return true;

  if( pole.second > 0 )
    if( ( sz[pole.first][pole.second-1] == make_pair(k, ntyp(t)) ) )
      return true;

  if( ( pole.first > 0 ) && ( pole.second < 7 ) )
    if( ( sz[pole.first-1][pole.second+1] == make_pair(k, ntyp(t)) ) )
      return true;

  if( pole.first > 0 )
    if( ( sz[pole.first-1][pole.second] == make_pair(k, ntyp(t)) ) )
      return true;

  if( ( pole.first > 0 ) && ( pole.second > 0 ) )
    if( ( sz[pole.first-1][pole.second-1] == make_pair(k, ntyp(t)) ) )
      return true;

  return false;

}

char lifig(figura f)
{

  switch(f)
  {

    case p:
      return 'p';

    case s:
      return 's';

    case g:
      return 'g';

    case w:
      return 'w';

    case h:
      return 'h';

    case k:
      return 'k';

    default:
      return ' ';

  }

}

vector< pair<int, int> > apply( pair< pair<int, int>, pair<int, int> > terazruch, szachownica sz, pair<int, int> *l2m, do_roszady* drszd)
{

  vector< pair<int, int> > modpol = { terazruch.first, terazruch.second };

  sz[terazruch.second.first][terazruch.second.second] = sz[terazruch.first.first][terazruch.first.second];
  sz[terazruch.first.first][terazruch.first.second] = {n, b};

  if( sz[terazruch.second.first][terazruch.second.second].first == k )
  {

    if( ( terazruch.first.second == 3 ) && ( terazruch.second.second == 1 ) )
    {

      sz[terazruch.first.first][terazruch.first.second-1] = sz[terazruch.first.first][terazruch.first.second-3];
      sz[terazruch.first.first][terazruch.first.second-3] = {n, b};

      modpol.push_back({terazruch.first.first, terazruch.first.second-1});
      modpol.push_back({terazruch.first.first, terazruch.first.second-3});

    }

    if( ( terazruch.first.second == 3 ) && ( terazruch.second.second == 5 ) )
    {

      sz[terazruch.first.first][terazruch.first.second+1] = sz[terazruch.first.first][terazruch.first.second+4];
      sz[terazruch.first.first][terazruch.first.second+4] = {n, b};

      modpol.push_back({terazruch.first.first, terazruch.first.second+1});
      modpol.push_back({terazruch.first.first, terazruch.first.second+4});

    }

  }

  if( ( sz[terazruch.second.first][terazruch.second.second].first == p ) && ( sz[terazruch.second.first][terazruch.second.second].second == b ) && ( ( l2m->first == terazruch.second.first-1 ) && ( l2m->second == terazruch.second.second ) ) )
  {

    sz[l2m->first][l2m->second] = {n, b};
    modpol.push_back({l2m->first, l2m->second});

  }

  if( ( sz[terazruch.second.first][terazruch.second.second].first == p ) && ( sz[terazruch.second.first][terazruch.second.second].second == c ) && ( ( l2m->first == terazruch.second.first+1 ) && ( l2m->second == terazruch.second.second ) ) )
  {

    sz[l2m->first][l2m->second] = {n, b};
    modpol.push_back({l2m->first, l2m->second});

  }

  if( sz[terazruch.second.first][terazruch.second.second].first == p )
    if( ( ( sz[terazruch.second.first][terazruch.second.second].second == b ) && ( terazruch.first.first == 1 ) && ( terazruch.second.first == 3 ) ) || ( ( sz[terazruch.second.first][terazruch.second.second].second == c ) && ( terazruch.first.first == 6 ) && ( terazruch.second.first == 4 ) ) )
    {

      *l2m = terazruch.second;
      return modpol;

    }

   //promocja piona na hetmana color true białe

  if( color && ( sz[terazruch.second.first][terazruch.second.second].second == b ) && ( sz[terazruch.second.first][terazruch.second.second].first == p ) && terazruch.second.first == 7 )
    sz[terazruch.second.first][terazruch.second.second].first = h;

   //promocja piona na hetmana color false czarne

  if( !color && ( sz[terazruch.second.first][terazruch.second.second].second == c ) && ( sz[terazruch.second.first][terazruch.second.second].first == p ) && terazruch.second.first == 0 )
    sz[terazruch.second.first][terazruch.second.second].first = h;

  if( sz[terazruch.second.first][terazruch.second.second].first == k ) // do roszady król
  {

    if( sz[terazruch.second.first][terazruch.second.second].second == b )
      drszd->crkb = true;

    if( sz[terazruch.second.first][terazruch.second.second].second == c )
      drszd->crkc = true;

  }

  if( sz[terazruch.second.first][terazruch.second.second].first == w ) // do roszady wieża
  {

    if( sz[terazruch.second.first][terazruch.second.second].second == b )
    {

      if( terazruch.first == make_pair(0, 0) )
        drszd->crwb1 = true;

      if( terazruch.first == make_pair(0, 7) )
        drszd->crwb2 = true;

    }

    if( sz[terazruch.second.first][terazruch.second.second].second == c )
    {

      if( terazruch.first == make_pair(7, 0) )
        drszd->crwc1 = true;

      if( terazruch.first == make_pair(7, 7) )
        drszd->crwc2 = true;

    }

  }

  if( l2m->first != -1 )
    if( sz[terazruch.second.first][terazruch.second.second].second == sz[l2m->first][l2m->second].second ) // !!!
      *l2m = {-1, -1};

  return modpol;

}

bool valid( pair< pair<int, int>, pair<int, int> > terazruch, bool color )
{

  ////cerr << "\nvalid { { " << terazruch.first.first << ", " << terazruch.first.second << " }, { " << terazruch.second.first << ", " << terazruch.second.second << " } }, " << int(color) << '\n';

  if( color )
  {

    if( gra[terazruch.first.first][terazruch.first.second].second == b )
      return false;

  }
  else
  {

    if( gra[terazruch.first.first][terazruch.first.second].second == c )
      return false;

  }

  ////cerr << "color: 1\n";

  szachownica sym;
  pair<int, int> local_l2m = main_l2m;
  do_roszady local_do_roszady = main_do_roszady;
  kopiuj(sym, gra);
  apply(terazruch, sym, &local_l2m, &local_do_roszady);

  for(int i=0;i<8;i++)
  {

    for(int j=0;j<8;j++)
    {

      if( ( sym[i][j].first == k ) && ( ( color && ( sym[i][j].second == c ) ) || ( !color && ( sym[i][j].second == b ) ) ) && czyszachowane({i, j}, {i, j}, sym[i][j].second, sym, &local_l2m, &local_do_roszady) )
        return false;

    }

  }

  pair<int, int> r;

  ruch({-1, -1}, &main_status, &main_status2, gra, &main_l2m, &main_do_roszady );

  ////cerr << "reset: 1\n";

  while(true)
  {

    r=ruch(terazruch.first, &main_status, &main_status2, gra, &main_l2m, &main_do_roszady );

    ////cerr << "\n{ " << r.first << ", " << r.second << " } == { " << terazruch.second.first << ", " << terazruch.second.second << " }\n";

    if( r.first == -1 )
      break;

    ////cerr << "\n{ " << r.first << ", " << r.second << " } == { " << terazruch.second.first << ", " << terazruch.second.second << " }\n";

    if( r == terazruch.second )
    {

      ////cerr << "check: 1\n";

      ruch({-1, -1}, &main_status, &main_status2, gra, &main_l2m, &main_do_roszady );
      return true;

    }

  }

  ////cerr << "check: 0\n";

  return false;

}

void rysuj(bool color)
{

  if( color )
  {

    cout << "  ";

    for(char i='H';i>='A';i--)
    {

      cout << "  " << i << "  ";

    }

    cout << '\n';

    for(int i=0;i<8;i++)
    {

      cout << "\33[0m" << i+1 << ' ';

      for(int j=0;j<8;j++)
      {

        cout << "\33[0m";

        if( (i+j)%2 )
          cout << "\33[1;48;5;238m";
        else
          cout << "\33[1;48;5;248m";

        if( gra[i][j].second == b )
          cout << "\33[38;5;15m";
        else
          cout << "\33[38;5;0m";

        cout << "  " << lifig(gra[i][j].first) << "  ";

      }

      cout << "\33[0m " << i+1 <<  "\n  ";

      for(int j=0;j<8;j++)
      {

        cout << "\33[0m";

        if( (i+j)%2 )
          cout << "\33[1;48;5;238m";
        else
          cout << "\33[1;48;5;248m";

        if( gra[i][j].second == b )
          cout << "\33[38;5;15m";
        else
          cout << "\33[38;5;0m";

        cout << "     ";

      }

      cout << '\n';

    }

    cout << "\33[0m";

    cout << "  ";

    for(char i='H';i>='A';i--)
    {

      cout << "  " << i << "  ";

    }

  }
  else
  {

    cout << "  ";

    for(char i='A';i<'I';i++)
    {

      cout << "  " << i << "  ";

    }

    cout << '\n';

    for(int i=7;i>=0;i--)
    {

      cout << "\33[0m" << i+1 << ' ';

      for(int j=7;j>=0;j--)
      {

        cout << "\33[0m";

        if( (i+j)%2 )
          cout << "\33[1;48;5;238m";
        else
          cout << "\33[1;48;5;248m";

        if( gra[i][j].second == b )
          cout << "\33[38;5;15m";
        else
          cout << "\33[38;5;0m";

        cout << "  " << lifig(gra[i][j].first) << "  ";

      }

      cout << "\33[0m " << i+1 <<  "\n  ";

      for(int j=0;j<8;j++)
      {

        cout << "\33[0m";

        if( !( (i+j)%2 ) )
          cout << "\33[1;48;5;238m";
        else
          cout << "\33[1;48;5;248m";

        if( gra[i][j].second == b )
          cout << "\33[38;5;15m";
        else
          cout << "\33[38;5;0m";

        cout << "     ";

      }

      cout << '\n';

    }

    cout << "\33[0m";

    cout << "  ";

    for(char i='A';i<'I';i++)
    {

      cout << "  " << i << "  ";

    }

  }

  cout << "\33[0m";

}

int main(void)
{

  srand(std::chrono::high_resolution_clock().now().time_since_epoch().count());
  ios_base::sync_with_stdio(0);

  string input;

  system("clear");

  cout << "szachista " << szachista_VERSION_MAJOR << "." << szachista_VERSION_MINOR << "\n\n";

  cout << "czas na ruch komputera ( czas zalecany to 15 )\n";
  cout << "> ";
  getline(cin, input);
  czas_na_ruch = stod(input); //może się wywalić

  //system("clear");
  cout << "\n\nbiałe (b) / czarne (c)?\n";

  while( ( input != "b" ) && ( input != "c" ) )
  {

    cout << "> ";
    getline(cin, input);

  }

  if( input == "c" )
    color=true;

  cout << "\nnaciśnij dowolny klawisz w celu rozpoczęcia gry... " << flush;

  nioset(0);
  char zzzzzzzzzzzzzzzzzzzzzzzzz = getchar();
  sioset();

  ruch({-1, -1}, &main_status, &main_status2, gra, &main_l2m, &main_do_roszady );

  if(color)
  {

    system("clear");
    // rysuj(color);
    //
    // cout << "\nmyślę..." << endl;
    //
    // apply( ruszaj(gra, &main_l2m, &main_do_roszady, b), gra, &main_l2m, &main_do_roszady );

    if( rand() % 2 )
      apply( { {1, 3}, {3, 3} }, gra, &main_l2m, &main_do_roszady );
    else
      apply( { {1, 4}, {3, 4} }, gra, &main_l2m, &main_do_roszady );

  }

  for(;;)
  {

    system("clear");
    rysuj(color);

    cout << '\n';

    ////cerr << "l2m: { " << l2m.first << ", " << l2m.second << " }\n\n";

    for(;;)
    {

      cout << "> ";
      getline(cin, input);

      if( ( (input.size() == 4) && ( ( input[0] >= 'a' ) && ( input[0] <= 'h' ) ) && ( ( input[1] >= '1' ) && ( input[1] <= '8' ) ) && ( ( input[2] >= 'a' ) && ( input[2] <= 'h' ) ) && ( ( input[3] >= '1' ) && ( input[3] <= '8' ) ) ) && !( ( input[0] == input[2] ) && ( input[1] == input[3] ) ) && valid( { { input[1]-'1', 7-(input[0]-'a') }, { input[3]-'1', 7-(input[2]-'a') } }, color ) )
        break;

      cout << "zły ruch!\n";

    }

    apply( { { input[1]-'1', 7-(input[0]-'a') }, { input[3]-'1', 7-(input[2]-'a') } }, gra, &main_l2m, &main_do_roszady );

    if( ( gra[input[3]-'1'][7-(input[2]-'a')].first == p ) && ( ( ( ( input[3]-'1' ) == 0 ) && gra[input[3]-'1'][7-(input[2]-'a')].second == c ) || ( ( ( input[3]-'1' ) == 7 ) && gra[input[3]-'1'][7-(input[2]-'a')].second == b ) ) ) // promocja piona
    {

      int x = input[3]-'1';
      int y = 7-(input[2]-'a');

      system("clear");
      rysuj(color);

      cout << "\ns/g/w/h?\n\n";

      for(;;)
      {

        cout << "> ";
        getline(cin, input);

        if( input == "s" )
        {

          gra[x][y].first = s;
          break;

        }

        if( input == "g" )
        {

          gra[x][y].first = g;
          break;

        }

        if( input == "w" )
        {

          gra[x][y].first = w;
          break;

        }

        if( input == "h" )
        {

          gra[x][y].first = h;
          break;

        }

      }

    }

    system("clear");
    rysuj(color);

    cout << "\nmyślę..." << endl;

    if(color)
      apply( ruszaj(gra, &main_l2m, &main_do_roszady, b), gra, &main_l2m, &main_do_roszady );
    else
      apply( ruszaj(gra, &main_l2m, &main_do_roszady, c), gra, &main_l2m, &main_do_roszady );

  }

  return 0;

}
