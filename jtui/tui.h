#ifndef JTBTERMINALUI
#define JTBTERMINALUI
#include "window.h"
#include <deque>
namespace jtb
{
class tui
{
//windows work like layers (not yet) or several interfaces to toggle between
//windows have a size and contains objects, compiles objects to words and lines
public:
	tui(short SizeX, short SizeY)
	: sizeX(SizeX), sizeY(SizeY)
	{
		init();
	}
	short sizeX;
	bool autoSizeX;
	short sizeY;
	bool autoSizeY;
	terminal t;
	std::deque<window> w;
	int windowIndex;
	input inp;
	void init();
	void setSize(unsigned short x, unsigned short y);
	void updateSize();
	void draw();
	key getinp();
private:
	std::deque<window>::iterator getWindowIter(int i);
	std::deque<window>::iterator getFirstWindowIter
	 (std::string nameOrCat, bool getByCat = false);
public:
	window * getWindow(int i);
	window * getFirstWindow(std::string nameOrCat, bool getByCat = false);
	void addWindow(window & win);
	bool delFirstWindow(std::string name);
	bool delWindow(short win);
	bool delAllWindows(std::string nameOrCat, bool delByCat = false);
	std::vector<window *> getAllBy(std::string nameOrCat, bool getByCat = false);
};
line combineLine(line a, line b, short offsetB);

}
#endif
