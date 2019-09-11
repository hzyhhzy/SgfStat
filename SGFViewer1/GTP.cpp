#include "pch.h"
#include "GTP.h"
#include <sstream>
#include <fstream>
#include <Windows.h>
using namespace std;
GTP::GTP()
{
}


GTP::~GTP()
{
}

void GTP::startGTP()
{
	if (gt == nullptr)return;
	ofstream logstream("SVdebug.txt");
	//gameTree gt;
//	gt.addSgfs("C:\\Users\\Administrator\\Desktop\\kata9sgf\\a.sgfs");
	stage<9> a;
	while (1)
	{
		string line;
		getline(cin,line);
		logstream << line << endl;
		stringstream liness(line);
		string oprname;
		liness >> oprname;
		if (oprname == "name")
		{
			cout << "= KataGo"<<endl;
		}
		else if (oprname == "version")
		{
			cout << "= 1.2" << endl;
		}
		else if (oprname == "clear_board")
		{
			movenum = 0;
			cout << "=" << endl;
		}
		else if (oprname == "undo")
		{
			if(movenum>0)movenum --;
			cout << "=" << endl;
		}
		else if (oprname == "play")
		{
			string color;
			liness >> color;
			if (color != "b"&&color != "w"&&color != "B"&&color != "W")
			{
				cout << "? Error command" << endl << endl;
				continue;
			}
			int x, y;
			string xy;
			liness >> xy;
			if (xy.size() == 2)
			{
				if (xy[0] >= 'A'&&xy[0] <= 'Z')xy[0] += ('a' - 'A');
				if (xy[0] > 'i')xy[0]--;
				x = xy[0] - 'a';
				y = xy[1] - '0' - 1;
			}
			else if (xy.size() == 3)
			{
				if (xy[0] >= 'A'&&xy[0] <= 'Z')xy[0] += ('a' - 'A');
				if (xy[0] > 'i')xy[0]--;
				x = xy[0] - 'a';
				y = 10 * (xy[1] - '0') + xy[2] - '0' - 1;
			}
			else
			{
				cout << "? Error command" << endl << endl;
				continue;
			}
			if (color == "b" || color == "B" )history[movenum+1]=history[movenum].copyAndPlay(x, y, stage<bs>::BLACK);
			if (color == "w" || color == "W" )history[movenum + 1] = history[movenum].copyAndPlay(x, y, stage<bs>::WHITE);
			movenum++;
			cout << "=" << endl;
		}
		else if (oprname == "kata-analyze")
		{
			cout << "=" << endl;
			cout << gt->getLizStr(history[movenum]);
		}
		else if (oprname == "lz-analyze")
		{
			cout << "=" << endl;
			cout << gt->getLizStr(history[movenum]);
		}
		else if (oprname == "quit")
		{
			cout << "=" << endl;
			break;
		}
		else cout << "=" << endl;
		cout << endl;
	}
	logstream.close();
}