#ifndef _ENCHERE_HPP_
#define _ENCHERE_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

//int enchere(string,int);

int enchere(string s, int res)
{
  int act=0;

    if(s == "bluffeur")
    {
      if(res<5)
      {
        //std::cout << " Je suis ! " <<  std::endl;
        act = 1;
      }
      else
      {
        //std::cout << " Je relance ! " <<  std::endl;
        act=2;
      }

    }
    if(s =="peureux")
    {
      if(res<2)
      {
        //std::cout << " Je me couche ! " <<  std::endl;
        act=0;
      }
      else if(res>=3 && res<=8 )
      {
        //std::cout << " Je suis ! " <<  std::endl;
        act=1;
      }
      else
      {
        //std::cout << " Je relance ! " <<  std::endl;
        act=2;
      }
    }

    if(s =="autiste")
    {
      int a = rand()%3;
      if(a==0)
      {
        //std::cout << " Je relance !" <<  std::endl;
        act=2;
      }
      if(a==1)
      {
        //std::cout << " Je suis !" <<  std::endl;
        act =1;
      }
      if(a==2)
      {
        //std::cout << " Je me couche !" <<  std::endl;
        act =0;
      }

    }
  return act;
}
#endif
