#include "object.h"

namespace jtb
{


	void object::setFGColor(color c) //{r, g, b}
	{
		content.FG=c;
	}
	void object::setBGColor(color c)
	{
		content.BG=c;
	}
	void object::enableColor(bool x)
	{
		content.enableColor = x;
	}
	bool object::colorEnabled()
	{
		return content.enableColor;
	}
	short object::lastX()
	{
		return x+content.w.size()-1;
	}
	void object::setText(std::string t)
	{
		text = t;
		if(maxLen < 1 || maxLen > t.size())
			content.w = t;
		else
			content.w = t.substr(0,maxLen);
	}
	void object::setMaxLen(short i)
	{
		maxLen = i;
		setText(text);
	}
	word object::render(short limit)
	{
		word ret = content;
		if(focused)
		{
			ret.BG = content.FG;
			ret.FG = content.BG;
		}
		ret.w = ret.w.substr(0,ret.w.size() + limit);
		return ret;
	}
	int object::focus()
	{
		focused = true;
		if(onFocus)
			return onFocus(this);
		return 0;
	}
	int object::unfocus()
	{
		focused = false;
		if(onUnfocus)
			return onUnfocus(this);
		return 0;
	}
	int object::select()
	{
		if(onSelect)
			return onSelect(this);
		return 0;
	}	

}
