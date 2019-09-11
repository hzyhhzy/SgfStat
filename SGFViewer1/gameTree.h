#pragma once
#include "stage.h"
#include "stageInfo.h"
#include <map>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
const unsigned bs = 9;
class gameTree
{
	std::map<stage<bs>, stageInfo> data;
	float komi = 7.0;

public:
	gameTree();
	~gameTree();
	stageInfo& operator[] (stage<bs> st)
	{
		st.selfSymmtery();
		return data[st];
	}
	void addStage(stage<bs> stage,float result,float score);//往树内添加局面
	bool addSgf(string str);//读一个sgf，然后添加所有局面
	void addSgfs(string path);//读一个大sgf，然后添加所有局面
	//string&& getStageLizzieStr(stage<bs> s,unsigned short minNum/*只将出现次数不小于minNum的局面导入sgf*/);//获取某局面的lizzie字符串
	//string&& getSgfStr(unsigned short minNum);//获取完整sgf字符串

	string getLizStr(stage<bs> s);//info move E5 visits 1476 utility -0.0327086 radius 0.00636433 winrate 0.484251 scoreMean -0.491455 scoreStdev 15.4565 prior 0.0232493 lcb 0.481978 utilityLcb -0.0389497 order 0 pv E5 D7 C6 F6 F5 G6 G5 D6 D5 
	pair<float,string> getMoveLizStrNoPV(stage<bs> s, unsigned char x, unsigned char y, unsigned char color);//move C4 visits 2385 winrate 5048 scoreMean 0.0308792 pv C4 D3 D6 E6 D7 C3 G6 E7 G4 C5 D5 D4 E8 info
};

