/**
 * @file   fleet.cpp
 * @Author jalcoleam@gmail.com
 * @date   November, 2015
 * @brief  
 *
 * Detailed 
 */

#include "fleet.h"

fleet::fleet()
{
  int x;
  int y;
  
  _score = 0;
  for (y=0; y< MAX_Y; y++)
    for (x=0; x< MAX_X; x++)
      play [y][x]=' ';
}


int fleet::new_ship (int x, int y, orientacion o, int l){
  char matriz[MAX_TAM_BARCO*2];
  int matriz_len=0;
  int cont=0;

  ship * b;
  if      ((o == horizontal) && ((x+l) > MAX_X)) return -1; // ERROR
  else if ((o == vertical) && ((y+l)   > MAX_Y)) return -1; // ERROR
 
  b = new ship (x,y,o,l);
  matriz_len=b->get_matrix (matriz);  
 
  cout << " BARCO MATRIZ "; 
  for (cont=0;cont<matriz_len*2 ;cont++) cout <<  (int)matriz [cont] <<" ";
  cout << endl;

  for (cont=0;cont<(matriz_len*2);cont+=2) if (play[(int)matriz[cont]][(int)matriz[cont+1]]=='@') break;
  if (cont<(matriz_len*2))
  {
    delete b;
    return -1;
  }

  for (cont=0;cont<(matriz_len*2);cont+=2) 
  {
    //cout << " PAINTING MATRIZ " << (int)matriz[l] << ":" << (int)matriz[l+1]<<endl;
    play[(int)matriz[cont]][(int)matriz[cont+1]]='@';
  }
  barcos.push_back (b); 

  return 0;
}

void fleet::print()
{
    int cont = 0;
    int cont_x = 0;
    int cont_y = 0;

    cout << "   ";
    for (cont = 0; cont < MAX_X;cont++) cout << (char)('A' + cont)<< " ";
    cout << endl;

    cout << "   ";
    for (cont = 0; cont < MAX_X;cont++) cout << "##";
    cout << endl;

    for (cont_y=0;cont_y<MAX_Y;cont_y++)
    {
      cout << cont_y+1 << " #";
      for (cont_x=0;cont_x<MAX_Y;cont_x++) cout << play[cont_y][cont_x] << " ";
      cout << "#" << endl;
    }
    
    cout << "   ";
    for (cont = 0; cont < MAX_X;cont++) cout << "##";
    cout << endl;
    cout << "SCORE :" << _score << endl;
}

disp_result fleet::disparo (int x, int y, int * score)
{
  disp_result res_flota=derrota;
  disp_result res;
  unsigned int cont =0;
  for (cont=0; cont< barcos.size(); cont++)
  {
    if (barcos[cont]->estado()!=hundido)
    {
      res = barcos[cont]->disparo (x,y);
//      cout << "resultado disparo " << x <<","<< y<<" ship number " << cont << "result  " <<res << endl;
      if (res != agua) break;
    }
  }
  if (res == agua) 
  {
    //cout << " MODIFYING POSITION FROM " << play[y][x] << " TO o"<< endl;
    play[y][x]='o';
  }
  else 
  {
    //cout << " MODIFYING POSITION FROM " << play[y][x] << " TO X"<< endl;
    play[y][x]='X';
  for (cont=0;cont<barcos.size();cont++)
    {
      if (barcos[cont]->estado() != hundido) 
      {
        res_flota=agua;
        break;
      }
    }
    if (res_flota == derrota) res = derrota;
  }
 // cout << "return disparos " << res << endl;
  _score += points_table[res];
  if (score != NULL) *score = _score;
  return res;
}

bool fleet::used (int x,int y)
{
  if ((MAX_X<=x) || (MAX_Y<=y)) return true;
  if (play[y][x]==' ' || play[y][x]=='@')return false;
  else return true;
}

int fleet::score()
{
  return _score;
}

