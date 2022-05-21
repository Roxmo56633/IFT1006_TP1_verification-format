/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   validation_format.h
 * Author: etudiant
 *
 * Created on 15 mai 2022, 18:49
 */

#ifndef VALIDATION_FORMAT_H
#define VALIDATION_FORMAT_H


//déclarer les constantes s'il y en a

//appel de fonction ici: avec; a la fin de chacun d'entre elles
bool validerFormatNom (const std::string& p_nom);
bool validerCodeIssn (const std::string& p_issn);
bool validerCodeIsbn (const std::string& p_isbn);

#endif /* VALIDATION_FORMAT_H */

