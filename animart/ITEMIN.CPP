#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

class Item
{
	char itfile[60];
	char itdesc[8][30];
	public:
	char itnm[50];
	char itcat[4][5];
	long double count, mrp, itprice;
	void itdat();
};
void Item :: itdat()
{
	strcpy(itcat[0], "ele");
	strcpy(itcat[1], "cell");
	strcpy(itcat[2], "evo");
	strcpy(itcat[3], "");
	strcpy(itfile, "c:\\animart\\ele\\cell\\evo.txt");
	/*for(int i=0; i<3; i++)
	{
		strcat(itfile, "\\");
		strcat(itfile, itcat[i]);
	}
	strcat(itfile, ".txt");*/
	strcpy(itnm, "HTC Evo 4G");
	itprice = 3399;
	count = 200;
}

void main()
{
	clrscr();
	Item I;
	char chi[60];
	int nof, i;
	clrscr();
	strcpy(chi, "c:\\tc\\bin\\dfh\\cell.dat");
	clrscr();
	I.itdat();
	ofstream fo(chi);
	fo.write((char*)&I, sizeof(I));
	ifstream f1(chi);
	while(f1.read((char *)&I, sizeof(I)))
		cout<<I.itnm<<"\n"<<I.count<<"\nRs."<<I.itprice<<"\n\n";
	getch();
}