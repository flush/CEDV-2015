/**
 * @file   ship.cpp
 * @Author jalcoleam@gmail.com
 * @date   November, 2015
 * @brief  
 *
 * Detailed
 */



#include "ship.h"

ship::ship (int x, int y, orientacion orient, int length, int id)
{
 this->_x_init = x;
 this->_y_init = y;
 this->_orient = orient;
 this->_length = length;
 this->_estado = agua;
 this->_id     = id;
 iniciar_matriz();
}


int  ship::x ()
{
  return this->_x_init;
}

int  ship::id ()
{
  return this->_id;
}

void ship::id (int id)
{
  this->_id = id;
}

int  ship::y ()
{
  return this->_y_init;
}

orientacion ship::orient()
{
  return this->_orient;
}

int ship::length()
{
  return this->_length;
}

disp_result ship::disparo(int x, int y)
{
  int cont = 0;
  disp_result resultado = agua;
  for (cont=0; cont<_length;cont++)
  {
    if ((_x_ro[cont] == x) && (_y_ro[cont]==y))
    {
      resultado = tocado;
      _x[cont] = -1;
      _y[cont] = -1;
      break;
    }
  }
  
  for (cont = 0; cont < _length; cont ++)
  {
    if ((_x[cont]>=0) && (_y[cont] >=0))
    {
      break;
    }
  }

  if ((resultado == tocado) && cont == _length) 
  {
    resultado = hundido;
  }
  //cout <<"ship " << x<<","<<y<<" : " << resultado << endl;
  _estado   = resultado;
  return resultado;
}

void ship::iniciar_matriz ()
{
  int cont =0;

  _x[0]= _x_init;
  _y[0]= _y_init;

  //cout << __FUNCTION__ << ": inicio x,y : " << _inicio_x << "," <<_inicio_y<<endl;
  if (_orient ==horizontal)
  {
  //cout << __FUNCTION__ << ": HORIZONTAL"<<endl;

    for (cont=1;cont<_length; cont++)
    {
      _x[cont]=_x_init+cont;
      _y[cont]=_y_init;
  //cout << __FUNCTION__ << ":" << cont << " x,y : " << _x[cont] << "," <<_y[cont]<<endl;
    } 
  }
  else
  {
  //cout << __FUNCTION__ << ": VERTICAL"<<endl;
    for (cont=1;cont<_length; cont++)
    {
      _x[cont]=_x_init;
      _y[cont]=_y_init+cont;
//  cout << __FUNCTION__ << ":" << cont << " x,y : " << _x[cont] << "," <<_y[cont]<<endl;
    } 
  }

  for (cont=0; cont <_length; cont++) 
  {
    _x_ro[cont]=_x[cont];
    _y_ro[cont]=_y[cont];
  }
}

int ship::get_matrix (char * matrix)
{
  int cont=0;

  for (cont=0;cont<_length;cont++)
  {
     matrix[cont*2]=_y[cont];
     matrix[(cont*2)+1]=_x[cont];
  //cout << __FUNCTION__ << ":" << cont << " x,y : " << (int)matriz[cont*2] << "," <<(int)matriz[(cont*2)+1]<<endl;
  }
  return cont;
}

void ship::print ()
{
  cout << " BARCO LEN " << _length<< endl;
  for (int y=0;y<_length;y++)
    for (int x=0;x<_length;x++)
      cout << "x:y " << x<<":"<<y<< " -> "<<_x[x]<<":"<<_y[y]<<endl;
}

disp_result ship::estado ()
{
  return _estado;
}
