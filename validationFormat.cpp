/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <ctype.h>

using namespace std;
string premierCaractere;
int cleIssn;


int totalAdd = 0;
int modulo = 0;
int cleTrouve = 0;
string verifier = "ISSN";
string test;
int caractereDomaine = 0;


string str_issn;
string str_isbn;


bool
validerFormatNom (const std::string& p_nom)
/*valide le format d'un nom, composé de lettres uniquement, espace et tirer - sont permis s'il y en a pas 2 de suite
 return true ou false*/
{
  if (!isalpha (p_nom[0]))
    return false;
  for (int i = 1; i < p_nom.length (); i++)
    {
      if (!isalpha (p_nom[i]))
        {
          if (p_nom[i] == '-' || p_nom[i] == ' ' )
            {
              if (i == p_nom.length () - 1 || p_nom[i +  1] == '-' || p_nom[i + 1] == ' ')
                return false;
            }
          else
            return false;
        }

    }
  return true;
}


bool
validerCodeIssn (const std::string& p_issn)
/*valide le code issn, verifie a l'aide du calcul de la clé (dernier chiffre)
 exemple de code valide: ISSN 1467-8640
 selon wikipedia:
8e chiffre algo modulo 11 des 7 chiffres précédents si le resultat du calcul est égale a 10
 * la derniere valeur est de 1 a 10 10 == X
 * de 2 a 8 on fait chaque nombre * sa position inversé, on additionne tous les produits et modulo 11, 11-le modulo = dernier chiffre
return true ou false */
{
  premierCaractere = p_issn[0];
  if (premierCaractere != "I")
    return false;

  premierCaractere = p_issn[1];
  if (premierCaractere != "S")
    return false;

  premierCaractere = p_issn[2];
  if (premierCaractere != "S")
    return false;

  premierCaractere = p_issn[3];
  if (premierCaractere != "N")
    return false;

  premierCaractere = p_issn[4];
  if (premierCaractere != " ")
    return false;

  //retirer tout ce qui n'est pas des nombre de la chaine
  str_issn = p_issn;
  str_issn.erase (remove (str_issn.begin (), str_issn.end (), 'I'), str_issn.end ());
  str_issn.erase (remove (str_issn.begin (), str_issn.end (), 'S'), str_issn.end ());
  str_issn.erase (remove (str_issn.begin (), str_issn.end (), 'N'), str_issn.end ());
  str_issn.erase (remove (str_issn.begin (), str_issn.end (), '-'), str_issn.end ());
  str_issn.erase (remove (str_issn.begin (), str_issn.end (), ' '), str_issn.end ());

  //obtenir la cle
  char cleIssnAscii = p_issn[13];
  int verifCleIssnAscii = cleIssnAscii;
  //verifier si la cle est X. si oui mettre 10
  if (verifCleIssnAscii == 88)
    {
      cleIssn = 10;
    }
  else
    {
      cleIssn = cleIssnAscii - 48;
    }


  //calculer la cle

  // mltiplier les nombres selon leurs position
  char premierNombreAscii = str_issn[0];
  int premierNombre = premierNombreAscii - 48;
  int premierMulti = premierNombre * 8;

  premierNombreAscii = str_issn[1];
  premierNombre = premierNombreAscii - 48;
  int deuxMulti = premierNombre * 7;

  premierNombreAscii = str_issn[2];
  premierNombre = premierNombreAscii - 48;
  int troisMulti = premierNombre * 6;

  premierNombreAscii = str_issn[3];
  premierNombre = premierNombreAscii - 48;
  int quatreMulti = premierNombre * 5;

  premierNombreAscii = str_issn[4];
  premierNombre = premierNombreAscii - 48;
  int cinqMulti = premierNombre * 4;

  premierNombreAscii = str_issn[5];
  premierNombre = premierNombreAscii - 48;
  int sixMulti = premierNombre * 3;

  premierNombreAscii = str_issn[6];
  premierNombre = premierNombreAscii - 48;
  int septMulti = premierNombre * 2;

  //additionner les multiplications obtenues
  totalAdd = premierMulti + deuxMulti + troisMulti + quatreMulti + cinqMulti + sixMulti + septMulti;

  //faire le modulo 11 du resultat
  modulo = totalAdd % 11;

  int verifCleIssn = 11 - modulo;
  cout << verifCleIssn << " verifCleIssn" << endl;

  // si le resultat est egal a la cle return true
  if (verifCleIssn != cleIssn)
    return false;
  else
    return true;
}


/*******************************************************************************/
bool
validerCodeIsbn (const std::string& p_isbn)
/*valide un code isbn-13
 "ISBN 978-2-7605-5379-8" -- true
3 premier chiffre doivent etre soit 978 ou 979
Le 13e chiffre est un code clé d’un seul chiffre situé entre 0 et 9 et est déterminé suite à un autre calcul complexe :
 * (1x1 + 3x2 +1x3 +3x4 +x5 + 3x6 + 1x7 + 3x8 + x9 + 3x10 + 1x11 + 3x12 + 1x13) = 0 (mod 10*
 *
de gauche a droite, les index paires sont multiplié par 3, (si index commence a 1) et impair par 1, additionner les resultats, faire le modulo de 10, 10-modulo = dernier chiffre*/
{
  int premiereValeur = 6;
  int deuxValeur = 0;
  int troisValeur = 0;
  int quatreValeur = 0;
  int cinqValeur = 0;
  int valSuivante = 0;
  //verifier si les 1res caracteres sont valides
  premierCaractere = p_isbn[0];
  if (premierCaractere != "I")
    return false;

  premierCaractere = p_isbn[1];
  if (premierCaractere != "S")
    return false;

  premierCaractere = p_isbn[2];
  if (premierCaractere != "B")
    return false;

  premierCaractere = p_isbn[3];
  if (premierCaractere != "N")
    return false;
  premierCaractere = p_isbn[4];
  if (premierCaractere != " ")
    return false;

  int longeureIsbn = p_isbn.length () - 1 ;
  premierCaractere = p_isbn[longeureIsbn];
  if (premierCaractere == "-")
    return false;

  int premierCaractere = p_isbn[5];
  premierCaractere = premierCaractere - 48;
  if (premierCaractere != 9)
    return false;

  premierCaractere = p_isbn[6];
  premierCaractere = premierCaractere - 48;
  if (premierCaractere != 7)
    return false;

  premierCaractere = p_isbn[7];
  premierCaractere = premierCaractere - 48;
  if (premierCaractere != 8 )
    if (premierCaractere != 9 )
      return false;

  premierCaractere = p_isbn[8];
  if (premierCaractere != 45)
    return false;

  premierCaractere = p_isbn[10];
  if (premierCaractere != 45)
    int caractereDomaine = premierCaractere - 48;

  //verif premier domaine 1
  int valeur = p_isbn[9];
  valSuivante = p_isbn[10];
  if (valSuivante - 48 < 0)
    premiereValeur = valeur - 48;



  //verif domaine a 2
  valeur = p_isbn[10];
  valSuivante = p_isbn[11];
  int valAvant = p_isbn[9] - 48;
  if ( valSuivante - 48 < 0)
    if (valeur - 48 > 0)
      if (premiereValeur == 6)
        deuxValeur = ( valAvant * 10) + (valeur - 48);


  //verif domaine a 3
  valeur = p_isbn[11];
  valSuivante = p_isbn[12];
  valAvant = p_isbn[10] - 48;
  int premiereVal = p_isbn[9] - 48;
  if (valSuivante - 48 < 0)
    if ( valeur - 48 > 0)
      if ( deuxValeur == 0)
        troisValeur = (premiereVal * 100)+(valAvant * 10) + (valeur - 48);

  //verif domaine a 4
  valeur = p_isbn[12];
  valSuivante = p_isbn[13];
  valAvant = p_isbn[11] - 48;
  int deuxiemeVal = p_isbn[10] - 48;
  if (valeur - 48 > 0)
    if (deuxValeur == 0)
      if (troisValeur == 0)
        if (valSuivante - 48 < 0)
          int quatreValeur = (premiereVal * 1000)+(deuxiemeVal * 100)+(valAvant * 10) + (valeur - 48);

  //verif domaine a 5
  valeur = p_isbn[13];
  valAvant = p_isbn[12] - 48;
  int troisiemeVal = p_isbn[11] - 48;
  if (valeur - 48 > 0)
    if (deuxValeur == 0)
      if (troisValeur == 0)
        if (quatreValeur == 0)
          cinqValeur = (premiereVal * 10000)+(deuxiemeVal * 1000)+(troisiemeVal * 100)+(valAvant * 10) + (valeur - 48);



  if (cinqValeur < 99000 or cinqValeur > 99999)
    if (quatreValeur < 9900 or quatreValeur > 9989)
      if (troisValeur < 950 or troisValeur > 989)
        if (troisValeur < 600 or troisValeur > 649)
          if (deuxValeur < 80 or deuxValeur > 94)
            if (premiereValeur == 6 or premiereValeur > 7)
              return false;


  for (int i = 0; i < p_isbn.length (); i++ )
    {
      char comparatifUn = p_isbn[i];
      char comparatifDeux = p_isbn[i + 1];

      int comparatifNum = comparatifUn;
      comparatifNum = comparatifNum - 48;

      if (comparatifUn == comparatifDeux)
        if (comparatifNum < 0)
          return false;
      const char tiret = '-';
      const char espace = ' ';
      if (comparatifUn == tiret)
        if (comparatifDeux == espace)
          return false;

      if (comparatifUn == espace)
        if (comparatifDeux == tiret)
          return false;
    }

  //retirer tout ce qui n'est pas des nombre de la chaine
  str_isbn = p_isbn;
  str_isbn.erase (remove (str_isbn.begin (), str_isbn.end (), 'I'), str_isbn.end ());
  str_isbn.erase (remove (str_isbn.begin (), str_isbn.end (), 'S'), str_isbn.end ());
  str_isbn.erase (remove (str_isbn.begin (), str_isbn.end (), 'B'), str_isbn.end ());
  str_isbn.erase (remove (str_isbn.begin (), str_isbn.end (), 'N'), str_isbn.end ());
  str_isbn.erase (remove (str_isbn.begin (), str_isbn.end (), '-'), str_isbn.end ());
  str_isbn.erase (remove (str_isbn.begin (), str_isbn.end (), ' '), str_isbn.end ());



  for (int i = 0; i < str_isbn.length (); i++)
    {
      if (not isdigit (str_isbn[i]))

        return false;
    }
  // mltiplier les nombres selon leurs position
  char NombreAscii = str_isbn[0];
  int Nombre = NombreAscii - 48;
  int premierMulti = Nombre * 1;


  NombreAscii = str_isbn[1];
  Nombre = NombreAscii - 48;
  int deuxMulti = Nombre * 3;


  NombreAscii = str_isbn[2];
  Nombre = NombreAscii - 48;
  int troisMulti = Nombre * 1;


  NombreAscii = str_isbn[3];
  Nombre = NombreAscii - 48;
  int quatreMulti = Nombre * 3;


  NombreAscii = str_isbn[4];
  Nombre = NombreAscii - 48;
  int cinqMulti = Nombre * 1;

  NombreAscii = str_isbn[5];
  Nombre = NombreAscii - 48;
  int sixMulti = Nombre * 3;

  NombreAscii = str_isbn[6];
  Nombre = NombreAscii - 48;
  int septMulti = Nombre * 1;


  NombreAscii = str_isbn[7];
  Nombre = NombreAscii - 48;
  int huitMulti = Nombre * 3;

  NombreAscii = str_isbn[8];
  Nombre = NombreAscii - 48;
  int neufMulti = Nombre * 1;

  NombreAscii = str_isbn[9];
  Nombre = NombreAscii - 48;
  int dixMulti = Nombre * 3;

  NombreAscii = str_isbn[10];
  Nombre = NombreAscii - 48;
  int onzeMulti = Nombre * 1;

  NombreAscii = str_isbn[11];
  Nombre = NombreAscii - 48;
  int douzeMulti = Nombre * 3;

  //additionner les multiplications obtenues
  totalAdd = premierMulti + deuxMulti + troisMulti + quatreMulti + cinqMulti + sixMulti + septMulti + huitMulti + neufMulti + dixMulti + onzeMulti + douzeMulti;

  //faire le modulo 10 du resultat
  modulo = totalAdd % 10;

  int verifCleIsbn = 10 - modulo;
  int cleIsbnAscii = str_isbn[12];
  int cleIsbn = cleIsbnAscii - 48;

  if (verifCleIsbn != cleIsbn)
    return false;

  return true;
}