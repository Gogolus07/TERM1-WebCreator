/**
 * @file Site.h
 * @brief Classe repr�sentant l'ensemble du site web
 * @author {Lucas CHABALIER, Th�ophile MANDON}
 * @version 0.1
 * @date 19/03/2016
 * Classe repr�sentant l'ensemble du site web
   Contient le nombre de pages max autoris�es, le nom du projet et toutes les pages web contenues dans le projet
 */

#ifndef SITE_H
#define SITE_H

#include <iostream>
#include <vector>
#include <string>
#include "PageWeb.h"

 /**
  * @class Site
  * Classe qui contient un ensemble de pages web
  */
class Site
{
    protected:
        unsigned int m_numberOfPagesMax;
        std::string m_nomProjet;
        std::vector<PageWeb> m_projet;
    public:
        Site();
        Site(std::string, int);

        void charger(std::string);
        /**
        * Supprime le contenu du projet
        */
        void clearProjet();

        std::string getNomProjet()const;
        void setNomProjet(std::string);

        PageWeb* getPage(unsigned int);
        void addPage();
        /**
        * Cr�e l'ensemble des pages html du projet
        * @param le nom du dossier dans lequel on va cr�er les pages, par d�fault le dossier actuel
        */
        void generate(std::string dossierCible="");

        /**
        * Sauvegarde en format json
        */
        std::string toJson();
        /**
        * Cr�e un fichier json pour sauvegarder le projet et un fichier json par page web qu'il contient
        */
        void sauvegarde(std::string);
};

#endif
