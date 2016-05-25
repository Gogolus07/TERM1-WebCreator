#include "../Include/Module.h"
//#include "../Include/jsoncpp/json/json.h"

using namespace std;

void moduleToElement(Element& e)
{
    string moduleName = e.getModuleName();
    /*if(moduleName == "")
      return;*/
    string path = "modules/"+moduleName+".json";
    cout << path <<endl;
    ifstream fichier(path, ifstream::binary);  // on ouvre en lecture le fichier JSON
    if(fichier)
    {
        //Là on ouvre le fichier JSON et tout et tout
        stringstream buffer;
        buffer << fichier.rdbuf();
        string content = buffer.str();

        Json::Value root; //Contiendra la racine
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( content, root );
        if(!parsingSuccessful)
        {
          std::cout  << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
          return;
        }
        e.setElementName(root["balise"].asString()); //Le nom de l'élément
        const Json::Value styles = root["style"];
        for(unsigned int i = 0;i<styles.size(); i++)
        {
            e.setContent(styles[i][0].asString()+" "+styles[i][1].asString());
        }
        const Json::Value elems = root["contenu"];
        if(!elems.empty())
        {
            for(unsigned int i = 0;i<elems.size(); i++)
            {
               Element tmp(elems[i]["nom"].asString());
               e.addElement(tmp);
            }
        }
        //On fait des trucs
        fichier.close();
    }
    else
        cerr << "Fichier impossible à ouvrir!" << endl;
}
