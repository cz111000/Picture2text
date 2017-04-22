// Picture2text.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	ifstream in("C:\\Users\\橙子\\Desktop\\picture.bmp", ios::in | ios::_Nocreate | ios::binary);
	ofstream out("C:\\Users\\橙子\\Desktop\\picture.txt", ios::out);
	if (in.is_open() && out.is_open())
	{
		char head[0x36];
		in.read(head, sizeof(head));
		long *width = (long*)&head[0x12];
		long *height = (long*)&head[0x16];
		long length = 4 - (*width * 3) % 4;
		char color[0x03];
		unsigned sum;
		if (*height > 0)
			in.seekg(0, ios::end);
		for (long i = 0; i < ((*height > 0) ? *height : -(*height)); i++)
		{
			if (*height > 0)
				in.seekg(-(*width * 3 + length), ios::cur);
			for (long j = 0; j < *width; j++)
			{
				in.read(color, sizeof(color));
				sum = (color[2] & 0xFF) + (color[1] & 0xFF) + (color[0] & 0xFF);
				if (sum == 0)
					out << " ";
				else if (sum < 85)
					out << "-";
				else if (sum < 85 * 2)
					out << "+";
				else if (sum < 255)
					out << "=";
				else if (sum < 255 + 85)
					out << "o";
				else if (sum < 255 + 85 * 2)
					out << "%";
				else if (sum < 255 * 2)
					out << "*";
				else if (sum < 255 * 2 + 85)
					out << "&";
				else if (sum < 255 * 2 + 85 * 2)
					out << "$";
				else if (sum < 255 * 3)
					out << "#";
				else
					out << "@";
			}
			in.seekg(length, ios::cur);
			if (*height > 0)
				in.seekg(-(*width * 3 + length), ios::cur);
			out << endl;
		}
		in.close();
		out.close();
	}

	return 0;
}
