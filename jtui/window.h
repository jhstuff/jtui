#include "object.h"
#include <map>

namespace jtb
{
class window
{
public:
	window(short SizeX, short SizeY, short X, short Y,
		std::string Name = "", std::string Category = "")
	: sizeX(SizeX), sizeY(SizeY), x(X), y(Y), name(Name), category(Category)
	{init();}
	void init()
	{
		useBorder = false;
		defBG = {0,0,0};
		defFG = {255,255,255};
		defBGChar = ' ';
		border[0] = '-';
		border[1] = '|';
		border[2] = '|';
		border[3] = '-';
		for(int i = 0; i<4; ++i)
			corner[i] = '*';
	}
	short sizeX;
	short sizeY;
	short x;
	short y;
	std::map<std::string,object> objects;
	std::string name;
	std::string category;
	color defBG;
	color defFG;
	char defBGChar;
	bool useBorder;
	char border[4]; //Top, Left, Right, Bottom
	char corner[4]; //TL, TR, BL, BRi
	std::string err;
	short errCode;
	word emptyLineWord(short, short, short);
	word limitWordLength(word, short);
	std::vector<line> render();

};

}
