#include "tui.h"

namespace jtb
{
	void tui::init()
	{
		w.clear();
		window temp(sizeX,sizeY,0,0);
		w.push_back(temp);
	}
	void tui::setSize(unsigned short x, unsigned short y)
	{
		sizeX = x;
		sizeY = y;
		w[0].sizeX = x;
		w[0].sizeY = y;
	}
	void tui::updateSize()
	{
		unsigned short x,y;
		getWinSize(&x,&y);
		setSize(x,y);
	}	
	void tui::draw()
	{
		//t.maxLineLength = sizeX;
		setCursor();	
		t.lines = w[0].render();
		std::cout<<t.comp();
		/*
		for(auto it = w.begin(); it!=w.end(); ++it)
		{
			
		}
		/**/
	}
	void tui::addWindow(window & win)
	{
		if(win.sizeX > sizeX || win.sizeY > sizeY)
			throw std::runtime_error("Invalid size in addWindow");
		w.push_back(win);
	}
	//bool tui::delWindow(short win);
	bool tui::delFirstWindow(std::string name)
	{
		for(int i = 0; i<w.size(); ++i)
		{
			if(w[i].name == name)
			{
				w.erase(w.begin() + i);
				return true;
			}
		}
		return false;
	}
	bool tui::delAllWindows(std::string nameOrCat, bool delByCat)
	{
		if(delByCat)
		{
			//iterate through vector w and del all matching by category
			for(int i = w.size()-1; i>-1; --i)
			{
				if(w[i].category == nameOrCat)
					w.erase(w.begin() + i);
			}
			
		}
		else
		{
			for(int i = w.size()-1; i>-1; --i)
			{
				if(w[i].name == nameOrCat)
					w.erase(w.begin() + i);
			}
		}
		return false;
	
	}
	std::vector<window *> tui::getAllBy(std::string nameOrCat, bool getByCat)
	{
	//iterate through vector w and get all matching by name or category starting from first element
		std::vector<window *> ret;
		if(getByCat)
		{
			for(int i = 0; i<w.size(); ++i)
			{
				if(w[i].category == nameOrCat)
					ret.push_back(&w[i]);
			}
			
		}
		else
		{
			for(int i = 0; i<w.size(); ++i)
			{
				if(w[i].name == nameOrCat)
					ret.push_back(&w[i]);
			}
		}
		return ret;
	}
//outside struct	
	line combineLine(line a, line b, short offsetB)
	{
		line ret;
		int t = 0;
		for(int i = 0; i<a.words.size(); ++i)
		{
		}

	}

}
