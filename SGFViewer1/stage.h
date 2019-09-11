#pragma once
template<unsigned int bs>
class stage
{
public:
	static constexpr unsigned char EMPTY = 0, BLACK = 1, WHITE = 2, INVALIDCOLOR = 3, PASS = 255;
	static constexpr unsigned char XLEN=(bs+3)/4;//char的长度，4个局面一个字节
	unsigned char board[bs][XLEN];//盘面,存储顺序x编号小的在低位
	unsigned short movenum;
	inline unsigned char getColor(unsigned char x, unsigned char y);//获得某个点的颜色
	inline void setColor(unsigned char x, unsigned char y, unsigned char color);//设置某个点的颜色
	bool checkLiberty(unsigned char x, unsigned char y);//检查某个点有没有气，有气返回0，没有气就提掉返回1，如果是空点也返回0

public:
	stage();
	~stage();
	bool play(unsigned char x, unsigned char y, unsigned char color);//落子，color=255代表pass,true成功，false失败
	stage&& copyAndPlay(unsigned char x, unsigned char y, unsigned char color);//落子,不修改原来盘面
//	friend bool operator<(const stage<bs>& a, const stage<bs>& b);//std::map的key值需要重载运算符
	bool operator==(const stage& b);
	stage symmtery(unsigned char type);//对称
	void selfSymmtery();//转化为最小对称形式
	void print();

}; 

template<unsigned int bs>
stage<bs>::stage()
{
	movenum = 0;
	for (int x = 0; x < XLEN; x++)for (int y = 0; y < bs; y++)board[y][x] = 0;
}

template<unsigned int bs>
stage<bs>::~stage()
{
}

template<unsigned int bs>
inline unsigned char stage<bs>::getColor(unsigned char x, unsigned char y)
{
	if (x < 0 || x >= bs || y < 0 || y >= bs)return INVALIDCOLOR;
	unsigned char data = board[y][x / 4];
	return data >> (2 * (x % 4)) & 0b00000011;

}

template<unsigned int bs>
inline void stage<bs>::setColor(unsigned char x, unsigned char y, unsigned char color)
{
	board[y][x / 4] = board[y][x / 4] & (~(0b00000011 <<(2* (x % 4)))) | (color <<(2* (x % 4)));

}

template<unsigned int bs>
void stage<bs>::print()
{
	std::cout << std::endl;
	std::cout<<"movenum="<<movenum<<std::endl<< "   ";
	for (int x = 0; x < bs; x++)std::cout << char('a' + x)<<" ";
	std::cout << std::endl;
	for (int y = 0; y < bs; y++)
	{
		if (y < 9)std::cout << " " << y + 1 << " ";
		else std::cout <<  y + 1 << " ";
		for (int x = 0; x < bs; x++)
		{
			unsigned char color = getColor(x, y);
			if (color == EMPTY)std::cout << "+ ";
			else if (color == BLACK)std::cout << "X ";
			else if (color == WHITE)std::cout << "O ";
			else if (color == INVALIDCOLOR)std::cout << "? ";
			else std::cout << "error ";
		}
		std::cout << std::endl;
	}
}


template<unsigned int bs>
bool stage<bs>::checkLiberty(unsigned char x, unsigned char y)
{
	unsigned char color = getColor(x, y);
	unsigned char oppocolor = 3 - color;//对手的颜色
	if (color == EMPTY || color == INVALIDCOLOR)return false;
	unsigned char neighbor4[4] = { getColor(x + 1, y),getColor(x - 1, y),getColor(x , y + 1),getColor(x, y - 1) };//周围4个点，如果足够判定就省去了循环
	if (neighbor4[0] == EMPTY || neighbor4[1] == EMPTY || neighbor4[2] == EMPTY || neighbor4[3] == EMPTY)return false;//周围4个交叉点有气
	if ((neighbor4[0] == oppocolor || neighbor4[0] == INVALIDCOLOR) && (neighbor4[1] == oppocolor || neighbor4[1] == INVALIDCOLOR) &&
		(neighbor4[2] == oppocolor || neighbor4[2] == INVALIDCOLOR) && (neighbor4[3] == oppocolor || neighbor4[3] == INVALIDCOLOR))//单子没气
	{
		setColor(x, y, EMPTY);
		return true;
	}
	unsigned char tmpboard[bs][bs];//0未探索节点，1已探索到但是未继续探索的节点，2已探索完成的节点
	for (int i = 0; i < bs*bs; i++)tmpboard[i / bs][i%bs] = 0;
	tmpboard[y][x] = 1;
	while (1)
	{
		//std::cout << "loop ";
		bool newNeighbor = false;//这一遍搜索是否有值为1的节点，如果没有说明搜索完毕且没气
		for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)if (tmpboard[y][x] == 1)
		{
			newNeighbor = true;
			tmpboard[y][x] = 2;
			unsigned char tmpcolor;
			if (tmpboard[y][x + 1] == 0)
			{
				tmpcolor = getColor(x + 1, y);
				if (tmpcolor == EMPTY)return false;
				else if (tmpcolor == color)tmpboard[y][x + 1] = 1;
			}
			if (tmpboard[y][x - 1] == 0)
			{
				tmpcolor = getColor(x - 1, y);
				if (tmpcolor == EMPTY)return false;
				else if (tmpcolor == color)tmpboard[y][x - 1] = 1;
			}
			if (tmpboard[y + 1][x] == 0)
			{
				tmpcolor = getColor(x , y + 1);
				if (tmpcolor == EMPTY)return false;
				else if (tmpcolor == color)tmpboard[y + 1][x ] = 1;
			}
			if (tmpboard[y-1][x] == 0)
			{
				tmpcolor = getColor(x , y-1);
				if (tmpcolor == EMPTY)return false;
				else if (tmpcolor == color)tmpboard[y-1][x ] = 1;
			}


		}
		if (newNeighbor == false)
		{
			for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)if (tmpboard[y][x] == 2)setColor(x, y, EMPTY);
			return true;
		}
	}

}

template<unsigned int bs>
bool stage<bs>::play(unsigned char x, unsigned char y, unsigned char color)
{
	if (color == PASS)
	{
		movenum++;
		return true;
	}
	if (getColor(x, y) != EMPTY)
	{
		//std::cout << "stage::play : Invalid move";
		return false;
	}
	if (color!=WHITE&&color!=BLACK)
	{
		std::cout << "stage::play : Invalid color";
		return false;
	}
	setColor(x, y, color);
	movenum++;
	unsigned char oppocolor = 3 - color;
	unsigned char tmpcolor;
	tmpcolor = getColor(x + 1, y);
	if (tmpcolor == oppocolor)checkLiberty(x + 1, y);
	tmpcolor = getColor(x - 1, y);
	if (tmpcolor == oppocolor)checkLiberty(x - 1, y);
	tmpcolor = getColor(x , y+1);
	if (tmpcolor == oppocolor)checkLiberty(x , y+1);
	tmpcolor = getColor(x , y-1);
	if (tmpcolor == oppocolor)checkLiberty(x , y-1);
	checkLiberty(x, y);
	return true;
}

template<unsigned int bs>
stage<bs>&& stage<bs>::copyAndPlay(unsigned char x, unsigned char y, unsigned char color)
{
	stage<bs> b = *this;
	b.play(x, y, color);
	return std::move(b);
}

template<unsigned int bs>
bool operator<(const stage<bs>& a,const stage<bs>& b)
{
	if (a.movenum < b.movenum)return true;
	if (a.movenum > b.movenum)return false;
	for (int x = 0; x < a.XLEN; x++)for (int y = 0; y < bs; y++)
	{
		if (a.board[y][x] < b.board[y][x])return true;
		if (a.board[y][x] > b.board[y][x])return false;
	}
	return false;

}

template<unsigned int bs>
bool stage<bs>::operator==(const stage& b)
{
	if (movenum!= b.movenum)return false;
	for (int x = 0; x < XLEN; x++)for (int y = 0; y < bs; y++)
	{
		if (board[y][x] != b.board[y][x])return false;
	}
	return true;

}

template<unsigned int bs>
void stage<bs>::selfSymmtery()
{
	stage<bs> t[8];
	for (int i = 0; i < 8; i++)t[i].movenum = movenum;
	t[0] = *this;
	for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)t[1].setColor(x, y, t[0].getColor(bs-1-x, y));
	for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)t[2].setColor(x, y, t[0].getColor(x, bs - 1 - y));
	for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)t[4].setColor(x, y, t[0].getColor(y, x));
	for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)t[5].setColor(x, y, t[4].getColor(bs - 1 - x, y));
	for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)t[6].setColor(x, y, t[4].getColor(x, bs - 1 - y));
	for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)t[3].setColor(x, y, t[2].getColor(bs - 1 - x, y));
	for (int y = 0; y < bs; y++)for (int x = 0; x < bs; x++)t[7].setColor(x, y, t[6].getColor(bs - 1 - x, y));
	for (int i = 0; i < 8; i++)
	{
		if (t[i] < *this)*this = t[i];
	}

}
