/**
 * @file PageWeb.h
 * @brief Classe repr�sentant la page web
 * @author {Lucas CHABALIER, Th�ophile MANDON}
 * @version 0.1
 * @date 19/03/2016
 * Classe repr�sentant la page web
   Contient le lien vers le html et le nom de la page
 */

#ifndef PAGEWEB_H
#define PAGEWEB_H

#include <iostream>
#include <string>
#include <fstream>
#include "Html.h"
#include "json/json.h"

 /**
  * @class PageWeb
  * Classe qui contient un HTML et le nom de la page web
  */
class PageWeb
{
	protected:
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

        /**
        * Cree le code html correspondant � la page web
        */
		std::string toString()const;
		/**
		* Cr�e le fichier html correspondants � la page web
		* @param le dossier dans lequel les pages html vont �tre cr��es
		*/
		void generate(std::string);

        /**
        * Sauvegarde en format json
        */
		std::string toJson();
		/**
		* Cr�e le fichier json de sauvegarde
		*/
		void sauvegarde();
};

#endif
