#ifndef JTBTUIXML
#define JTBTUIXML

#include "tui.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"


namespace jtb
{
namespace tuixml
{

namespace globals
{
	static std::string error = "";
	static std::string errorStoi = "";
	static bool ignoreUnknown = false;
	static bool throwOnError = true;
}
namespace helper
{
	int stoi(std::string s, bool * err);
}


bool parseTuiAttr(rapidxml::xml_attribute<> * attr, tui * t);

bool parseObject(rapidxml::xml_node<> * obj, window * w);

bool parseWindowAttr(rapidxml::xml_attribute<> * attr, window * w);

bool parseWindow(rapidxml::xml_node<> * win, tui * t);

bool parseString(rapidxml::xml_node<> * str, tui * t);

bool parseInt(rapidxml::xml_node<> * integer, tui * t);

bool loadFromXML(std::string filename, tui * t);
	
}
}

#endif
