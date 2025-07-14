#ifndef JTBTERMINALUI
#define JTBTERMINALUI
#include "window.h"
#include <deque>
namespace jtb
{
class tui
{
//windows work like layers
//windows have a size and contains objects, compiles objects to words and lines
public:
	tui(short SizeX, short SizeY)
	: sizeX(SizeX), sizeY(SizeY)
	{
		init();
	}
	short sizeX;
	short sizeY;
	terminal t;
	std::deque<window> w;
	input inp;
	void init();
	void setSize(unsigned short x, unsigned short y);
	void updateSize();
	void draw();
	key getinp();
	void addWindow(window & win);
	bool delFirstWindow(std::string name);
	bool delWindow(short win);
	bool delAllWindows(std::string nameOrCat, bool delByCat = false);
	std::vector<window *> getAllBy(std::string nameOrCat, bool getByCat = false);
};
line combineLine(line a, line b, short offsetB);

}
#endif
