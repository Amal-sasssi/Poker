#ifndef _POKER_HAND_HPP_
#define _POKER_HAND_HPP_

#include <iostream>
#include <time.h>








int Nb_nouvelle_carte(string strategie,int b)
{
  int a;
  int nb;
  if(strategie=="autiste")
  {
    a=rand()%3;
    if(a==0)
    {
      nb=0;
    }
    if(a==0)
    {
      nb=1;
    }
    if(a==0)
    {
      nb=2;
    }
  }
  if(strategie=="peureux")
  {
    if(b>=2)
    {
      nb=0;
    }
    else
    {
      nb=1;
    }
  }
  if(strategie=="bluffeur")
  {
    if(b>=6)
    {
      nb=0;
    }
    else if(b<6 && b>=3)
    {
      nb=1;
    }
    else
    {
      nb=2;
    }
  }
  return nb;
}
