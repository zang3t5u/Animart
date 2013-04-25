#include <fstream.h>
#include <conio.h>
#include <stdio.h>

class Budge
{
	public:
	long double budget;
}B;
void main()
{
	clrscr();
	ifstream fin("c:\\animart\\budget.dat");
	while(fin.read((char *)&B, sizeof(B)))
		cout<<B.budget;
	getch();
}