#include <iostream>
#include <vector>
#include "../Include/Html.h"
#include "../Include/Element.h"
#include "../Include/PageWeb.h"
#include "../Include/Site.h"


using namespace std;

int main(int argc, char *argv[])
{
	Site s("proj",15);
	s.addPage();
	PageWeb* web = s.getPage(0);
	web->setNom("Test");
	Html* html = web->getRoot();
	html->getHead()->setTitle("Le projet");
	Body* body = html->getBody();
	Element e("p","Coucou");
	body->addElement(e);
	Element e2("p","C'est le projet");
	body->addElement(e2);
	s.addPage();
	Html* html2 = s.getPage(1)->getRoot();
	html2->getBody()->addElement(e);
	s.generate();
	cout << s.getPage(0)->toString();
	cout << endl << s.getPage(1)->toString();
	cout << "\n";
	cout<<endl<<endl<<s.toJson();
	cout<<endl<<endl<<s.getPage(0)->toJson();
	s.sauvegarde();

	Site s2("proj2",15);
    s2.charger("proj.json");
    cout << s2.getPage(0)->toString();

    /*cout<<endl<<endl;
	Element r("p_perso"); //Je like cette petite guerre des commentaires ou on commente les tests de l'autre
	r.toString();*/
  return 0;
}
