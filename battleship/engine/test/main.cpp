/**
 * @file   main.cpp
 * @Author jalcoleam@gmail.com
 * @date   November, 2015
 * @brief  
 *
 * Detailed 
 */

#include "common.h"
#include "ship.h"
#include "fleet.h"

using namespace std;


disp_result inteligent_cpu_play (fleet *p)
{
  disp_result res = agua;
  static disp_result prev_res=agua; 

  static int last_xy [2];
  int x;
  int y;
  int tiro_ok=-1; 
  while (tiro_ok !=0)
  {
    if (prev_res==tocado) 
    {
      if (!p->used(last_xy[0]-1,last_xy[1]) || 
          !p->used(last_xy[0]+1,last_xy[1]) || 
          !p->used(last_xy[0]  ,last_xy[1]-1) || 
          !p->used(last_xy[0]  ,last_xy[1]-1))
      {
        x=random(last_xy[0]+1,last_xy[0]-1);
        y=random(last_xy[1]+1,last_xy[1]-1);
      }
      else 
      {
      x=random(7);
      y=random(7);
      }
    }
    else 
    {
      x=random(7);
      y=random(7);
    }

    if (!p->used(x,y)) tiro_ok = 0;
  }
  res =  p->disparo(x,y);
  cout << "shoot: " << x<<":"<<y<< " " << print_disp_result (res) << endl;
  prev_res = res;
  last_xy [0]=x;
  last_xy [1]=y;
   
  return res;
}

disp_result cpu_play (fleet *p)
{
  int x;
  int y;
  disp_result res = agua;
  x=random(7);
  y=random(7);
  res =  p->disparo(x,y);
  cout << "shoot: " << x<<":"<<y<< " " << print_disp_result (res) << endl;
  return res;
}


void allocate_random_ships(fleet * p,int num_ships)
{
  int res  = 0;
  int cont = 0;

  while (cont <num_ships)
  {
    //res = p->nuevo_barco ( random(7),random(7),(orientacion)(random(1)),4);
    res = p->new_ship ( random(7),random(7),(orientacion)(random(1)),random(4,1));
    if (res == 0) cont++;
  }

//  p->print();
}

void allocate_fixed_ships(fleet * p, int num_ships)
{
  int res = 0;
  res = p->new_ship ( 7,0,vertical,4);
  res = p->new_ship ( 0,0,vertical,4);
  res = p->new_ship ( 7,4,vertical,4);
  res = p->new_ship ( 0,4,vertical,4);
  p->print();
}

int main (int argc, char * argv [])
{
  fleet p1;
  fleet p2;
  disp_result disp;
  cout << "\nPLAYER 1 SHIPS ALLOCATED " << endl;
  allocate_random_ships (&p1,4);

  cout << "\nPLAYER 2 SHIPS ALLOCATED " << endl;
  allocate_random_ships (&p2,4);

  cout << "\nPLAY START\n" << endl;

  while (1)
  {
    sleep (0.5);
    cout << "\nPLAYER 1 SHIPS " << endl;
    p1.print ();

    cout << "\nPLAYER 2 SHIPS " << endl;
    p2.print ();

    cout << "PLAYER 1 ";
    disp = inteligent_cpu_play(&p2);
    //cout << print_disp_result (disp) << " SCORE " << p2.score() << endl;
    if (disp == derrota) 
    {
      cout << "PLAYER 1 WIN" << endl;
      p2.print();
      break;
    }

    cout << "PLAYER 2 ";
    disp= cpu_play(&p1);
    //cout << print_disp_result (disp) << " SCORE "<< p1.score()<<endl;
    if (disp == derrota) 
    {
      cout << "PLAYER 2 WIN" << endl;
      p1.print();
      break;
    }
  }
  return 0;
}
