#include <fstream.h>
#include <conio.h>
#include <stdio.h>

class Item
{
	char itfile[60];
	char itdesc[8][30];
	public:
	char itnm[50];
	char itcat[4][5];
	long double count, mrp, itprice;
};

void main()
{
	clrscr();
	ifstream f1("c:\\animart\\ele\\cell.dat");
	Item I;
	while(f1.read((char *)&I, sizeof(I)))
		cout<<I.itnm<<"\n"<<I.count<<"\nRs."<<I.itprice<<"\n\n";
	getch();
}