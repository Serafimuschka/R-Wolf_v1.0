// listdisk.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include<iostream>
#include<windows.h>
#include <conio.h>
using namespace std;
int main()
{
	char buf[26];
	GetLogicalDriveStringsA(sizeof(buf), buf);
	const char *DRF[] = { "Unknown" , "Invalid path",
		"Removable", "Fixed" , "Network drive","CD-ROM", "RAM disk" };
	for (char *s = buf; *s; s += strlen(s) + 1)
		cout << s << "  " << DRF[GetDriveTypeA(s)] << endl;

	_getch();
	return 0;
}