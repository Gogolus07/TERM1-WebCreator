/**
 * @file PageWeb.h
 * @brief Classe représentant la page web
 * @author {Lucas CHABALIER, Théophile MANDON}
 * @version 0.1
 * @date 19/03/2016
 * Classe représentant la page web
   Contient le lien vers le html et le nom de la page
 */

#ifndef PAGEWEB_H
#define PAGEWEB_H

#include <iostream>
#include <string>
#include <fstream>
#include "Html.h"
#include "json/json.h"

//Contient un HTML
class PageWeb
{
	private:
		std::string m_nom;
		Html m_root;
	public:
		PageWeb();
		PageWeb(std::string);

        Element* recupererElement(Json::Value);
        void charger(std::string);

		std::string getNom()const;
		void setNom(std::string);

		Html* getRoot();

		std::string toString()const;
		void generate(std::string);

		std::string toJson();
		void sauvegarde();
};

#endif
