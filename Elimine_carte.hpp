#ifndef _ELIMINE_CARTE_HPP_
#define _ELIMINE_CARTE_HPP_

#include <iostream>
#include <time.h>
#include "poker_hand.hpp"








int Elimine_carte(string strategie,CARTE Carte[5], int b)
{
  CARTE carte_elimine;
  int a=1;
  int i;
  int c_coeur=0;
  int c_pique=0;
  int c_trefle =0;
  int c_carreaux =0;
  if(strategie=="autiste")
  {
    a=rand()%5;
  }
  if(strategie=="peureux")
  {
    if(b==0)
    {
      for(i=0;i<5;i++)
      {
        if(a>=Carte[i].valeur && Carte[i].valeur>0)  //On elimine la plus petite valeur
        {
          a=i;
        }
      }

      for( i =0; i<5 ;++i) //On essaye de voir si on a au moins 3 ou 4 cartes meme couleur pour nous debarasser de cette carte
          {
              if( cards[i].couleur == 0) {c_coeur ++;}
              if( cards[i].couleur == 1) {c_carreaux ++;}
              if( cards[i].couleur == 2) {c_trefle ++;}
              if( cards[i].couleur == 3) {c_pique ++;}
          }

      if(c_coeur == 4 || c_coeur==3)
      {
        for(i=0;i<5;i++)
        {
          if(Carte[i].couleur != 0)
          {
            a=i;

          }
        }
      }
      if(c_pique == 4 || c_pique==3)
      {
        for(i=0;i<5;i++)
        {
          if(Carte[i].couleur != 3)
          {
            a=i;

          }
        }
      }
      if(c_trefle ==4 || c_trefle==3)
      {
        for(i=0;i<5;i++)
        {
          if(Carte[i].couleur != 2)
          {
            a=i;

          }
        }
      }
      if(c_carreaux ==4 || c_carreaux ==3)
      {
        for(i=0;i<5;i++)
        {
          if(Carte[i].couleur != 1)
          {
            a=i;

          }
        }
      }


    }
  }
  return a;
}
#endif
