#ifndef _POKER_HAND_HPP_
#define _POKER_HAND_HPP_

#include <iostream>


typedef struct _CARTE_{
int valeur; // 0 à 12 pour As à Roi
int couleur; // 0 à 3 (trefle, carreau, coeur et pique)
} CARTE;





int poker_hand(CARTE cards[5])
{
  int res = 0;
  int i,j,k;
  int valeur_i, valeur_j, valeur_k;
  int nb_carte =5;
  int couleur_i, couleur_j;
  int v=0;
  int c=0;
  int couleur,valeur,max;

/////////////////////////////////////////////////////
/* On cherche une quinte flush royal*/

  for(i=0; i<nb_carte; ++i)
  {
    valeur_i = cards[i].valeur;
    if(valeur_i>=9 || valeur_i==0)
    {
      v=v+1;
    }

  }
  if(v==5)
  {
      couleur_i=cards[0].couleur;
      for(j=1;j<nb_carte;j++)
      {
        couleur_j=cards[j].couleur;
        if(couleur_i == couleur_j)
        {
          c=c+1;
        }
      }

  }
    if(c==4)
    {
      res =9;
      //std::cout<<  "J'ai une quinte flush royal" << std::endl;
    }


//////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/* On cherche une Quinte flush*/

if(res==0)
{
  int r=0;
  int min=0;
  int max=0;
  int min1=0;
  int max1=0;
  int j,i;
  int nb_carte=5;
  for(j=1;j<nb_carte;j++)
  {
    i=0;
    for(i=0;i<j;i++)
    {
      while(cards[j].valeur<cards[i].valeur)
      {
        min =cards[j].valeur;
        cards[j].valeur = cards[i].valeur;
        cards[i].valeur=min;
        min1 =cards[j].couleur;
        cards[j].couleur = cards[i].couleur;
        cards[i].couleur=min1;
      }
    }


  }
  /*std::cout<<  cards[0].valeur << std::endl;
  std::cout<<  cards[1].valeur << std::endl;
  std::cout<< cards[2].valeur << std::endl;
  std::cout<<  cards[3].valeur << std::endl;
  std::cout<<  cards[4].valeur << std::endl;*/

  for(i=1;i<nb_carte;i++)
  {
    if(cards[i].valeur==cards[i-1].valeur+1)
    {
      r=r+1;

    }

  }
  c=0;
  if(r==4)
  {
      couleur_i=cards[0].couleur;
      for(j=1;j<nb_carte;j++)
      {
        couleur_j=cards[j].couleur;
        if(couleur_i == couleur_j)
        {
          c=c+1;
        }
      }

  }


  if(c==4)
  {
    res=8;
    //std::cout<<  "J'ai une quinte" << std::endl;
  }


}

//////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/* On cherche un Carré*/

if(res==0)
{
  c=0;
  for(i=0;i<nb_carte;++i)
  {
    for(j=i; j<nb_carte;++j)
    {
      if(cards[j].valeur == cards[i].valeur)
      {
        c=c+1;
        if(c==4)
        {
          //std::cout<<  "J'ai un carré " << std::endl;
          i = nb_carte;
          res = 7;
          j=nb_carte;
        }
      }
    }
    c=0;
  }




}

//////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/* On cherche une Main pleine */

if(res==0)
{
  for( i = 0; i< nb_carte; ++i)
  {
    valeur_i = cards[i].valeur;
    for(int j = i+1; j< nb_carte; ++j)
    {
      valeur_j = cards[j].valeur;
      if(valeur_j == valeur_i)
      {
        for(int k = j+1; k< nb_carte; ++k)
        {
          int valeur_k = cards[k].valeur;
          if(valeur_k == valeur_i)
          {
            res =3 ;
            valeur = cards[k].valeur;
            if(res == 3) break;

          }
        }
      }
    }
  }
  if(res==3)
  {
    for( i = 0; i< nb_carte; i++)
    {
      if(cards[i].valeur != valeur)
      {
        valeur_i = cards[i].valeur;
        for(j = i+1; j <nb_carte;j++)
        {
          valeur_j = cards[j].valeur;
          if(valeur_i == valeur_j)
          {
            res  = 6;
            //std::cout<<  "J'ai une main pleine" << std::endl;
            j=nb_carte;
            i=nb_carte;



          }

        }

      }


    }
    if(res==3)
    {
      j=nb_carte;
      i=nb_carte;
      res =0;
    }
  }

}


//////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/* On cherche une Couleur*/

if(res == 0)
{
    int c_coeur=0;
    int c_pique=0;
    int c_trefle =0;
    int c_carreaux =0;
    for(int i =0; i<nb_carte ;++i)
        {
            if( cards[i].couleur == 0) {c_coeur ++;}
            if( cards[i].couleur == 1) {c_carreaux ++;}
            if( cards[i].couleur == 2) {c_trefle ++;}
            if( cards[i].couleur == 3) {c_pique ++;}
        }

    if(c_coeur == 5 || c_pique == 5 || c_trefle ==5 || c_carreaux ==5  )
    {
      res = 5;
      //std::cout<<  "J'ai une couleur " << std::endl;
    }

}

//////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/* On cherche une Suite*/

if(res==0)
{
  int r=0;
  int min=0;
  int max=0;
  int min1=0;
  int max1=0;
  int j,i;
  int nb_carte=5;
  for(j=1;j<nb_carte;j++)
  {
    i=0;
    for(i=0;i<j;i++)
    {
      while(cards[j].valeur<cards[i].valeur)
      {
        min =cards[j].valeur;
        cards[j].valeur = cards[i].valeur;
        cards[i].valeur=min;
        min1 =cards[j].couleur;
        cards[j].couleur = cards[i].couleur;
        cards[i].couleur=min1;
      }
    }


  }
  /*std::cout<<  cards[0].valeur << std::endl;
  std::cout<<  cards[1].valeur << std::endl;
  std::cout<< cards[2].valeur << std::endl;
  std::cout<<  cards[3].valeur << std::endl;
  std::cout<<  cards[4].valeur << std::endl;*/

  for(i=1;i<nb_carte;i++)
  {
    if(cards[i].valeur==cards[i-1].valeur+1)
    {
      r=r+1;

    }

  }
  v=0;
  for(i=0; i<nb_carte; ++i)
  {
    valeur_i = cards[i].valeur;
    if(valeur_i>=9 || valeur_i==0)
    {
      v=v+1;
    }

  }


  if(r==4 || v==5)
  {
    res=4;
    //std::cout<<  "J'ai une suite" << std::endl;
  }


}
/////////////////////////////////////////////////////


/////////////////////////////////////////////////////
/* On cherche un brelan*/
if(res==0)
{
  for( i = 0; i< nb_carte; ++i)
  {
    valeur_i = cards[i].valeur;
    for(int j = i+1; j< nb_carte; ++j)
    {
      valeur_j = cards[j].valeur;
      if(valeur_j == valeur_i)
      {
        for(int k = j+1; k< nb_carte; ++k)
        {
          int valeur_k = cards[k].valeur;
          if(valeur_k == valeur_i)
          {
            res =3 ;
            valeur = cards[k].valeur;
            if(res == 3)
            {
              //std::cout<<  "J'ai un brelan" << std::endl;

              break;
            }

          }
        }
      }
    }
  }
}
/////////////////////////////////////////////////////
/* On cherche une double paire*/

if(res==0)
{
  for( i = 0; i< nb_carte; ++i)
  {
    valeur_i = cards[i].valeur;
    couleur_i = cards[i].couleur;
    for(j = i+1; j <nb_carte;++j)
    {
      valeur_j = cards[j].valeur;
      if(valeur_i == valeur_j)
      {
        i = nb_carte;
        res  = 1;
        couleur = cards[j].couleur;
        valeur = cards[j].valeur;
        break;


      }
    }
  }
  if(res==1)
  {
    for( i = 0; i< nb_carte; ++i)
    {
      if(cards[i].couleur != couleur && cards[i].valeur != valeur)
      {
        valeur_i = cards[i].valeur;
        couleur_j = cards[i].couleur;
        for(j = i+1; j <nb_carte;++j)
        {
          valeur_j = cards[j].valeur;
          if(valeur_i == valeur_j)
          {
            i=nb_carte;
            res  = 2;
            //std::cout<<  "J'ai une double paire" << std::endl;

            break;


          }
        }
      }


    }
  }
}




/////////////////////////////////////////////////////
/* On cherche une paire*/

  if(res==0 || res==1)
  {
    for( i = 0; i< nb_carte; ++i)
    {   valeur_i = cards[i].valeur;
      for(j = i+1; j <nb_carte;++j)
      {
        valeur_j = cards[j].valeur;
        if(valeur_i == valeur_j)
        {
          res  = 1;
          //std::cout<<  "J'ai une paire" << std::endl;

          break;
        }
      }
    }
  }



//////////////////////////////////////////////////////

    return res;
}
#endif
