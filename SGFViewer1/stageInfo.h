#pragma once
#include "cmath"
class stageInfo
{
private:
	unsigned long count=0;//����
	double bwins=0;//�ڻ�ʤ��,����0.5
	double scoreTotal=0;//����������Ӳ�ͣ����ڼ���ƽ���Ӳ,����0��ĿΪ��׼
	double scoreSqr=0;//����������Ӳ�ƽ���ͣ����ڼ����Ӳ�

public:
	stageInfo();
	~stageInfo();
	inline unsigned long getCount() { return count; }
	inline double getBWins() { return bwins; }
	inline float getBWr() { return float(bwins) / count; }
	inline float getScoreAvr() { return scoreTotal / count; }
	inline float getScoreStdev() { return sqrt(scoreSqr/count-scoreTotal*scoreTotal/count/count); }
	void add(float result/* �Ƿ��ʤ*/, float score)
	{
		count++;
		bwins += result;
		scoreTotal += score;
		scoreSqr += (score*score);
	}
};
