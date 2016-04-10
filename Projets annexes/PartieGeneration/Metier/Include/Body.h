/**
 * @file Body.h
 * @brief Classe représentant le body de la page web
 * @author {Lucas CHABALIER, Théophile MANDON}
 * @version 0.1
 * @date 19/03/2016
 * Classe représentant le body d'une page web
 */

#ifndef BODY_H
#define BODY_H

#include <iostream>
#include <vector>
#include "Element.h"


 /*
  * @class Body
  * Classe héritée d'Element qui contient l'ensemble des éléments de la page ( = <body>...</body>)
  */
class Body : public Element
{
public:
	Body();
	~Body();

    std::string toString() const;
	std::string toJson();
};
#endif
