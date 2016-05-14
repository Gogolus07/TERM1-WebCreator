/**
 * @file Html.h
 * @brief Classe représentant le html de la page web
 * @author {Lucas CHABALIER, Théophile MANDON}
 * @version 0.1
 * @date 19/03/2016
 * Classe représentant le Html d'une page web
   Contient les liens vers le body et le head de la page
 */

#ifndef HTML_H
#define HTML_H

#include <iostream>
#include "Element.h"
#include "Head.h"
#include "Body.h"

 /**
  * @class Html
  * Classe qui contient l'ensemble de la page web
  */
class Html
{
public:
	Html();
	~Html();

	Body* getBody();
	Head* getHead();

    /**
	* Cree le code html correspondant à la page web
	*/
    std::string toString()const;
    /**
	* Sauvegarde en format json
	*/
	std::string toJson()const;
protected:
	Body *m_body;
	Head *m_head;

};

#endif
