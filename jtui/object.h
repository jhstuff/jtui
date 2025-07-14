#include "../jterm.h"
namespace jtb
{
class object
{
public:
	object()
	: onFocus(nullptr),onUnfocus(nullptr),onSelect(nullptr)
	{
	
	}
	word content;
	void setFGColor(color c); //{r, g, b}
	void setBGColor(color c);
	void enableColor(bool x);
	bool colorEnabled();
	
	std::string text;
	void setText(std::string t);
	
	short x;
	short y;
	short lastX();
		
	short maxLen; //<1: ignore, >0: cut word if exceeding
	void setMaxLen(short i);

	word render(short limit);
	
	char type;
	bool focused;
	int (*onFocus)(object*);
	int (*onUnfocus)(object*);
	int (*onSelect)(object*);
	int focus();
	int unfocus();
	int select();
	//0, text specific
	//1, button specific
	//2, textbox specific
	//3...
};
}
