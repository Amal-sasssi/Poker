#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cartes.hpp"
#include <iostream>
#include "Reconnaissance.hpp"
#include "poker_hand.hpp"
#include "enchere.hpp"
#include "Nb_nouvelle_carte.hpp"
//#include "Elimine_carte.hpp"



using namespace std;


char const *Valeur[] = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "valet", "dame", "roi"};  //Toutes les valeurs des cartes
char const *Couleur[] = {"trèfle", "carreau", "coeur", "pique"}; //Toutes les couleurs des cartes



typedef struct Joueur
{
    string strategie;
    int nb_jeton;
} Joueur;   //Structure du joueur il y aura sa stratégie ainsi que son nombre de jeton qui lui reste

//Définition des fonctions
string strategie(Joueur);
void InitialiseJeu();


CARTE Jeu[52]; //Tableau de toutes les cartes du jeu
int gMax; // indice de carte maximal
CARTE mes_cartes[5]; //Mes cartes (valeur et couleur)
CARTE joueur1[5]; //Les cartes des joueurs (valeur et couleur)



string strategie(Joueur j) //Donne une strategie pour le joueur peureux, autiste ou bluffeur
{
  int b;
  b = rand()%3; // b=0,1,2
  string strat[3]; //tableau contenant les stratégies
  strat[0]="bluffeur";
  strat[1]="peureux";
  strat[2]="autiste";

  j.strategie = strat[b]; //pour le joueur j on lui donne une strategie
  //std::cout << strat[b] << std::endl;
  return(strat[b]);
}




// Initialisation du jeu
void InitialiseJeu()
{
  int v, c, i;;
  i = 0;
  for (c=0; c<=3; c++)
  {
    for (v=0; v<13; v++)
    {
      Jeu[i].valeur = v; //on initialise le jeu avec toutes les cartes
      Jeu[i].couleur = c;
      i++;
    }
  }
}

//Fonction on distribue
CARTE *Distribue(CARTE *pCarte)
{
  int indice;

  if (gMax)
  {
    indice = rand()%(gMax);
  }
  else
  {
    indice = 0;
  }
// on renseigne la carte choisie, prise au hasard
 *pCarte = Jeu[indice];

// On insère la dernière carte du paquet à la place !!!
  Jeu[indice] = Jeu[gMax];
  gMax--;
  return pCarte;
}



int main(int argc, char **argv)
{
  std::cout << " Bienvenu pour une nouvelle partie de Poker ! " << std::endl;


  CARTE Nouvelle_carte[5]; //Le nouveau paquet de carte quand on a enlevé un ou deux cartes
  int nb_carte_new; //Nombre de nouvelle carte que l'on veut
  int i,j,k; //indices
  int joueur_present[8]; //Tableau indiquant si une personne s'est couchée (0) a mit tapis (2) ou continue le jeu(1)
  Joueur joueur[8]; //8 joueurs avec leur strategie et nombre de jeton qu'il leur reste
  CARTE Carte;
  int cave=100; //Les caves que l'on peut alimenter notre tapis
  int mise[8]; //Les mises que l'on a devant nous
  CARTE Car[100]; //Car on ne peut pas redistribuer avec le meme paquet de carte du coup tableau de toutes les redistributions
  CARTE Carte1[8][5]; //Tableau de nos 8 joueurs et leur cartes
  int a;
  int z;

  for(i=0;i<7;i++)
  {
    joueur[i].nb_jeton =1000; //Initialise le nombre de jeton

    z=rand()%3+1; //Pour faire aléatoirement notre tapis
    mise[i]=0;
    mise[i]=mise[i]+z*cave;
    std::cout <<" Le joueur " << i << " prend pour tapis : " << mise[i] << std::endl;
    joueur[i].nb_jeton= joueur[i].nb_jeton - mise[i];

  }
  joueur[7].nb_jeton=1000;
  std::cout << "Combien vous voulez prendre pour votre tapis: (100 ou 200 ou 300)" << std::endl;
  std::cin >> mise[7];
  joueur[7].nb_jeton=joueur[7].nb_jeton-mise[7];

  srand(time(NULL)); // initialiser le générateur aléatoire
  gMax = 51;
  InitialiseJeu(); // Initialise notre jeu

  for(i=0; i<5; i++)
  {
    for (j=0; j<8; j++)
    {
      Distribue(&Carte); //On distribue a une a une les cartes

      Carte1[j][i].valeur= Carte.valeur; //On enregistre la valeur et la couleur de la carte

      Carte1[j][i].couleur= Carte.couleur;
      //std::cout << "La carte de : " << j << std::endl;
      //Reconnaissance(Carte.valeur, Couleur[Carte.couleur]);


      if(j==7)
      {
        mes_cartes[i].valeur =Carte.valeur;
        mes_cartes[i].couleur = Carte.couleur;
        //Reconnaissance(Carte.valeur, Couleur[Carte.couleur]);
      }
      std::cout << "Joueur" << j << " : " << std::endl;

      std::cout << "Dos de la carte : " << cartes::dos << std::endl;
    }
  }
  for(k=0;k<5;k++)
  {

    Reconnaissance(Carte1[7][k].valeur, Couleur[Carte1[7][k].couleur]); //On montre nos cartes
  }
  for(k=0;k<7;k++)
  {
    //std::cout << " La stratégie du joueur " << k+1 << " est : " << std::endl;

    joueur[k].strategie=strategie(joueur[k]); //On donne une strategie a tous les joueurs
    //std::cout<<  joueur[k].strategie << std::endl;

  }

  int mon_enchere[8]; //Les encheres de tous le monde

  for(k=0;k<8;k++)
  {
    joueur_present[k]=1; //Les joueurs sont tous dans la partie
    mon_enchere[k]=0; //Ce que je vais encherir
  }

  int nb_joueur_present = 8;
  int t;
  int point_max;
  int joueur_max_point[8];
  int mi=0; //La mise qui va varier tout au long de l'enchere
  int b[8]; //On fait un tableau avec la valeur de la combinaison que la personne a
  int c; //Notre enchere si on se couche, on suit ou on relance
  string action;
  int coucher; //Nombre de personne qui s'est couché
  int suivre; //Nombre de personne qui a suivu
  int relancer=1; //Nombre de personne qui a relancer
  string s; //Strategie
  float pot; //Le nombre de jeton total qu'on met au milieu de la table
  float pot1;
  int max=300; //Ce que l'on a le maximum dans le tapis
  int nb_joueur_point_max; //Le nombre de joueur qui ont le meme nombre max de point
  int partie=1; //Numero des parties
  int tour=0; //Nombre de tour par partie
  int reapprovisionner=0;
  int elimine=0;
  while(elimine!=7)
  {

  nb_joueur_point_max=0;
  point_max=0;
  for(j=0;j<8;j++)
  {
    joueur_max_point[j]==0;

  }
    tour=0;
    mi=0;
    pot=0;
    mi=mi+partie;
    std::cout<< " On lance le jeu à " << mi << std::endl;
    relancer=1;
    coucher=0;
    while(relancer>0 && coucher!=7)
    {

      tour=tour+1;
      relancer=0;
      suivre=0;
      coucher=0;

      for(t=0;t<7;t++)
      {

        if(joueur_present[t]==1 && mi<max)
        {

          s = joueur[t].strategie;
          b[t]=poker_hand(Carte1[t]);
          std::cout<< " Le joueur " << t << " a " << b[t]  << std::endl;

          c = enchere(s,b[t]);

          if(c==2 && mi<max)
          {

            if(s=="bluffeur")
            {
              mon_enchere[t]=rand()%99+1;
              if(mi+mon_enchere[t]>=mise[t])
              {
                if(mi>=mise[t])
                {
                  relancer=relancer+1;
                  coucher=coucher+1;
                  pot = pot+mise[t];
                  std::cout<< " Le joueur " << t << " suit et met son tapis " << mise[t] << " Le pot est " << pot << std::endl;
                  joueur_present[t]=2;
                  mise[t]=0;
                }
                else
                {

                  mi=mi+mise[t];
                  mon_enchere[t]=mise[t];
                  pot=pot+mon_enchere[t];
                  coucher=coucher+1;
                  joueur_present[t]=2;
                  std::cout<< " Le joueur " << t << " relance et met son tapis " << mise[t] << " Le pot est " << pot << std::endl;
                  std::cout<< " L'enchere est à " << mi << std::endl;

                  mise[t]=0;

                }

              }
              else
              {
                relancer=relancer+1;
                mi=mon_enchere[t]+mi;
                pot=pot+mi;
                mise[t]=mise[t]-mi;


                std::cout<< " Le joueur " << t << " relance de : " << mon_enchere[t] << " Le pot est " << pot << std::endl;
                std::cout<< " L'enchere est à " << mi << std::endl;

              }

            }
            if(s=="peureux")
            {
              mon_enchere[t]=rand()%79+1;
              if(mi+mon_enchere[t]>=mise[t])
              {
                if(mi>=mise[t])
                {
                  pot = pot+mise[t];
                  joueur_present[t]=2;

                  std::cout<< " Le joueur " << t << " suit et met son tapis " << mise[t] << " Le pot est " << pot << std::endl;
                  coucher=coucher+1;
                  mise[t]=0;
                }
                else
                {
                  mi=mi+mise[t];
                  mon_enchere[t]=mise[t];
                  coucher=coucher+1;
                  joueur_present[t]=2;
                  pot=pot+mon_enchere[t];

                  std::cout<< " Le joueur " << t << " met son tapis " << mise[t] << " Le pot est " << pot << std::endl;
                  std::cout<< " L'enchere est à " << mi << std::endl;

                  mise[t]=0;

                }

              }
              else
              {
                relancer=relancer+1;

                mi=mon_enchere[t]+mi;
                pot=pot+mi;
                mise[t]=mise[t]-mi;


                std::cout<< " Le joueur " << t << " relance de : " << mon_enchere[t] << " Le pot est " << pot << std::endl;
                std::cout<< " L'enchere est à " << mi << std::endl;

              }


            }

            if(s=="autiste")
            {
              relancer=relancer+1;
              mon_enchere[t]=rand()%139+1;
              if(mi+mon_enchere[t]>=mise[t])
              {
                if(mi>=mise[t])
                {
                  pot = pot+mise[t];
                  joueur_present[t]=2;

                  std::cout<< " Le joueur " << t << " suit et met son tapis " << mise[t] << " Le pot est " << pot << std::endl;

                  mise[t]=0;
                }
                else
                {
                  mi=mi+mise[t];
                  mon_enchere[t]=mise[t];

                  joueur_present[t]=2;
                  pot=pot+mon_enchere[t];

                  std::cout<< " Le joueur " << t << "relance et met son tapis " << mise[t] << " Le pot est " << pot << std::endl;
                  std::cout<< " L'enchere est à " << mi << std::endl;

                  mise[t]=0;

                }

              }
              else
              {
                mi=mon_enchere[t]+mi;
                pot=pot+mi;
                mise[t]=mise[t]-mi;


                std::cout<< " Le joueur " << t << " relance de : " << mon_enchere[t] << " Le pot est " << pot << std::endl;
                std::cout<< " L'enchere est à " << mi << std::endl;

              }

            }
          }
            //std::cout<<  t << " Sa stratégie est :" << s << std::endl;

          if(c==0 && mi<max)
          {

            coucher=coucher+1;
            joueur_present[t]=0;
            if(relancer==0)
            {
              mise[t]=mise[t]-partie;
              pot = pot+partie;
            }
            //mise[t]=mise[t]-10;
            //pot =pot+10;
            std::cout<< " Le joueur " << t <<" se couche " << " Le pot est " << pot << std::endl;

          }
          if(c==1 && mi<max)
          {
            suivre=suivre+1;
            if(mi>=mise[t])
            {


              joueur_present[t]=2;
              pot=pot+mise[t];

              std::cout<< " Le joueur " << t << " met son tapis " << mise[t] << " Le pot est " << pot << std::endl;
              std::cout<< " L'enchere est à " << mi << std::endl;

              mise[t]=0;
            }
            else
            {
              pot=pot+mi;

              std::cout<< " Le joueur " << t << " suit : " << mi << " Le pot est " << pot << std::endl;
              std::cout<< " L'enchere est à " << mi << std::endl;

              mise[t]=mise[t]-mi;


            }

          }

        }


      }



      if(joueur_present[7]==1 &&  mi<max && mise[7]>0)
      {
        b[7]=poker_hand(Carte1[7]);
        std::cout<<" Nombre de point : " << b[7] <<std::endl;


        std::cout<<"Que voulez-vous faire ? (Je me couche ! (A), Je suis ! (B), Je mise ! (C))" <<std::endl;
        action="D";
        while(action != "A" && action != "B" && action != "C")
        {
          std::cin >> action;
        }
        if(action == "A")
        {
          std::cout<<  "Vous vous couchez !" << std::endl;
          coucher=coucher+1;
          joueur_present[7]=0;
          if(relancer==0)
          {
            mise[7]=mise[7]-partie;
            pot=pot+partie;
          }

        }
        if(action == "B")
        {
          std::cout<<  "Vous suivez !" << std::endl;
          suivre=suivre+1;

          if(mi<mise[7])
          {
            pot=pot+mi;
            mise[7]=mise[7]-mi;
            std::cout<< " L'enchere est à " << mi << std::endl;
            joueur_present[7]=1;

          }
          else
          {
            joueur_present[7]=2;
            std::cout<< " Je met mon tapis " << mise[7] << std::endl;
            std::cout<< " L'enchere est à " << mi << std::endl;
            joueur_present[7]=0;
            pot=pot+mise[7];
            mise[7]=0;
          }
          if(mise[7]<=0)
          {
            joueur_present[7]=2;

          }

        }
        if(action == "C")
        {
          std::cout<<  "Vous relancez, " << " il faut relancer de plus de " << mi <<" Et il vous reste "<< mise[7]<<std::endl;
          std::cin >> mon_enchere[7];
          mi=mi+mon_enchere[7];
          std::cout<< " L'enchere est à " << mi << std::endl;
          joueur_present[7]=1;
          relancer=relancer+1;
          pot=pot+mi;
          mise[7]=mise[7]-mi;
          if(mise[7]<=0)
          {
            joueur_present[7]=2;

          }

      }
      std::cout<< " J'ai "  << mise[7] << " jetons " << std::endl;

      for(i=0;i<7;i++)
      {
        if(joueur_present[i]==1 && relancer>0 && coucher!=7)
        {
          nb_carte_new=Nb_nouvelle_carte(joueur[i].strategie,b[i]);
          std::cout<< " Le joueur " << i << " veux échanger : " << nb_carte_new << " cartes "<< std::endl;

          for(j=1;j<=nb_carte_new;j++)
          {
            //Nouvelle_carte = Elimine_carte(joueur[i].strategie,Carte1[t], b[j]);
            if(gMax>0)
            {
              if(partie==1)
              {
                Distribue(&Carte);

                Carte1[i][j].valeur= Carte.valeur; //On enregistre la valeur et la couleur de la carte

                Carte1[i][j].couleur= Carte.couleur;
                std::cout << "La nouvelle carte de : " << i << std::endl;
                //Reconnaissance(Carte1[i][j].valeur, Couleur[Carte1[i][j].couleur]);

                  std::cout << "Dos de la carte : " << cartes::dos << std::endl;
                  std::cout << "La carte de : " << j << std::endl;
                  //Reconnaissance(Carte1[i][j].valeur, Couleur[Carte1[i][j].couleur]);
              }
              else
              {
                Distribue(&Carte);

                Carte1[i][j].valeur= Car[partie-1].valeur; //On enregistre la valeur et la couleur de la carte

                Carte1[i][j].couleur= Car[partie-1].couleur;
                //std::cout << "La nouvelle carte de : " << j << std::endl;
                //Reconnaissance(Car[partie].valeur, Couleur[Car[partie].couleur]);
                  //std::cout << "Dos de la carte : " << cartes::dos << std::endl;
                  std::cout << "La carte de : " << j << std::endl;
                  Reconnaissance(Carte1[i][j].valeur, Couleur[Carte1[i][j].couleur]);

              }
            }


          }
        }


      }
      if(gMax>0 && joueur_present[7]==1 && relancer>0 && coucher!=7)
      {
        for(k=0;k<5;k++)
        {

          Reconnaissance(Carte1[7][k].valeur, Couleur[Carte1[7][k].couleur]); //On montre nos cartes
        }
        std::cout << "Combien voulez-vous échanger de carte : " << std::endl;
        std::cin >> nb_carte_new;
        while(nb_carte_new>0)
        {
          nb_carte_new--;
          std::cout << "Vous vous voulez échanger quelle carte : (Donner le rang de la carte dans votre paquet (0,1,....4))" << std::endl;
          std::cin >> i;
          if(partie==1)
          {
            Distribue(&Carte);

            Carte1[7][i].valeur= Carte.valeur; //On enregistre la valeur et la couleur de la carte

            Carte1[7][i].couleur= Carte.couleur;
            std::cout << "Ma nouvelle carte est : " << std::endl;
            Reconnaissance(Carte1[7][i].valeur, Couleur[Carte1[7][i].couleur]);

          }
          else
          {
            Distribue(&Car[partie-1]);

            Carte1[7][i].valeur= Car[partie-1].valeur; //On enregistre la valeur et la couleur de la carte

            Carte1[7][i].couleur= Car[partie-1].couleur;
            //std::cout << "La nouvelle carte de : " << j << std::endl;
            //Reconnaissance(Car[partie].valeur, Couleur[Car[partie].couleur]);

              std::cout << "Ma nouvelle carte est : " <<  std::endl;
              Reconnaissance(Carte1[7][i].valeur, Couleur[Carte1[7][i].couleur]);
              for(i=0;i<5;i++)
              {
                Reconnaissance(Carte1[7][i].valeur, Couleur[Carte1[7][i].couleur]);

              }

          }

        }
      }



    }

  }
  std::cout<< " Le pot est " << pot << std::endl;

  if(coucher!=7)
  {
    point_max=0;
    nb_joueur_point_max=0;
    for(j=0;j<8;j++)
    {
      if(b[j]>=point_max && (joueur_present[j]==2 || joueur_present[j]==1))
      {
        point_max=b[j];
      }

    }
    for(j=0;j<8;j++)
    {
      if(b[j]==point_max && (joueur_present[j]==2 || joueur_present[j]==1))
      {
        nb_joueur_point_max=nb_joueur_point_max+1;

        joueur_max_point[j]==1;
        std::cout<< " Le joueur " << j << " a le nombre max de point " << " il a "<< b[j] <<std::endl;

        /*for(i=0;i<5;i++)
        {
          //Reconnaissance(Carte1[j][i].valeur, Couleur[Carte1[j][i].couleur]); //On montre nos cartes

        }*/
      }

    }
    pot1 = pot/nb_joueur_point_max;
    std::cout<< " Le nombre de joueur ayant le maximun de point est : " << nb_joueur_point_max <<std::endl;

    for(j=0;j<8;j++)
    {

      if(nb_joueur_point_max>1 || coucher<7 || relancer > 1)
      {

        std::cout<< " Le joueur " << j << " dois montrer ses cartes "<< std::endl;
        for(i=0;i<5;i++)
        {
          Reconnaissance(Carte1[j][i].valeur, Couleur[Carte1[j][i].couleur]); //On montre nos cartes

        }

      }
      if(nb_joueur_point_max==1 && b[j]==point_max && (joueur_present[j]==2 || joueur_present[j]==1))
      {
        mise[j]= mise[j]+pot;
        std::cout<< " Le joueur " << j << " a gagné la mise, il empauche " << pot << " Et sa mise est : " <<mise[i] << std::endl;


      }


    }
    if(nb_joueur_point_max>1)
    {
      for(i=0;i<8;i++)
      {
        if(b[i]==point_max && (joueur_present[i]==2 || joueur_present[i]==1))
        {
          mise[i]= mise[i]+pot1;


        }
      }

    }


    //compare()
  }
  else
  {
    for(i=0;i<8;i++)
    {
      if(joueur_present[i]==1)
      {
        std::cout<< " Le joueur " << i << " a gagné la mise, il empauche " << pot << std::endl;
        mise[i]= mise[i]+pot;

      }
    }

  }

  for(i=0;i<7;i++)
  {
    if(joueur_present[i]>=0 && (joueur[i].nb_jeton >0 ||  mise[i]>10))
    {
      //std::cout<< " A Le joueur " << i << " a  " << mise[i] << " devant lui et en reserve " << joueur[i].nb_jeton << std::endl;
      if(joueur[i].nb_jeton >0)
      {
        joueur_present[i]=1;
        reapprovisionner=rand()%3;
        while(reapprovisionner*cave>joueur[i].nb_jeton >0)
        {
          reapprovisionner=rand()%3;

        }
        mise[i]=mise[i]+cave*reapprovisionner;
        joueur[i].nb_jeton = joueur[i].nb_jeton - cave*reapprovisionner;
        if(mise[i]<=10)
        {
          //std::cout<< "  B Le joueur " << i << " a  " << mise[i] << " devant lui et en reserve " << joueur[i].nb_jeton << std::endl;

          mise[i]=mise[i]+cave;
          joueur[i].nb_jeton = joueur[i].nb_jeton-cave;
        }
      }

      /*if(joueur[i].nb_jeton <0)
      {
        //std::cout<< " C Le joueur " << i << " a  " << mise[i] << " devant lui et en reserve " << joueur[i].nb_jeton << std::endl;

        mise[i]=mise[i]-cave*reapprovisionner;
        joueur[i].nb_jeton =cave*reapprovisionner;
        mise[i]=mise[i]+joueur[i].nb_jeton;
      }*/
    }
    else if(joueur[i].nb_jeton <=0 &&  mise[i]<=10)
    {
      //std::cout<< "  D Le joueur " << i << " a  " << mise[i] << " devant lui et en reserve " << joueur[i].nb_jeton << std::endl;

      joueur_present[i]=-1;
      std::cout<< " Le joueur " << i << " est éliminé car il n'a pas de jeton  "  << std::endl;
      elimine =elimine+1;

    }
    std::cout<< " Le joueur " << i << " a  " << mise[i] << " devant lui et en reserve " << joueur[i].nb_jeton << std::endl;


  }


  if(mise[7]>=10)
  {
    if(joueur_present[7]>=0)
    {
      joueur_present[7]=1;

    }
    if(joueur[7].nb_jeton>0)
    {
      reapprovisionner=rand()%3;

      mise[7]=mise[7]+cave*reapprovisionner;
      joueur[7].nb_jeton = joueur[7].nb_jeton - cave*reapprovisionner;
      if(joueur[7].nb_jeton<0)
      {
        mise[7]=mise[7]+joueur[7].nb_jeton;
        joueur[7].nb_jeton = 0;
      }

    }

    std::cout<< " Le joueur " << 7 << " a  " << mise[7] << " devant lui et en reserve " << joueur[7].nb_jeton << std::endl;


    //std::cout<< " Le joueur " << 7 << " a  " << mise[7] << " devant lui et en reserve " << joueur[7].nb_jeton << std::endl;


  }
  else
  {
    if(joueur_present[7]>=0)
    {
      if(joueur[7].nb_jeton>=0)
      {
        joueur_present[7]=1;
        mise[7]=mise[7]+cave;
        joueur[7].nb_jeton = joueur[i].nb_jeton-cave;
      }
      else
      {
        joueur_present[7]=-1;
        std::cout<< " Vous êtes éliminé  "  << std::endl;
        elimine =elimine+1;

      }

    }
  }
  //std::cout<< " J'ai  " << mise[i] << " devant moi et en reserve " << joueur[i].nb_jeton << " Je suis " << joueur_present[7] << std::endl;
  srand(time(NULL)); // initialiser le générateur aléatoire
  gMax = 51;

  InitialiseJeu(); // Initialise notre jeu
  partie=partie+1;

  for(i=0; i<8; i++)
  {

      for (j=0; j<5; j++)
      {
        if(joueur_present[i]==1)
        {
          Distribue(&Car[partie-1]); //On distribue a une a une les cartes

          Carte1[i][j].valeur= Car[partie-1].valeur; //On enregistre la valeur et la couleur de la carte

          Carte1[i][j].couleur= Car[partie-1].couleur;
          //std::cout << "La nouvelle carte de : " << j << std::endl;
          //Reconnaissance(Car[partie].valeur, Couleur[Car[partie].couleur]);



        }

      }


  }
  for(i=0;i<5;i++)
  {
      std::cout << "Ma nouvelle carte est : " <<  std::endl;
      Reconnaissance(Carte1[7][i].valeur, Couleur[Carte1[7][i].couleur]);

  }








}


}
