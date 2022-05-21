/**
 * \file programmePrincipal.cpp
 * \brief
 */

#include <iostream>
#include <array>
#include "fonctionsUtilitaires.h"
using namespace std;

//int MAX_ETUDIANTS = 4;
//const int MAX_EXAMENS = 2;


int
main ()
{
  int num;
  int nbEleves;
  array<array<int, MAX_EXAMENS>, MAX_ETUDIANTS> tabNotes;

  bool valeurCorrecte = false;
  while (!valeurCorrecte)
    {
      cout << "Saisissez le nombre d'élèves" << endl;
      cin >> nbEleves;
      if (nbEleves > 0 && nbEleves <= MAX_ETUDIANTS)
        {
          valeurCorrecte = true;
        }
    }
  cout << "Saisir uniquement des nombres entiers positifs et inférieurs à 100 " << endl <<
          "(ce programme ne prend pas en charge la validation de saisie)" << endl;
  saisieNotes (tabNotes, &nbEleves);
  cout << '\n';
  cout << "nombre d'étudiants : " << nbEleves << endl;
  cout << "note minimum : " << minimum (tabNotes, &nbEleves) << endl; //dans tout le monde
  cout << "note maximum :" << maximum (tabNotes, &nbEleves) << endl; //dans tout le monde
  cout << "écart type : " << ecartType (tabNotes[0]) << endl; //du 1re etudiant

  afficherTableau (tabNotes, &nbEleves);
  return 0;
}
