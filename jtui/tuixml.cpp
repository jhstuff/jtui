#include "tuixml.h"

namespace jtb
{
namespace tuixml
{

namespace helper
{
	int stoi(std::string s, bool * err)
	{
		int ret = 0;
		*err = false;
		try
		{
			ret = std::stoi(s);
		}
		catch(std::invalid_argument e)
		{
			globals::errorStoi = "Could not convert to int, invalid arg: " + s;
			*err = true;
		}
		catch(std::out_of_range e)
		{
			globals::errorStoi = "Could not convert to int, out of range: " + s;
			*err = true;
		}
		return ret;
	}
}


bool parseTuiAttr(rapidxml::xml_attribute<> * attr, tui * t)
{
	if(attr->name() == std::string("sizeX"))
	{
		if(attr->value() == std::string("auto"))
			t->autoSizeX = true;
		else
		{
			t->sizeX; //fix
		}
	}
	else if(attr->name() == std::string("sizeY"))
	{
		if(attr->value() == std::string("auto"))
			t->autoSizeY = true;
		else
		{
			t->sizeY; //fix
		}
	}
	else if(attr->name() == std::string("sizeX"))
	{}
	else if(attr->name() == std::string("sizeX"))
	{}
	else if(attr->name() == std::string("sizeX"))
	{}
	else if(attr->name() == std::string("sizeX"))
	{}
	else
	{
		if(!globals::ignoreUnknown)
		{
			globals::error = "Unknown attribute for jtuiconf";
			return false;
		}
	}
	return true;
}

bool parseObject(rapidxml::xml_node<> * obj, window * w)
{
	if(obj->name() != std::string("object"))
	{
		if(globals::ignoreUnknown)
			return true;
		globals::error = "Node under window is not object: " + std::string(obj->name());
		return false;
	}
	object o;
	bool stoiErr;
	int temp;
	std::string name;
	for(rapidxml::xml_attribute<> * attr = obj->first_attribute(); attr; attr = attr->next_attribute())
	{
		if(attr->name()==std::string("x"))
		{
			temp = helper::stoi(attr->value(),&stoiErr);
			if(stoiErr)
			{
				globals::error = globals::errorStoi;
				return false;
			}
			o.x = temp;
		}
		else if(attr->name()==std::string("y"))
		{
			temp = helper::stoi(attr->value(),&stoiErr);
			if(stoiErr)
			{
				globals::error = globals::errorStoi;
				return false;
			}
			o.y = temp;
		}
		else if(attr->name()==std::string("name"))
		{
			name=attr->value();
		}
		else if(attr->name()==std::string("y"))
		{}
		else if(!globals::ignoreUnknown)
		{
			globals::error = "Unknown attribute in object: "
			 + std::string(attr->name());
			return false;
		}
	}
	if(name == "")
	{
		//take first available name
		name += "a";
		int i = 0;
		while(w->objects.find(name) != w->objects.end())
		{
			name[i]++;
			if(name[i]=='z')
			{
				name += "a";
				++i;
			}
		}
	}
	else
	{
		if(w->objects.find(name) != w->objects.end())
		{
			//take first available name
			name += "_a";
			int i = 1;
			while(w->objects.find(name) != w->objects.end())
			{
				name[i]++;
				if(name[i]=='z')
				{
					name += "a";
					++i;
				}
			}
		}
	}
	o.setText(obj->value());
	w->objects[name] = o;
	return true;
}

bool parseWindowAttr(rapidxml::xml_attribute<> * attr, window * w)
{
	if(attr->name() == std::string("sizeX"))
	{}
	else if(attr->name() == std::string("sizeY"))
	{}
	else if(attr->name() == std::string("name"))
	{
		w->name = attr->value();
	}
	else if(attr->name() == std::string("category"))
	{
		w->category = attr->value();
	}
	else if(attr->name() == std::string("sizeX"))
	{}
	else
	{
		if(!globals::ignoreUnknown)
		{
			globals::error =
			 "Unknown attribute for window: " + std::string(attr->name());
			return false;
		}
	}
	return true;
}

bool parseWindow(rapidxml::xml_node<> * win, tui * t)
{
	if(win->name() != std::string("window"))
	{
		if(globals::ignoreUnknown)
			return true;
		else
		{
			globals::error = "Node under jtuiconf is not window: "
			 + std::string(win->name());
			return false;
		}
	}
	window * w = &t->w.emplace_back(0,0,0,0); //fix: use better constructor
	for(rapidxml::xml_attribute<> * attr = win->first_attribute(); attr; attr = attr->next_attribute())
	{
		if(!parseWindowAttr(attr,w))
			return false;
	}
	for(rapidxml::xml_node<> * obj = win->first_node(); obj; obj = obj->next_sibling())
	{
		if(!parseObject(obj,w))
			return false;
	}
	return true;
}

bool loadFromXML(std::string filename, tui * t)
{
	if(!t)
	{
		globals::error = "tui * t is nullptr";
		if(globals::throwOnError)
			throw std::runtime_error(globals::error); 
		return false;
	}
	rapidxml::xml_document<> doc;
	try
	{
		rapidxml::file<> xmlF(filename.c_str());
		doc.parse<0>(xmlF.data());
	}
	catch(const std::runtime_error & e)
	{
		globals::error = "Could not open file: " + filename;
		if(globals::throwOnError)
			throw std::runtime_error(globals::error); 
		return false;
	}
	rapidxml::xml_node<> * rootNode = doc.first_node();
	rapidxml::xml_node<> * curNode = rootNode;
	if(curNode->name() != std::string("jtuiconf"))
	{
		globals::error = "Root node is not jtuiconf";
		if(globals::throwOnError)
			throw std::runtime_error(globals::error); 
		return false;
	}
	//parse tui config
	for(rapidxml::xml_attribute<> * attr = curNode->first_attribute(); attr; attr = attr->next_attribute())
	{
		if(!parseTuiAttr(attr,t))
		{
			if(globals::throwOnError)
				throw std::runtime_error(globals::error); 
			return false;
		}
	}
	if( !(curNode = curNode->first_node()) )
	{
		globals::error = "No window under jtuiconf";
		if(globals::throwOnError)
			throw std::runtime_error(globals::error); 
		return false;
	}
	//parse windows in tui
	for(rapidxml::xml_node<> * win = curNode; win; win = win->next_sibling())
	{
		if(!parseWindow(win,t))
		{
			if(globals::throwOnError)
				throw std::runtime_error(globals::error); 
			return false;
		}
	}

	return true;
}
	
}
}
