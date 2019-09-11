#include "pch.h"
#include "gameTree.h"
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

gameTree::gameTree()
{
}


gameTree::~gameTree()
{
}

void gameTree::addStage(stage<bs> stage, float result, float score)
{
	stage.selfSymmtery();
	data[stage].add(result, score);
}

bool gameTree::addSgf(string str)//只支持katago的训练谱
{
	if (str.size() < 10)return false;
	stringstream ss(str);
	string temp;
	getline(ss, temp, ';');
	if (temp[temp.size()-1] != '(')return false;

	//读取sgf属性
	float komi;
	float score;
	float result;
	getline(ss, temp, ';');
	if (temp.size() < 10)return false; 
	stringstream infoss(temp);
	string item, value;
	int itemcount = 0;//保证SZ KM RE的顺序
	while (getline(infoss, item, '[') && getline(infoss, value, ']'))
	{
		if (item == "SZ")
		{
			itemcount = 1;
			int sgfbs;
			stringstream(value) >> sgfbs;
			if (sgfbs != bs)return false;

		}
		if (item == "KM")
		{
			if (itemcount != 1)return false;
			itemcount = 2;
			stringstream(value) >> komi;
			if (!(komi < 50 && komi > -50))return false;
		//	if (komi>7.1||komi<6.9)return false;

		}
		if (item == "RE")
		{
			if (itemcount != 2)return false;
			itemcount = 3;
			if (value[0] == '0')
			{
				result = 0.5;
				score = komi;
			}

			else
			{
				if (value[2] == 'R')
				{
					return false;//只要有结果的对局
				}
				stringstream ress(value);
				string color; 
				getline(ress, color, '+');
				if (color == "B")result = 1;
				else if (color == "W")result = 0;
				else return false;
				ress >> score;
				if (!(score < 500 && score > -500))return false;
				if (color == "B")score=komi+score;
				else if (color == "W")score = komi - score;
			}
		}
	}
	//cout << "komi=" << komi << " result=" << result << " score=" << score << endl;

	//读棋谱内容
	stage<bs> s;
	addStage(s, result, score);
	while (getline(ss, temp, ';'))
	{
	//	s.print();
		if (temp.empty())return true;
		unsigned char color=temp[0];
		if (color != 'B'&&color != 'W')continue;
		if (temp[2] == ']')
		{
			s.play(0, 0, s.PASS);
			addStage(s, result, score);
			continue;
		}
		unsigned char x, y;
		x = temp[2] - 'a';
		y = temp[3] - 'a';
		if (color == 'B')
		{
			s.play(x, y, s.BLACK);
			addStage(s, result, score);
		}
		else if (color == 'W')
		{
			s.play(x, y, s.WHITE);
			addStage(s, result, score);
		}



	}
	return true;
}

void gameTree::addSgfs(string path)
{
	ifstream ifs(path);
	if (!ifs.good())
	{
		cout << "gameTree::addSgfs :File Not Exist" << endl;
	}
	string oneSgf;
	int count = 0;
	while (getline(ifs, oneSgf, ')'))
	{
		if (oneSgf.size() > 10)
		{
			if (addSgf(oneSgf))
			{
				count++;
				if(count%100==0)cout << "successfully load sgf " << count << endl;
			}
			else
			{
				count++;
				cout << "failed to load sgf " << count << endl;
			}
		}
	}


}

string gameTree::getLizStr(stage<bs> s)
{
	vector< pair<float, string>> temp;
	unsigned char color;
	if (s.movenum % 2)color = s.WHITE;
	else color = s.BLACK;
	pair<float, string> pass = getMoveLizStrNoPV(s, 0, 0, s.PASS);
	if (!pass.second.empty())temp.push_back(pass);
	for (int x = 0; x < bs; x++)
	{
		for (int y = 0; y < bs; y++)
		{
			pair<float, string> t = getMoveLizStrNoPV(s, x, y, color);
			if(!t.second.empty())temp.push_back(t);
		}
	}
	sort(temp.begin(), temp.end());
	string output;
	for (int i = 0; i < temp.size(); i++)
	{
		output += temp[temp.size() - i-1].second + to_string(i)+" "+"PV A1 ";
	}
	return output;
}
pair<float/*排序用*/, string> gameTree::getMoveLizStrNoPV(stage<bs> s, unsigned char x, unsigned char y, unsigned char color)
{
	if(!s.play(x, y, color))return make_pair(0, string());
	s.selfSymmtery();
	if (!data.count(s))return make_pair(0, string());
	stageInfo si = data[s];
	string output = "info move ";
	if (color == s.PASS)
	{
		output += "pass ";
	}
	else
	{
		if (x >= 8)output += char(x + 'A' + 1);
		else output += char(x + 'A');
		output += to_string(y + 1);
		output += " ";
	}
	output += "visits " + to_string(si.getCount())+" ";
	output += "winrate "; 
	//output += to_string(si.getBWr()) + " ";
	if (color == s.BLACK)output += to_string(si.getBWr()) + " ";
	else output += to_string(1 - si.getBWr()) + " ";
	output += "scoreMean ";
	if (color == s.BLACK)output += to_string(si.getScoreAvr() - komi) + " ";
	else output += to_string(-si.getScoreAvr() + komi) + " ";
	output += "scoreStdev ";
	output += to_string(si.getScoreStdev()) + " ";
	output += "lcb ";
	//output += to_string(si.getBWr()) + " ";
	if (color == s.BLACK)output += to_string(si.getBWr()) + " ";
	else output += to_string(1 - si.getBWr()) + " ";
	output += "order ";
	return make_pair(si.getCount(),output);

}