#include "../Include/Head.h"

using namespace std;

Head::Head() : m_title("") {}

Head::Head(std::string title) : m_title(title) {}

Head::~Head() {}

string Head::getTitle() const
{
    return m_title;
}

void Head::setTitle(string title)
{
    m_title = title;
}

string Head::getScript(unsigned int i) const
{
    if(i<m_scripts.size())
    {
        return m_scripts[i];
    }
    else
    {
        return "";
    }
}

void Head::addScript(string script)
{
    m_scripts.push_back(script);
}

void Head::removeScript(unsigned int i)
{
    if(i<m_scripts.size())
    {
        m_scripts.erase(m_scripts.begin()+i);
    }
}

string Head::getLink(unsigned int i) const
{
    if(i<m_links.size())
    {
        return m_links[i];
    }
    else
    {
        return "";
    }
}

void Head::addLink(string link)
{
    m_links.push_back(link);
}

void Head::removeLink(unsigned int i)
{
    if(i<m_links.size())
    {
        m_links.erase(m_links.begin()+i);
    }
}

string Head::toString() const
{
    string res = "<head>\n";
    res+="<title>"+m_title+"</title>";
    for(unsigned int i=0;i<m_links.size();i++)
    {
        res+="<link href=\""+m_links[i]+"\" />\n";
    }
    for(unsigned int i=0;i<m_scripts.size();i++)
    {
        res+="<scipt src=\""+m_scripts[i]+"\" />\n";
    }
    res+="</head>\n";
    return res;
}

string Head::toJson()
{
    string res="\t\t\t\"head\" : [\n";
    res+="\t\t\t\t{\"script\" : [";
    for(unsigned int i=0;i<m_scripts.size();i++)
    {
        if(i!=0){
            res+=", ";
        }
        res+="\""+m_scripts[i]+"\"";
    }
    res+="]},\n";

    res+="\t\t\t\t{\"links\" : [";
    for(unsigned int i=0;i<m_links.size();i++)
    {
        if(i!=0){
            res+=", ";
        }
        res+="\""+m_links[i]+"\"";
    }
    res+="]},\n";
    res+="\t\t\t\t{\"title\" : \""+m_title+"\"}\n";
    res+="\t\t\t],\n";
    return res;
}
