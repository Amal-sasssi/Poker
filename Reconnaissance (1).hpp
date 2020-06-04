#ifndef _RECONNAISSANCE_HPP_
#define _RECONNAISSANCE_HPP_

#include "cartes.hpp"
#include <iostream>



int Reconnaissance(int valeur, char const* couleur)
{
  if(couleur == "trèfle")
  {

    std::cout << "Ma carte est : " << cartes::trefles[cartes::id_cartes(valeur)] << std::endl;

  }

  if(couleur == "coeur")
  {

    std::cout << "Ma carte est : " << cartes::coeurs[cartes::id_cartes(valeur)] << std::endl;

  }

  if(couleur == "carreau")
  {

    std::cout << "Ma carte est : " << cartes::carreaux[cartes::id_cartes(valeur)] << std::endl;

  }

  if(couleur == "pique")
  {

    std::cout << "Ma carte est : " << cartes::piques[cartes::id_cartes(valeur)] << std::endl;

  }

}
#endif
