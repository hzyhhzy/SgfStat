#pragma once
#include "gameTree.h"
#include <map>
class gameTree;
class GTP
{
private:
	gameTree* gt;
	int movenum = 0;
	std::map<int, stage<bs>> history;
	GTP();
public:
	GTP(gameTree* gt) :gt(gt) { history[0] = stage<bs>(); }
	~GTP();
	void startGTP();
};

