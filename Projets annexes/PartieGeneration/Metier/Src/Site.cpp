#include "../Include/Site.h"

using namespace std;

Site::Site() : m_numberOfPagesMax(1), m_nomProjet("Sans titre") {}

Site::Site(string nom, int i) : m_numberOfPagesMax(i), m_nomProjet(nom) {}

string Site::getNomProjet()const { return m_nomProjet;}
void Site::setNomProjet(string nom) {m_nomProjet = nom;}

PageWeb* Site::getPage(unsigned int i)
{
	if(i >= m_numberOfPagesMax)
		return NULL;
	return &m_projet[i];
}

void Site::addPage()
{
	if(m_projet.size() == m_numberOfPagesMax)
	{
		cerr << "Nombre max de pages atteint!" << endl;
	}
	else
	{
		PageWeb p;
		m_projet.push_back(p);
	}
}

void Site::clearProjet()
{
    for(unsigned int i=0;i<m_projet.size();i++)
    {
        m_projet.erase(m_projet.begin());
    }
}

void Site::generate(string dossierCible)
{
	cout << "Creation du projet site web : " << m_nomProjet <<endl;
  for(unsigned int i=0;i<m_projet.size();i++)
	{
		cout << "Creation de la page numero " << i << "\n";
		m_projet[i].generate(dossierCible);
	}
	cout << "Fin de la creation";
}

string Site::toJson() const
{
    string res ="{\n";
    res+="\t\"nom\" : \""+m_nomProjet+"\",\n";
    res+="\t\"type\" : \"projet\",\n";
    res+="\t\"html\" : [";
    for(unsigned int i=0;i<m_projet.size();i++)
    {
        res+="\""+m_projet[i].getNom()+".json\"";
        if(i<m_projet.size()-1)
        {
            res+=", ";
        }
    }
    res+="]\n";
    res+="}";
    return res;
}

void Site::sauvegarde()
{
    ofstream file(getNomProjet()+".json", ios::out | ios::trunc);
	if(file)
    {
        file<<toJson();
        for(unsigned int i=0;i<m_projet.size();i++)
        {
            m_projet[i].sauvegarde();
        }
    }
    else
    {
        cerr<<"Echec de la sauvegarde du projet "<<getNomProjet()<<"\n";
    }
}

void Site::charger(string jsonfile)
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
            m_nomProjet = root["nom"].asString();
            Json::Value pages = root["html"];
            if(!pages.empty()&&pages.size()<=m_numberOfPagesMax)
            {
                clearProjet();
                for(unsigned int i=0;i<pages.size();i++)
                {
                    addPage();
                    getPage(i)->charger(pages[i].asString());
                }
            }
            else
            {
                if(pages.empty())
                {
                    cerr << "Projet vide, est ce intentionnel ?";
                }
                else
                {
                    cerr << "Projet trop petit, changez le nombre de pages maximum";
                }
            }
        }
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier " << jsonfile << "\n";
    }
}
