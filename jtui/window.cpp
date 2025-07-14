#include "window.h"

namespace jtb
{

	word window::emptyLineWord(short x = 0, short y = 0, short len = -1)
	{
		word ret;
		if(!len)
			return ret;
		if(len == -1)
			len = sizeX;
		if(!useBorder)
		{
			for(;ret.w.size()<len && ret.w.size()+x<sizeX;)
				ret.w += defBGChar;
			return ret;
			
		}
		char rightEnd = border[2];
		if(!x)
		{
			if(!y)
				ret.w += corner[0];
			else if(y == sizeY-1)
				ret.w += corner[2];
			else
				ret.w += border[1];
			
		}
		char fill = defBGChar;
		if(!y)
		{	
			fill = border[0];
			rightEnd = corner[1];
		}
		if(y == sizeY-1)
		{
			fill = border[3];
			rightEnd = corner[3];
		}
		while(ret.w.size()<len && ret.w.size()+x<sizeX-1)
			ret.w += fill;
		if(ret.w.size()<len)
			ret.w += rightEnd;
		return ret;
	}

	std::vector<line> window::render()
	{
		err = "";
		errCode = 0;
		std::vector<line> ret;
		for(int i = 0; i<sizeY; ++i)
			ret.emplace_back();
		std::map<short, std::map<short, object>> ordering; //<y, <x, object>>
		short maxY = 0;
		for(auto it = objects.begin(); it!= objects.end(); ++it)
		{//iterate through objects and put at their positions
		 	auto & yPos = ordering[it->second.y];

			if(yPos.find(it->second.x) != yPos.end())
			{//err, already exists at x
				err += " <Objects at same X, line[" + std::to_string(it->second.x)
					+ "]>";
			 	errCode = errCode | 0b1;
				continue;
			}
			yPos[it->second.x] = it->second;/**/
			//ordering[it->second.y][it->second.x] = it->second;
			if(it->second.y>maxY)
				maxY = it->second.y;
		}
		for(int i = 0; i<maxY+1 && i<ret.size(); ++i)
		{//corners and borders must be accounted for, y loop
			if(ordering[i].empty())
			{
				ret[i].words.push_back(emptyLineWord(0,i));
				continue;
			}
			if(ordering[i].begin()->first != 0)
			{
				ret[i].words.push_back(emptyLineWord(0,i,ordering[i].begin()
					->second.x));
			}
			for(auto it = ordering[i].begin(); it!=ordering[i].end(); ++it)
			{//x loop
				ret[i].words.push_back(it->second.render(sizeX - (it->second.lastX()+1+useBorder)));
				auto next = std::next(it,1);
				if(next == ordering[i].end())
				{
					ret[i].words.push_back(emptyLineWord(it->second.lastX()+1,i));
					continue;
				}
				if(it->second.lastX() < next->second.x)
				{
					ret[i].words.push_back(emptyLineWord(it->second.lastX()+1,i,
						next->second.x-1 - it->second.lastX()));
				}
				else if(it->second.lastX() >= next->second.x)
				{//application chooses how to handle error
					err += " <Conflicting words, line[" + std::to_string(i)
						+ "]>" + std::to_string(it->second.lastX()) + " " + std::to_string(next->second.x);
					errCode = errCode | 0b10;
				}
				
			}
		}
		for(int i = maxY+1; i<sizeY; ++i)
		{
			ret[i].words.push_back(emptyLineWord(0,i));
		}
		return ret;
	}

}
