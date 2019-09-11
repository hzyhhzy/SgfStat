#pragma once
#include <string>
#include <iostream>
#include "stage.h"
#include "GTP.h"
using namespace std;
void test1()
{
	stage<19> a;
	a.setColor(4, 4, a.BLACK);
	a.print();
	a.setColor(2, 3, a.WHITE);
	a.print();
	a.setColor(3, 2, a.BLACK);
	a.print();
	a.setColor(2, 5, a.WHITE);
	a.print();
	a.setColor(6, 5, a.BLACK);
	a.print();
	a.setColor(2, 5, a.BLACK);
	a.print();
	//a.
}
void test2()
{
	gameTree gt;
	gt.addSgfs("C:\\Users\\Administrator\\Desktop\\kata9sgf\\a.sgfs");
	stage<9> a;
	while (1)
	{
		string opr;
		cin >> opr;
		if (opr == "clear")a=stage<9>();
		if (opr != "play")continue;
		string color;
		cin >> color;
		if (color != "b"&&color != "w")continue;
		int x, y;
		string xy;
		cin >> xy;
		if (xy.size() == 2)
		{
			x = xy[0] - 'a';
			y = xy[1] - '0'-1;
		}
		else if(xy.size() == 3)
		{
			x = xy[0] - 'a';
			y = 10*(xy[1] - '0')+ xy[2] - '0'-1;
		}
		else continue;
		if (color == "b")a.play(x, y, a.BLACK);
		if (color == "w")a.play(x, y, a.WHITE);
		//a.selfSymmtery();
		a.print();
		stageInfo &si = gt[a];
		cout << "num=" << si.getCount() << endl << "Bwr=" << si.getBWr() << endl << "Score=" << si.getScoreAvr()<< endl << "Stdev=" << si.getScoreStdev() << endl;
	}
}
void test3()
{
	gameTree gt;
	gt.addSgfs("C:\\Users\\Administrator\\Desktop\\kata9sgf\\a.sgfs");
	//gt.addSgf("(;FF[4]GM[1]SZ[9]PB[b20c256-s323214080-d113773481]PW[b20c256-s323214080-d113773481]HA[0]KM[6.5]RU[koPOSITIONALscoreAREAsui0]RE[W+1.5]C[startTurnIdx=3,mode=0,modeM1=0,modeM2=0];B[ed];W[df];B[cd];W[fe]C[0.38 0.62 0.00 -1.7];B[gc]C[0.37 0.63 0.00 -2.3];W[gd]C[0.40 0.60 0.00 -1.3];B[ee]C[0.42 0.58 0.00 -1.0];W[ef]C[0.39 0.61 0.00 -2.1];B[ff]C[0.51 0.49 0.00 0.3];W[gf]C[0.46 0.54 0.00 -0.9];B[fg]C[0.48 0.52 0.00 -0.4];W[gg]C[0.49 0.51 0.00 -0.4];B[eh]C[0.49 0.51 0.00 -0.3];W[cg]C[0.49 0.51 0.00 -0.2];B[gh]C[0.50 0.50 0.00 0.0];W[hh]C[0.51 0.49 0.00 -0.0];B[bf]C[0.50 0.50 0.00 -0.1];W[dh]C[0.46 0.54 0.00 -0.8];B[hd]C[0.54 0.46 0.00 1.0];W[fc]C[0.56 0.44 0.00 2.0];B[fd]C[0.63 0.37 0.00 3.4];W[ge]C[0.69 0.31 0.00 3.9];B[hg]C[0.72 0.28 0.00 5.5];W[hf]C[0.69 0.31 0.00 4.2];B[cf]C[0.71 0.29 0.00 4.6];W[hc]C[0.69 0.31 0.00 3.4];B[hi]C[0.78 0.22 0.00 5.6];W[ig]C[0.73 0.27 0.00 3.9];B[de]C[0.75 0.25 0.00 4.0];W[dg]C[0.80 0.20 0.00 4.3];B[bg]C[0.80 0.20 0.00 4.3];W[di]C[0.75 0.25 0.00 3.4];B[ih]C[0.85 0.15 0.00 4.6];W[hg]C[0.85 0.15 0.00 5.2];B[gb]C[0.89 0.11 0.00 4.9];W[hb]C[0.79 0.21 0.00 3.1];B[he]C[0.85 0.15 0.00 3.9];W[ii]C[0.84 0.16 0.00 2.8];B[fb]C[0.90 0.10 0.00 6.5];W[gi]C[0.84 0.16 0.00 1.9];B[ha]C[0.88 0.12 0.00 2.0];W[id]C[0.88 0.12 0.00 1.9];B[bh]C[0.91 0.09 0.00 1.9];W[bi]C[0.93 0.07 0.00 2.0];B[ib]C[0.98 0.02 0.00 2.6];W[ie]C[0.97 0.03 0.00 2.1];B[ah]C[0.97 0.03 0.00 2.1];W[ci]C[0.98 0.02 0.00 2.2];B[ai]C[0.98 0.02 0.00 2.3];W[fh]C[0.98 0.02 0.00 2.5];B[ga]C[1.00 0.00 0.00 2.3];W[ic]C[0.99 0.01 0.00 1.9];B[ia]C[0.99 0.01 0.00 2.1];W[ch]C[0.99 0.01 0.00 1.6];B[dd]C[1.00 0.00 0.00 2.1];W[eg]C[1.00 0.00 0.00 1.6];B[ec]C[1.00 0.00 0.00 1.6];W[ei]C[1.00 0.00 0.00 1.6];B[]C[1.00 0.00 0.00 1.5];W[]C[1.00 0.00 0.00 1.6])");
}
void test4(std::string filename)
{
	gameTree gt;
	gt.addSgfs(filename);
	GTP gtp(&gt);
	gtp.startGTP();
}
