#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

class Item
{
	char itfile[60];
	char itdesc[8][30];
	long double itprice,  sp;
	public:
	char itnm[50];
	char itcat[4][5];
	long double count;
	void itdat(char [], char [], char [], char[], int);
};
void Item :: itdat(char w[], char x[], char y[], char z[], int nof)
{
	char che[50], newche[50];
	int point = 0, j = nof-1;
	strcpy(itcat[0], w);
	strcpy(itcat[1], x);
	strcpy(itcat[2], y);
	strcpy(itcat[3], z);
	strcpy(itfile, "c:\\animart");
	strcpy(che, "c:\\animart");
	for(int i=0; i<nof; i++)
	{
		strcat(itfile, "\\");
		strcat(itfile, itcat[i]);
	}
	strcat(itfile, ".txt");
	cout<<"Enter Item Name or Model with company name:\n";
	gets(itnm);
	cout<<"\nEnter Price:\n";
	cin>>itprice;
	cout<<"\nNo. of Pieces in Stock:\n";
	cin>>count;
	for(i=0; i<j; i++)
	{
		strcat(che, "\\");
		strcat(che, itcat[i]);
	}
	strcat(che, ".dat");
}

void main()
{
	clrscr();
	Item I;
	char ch='y', fit[4][8], chi[60];
	int nof, i;
	strcpy(chi, "c:\\animart");
	while((ch == 'y') || (ch == 'Y'))
	{
		clrscr();
		cout<<"Enter no. of folders (after \"c:\\animart\\\")\n";
		cin>>nof;
		for( i=0; i<nof; i++)
		{
			cout<<"Enter folder "<<i+1<<" : ";
			cin>>fit[i];
			strcat(chi, "\\");
			strcat(chi, fit[i]);
		}
		clrscr();
		cout<<"\nEnter File Name (without.txt): ";
		cin>>fit[i];
		strcat(chi, "\\");
		strcat(chi, fit[i]);
		strcat(chi, ".txt");
		nof += 1;
		I.itdat(fit[0], fit[1], fit[2], fit[3], nof);
		ofstream fo(chi, ios :: app);
		fo.write((char*)&I, sizeof(I));
		cout<<"Want to Enter more (y/n) ? ";
		cin>>ch;
	}
	getch();
}