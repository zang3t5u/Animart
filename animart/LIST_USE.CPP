#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>

class User
{
	char usernm[20], pass[30], verpass[30];
	public:
	long double balance;
	void nm();
};

void User :: nm()
{
	cout<<usernm<<" "<<balance<<"\n";
}
void main()
{
	clrscr();
	User ch;
	/*cout<<"Enter name: ";
	gets(ch.nm);
	ofstream fo("c:\\animart\\users.dat");
	fo.write((char *)&ch, sizeof(ch));
	fo.close();
	*/
	ifstream fi("c:\\animart\\users.dat");
	while(fi.read((char *)&ch, sizeof(ch)))
	{
		ch.nm();
	}
	getch();

}