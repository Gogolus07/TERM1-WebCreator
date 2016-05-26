/**
 * @file Module.h
 * @brief Fonction utilisée pour la gestion des modules
 * @author {Lucas CHABALIER, Théophile MANDON}
 * @version 0.1
 * @date 26/03/2016
 * Fonction utilisée pour la gestion des modules
   Va chercher si les modules correspondant aux elements utilisés sont existants et les charge en mémoire
 */

#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>
#include <fstream>
#include "Element.h"
#include "json/json.h"

/**
 * @fn moduleToElement
 * @brief Fonction qui va lire un .json pour permettre le passage du module à un Element de la page web
 * @param Element &elem : Un élément, qui a au moins un nom de module
 * @return Modifie l'élément si le JSON est correctement trouvé, sinon ne fait rien.
 */
void moduleToElement(Element& e);

#endif
