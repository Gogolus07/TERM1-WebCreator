/**
 * @file Head.h
 * @brief Classe représentant le Head de la page web
 * @author {Lucas CHABALIER, Théophile MANDON}
 * @version 0.1
 * @date 19/03/2016
 * Classe représentant le Head d'une page web
   Contient les liens vers les scripts JS, feuilles de style CSS, et définitions des métadonnées
 */

#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include "Element.h"

 /**
  * @class Head
  * Classe qui contient l'ensemble des liens css,js, les métadonnées, et le titre d'une page web
  */
class Head
{
public:
	Head();
	Head(std::string);
	~Head();

	/**
	* Sauvegarde en format json
	*/
	std::string toJson();
	/**
	* Cree le code html correspondant au head de la page web
	*/
	std::string toString()const;

	//Getters & setters
	std::string getTitle()const;
	void setTitle(std::string);

	std::string getScript(unsigned int)const;
	void addScript(std::string);
	void removeScript(unsigned int);

	std::string getLink(unsigned int)const;
	void addLink(std::string);
	void removeLink(unsigned int);

protected:
    std::string m_title;
    std::vector<std::string> m_scripts;
    std::vector<std::string> m_links;
};
#endif
