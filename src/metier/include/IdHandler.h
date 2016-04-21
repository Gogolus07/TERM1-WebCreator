/**
 * @file IdHandler.h
 * @brief Classe représentant la gestion des id pour les balises
 * @author {Lucas CHABALIER, Théophile MANDON}
 * @version 0.1
 * @date 19/03/2016
 * Classe représentant la gestion des id pour les balises
   Va générer les id des balises de la forme : nomBaliseX avec X le numéro correspondant au nombre de fois ou la balise a été utilisée
 */

#ifndef IDHANDLER_H
#define IDHANDLER_H

#include <iostream>
#include <string>
#include <map>

static std::map<std::string, int> ids;

/**
 * @fn generateId
 * @brief Fonction qui génère l'ID d'un élément (pour le CSS)
 * @param string elementName : le nom de l'élément
 * @return l'ID de l'élément, sous la forme : elementNameX (x étant la xième occurence du type de l'élément)
 */
std::string generateId(std::string);

#endif
