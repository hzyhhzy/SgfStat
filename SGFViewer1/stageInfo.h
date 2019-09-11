#pragma once
#include "cmath"
class stageInfo
{
private:
	unsigned long count=0;//盘数
	double bwins=0;//黑获胜数,和棋0.5
	double scoreTotal=0;//所有盘面的子差和（用于计算平均子差）,均以0贴目为基准
	double scoreSqr=0;//所有盘面的子差平方和（用于计算子差方差）

public:
	stageInfo();
	~stageInfo();
	inline unsigned long getCount() { return count; }
	inline double getBWins() { return bwins; }
	inline float getBWr() { return float(bwins) / count; }
	inline float getScoreAvr() { return scoreTotal / count; }
	inline float getScoreStdev() { return sqrt(scoreSqr/count-scoreTotal*scoreTotal/count/count); }
	void add(float result/* 是否黑胜*/, float score)
	{
		count++;
		bwins += result;
		scoreTotal += score;
		scoreSqr += (score*score);
	}
};
