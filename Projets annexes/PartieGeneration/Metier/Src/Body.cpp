#include "../Include/Body.h"

using namespace std;

Body::Body() {}

Body::~Body() {}

string Body::toString() const
{
    string res="<body>\n";
    for(unsigned int i=0;i<m_childElements.size();i++)
    {
        res+=m_childElements[i].toString();
    }
    res+="</body>\n";
    return res;
}

string Body::toCss() const
{
    string res="body {\n";
    for(map<string,string>::const_iterator i=m_styles.begin();i!=m_styles.end();i++)
    {
        res+="\t"+i->first+";"+i->second+";\n";
    }
    res+="}\n\n";
    for(unsigned int i=0;i<m_childElements.size();i++)
    {
        res+=m_childElements[i].toCss();
    }
    return res;
}

string Body::toJson() const
{
    string res="\t\t\t\"body\" : [\n";
    res+="\t\t\t\t{ \"content\" : [\n";
    for(unsigned int i=0;i<m_childElements.size();i++)
    {
        if(i>0)
        {
            res+=", \n";
        }
        res+=m_childElements[i].toJson();
    }
    res+="\t\t\t\t]}";
    res+="\t\t\t]\n";
    return res;
}
