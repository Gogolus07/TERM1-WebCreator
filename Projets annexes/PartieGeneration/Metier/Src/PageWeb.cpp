#include "../Include/PageWeb.h"

using namespace std;

PageWeb::PageWeb() : m_nom("Sans titre") {}

PageWeb::PageWeb(string nom) : m_nom(nom) {}

string PageWeb::getNom()const {return m_nom;}
void PageWeb::setNom(string nom) {m_nom = nom;}

Html* PageWeb::getRoot() { return &m_root; }

string PageWeb::toString()const
{
	cout << "PageWeb : " << m_nom << "\n";
	return m_root.toString();
}

void PageWeb::generate(string dossierCible=""){
    ofstream file(dossierCible+getNom()+".html", ios::out | ios::trunc);
	if(file)
    {
        file<<toString();
    }
    else
    {
        cerr<<"Echec de la sauvegarde de la page " <<getNom()<<"\n";
    }
}

string PageWeb::toJson()
{
    string res="{\n";
    res+="\t\"page\" : \""+m_nom+"\",\n";
    res+="\t\"content\" : {\n";
    res+=m_root.toJson();
    res+="\n\t}\n";
    res+="}";
    return res;
}

void PageWeb::sauvegarde()
{
    ofstream file(getNom()+".json", ios::out | ios::trunc);
	if(file)
    {
        file<<toJson();
    }
    else
    {
        cerr<<"Echec de la sauvegarde de la page " <<getNom()<<"\n";
    }
}

Element* PageWeb::recupererElement(Json::Value elem)
{
    Element* e = new Element(elem["type"].asString(),elem["texte"].asString());
    //Les ids se font automatiquement. Normalement c'est les mêmes, sinon on rajoutera un autre constructeur.
    Json::Value attributs = elem["attributes"];
    if(!attributs.empty())
    {
        for(unsigned int i=0;i<attributs.size();i++)
        {
            e->setAttribute(attributs[i]["attribute"].asString(),attributs[i]["value"].asString());
        }
    }
    Json::Value style = elem["style"];
    if(!style.empty())
    {
        for(unsigned int i=0;i<style.size();i++)
        {
            e->setStyle(style[i]["style"].asString(),style[i]["value"].asString());
        }
    }
    Json::Value fils = elem["content"];
    if(!fils.empty())
    {
        for(unsigned int i=0;i<fils.size();i++)
        {
            e->addElement(*recupererElement(fils[i]["element"]));
        }
    }
    return e;
}

void PageWeb::charger(string jsonfile)
{
    ifstream fichier(jsonfile,ifstream::binary);
    if(fichier)
    {
        stringstream buffer;
        buffer << fichier.rdbuf();
        string content = buffer.str();
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( content, root );
        if(!parsingSuccessful)
        {
          cerr  << "Impossible de parser le fichier " << jsonfile << "\nLa sauvegarde est peut être corromue. Erreur de parsage : \n" << reader.getFormattedErrorMessages();
          return;
        }
        else
        {
            m_nom = root["page"].asString();
            Json::Value head = root["content"]["html"]["head"];
            getRoot()->getHead()->setTitle(head["title"].asString());
            Json::Value scripts = head["script"];
            Json::Value links = head["links"];
            if(!scripts.empty())
            {
                for(unsigned int i=0;i<scripts.size();i++)
                {
                    getRoot()->getHead()->addScript(scripts[i].asString());
                }
            }
            if(!links.empty())
            {
                for(unsigned int i=0;i<links.size();i++)
                {
                    getRoot()->getHead()->addLink(links[i].asString());

                }
            }

            Json::Value body = root["content"]["html"]["body"];
            if(!body["content"].empty())
            {
                for(unsigned int i=0;i<body["contenu"].size();i++)
                {
                    getRoot()->getBody()->addChild(*recupererElement(body["content"][i]["element"]));
                }
            }
        }
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier " << jsonfile << "\n";
    }
}
