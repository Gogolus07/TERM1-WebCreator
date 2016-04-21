#include "../Include/IdHandler.h"

using namespace std;

string generateId(string id)
{
	if(ids.find(id) == ids.end())
	{
		ids[id] = 1;
		return id+"0";
	}
	else {
		string ret = id+to_string(ids[id]);
		ids[id]++;
		return ret;
	}
}
