#include <fstream.h>
#include <ctype.h>
#include <bios.h>
#include <dos.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip.h>
#include <string.h>
#include <animart.h>

class Budge
{
	public:
	long double budget;
}B;

int use();
int stock();
int members=0;
int del(int &, char[]);
int choice2, choice3;
char choice, choice1, a ,b ,c ,d ,e, fit[4][5] ,subch;
long double p=0;

int buy(char [], Budge &);
void Anima(Budge &, char [], char);
void look();

void stringinit(char *buff, int size)
{
	for(int i = 0; i < size; i++)
	{
		buff[i] = NULL;
	}
}

int fieldEntry(char *a, int x, int y, int &no, char type, int size)
{
	int keyBACKSPACE = 8,keyESCAPE = 27,keyENTER = 7181, point;

	_setcursortype(_NORMALCURSOR);
	gotoxy(x, y);
	char input;
	int n = no;
	while(1)
	{
		input = bioskey(0);
		if(((isalnum(input))|| input == '@' || input=='_' || input == ' ' ||
			input == '/' || input == '.')  && no<size)
		{
			if(type == 'u')      //For normal input
			{
				a[no] = input;
				no++;
				cout<<input;

			}
			if(type == 'p')    //For 'asterisk' input
			{
				a[no] = input;
				no++;
				cout<<"*";
			}
		}
		else  if(input == keyBACKSPACE && no!=0)
		{
			gotoxy(x+no-1, y);
			cout<<" ";
			gotoxy(x+no-1,y);
			no--;
			a[no] = NULL;
		}

		else if(input == char(keyENTER))
		{
			point = 1;
			break;
		}
		else if(input == char(keyESCAPE))
		{
			point = 0;
			break;
		}
	}
	no = n;
	return point;
}

class User
{
	char usernm[20], pass[30], verpass[30];
	public:
	long double balance;
	int read();
	int check(User us);
	int ch_nm(char nm[], char);
	int ch_val(char unm[], char ps[]);
	int ver();
	char* nm();
	void disp();
}us;

int ind=0, passn = 0;
char usert[30],passw[50];

char* User :: nm()
{
	return usernm;
}
void User :: disp()
{
	cout<<"Username: "<<usernm<<"\nPassword: "<<pass<<"\nBalance: "<<balance<<endl;
}

int User :: read()
{
	animate();
	int point=1;
	gotoxy(1,11);
	cout<<"To Cancel : Press \'esc\' while entering password or while re-entering password...";
	cout<<endl<<"BE AVISED: You'll not be able to cancel once you re-enter the password...\n";
	cout<<"\nOnce you have successfully verified the password\nAnd if your Username doesn't match any of our existing Usernames\nYou agree to our policies\nAnd your Balance will not be refunded when you delete your account...";
	gotoxy(1,3);
	cout<<"Username: ";
	gets(usernm);
	cout<<"Password: ";
	stringinit(pass, 50);
	if(fieldEntry(pass, 11, 4, passn, 'p', sizeof(pass)))
	{
		cout<<endl<<"Re-enter Password: ";
		stringinit(verpass, 50);
		//load();
		if(fieldEntry(verpass, 20, 5, passn, 'p', sizeof(verpass)))
		{
			gotoxy(1, 11);
			cout<<"Your Balance will be used as the mode of payment on this site...                                              \n";
			for(int i=0; i<=79; i++)
				cout<<" ";
			cout<<"\nIf your Username doesn't match any of the existing Usernames,\nYou'll not be able to cancel now...                                         \n";
			cout<<"The Balance you enter will not be refunded if you delete your account...        ";
			for(i=1; i<=2; i++)
			{
				for(int j=1; j<=79; j++)
					cout<<" ";
				cout<<endl;
			}
			gotoxy(1, 5);
			cout<<"\nBalance: ";
			cin>>balance;
		}
		else
		{
			strcpy(usernm,"");
			strcpy(verpass,"");
			strcpy(pass, "");
			balance=0;
			point = 0;
		}
	}
	else
	{
		strcpy(pass,"");
		strcpy(usernm,"");
		point = 0;
	}
	return point;
}

int User :: ver()
{
	if(strcmp(verpass, pass) == 0)
		return 1;
	return 0;
}

int User :: ch_val(char unm[], char ps[])
{
	if(strcmp(pass, ps))
		return -1;
	else if((strcmp(unm, usernm)==0) && (strcmp(pass, ps)==0))
		return 1;
	return 0;
}

int User :: ch_nm(char nam[], char p = 's')
{
	if(p == 's')
		if(strcmp(usernm, nam) == 0)
			return 1;
		else
			return 0;
	else
	{
		if(strcmpi(usernm, nam) == 0)
			return 1;
		else
			return 0;
	}
}

int User :: check(User us)
{
	char nm[30];
	strcpy(nm, usernm);
	if(us.ch_nm(nm) == 1)
		return 1;
	return 0;
}

class Admin
{
	char usernm[20], pass[30], verpass[30];
	public:
	int read();
	int check(User us);
};

int Admin :: check(User us)
{
	char nm[30];
	strcpy(nm, usernm);
	if(us.ch_nm(nm, 'i') == 1)
		return 1;
	return 0;
}

User u[500], usr;
int tradeconf(Budge &B, char cur[], char trade, long double itprice, long double count1, char itnm[])
{
	char usrnm[30], pss[30];
	long double z = (itprice * count1);
	int detect = 1, point, cursor = 4;
	User us;
	animate();
	gotoxy(1,8);
	cout<<"NOTE: This is for security reasons";
	gotoxy(1,3);
	cout<<"Enter Username:";
	gets(usrnm);
	int flag=0, tab = 0, f=0;
	ifstream f3("c:\\animart\\users.dat");
	ofstream f4("c:\\animart\\newusers.dat");
	//load();
	if(strcmp(cur, usrnm)==0)
	{
		while(f3.read((char *)&us, sizeof(us)))
		{
			flag = 0;
			if(us.ch_nm(usrnm) == 1)
			{
				verif:
				cout<<"Enter Password:";
				stringinit(pss, 50);
				//load();
				if(fieldEntry(pss, 16, cursor, passn, 'p', sizeof(pss)));
				else
				{
					detect = 0;
					break;
				}
				if(detect)
				{
					if(us.ch_val(usrnm, pss) == -1)
					{
						if(tab<3)
						{
							tab++;
							animate();
							gotoxy(1, 12);
							cout<<"NOTE: This is for security reasons.";
							gotoxy(1, 3);
							cout<<"\n\n"<<setw(52)<<"Passwords do not match..\n"<<setw(46)<<"Try again...\n"<<setw(37)<<"You have "<<(3-tab)<<" chances left"<<endl<<endl;
							cursor = 9;
							goto verif;
						}
						else
						{
							for(int i=5; i>=1; i--)
							{
								animate();
								cout<<setw(5)<<"Error... You will be redirected back in "<<i<<" seconds...";
								delay(1000);
								flag = 0;
							}
						}
					}
					else
					{
						char dec;
						de1:
						if(trade == 's')
							cout<<"\nAre you sure you want to sell "<<count1<<" "<<itnm<<"(s) (y/n)? ";
						else
							cout<<"\nAre you sure you want to buy "<<count1<<" "<<itnm<<"(s) (y/n)? ";
						cin>>dec;
						if((dec=='n') || (dec=='N'))
							flag = 2;
						else if((dec == 'y') || (dec == 'Y'))
							flag = 1;
						else
						{
							animate();
							cout<<"\n\n\n"<<setw(55)<<"Invalid choice!!!"<<"\n";
							goto de1;
						}
						f = flag;
					}
				}
			}
			if(flag==1)
			{
				if(trade == 's')
				{
					us.balance += z;
					B.budget -= z;
				}
				else
				{
					if(us.balance < z)
					{
						//load();
						cout<<"Sorry... You don't have enough balance...";
						f = 2;
						cout<<"\n\nPress any key to continue...";
						getch();
					}
					else
					{
						us.balance -= z;
						B.budget += z;
					}
				}
			}
			f4.write((char *)&us, sizeof(us));
		}
		f3.close();
		f4.close();
		remove("c:\\animart\\users.dat");
		rename("c:\\animart\\newusers.dat", "c:\\animart\\users.dat");
		//load();
		if(detect)
		{
			if(f==0)
			{
				for(int j=5; j>0; j--)
				{
					animate();
					cout<<setw(55)<<"Invalid Username or Password..."<<endl;
					redirect(j);
				}
				point = 0;
			}
			else if(f==1)
			{
				for(int j=5; j>0; j--)
				{
					animate();
					gotoxy(1, 20);
					cout<<setw(49)<<"Congratulations!!!"<<endl;
					if(trade == 's')
						cout<<setw(36)<<"Sold "<<count1<<" "<<itnm<<"(s)!!!"<<endl;
					else
						cout<<setw(38)<<"Bought "<<count1<<" "<<itnm<<"(s)!!!"<<endl;
					redirect(j);
				}
				point = 1;
			}
			else
			{
				for(int j=5; j>0; j--)
				{
					animate();
					if(trade == 's')
						cout<<setw(48)<<"Item not sold..."<<endl;
					else
						cout<<setw(49)<<"Item not bought..."<<endl;
					redirect(j);
				}
				point = -1;
				Anima(B, cur, 'u');
			}
		}
	}
	else
	{
		for(int j=5; j>0; j--)
		{
			animate();
			cout<<setw(49)<<"Invalid Username..."<<endl<<endl;
			cout<<setw(47)<<"Logging Out and"<<endl;
			redirect(j);
		}
		point = 0;
	}
	return point;
}

class Item
{
	char itfile[60];
	char itdesc[8][30];
	public:
	char itnm[50];
	char itcat[4][5];
	long double count, mrp, itprice;
	int itsell(Budge &, char[], char [], char [], char [], char[], int);
	int filech(char []);
	int itbuy(Budge &, char[], char [], char [], char [], char[], int);
};

int Item :: filech(char fi[])
{
	if(strcmpi(fi, itfile) == 0)
		return 1;
	return 0;
}

int Item :: itbuy(Budge &B, char cur[], char w[], char x[], char y[], char z[], int nof)
{
	char che[50], datf[50], newdatf[50];
	int j;
	long double count1;
	j = nof - 1;
	strcpy(che, "c:\\animart");
	strcpy(datf, "c:\\animart");
	strcpy(newdatf, "c:\\animart");
	strcpy(itcat[0], w);
	strcpy(itcat[1], x);
	strcpy(itcat[2], y);
	strcpy(itcat[3], z);
	for(int i=0; i<nof; i++)
	{
		strcat(che,"\\");
		strcat(che, itcat[i]);
		if(i==j)
		{
			strcat(datf, ".dat");
			strcat(newdatf, ".dat");
		}
		else if(i==j-1)
		{
			strcat(newdatf, "\\");
			strcat(newdatf, "new");
			strcat(newdatf, itcat[i]);
			strcat(datf, "\\");
			strcat(datf, itcat[i]);
		}
		else
		{
			strcat(newdatf, "\\");
			strcat(newdatf, itcat[i]);
			strcat(datf, "\\");
			strcat(datf, itcat[i]);
		}
	}
	strcat(che, ".txt");
	ifstream f1(datf);
	Item I;
	int k=1, pointer = 0, cursor = 3;
	while(f1.read((char *)&I, sizeof(I)))
	{
		if(I.filech(che)==1)
		{
			animate();
			buy:
			k=0;
			ifstream f2(che);
			char c;
			while(f2)
			{
				f2.get(c);
				cout<<c;
				if(I.count>0)
				{
					if(k==1)
					{
						gotoxy(73, cursor);
						cout<<"In Stock";
						gotoxy(73, cursor+1);
						cout<<"--------";
						gotoxy(1, cursor+2);
					}
					pointer = 1;
				}
				else if(I.count<=0)
				{
					if(k==1)
					{
						gotoxy(66, cursor);
						cout<<"Out of Stock!!!\n";
						gotoxy(66, cursor+1);
						cout<<"--------------";
						gotoxy(1, cursor+2);
					}
					pointer = -1;
				}
				if(c == '\n')
					k++;
			}
			f2.close();
			char ch;
			cout<<"\n\nIs this what you were looking for (y/n)? ";
			cin>>ch;
			if(pointer == 1)
			{
				if((ch == 'y')||(ch == 'Y'))
				{
					animate();
					long double count1;
					cout<<"Enter Quantity you want to buy: ";
					cin>>count1;
					pieces:
					animate();
					if(count1<=I.count)
					{
						int z = tradeconf(B, cur, 'b', I.itprice, count1, I.itnm);
						if(z==1)
						{
							ifstream fin(datf);
							ofstream fout(newdatf);
							while(fin.read((char *)&I, sizeof(I)))
							{
								if(strcmpi(I.itcat[j], itcat[j]) == 0)
								{
									I.count -= count1;
								}
								fout.write((char *)&I, sizeof(I));
							}
							fin.close();
							fout.close();
							remove(datf);
							rename(newdatf, datf);
							pointer = 1;
						}
						else if(z==0)
							pointer = 0;
						else
							pointer = -1;
					}
					else
					{
						char ch1;
						piece2:
						cout<<"\n\n\nSorry... We have only "<<I.count<<" pieces of "<<I.itnm<<" in our stock...\n";
						cout<<"Do you want to buy "<<I.count<<" pieces instead (y/n) ? ";
						cin>>ch1;
						if((ch1=='y')||(ch1=='Y'))
						{
							count1 = I.count;
							goto pieces;
						}
						else if((ch1=='n') || (ch1=='N'))
							pointer = -1;
						else
						{
							animate();
							cout<<setw(48)<<"Invalid Choice!!!"<<cur;
							gotoxy(1, 4);
							goto piece2;
						}
					}
				}
				else if((ch == 'n')||(ch == 'N'))
					pointer = -1;
				else
				{
					animate();
					cout<<"Invalid choice!!!\n";
					cursor = 4;
					goto buy;
				}
			}
			else if(pointer == -1)
			{
				cout<<"Sorry... We're out of stock...\n";
				cout<<"Please try again later...";
				cout<<"\n\nPress any key to continue...";
				getch();
			}
		}
	}
	return pointer;
}

int Item :: itsell(Budge &B, char cur[], char w[], char x[], char y[], char z[], int nof)
{
	char che[50], newche[50];
	int j, p = 0;
	long double count1;
	j = nof - 1;
	strcpy(itcat[0], w);
	strcpy(itcat[1], x);
	strcpy(itcat[2], y);
	strcpy(itcat[3], z);
	strcpy(itfile, "c:\\animart");
	strcpy(che, "c:\\animart");
	strcpy(newche, "c:\\animart");
	animate();
	if(strcmpi(itcat[j], "")==0)
	{
		cout<<"Enter Item Name or Model with company name:\n";
		gets(itnm);
		cout<<"\nEnter Price:\n";
		cin>>itprice;
		noit:
		cout<<"\nEnter Quantity to sell:\n";
		cin>>count1;
		if(B.budget < count1*itprice)
		{
			//load();
			animate();
			cout<<"Enter Item Name or Model with company name:\n"<<itnm;
			cout<<"\n\nEnter Price:\n"<<itprice;
			cout<<"\n\nSorry... We don't have enough budget...\nTry reducing the quantity to sell...\nIf problem persists, enter quantity to sell as \'0\' and come back later...\n";
			cout<<"\n\nPress any key to continue...";
			goto noit;
		}
		if(count1!=0)
		{
			cout<<"\nGive atmost 8 features... (Enter \'-\' if no more features)\n";
			for(int i=0; i<8; i++)
			{
				cout<<i+1<<": ";
				gets(itdesc[i]);
			}
			int z = tradeconf(B, cur, 's', itprice, count1, itnm);
			if(z==1)
			{
				int l = strlen(itnm), c=0;
				for(int i=0; i<l; i++)
				{
					if((i==0) || (itnm[i+1] == '\0') || (itnm[i-1] == ' ') || (itnm[i+1]=='-'))
					{
						if(c<4)
							itcat[j][c] = itnm[i];
						c++;
					}
				}
				if(c<4)
				{
					for(int i=1; i<=l; i++)
					{
					if((i==1) || (itnm[i+1] == ' ') || (itnm[i+1]=='-'))
						{
							if(c<4)
								itcat[j][c] = itnm[i];
							c++;
						}
					}
					randomize();
					int a[26], marq=0;
					for(i=65; i<91; i++)
					{
						a[marq] = i;
						marq++;
					}
					if(c<4)
					{
						for(i=0; i<2; i++)
						{
							marq = random(26);
							itcat[j][c] = a[marq];
							c++;
						}
					}
				}
				for(i=0; i<j; i++)
				{
					strcat(che, "\\");
					strcat(newche, "\\");
					strcat(che, itcat[i]);
					if(i==j-1)
						strcat(newche, "new");
					strcat(newche, itcat[i]);
				}
				strcat(che, ".dat");
				strcat(newche, ".dat");
				ifstream fin(che);
				ofstream fout(newche);
				Item I;
				int point = 0;
				while(fin.read((char *)&I, sizeof(I)))
				{
					if(strcmpi(I.itnm, itnm) == 0)
					{
						point = 1;
						I.count += count1;
						count1 = I.count;
						strcpy(itnm, I.itnm);
						for(i=0; i<nof; i++)
						strcpy(itcat[i], I.itcat[i]);
						itprice = I.itprice;
						strcpy(itfile, I.itfile);
					}
					fout.write((char *)&I, sizeof(I));
				}
				remove(che);
				rename(newche, che);
				fin.close();
				fout.close();
				if(point == 0)
				{
					count = count1;
					for(int i=0; i<nof; i++)
					{
						strcat(itfile, "\\");
						strcat(itfile, itcat[i]);
					}
					strcat(itfile, ".txt");
					ofstream fout(itfile);
					fout<<itnm<<"\n\n";
					for(i=0; i<8; i++)
					{
						if(strcmp(itdesc[i], "-"))
						fout<<itdesc[i]<<"\n";
					}
					mrp = itprice + 10*itprice/100;
					itprice = itprice + 5*itprice/100;
					fout<<"\nMRP: Rs."<<mrp<<"\nSpecial Price: Rs."<<itprice;
					fout.close();
				}
				p = 1;
			}
			else if(z==0)
				p = 0;
			else
				p = -1;
		}
		else
		{
			strcpy(itnm, "");
			itprice = 0;
			mrp=0;
			for(int i=0; i<8; i++)
				strcpy(itdesc[i], "");
			for(i=0; i<4; i++)
				strcpy(itcat[i], "");
			p = -1;
		}
	}
	else
	{
		for(int i=0; i<j; i++)
		{
			strcat(che, "\\");
			strcat(newche, "\\");
			strcat(che, itcat[i]);
			if(i==j-1)
				strcat(newche, "new");
			strcat(newche, itcat[i]);
		}
		strcat(che, ".dat");
		strcat(newche, ".dat");
		ifstream fin(che);
		Item I;
		char c;
		while(fin.read((char *)&I, sizeof(I)))
		{
			if(strcmpi(I.itcat[j], itcat[j]) == 0)
			{
				itprice = I.itprice;
				strcpy(itnm, I.itnm);
				break;
			}
		}
		fin.close();
		for(i=0; i<nof; i++)
		{
			strcat(itfile, "\\");
			strcat(itfile, itcat[i]);
		}
		strcat(itfile, ".txt");
		sell:
		ifstream f1(itfile);
		while(f1)
		{
			f1.get(c);
			cout<<c;
		}
		char ch;
		cout<<"\nIs this what you were looking for (y/n)? ";
		cin>>ch;
		if((ch=='y')||(ch=='Y'))
		{
			animate();
			noit1:
			cout<<"\nEnter quantity to sell:\n";
			cin>>count1;
			if(B.budget<count1*itprice)
			{
				animate();
				cout<<"\n\nSorry... We don't have enough budget...\nTry reducing the quantity to sell...\nIf problem persists, enter quantity to sell as \'0\' and come back later...\n";
				cout<<"\n\nPress any key to continue...";
				goto noit1;
			}
			if(count1!=0)
			{
				int z = tradeconf(B, cur, 's', itprice, count1, itnm);
				if(z==1	)
				{
					ifstream fin(che);
					ofstream fout(newche);
					while(fin.read((char *)&I, sizeof(I)))
					{
						if(strcmpi(I.itcat[j], itcat[j]) == 0)
						{
							I.count += count1;
						}
						fout.write((char *)&I, sizeof(I));
					}
					fin.close();
					fout.close();
					remove(che);
					rename(newche, che);
					p = 1;
				}
				else if(z==0)
					p = 0;
				else
					p = -1;
			}
			else
				p = -1;
		}
		else if((ch=='n')||(ch=='N'))
			p=-1;
		else
		{
			animate();
			cout<<"Invalid Choice!!!\n";
			goto sell;
		}
	}
	return p;
}

int sell(char cur[], Budge &B)
{
	int pointer;
	Item I, I1, I2[50];
	int ind, z, k;
	animate();
	sell:
	cout<<setw(49)<<"Welcome To Animart"<<setw(31)<<cur;
	cout<<setw(50)<<"------------------ ";
	cout<<endl<<endl<<endl<<"What Would You Like To Do : ";
	cout<<endl<<"--------------------------- ";
	cout<<endl<<"1. Buy ";
	cout<<setw(24)<<"2. Sell"<<"\t\t\t\t3.Back ";
	cout<<endl<<"--------               ---------\t\t\t---------";
	cout<<setw(38)<<endl<<"a. Electronics ";
	cout<<setw(32)<<endl<<"b. Books ";
	cout<<setw(42)<<endl<<"c. Home Appliances ";
	cout<<setw(40)<<endl<<"d. Entertainment ";
	gotoxy(29,7);
	cin>>choice;
	if (choice == '1')
		if(buy(cur, B))
			return 1;
		else
			return 0;
	else if(choice == '2')
	{
		animate();
		goto sell;
	}
	else if(choice == '3')
		return 1;
	else if(choice == 'a')
	{
		strcpy(fit[0], "ele");
		animate();
		c1a:
		cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
		cout<<setw(50)<<"--------------------- ";
		cout<<endl<<endl;
		cout<<"What Would You Like To Sell: ";
		cout<<endl<<endl<<"1. Cellphones & PDA's"<<setw(56)<<"6. Back";
		cout<<endl<<"2. Computers ";
		cout<<endl<<"3. Tv, Audio & Video ";
		cout<<endl<<"4. Cameras ";
		cout<<endl<<"5. Air Conditioners";
		gotoxy(30,7);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "cell");
			int k, cursor = 10;
			animate();
			c2:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"CELLPHONES & PDA's";
			cout<<endl<<"------------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c2;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "Comp");
			animate();
			int k, cursor = 10;
			c2a:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"COMPUTERS";
			cout<<endl<<"---------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2a;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c2a;
			}
		}
		else if(choice2 == 3)
		{
			strcpy(fit[1], "TV");
			animate();
			int k, cursor = 10;
			c2b:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			cout<<endl<<endl<<endl<<"Tv, Audio & Video";
			cout<<endl<<"-----------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2b;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c2b;
			}
		}
		else if(choice2 == 4)
		{
			strcpy(fit[1], "Cam");
			int k, cursor = 10;
			animate();
			c2c:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"CAMERAS";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2c;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c2c;
			}
		}
		else if(choice2 == 5)
		{
			strcpy(fit[1], "AC");
			int k, cursor = 10;
			animate();
			c2d:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"AIR CONDITIONERS";
			cout<<endl<<"----------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2d;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c2d;
			}
		}
		else if(choice2 == 6)
		{
			animate();
			goto sell;
		}
		else
		{
			animate();
			cout<<"Invalid choice...";
			gotoxy(1, 3);
			goto c1a;
		}
	}
	else if(choice == 'b')
	{
		strcpy(fit[0], "boo");
		animate();
		c1b:
		cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
		cout<<setw(47)<<"---------------";
		cout<<endl<<endl;
		cout<<"What Would You Like To Sell : ";
		cout<<endl<<"1. Fiction"<<setw(71)<<"8. Back";
		cout<<endl<<"2. Romance ";
		cout<<endl<<"3. Science Fiction ";
		cout<<endl<<"4. Biographies and Autobiographies ";
		cout<<endl<<"5. Fantasy ";
		cout<<endl<<"6. Humour ";
		cout<<endl<<"7. Mystery ";
		gotoxy(30, 9);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "fic");
			int k, cursor = 10;
			animate();
			c3:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"FICTION";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(53)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c3;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "rom");
			animate();
			int k, cursor = 10;
			c3a:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"ROMANCE";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3a;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c3a;
			}
		}
		else if(choice2 == 3)
		{
			strcpy(fit[1], "scifi");
			animate();
			int k, cursor = 10;
			c3b:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl<<endl<<"SCIENCE FICTION";
			cout<<endl<<"---------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3b;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c3b;
			}
		}
		else if(choice2 == 4)
		{
			strcpy(fit[1], "bio");
			int k, cursor = 10;
			animate();
			c3c:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"BIOGRAPHIES AND AUTOBIOGRAPHIES";
			cout<<endl<<"-------------------------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3c;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c3c;
			}
		}
		else if(choice2 == 5)
		{
			strcpy(fit[1], "fant");
			int k, cursor = 10;
			animate();
			c3d:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"FANTASY";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3d;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c3d;
			}
		}
		else if(choice2 == 6)
		{
			strcpy(fit[1], "hum");
			int k, cursor = 10;
			animate();
			c3e:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"HUMOUR";
			cout<<endl<<"------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3e;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c3e;
			}
		}
		else if(choice2 == 7)
		{
			strcpy(fit[1], "myst");
			int k, cursor = 10;
			animate();
			c3f:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"MYSTERY";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3f;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c3f;
			}
		}
		else if(choice2 == 8)
		{
			animate();
			goto sell;
		}
		else
		{
			animate();
			cout<<"Invalid choice...\n";
			goto c1b;
		}
	}
	else if(choice == 'c')
	{
		strcpy(fit[0], "@hom");
		animate();
		c1c:
		cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
		cout<<setw(47)<<"---------------";
		cout<<endl<<endl;
		cout<<"What Would You Like To Sell : ";
		cout<<endl<<"1. Microwave"<<setw(38)<<"6. Back";
		cout<<endl<<"2. Refrigerator";
		cout<<endl<<"3. Vacuum Cleaner";
		cout<<endl<<"4. Washing Machine";
		cout<<endl<<"5. Water Purifier";
		gotoxy(30, 7);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "MW");
			int k, cursor = 10;
			animate();
			c4:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"MICROWAVE";
			cout<<endl<<"---------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c4;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "REF");
			int k, cursor = 10;
			animate();
			c4a:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"REFRIGERATOR";
			cout<<endl<<"------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4a;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c4a;
			}
		}
		else if(choice2 == 1)
		{
			strcpy(fit[1], "VC");
			int k, cursor = 10;
			animate();
			c4b:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"VACUUM CLEANER";
			cout<<endl<<"--------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4b;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c4b;
			}
		}
		else if(choice2 == 4)
		{
			strcpy(fit[1], "WM");
			int k, cursor = 10;
			animate();
			c4c:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"WASHING MACHINE";
			cout<<endl<<"---------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4c;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c4c;
			}
		}
		else if(choice2 == 5)
		{
			strcpy(fit[1], "WP");
			int k, cursor = 10;
			animate();
			c4d:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"WATER PURIFIER";
			cout<<endl<<"--------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4d;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c4d;
			}
		}
		else if(choice2 == 6)
		{
			animate();
			goto sell;
		}
		else
		{
			animate();
			cout<<"Invalid choice...\n";
			goto c1c;
		}
	}
	else if(choice == 'd')
	{
		strcpy(fit[0], "emnt");
		animate();
		c1d:
		cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
		cout<<setw(51)<<"-----------------------";
		cout<<endl<<endl;
		cout<<"What Would You Like To Sell : ";
		cout<<endl<<"1. Games"<<setw(67)<<"4. Back";
		cout<<endl<<"2. Movies";
		cout<<endl<<"3. Music Players";
		gotoxy(30, 5);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "GAM");
			int k, cursor = 10;
			animate();
			c5:
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			cout<<endl<<endl;
			cout<<endl<<"GAMES";
			cout<<endl<<"-----\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1d;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c5;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c5;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "MOV");
			int k, cursor = 10;
			animate();
			c5a:
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			cout<<endl<<endl;
			cout<<endl<<"MOVIES";
			cout<<endl<<"------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1d;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c5a;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c5a;
			}
		}
		else if(choice2 == 3)
		{
			strcpy(fit[1], "MP");
			int k, cursor = 10;
			animate();
			c5b:
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			cout<<endl<<endl;
			cout<<endl<<"MUSIC PLAYERS";
			cout<<endl<<"-------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+2;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-2)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1d;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c5b;
			}
			z = I.itsell(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
					pointer = 1;
				}
			}
			else
			{
				animate();
				goto c5b;
			}
		}
		else if(choice2 == 4)
		{
			animate();
			goto sell;
		}
		else
		{
			animate();
			cout<<"Invalid choice...\n";
			goto c1d;
		}
	}
	else
	{
		animate();
		cout<<"Invalid choice...";
		gotoxy(1,3);
		goto sell;
	}
	return pointer;
}

int buy(char cur[], Budge &B)
{
	int pointer, i;
	Item I, I1, I2[50];
	int ind, k, z, cursor = 10;
	animate();
	buy:
	cout<<setw(49)<<"Welcome To Animart"<<setw(31)<<cur;
	cout<<setw(50)<<"------------------ ";
	cout<<endl<<endl<<endl<<"What Would You Like To Do : ";
	cout<<endl<<"--------------------------- ";
	cout<<endl<<"1. Buy ";
	cout<<setw(24)<<"2. Sell"<<"\t\t\t\t3.Back ";
	cout<<endl<<"--------               ---------\t\t\t---------";
	cout<<endl<<"a. Electronics ";
	cout<<endl<<"b. Books ";
	cout<<endl<<"c. Home Appliances ";
	cout<<endl<<"d. Entertainment ";
	gotoxy(29,7);
	cin>>choice;
	if (choice == '2')
		if(sell(cur, B))
			return 1;
		else
			return 0;
	else if(choice == '1')
	{
		animate();
		goto buy;
	}
	else if(choice == '3')
		return 1;
	else if(choice == 'a')
	{
		strcpy(fit[0], "ele");
		animate();
		c1a:
		cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
		cout<<setw(50)<<"--------------------- ";
		cout<<endl<<endl;
		cout<<"What would You Like To Buy :";
		cout<<endl<<endl<<"1. Cellphones & PDA's ";
		cout<<endl<<"2. Computers ";
		cout<<endl<<"3. Tv, Audio & Video ";
		cout<<endl<<"4. Cameras ";
		cout<<endl<<"5. Air Conditioners ";
		cout<<endl<<"6. Back";
		gotoxy(30,8);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "cell");
			animate();
			c2:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"CELLPHONES & PDA's";
			cout<<endl<<"------------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
				}
				pointer = 1;
			}
			else
			{
				animate();
				goto c2;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "Comp");
			animate();
			c2a:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"COMPUTERS";
			cout<<endl<<"---------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"--------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2a;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z== 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
				}
				pointer = 1;
			}
			else
			{
				animate();
				goto c2a;
			}
		}
		else if(choice2 == 3)
		{
			strcpy(fit[1], "TV");
			animate();
			c2b:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			cout<<endl<<"Tv, Audio & Video";
			cout<<endl<<"-----------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2b;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
			{
				if(strcmpi(fit[2], "") == 0)
				{
					char che[50];
					strcpy(che, "c:\\animart");
					for(int i=0; i<2; i++)
					{
						strcat(che, "\\");
						strcat(che, fit[i]);
					}
					strcat(che, ".dat");
					ofstream fo(che, ios::app);
					fo.write((char *)&I, sizeof(I));
				}
				pointer = 1;
			}
			else
			{
				animate();
				goto c2b;
			}
		}
		else if(choice2 == 4)
		{
			strcpy(fit[1], "Cam");
			animate();
			c2c:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"CAMERAS";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2c;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c2c;
			}
		}
		else if(choice2 == 5)
		{
			strcpy(fit[1], "AC");
			animate();
			c2d:
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			cout<<endl<<endl;
			cout<<endl<<"CAMERAS";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(50)<<"ANIMART - ELECTRONICS "<<setw(30)<<cur;
			cout<<setw(50)<<"------------------- ";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1a;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c2d;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c2d;
			}
		}
		else if(choice2 == 6)
		{
			animate();
			goto buy;
		}
		else
		{
			animate();
			cout<<"Invalid choice...";
			gotoxy(1, 3);
			goto c1a;
		}
	}
	else if(choice == 'b')
	{
		strcpy(fit[0], "boo");
		animate();
		c1b:
		cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
		cout<<setw(47)<<"---------------";
		cout<<endl<<endl;
		cout<<"What Would You Like To Sell : ";
		cout<<endl<<"1. Fiction"<<setw(71)<<"8. Back";
		cout<<endl<<"2. Romance ";
		cout<<endl<<"3. Science Fiction ";
		cout<<endl<<"4. Biographies and Autobiographies ";
		cout<<endl<<"5. Fantasy ";
		cout<<endl<<"6. Humour ";
		cout<<endl<<"7. Mystery ";
		gotoxy(30, 9);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "fic");
			int k, cursor = 10;
			animate();
			c3:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"FICTION";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(53)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c3;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "rom");
			animate();
			int k, cursor = 10;
			c3a:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"ROMANCE";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3a;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c3a;
			}
		}
		else if(choice2 == 3)
		{
			strcpy(fit[1], "scifi");
			animate();
			int k, cursor = 10;
			c3b:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl<<endl<<"SCIENCE FICTION";
			cout<<endl<<"---------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3b;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c3b;
			}
		}
		else if(choice2 == 4)
		{
			strcpy(fit[1], "bio");
			int k, cursor = 10;
			animate();
			c3c:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"BIOGRAPHIES AND AUTOBIOGRAPHIES";
			cout<<endl<<"-------------------------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			cout<<k-1<<".Other";
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3c;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c3c;
			}
		}
		else if(choice2 == 5)
		{
			strcpy(fit[1], "fant");
			int k, cursor = 10;
			animate();
			c3d:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"FANTASY";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;

			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3d;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c3d;
			}
		}
		else if(choice2 == 6)
		{
			strcpy(fit[1], "hum");
			int k, cursor = 10;
			animate();
			c3e:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"HUMOUR";
			cout<<endl<<"------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;

			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3e;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c3e;
			}
		}
		else if(choice2 == 7)
		{
			strcpy(fit[1], "myst");
			int k, cursor = 10;
			animate();
			c3f:
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"MYSTERY";
			cout<<endl<<"-------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - BOOKS"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1b;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c3f;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c3f;
			}
		}
		else if(choice2 == 8)
		{
			animate();
			goto buy;
		}
		else
		{
			animate();
			cout<<"Invalid choice...\n";
			goto c1b;
		}
	}
	else if(choice == 'c')
	{
		strcpy(fit[0], "@hom");
		animate();
		c1c:
		cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
		cout<<setw(47)<<"---------------";
		cout<<endl<<endl;
		cout<<"What Would You Like To Sell : ";
		cout<<endl<<"1. Microwave"<<setw(38)<<"6. Back";
		cout<<endl<<"2. Refrigerator";
		cout<<endl<<"3. Vacuum Cleaner";
		cout<<endl<<"4. Washing Machine";
		cout<<endl<<"5. Water Purifier";
		gotoxy(30, 7);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "MW");
			int k, cursor = 10;
			animate();
			c4:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"MICROWAVE";
			cout<<endl<<"---------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c4;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "REF");
			int k, cursor = 10;
			animate();
			c4a:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"REFRIGERATOR";
			cout<<endl<<"------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
				else
					strcpy(fit[2], "");
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4a;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c4a;
			}
		}
		else if(choice2 == 1)
		{
			strcpy(fit[1], "VC");
			int k, cursor = 10;
			animate();
			c4b:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"VACUUM CLEANER";
			cout<<endl<<"--------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4b;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c4b;
			}
		}
		else if(choice2 == 4)
		{
			strcpy(fit[1], "WM");
			int k, cursor = 10;
			animate();
			c4c:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"WASHING MACHINE";
			cout<<endl<<"---------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4c;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c4c;
			}
		}
		else if(choice2 == 5)
		{
			strcpy(fit[1], "WP");
			int k, cursor = 10;
			animate();
			c4d:
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			cout<<endl<<endl;
			cout<<endl<<"WATER PURIFIER";
			cout<<endl<<"--------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(47)<<"ANIMART - @HOME"<<setw(33)<<cur;
			cout<<setw(47)<<"---------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1c;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c4d;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c4d;
			}
		}
		else if(choice2 == 6)
		{
			animate();
			goto buy;
		}
		else
		{
			animate();
			cout<<"Invalid choice...\n";
			goto c1c;
		}
	}
	else if(choice == 'd')
	{
		strcpy(fit[0], "emnt");
		animate();
		c1d:
		cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
		cout<<setw(51)<<"-----------------------";
		cout<<endl<<endl;
		cout<<"What Would You Like To Sell : ";
		cout<<endl<<"1. Games"<<setw(67)<<"4. Back";
		cout<<endl<<"2. Movies";
		cout<<endl<<"3. Music Players";
		gotoxy(30, 5);
		cin>>choice2;
		if(choice2 == 1)
		{
			strcpy(fit[1], "GAM");
			int k, cursor = 10;
			animate();
			c5:
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			cout<<endl<<endl;
			cout<<endl<<"GAMES";
			cout<<endl<<"-----\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1d;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c5;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c5;
			}
		}
		else if(choice2 == 2)
		{
			strcpy(fit[1], "MOV");
			int k, cursor = 10;
			animate();
			c5a:
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			cout<<endl<<endl;
			cout<<endl<<"MOVIES";
			cout<<endl<<"------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1d;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c5a;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c5a;
			}
		}
		else if(choice2 == 3)
		{
			strcpy(fit[1], "MP");
			int k, cursor = 10;
			animate();
			c5b:
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			cout<<endl<<endl;
			cout<<endl<<"MUSIC PLAYERS";
			cout<<endl<<"-------------\n\n";
			char fipath[50];
			strcpy(fipath, "c:\\animart");
			for(int i=0; i<2; i++)
			{
				strcat(fipath, "\\");
				strcat(fipath, fit[i]);
			}
			strcat(fipath, ".dat");
			ifstream fin(fipath);
			ind = 0;
			while(fin.read((char *)&I1, sizeof(I1)))
			{
				I2[ind] = I1;
				cout<<ind+1<<"."<<I2[ind].itnm<<endl;
				ind++;
			}
			fin.close();
			k = ind+1;
			gotoxy(69, cursor);
			cout<<k<<") Back";
			gotoxy(1, k+10);
			cout<<"Enter Your Choice : ";
			cin>>choice3;
			animate();
			cout<<setw(51)<<"ANIMART - ENTERTAINMENT"<<setw(29)<<cur;
			cout<<setw(51)<<"-----------------------";
			if(choice3 <= k)
			{
				if(choice3 <= k-1)
					strcpy(fit[2], I2[choice3 - 1].itcat[2]);
				else if(choice3 == k)
				{
					animate();
					goto c1d;
				}
			}
			else
			{
				animate();
				cout<<"Invalid Choice...\n";
				cursor = 11;
				goto c5b;
			}
			z = I.itbuy(B, cur, fit[0], fit[1], fit[2], "", 3);
			if(z==0)
				pointer = 0;
			else if(z == 1)
				pointer = 1;
			else
			{
				animate();
				goto c5b;
			}
		}
		else if(choice2 == 4)
		{
			animate();
			goto buy;
		}
		else
		{
			animate();
			cout<<"Invalid choice...\n";
			goto c1d;
		}
	}
	else
	{
		animate();
		cout<<"Invalid choice...";
		gotoxy(1,3);
		goto buy;
	}
	return pointer;
}

void homepage()
{
	textbackground(0);
	textcolor(9);
	clrscr();
	cout<<"    __              "<<endl;
	cout<<" / /  \\ \\  _____    ___  _______  ____       ____     __      _____    _______"<<endl;
	cout<<"| |    | | | |\\ \\   | | |__   __| | \\ \\     / / |  / /  \\ \\  | |  \\ \\ |__   __|"<<endl;
	cout<<"| |----| | | | \\ \\  | |    | |    | |\\ \\   / /| | | |    | | | |  / /    | |"<<endl;
	cout<<"| |----| | | |  \\ \\ | |    | |    | | \\ \\ / / | | | |----| | | |/ /      | |"<<endl;
	cout<<"| |    | | | |   \\ \\| |    | |    | |  -----  | | | |----| | | |\\ \\      | |"<<endl;
	cout<<"| |    | | | |    \\ | |  __| |__  | |   ---   | | | |    | | | | \\ \\     | |"<<endl;
	cout<<"|_|    |_| |_|     \\__| |_______| |_|         |_| |_|    |_| |_|  \\_\\    |_|"<<endl<<endl;
	gotoxy(72, 9);
	cout<<"Anithing.";
	delay(1000);
	gotoxy(63, 9);
	cout<<"Anithing. Anitime.";
	delay(1000);
	for(int i=0; i<53; i++)
	{
		gotoxy(53-i, 9);
		cout<<"Anithing. Anitime. Aniwhere.";
		if(i==0)
			delay(900);
		if(i!=0)
			cout<<" ";
		gotoxy(80-i, 9);
		delay(100);
	}
	delay(500);
	//load();
}

int ext(Budge &B)
{
	animate();
	int p = 0;
	char c;
	ex:
	gotoxy(1, 11);
	cout<<setw(58)<<"Are you sure you want to exit (y/n)? ";
	cin>>c;
	if((c=='y') || (c=='Y'))
	{
			animate();
			gotoxy(35,8);
			ofstream fou("c:\\animart\\budget.dat");
			fou.write((char *)&B, sizeof(B));
			cout<<"EXITING..!!";
		//	load();
			p = 1;
	}
	else if((c=='n') || (c=='N'))
	{
		p = 0;
	}
	else
	{
		animate();
		cout<<"\n\n\n"<<setw(55)<<"Invalid choice!!!"<<"\n"<<setw(46)<<"Try again!!!"<<"\n";
		goto ex;
	}
	return p;
}

void Anima(Budge &B, char cur[], char s = 'u')
{
	int i=0, c, cb1, cb2[5], cbe[7], cst, csca, smAC;
	char buying;
	animate();
	start:
	if(s=='u')
	{
		ifstream fin("c:\\animart\\users.dat");
		User us;
		cout<<setw(6);
		for(i=1; i<=70; i++)
		{
			cout<<"*";
		}
		for(i=1; i<=11; i++)
		{
			cout<<endl;
			if(i==4)
				cout<<setw(6)<<"*"<<setw(35)<<"1.BUY"<<setw(34)<<"*";
			else if(i==5)
				cout<<setw(6)<<"*"<<setw(36)<<"2.SELL"<<setw(33)<<"*";
			else if(i==6)
				cout<<setw(6)<<"*"<<setw(39)<<"3.BALANCE"<<setw(30)<<"*";
			else if(i==7)
				cout<<setw(6)<<"*"<<setw(36)<<"4.EXIT"<<setw(33)<<"*";
			else if(i==8)
				cout<<setw(6)<<"*"<<setw(38)<<"5.LOGOUT"<<setw(31)<<"*";
			else if(i==9)
				cout<<setw(6)<<"*"<<setw(43)<<"6.DELETE ACC."<<setw(26)<<"*";
			else
				cout<<setw(6)<<"*"<<setw(69)<<"*";
		}
		cout<<endl<<setw(6);
		for(i=1; i<=70; i++)
		{
			cout<<"*";
		}
		cout<<endl<<endl<<setw(50)<<"Enter your choice: ";
		cin>>c;
		ofstream fo("c:\\animart\\budget.dat");
		switch(c)
		{
			case 1: animate();
							if(buy(cur, B)==0)
								break;
							animate();
							goto start;

			case 2: animate();
							if(sell(cur, B)==0)
								break;
							animate();
							goto start;

			case 3: animate();
							while(fin.read((char*)&us, sizeof(us)))
							{
								gotoxy(1, 21);
								if(us.ch_nm(cur))
								cout<<setw(45)<<"Balance: Rs. "<<us.balance<<"\n\n";
							}
							cout<<setw(55)<<"Press any key to continue...";
							getch();
							animate();
							goto start;

			case 4: if(ext(B))
							exit(0);
							animate();
							goto start;

			case 5: animate();
							gotoxy(1, 11);
							char c;
							lout:
							cout<<setw(58)<<"Are you sure you want to logout (y/n)? ";
							cin>>c;
							if((c=='y') || (c=='Y'))
							{
								fo.write((char *)&B, sizeof(B));
								animate();
								look();
							}
							else if((c=='n') || (c=='N'))
							{
								goto start;
							}
							else
							{
								animate();
								cout<<"\n\n\n"<<setw(55)<<"Invalid choice!!!"<<"\n"<<setw(46)<<"Try again!!!"<<"\n";
								goto lout;
							}

			case 6: if(del(members, cur) == 1)
								break;
							animate();
							goto start;

			default:animate();
							cout<<setw(48)<<"Invalid Choice!!!"<<endl;
							cout<<setw(46)<<"Choose again"<<endl;
							cout<<setw(46)<<"------------"<<endl<<endl;
							goto start;
		}
	}
	else
	{
		ifstream fin("c:\\animart\\admin.dat");
		Admin A;
		cout<<setw(6);
		for(i=1; i<=70; i++)
		{
			cout<<"*";
		}
		for(i=1; i<=11; i++)
		{
			cout<<endl;
			if(i==4)
				cout<<setw(6)<<"*"<<setw(44)<<"1.USER OPTIONS"<<setw(25)<<"*";
			else if(i==5)
				cout<<setw(6)<<"*"<<setw(42)<<"2.VIEW STOCK"<<setw(27)<<"*";
			else if(i==6)
				cout<<setw(6)<<"*"<<setw(38)<<"3.BUDGET"<<setw(31)<<"*";
			else if(i==7)
				cout<<setw(6)<<"*"<<setw(38)<<"4.LOGOUT"<<setw(31)<<"*";
			else if(i==8)
				cout<<setw(6)<<"*"<<setw(36)<<"5.EXIT"<<setw(33)<<"*";
			else
				cout<<setw(6)<<"*"<<setw(69)<<"*";
		}
		cout<<endl<<setw(6);
		for(i=1; i<=70; i++)
		{
			cout<<"*";
		}
		cout<<endl<<endl<<setw(50)<<"Enter your choice: ";
		cin>>c;
		ofstream fo("c:\\animart\\budget.dat", ios::app);
		switch(c)
		{
			case 1: animate();
							if(use()==0)
								break;
							animate();
							goto start;

			case 2: animate();
							if(stock()==0)
								break;
							animate();
							goto start;

			case 3: animate();
							gotoxy(1, 21);
							cout<<setw(45)<<"Budget: Rs. "<<B.budget<<"\n\n";
							cout<<setw(53)<<"Press any key to continue...";
							getch();
							animate();
							goto start;

			case 4: animate();
							gotoxy(1, 11);
							char c;
							lout1:
							cout<<setw(58)<<"Are you sure you want to logout (y/n)? ";
							cin>>c;
							if((c=='y') || (c=='Y'))
							{
								fo.write((char *)&B, sizeof(B));
								animate();
								look();
							}
							else if((c=='n') || (c=='N'))
							{
								goto start;
							}
							else
							{
								animate();
								cout<<"\n\n\n"<<setw(55)<<"Invalid choice!!!"<<"\n"<<setw(46)<<"Try again!!!"<<"\n";
								goto lout1;
							}

			case 5: if(ext(B))
							exit(0);
							animate();
							goto start;

			default:animate();
							cout<<setw(48)<<"Invalid Choice!!!"<<endl;
							cout<<setw(46)<<"Choose again"<<endl;
							cout<<setw(46)<<"------------"<<endl<<endl;
							goto start;
		}
	}
}


void signin(int &members, Budge &B)
{

	animate();
	int t=0, i;
	i=members;
	cout<<endl<<endl<<endl<<endl<<setw(61)<<"Please login using your ANIMART account!!";
	login:
	gotoxy(1,19);
	cout<<"To Cancel: Press \'esc\' while entering password...";
	gotoxy(31,11);
	cout<<"Username:";
	gets(usert);
	cout<<setw(39)<<"Password:";
	stringinit(passw, 50);
	if(fieldEntry(passw, 40, 12, passn, 'p', sizeof(passw)))
	{
		if((strcmp(usert, "admin")==0) && (strcmp(passw, "admin")==0))
		{
			Anima(B, usert, 'a');
		}
		else
		{
			ifstream fin("c:\\animart\\users.dat");
			User u;
			int marker = -1, m=0;
			while(fin.read((char *)&u, sizeof(u)))
			{
				int z = u.ch_val(usert, passw);
					if(z == 1)
				{
					marker = m;
					break;
				}
				m++;
			}
			if(marker!=-1)
			{
				animate();
				gotoxy(33, 11);
				//int l = strlen(usert), w;
				//w = 40 + (8+(l+1))/2;
				cout<<"WELCOME "<<usert;
				delay(500);
				Anima(B, usert);
			}
			else
			{
				animate();
				t++;
				if(t<3)
				{
					cout<<"\n\n\n\n"<<setw(55)<<"Invalid username or password!!!"<<endl<<setw(45)<<"Try again.\n"<<setw(37)<<"You have "<<(3-t)<<" chances left"<<"\n\n";
					goto login;
				}
				else
				{
					for(int i=5; i>0; i--)
					{
						animate();
						cout<<setw(5)<<"Error... You will be redirected to the homepage in "<<i<<" seconds...";
						delay(1000);
					}
				}
			}
		}
	}
	else
	{}
}


void signup(int &members, Budge &B)
{
	animate();
	cout<<setw(48)<<"Sign up for Animart"<<endl;
	cout<<setw(48)<<"-------------------"<<endl<<endl;
	sup:
	if(u[ind].read())
	{
		animate();
		gotoxy(35,8);
		cout<<"VALIDATNG..!!"<<endl;
		//load();
		int t=0, v = u[ind].ver();
		if(v == 1)
		{
			int i, flag=0;
			if(members!=0)
			{
				ifstream fin("c:\\animart\\users.dat");
				while(fin.read((char *)&usr, sizeof(usr)))
				{
					if(usr.check(u[ind])==1)
					{
						flag = 1;
						t++;
						break;
					}
				}
				fin.close();
				Admin A;
				fin.open("c:\\animart\\admin.dat");
				while(fin.read((char *)&A, sizeof(A)))
				{
					if(A.check(u[ind])==1)
					{
						flag = 1;
						t++;
						break;
					}
				}
				if(flag == 1)
				{
					if(t<3)
					{
						animate();
						cout<<"\n\n\n"<<setw(57)<<"Sorry... Username already taken..."<<"\n"<<setw(48)<<"Try another name."<<"\n";
						getch();
						goto sup;
					}
					for(int i=5; i>0; i--)
					{
						animate();
						cout<<setw(5)<<"Error... You will be redirected to the homepage in "<<i<<" seconds...";
						delay(1000);
						flag = 0;
					}
				}
			}
			animate();
			gotoxy(1, 11);
			//load();
			B.budget += u[ind].balance;
			ofstream fou("c:\\animart\\budget.dat");
			fou.write((char *)&B, sizeof(B));
			cout<<setw(58)<<"You Have Successfully Joined Us..."<<endl;
			cout<<setw(54)<<"Press any key to continue...";
			ofstream fo("c:\\animart\\users.dat", ios::app);
			fo.write((char *)&u[ind], sizeof(u[ind]));
			ind++;
			members++;
			getch();
		}
		else
		{
			t++;
			if(t<3)
			{
				animate();
				cout<<"\n\n\n"<<setw(52)<<"Passwords do not match..."<<"\n"<<setw(46)<<"Try again..."<<"\n";
				getch();
				goto sup;
			}
			else
			{
				for(int i=5; i>0; i--)
				{
					animate();
					cout<<setw(5)<<"Error... You will be redirected to the homepage in "<<i<<" seconds...";
					delay(1000);
				}
			}
		}
	}
	else{}
}

int del(int &members, char cur[])
{
	char usrnm[30], pss[30];
	int detect = 1, pointer;
	User us;
	animate();
	cout<<"Enter Username:";
	gets(usrnm);
	int flag=0, tab = 0, f=0, cursor = 4;
	ifstream f3("c:\\animart\\users.dat");
	ofstream f4("c:\\animart\\newusers.dat");
	if(strcmp(cur, usrnm)==0)
	{
		while(f3.read((char *)&us, sizeof(us)))
		{
			flag = 0;
			if(us.ch_nm(usrnm) == 1)
			{
				verif:
				cout<<"Enter Password:";
				stringinit(pss, 50);
				if(fieldEntry(pss, 16, cursor, passn, 'p', sizeof(pss)));
				else
				{
					detect = 0;
					break;
				}
				if(detect)
				{
					if(us.ch_val(usrnm, pss) == -1)
					{
						if(tab<3)
						{
							tab++;
							animate();
							cout<<"\n\n"<<setw(52)<<"Passwords do not match..."<<"\n"<<setw(46)<<"Try again..."<<"\n"<<setw(37)<<"You have "<<(3-tab)<<" chances left"<<endl<<endl;
							cursor = 9;
							goto verif;
						}
						else
						{
							for(int i=5; i>0; i--)
							{
								animate();
								cout<<setw(5)<<"Error... You will be redirected back in "<<i<<" seconds...";
								delay(1000);
								flag = 0;
							}
						}
					}
					else
					{
						char dec;
						de1:
						cout<<"\n\nIf you delete your account, your money will not be refunded...\n";
						cout<<"\nContinue to delete this account(y/n)? ";
						cin>>dec;
						if((dec=='n') || (dec=='N'))
							flag = 2;
						else if((dec == 'y') || (dec == 'Y'))
							flag = 1;
						else
						{
							animate();
							cout<<"\n\n\n"<<setw(55)<<"Invalid choice!!!"<<"\n";
							goto de1;
						}
						f = flag;
					}
				}
			}
			if(flag!=1)
				f4.write((char *)&us, sizeof(us));
		}
		f3.close();
		f4.close();
		remove("c:\\animart\\users.dat");
		rename("c:\\animart\\newusers.dat", "c:\\animart\\users.dat");
		if(detect)
		{
			if(f==0)
			{
				for(int j=5; j>0; j--)
				{
					animate();
					cout<<setw(55)<<"Invalid Username or Password..."<<endl;
					redirect(j);
					pointer = 1;
				}
			}
			else if(f==1)
			{
				for(int j=5; j>0; j--)
				{
					members--;
					animate();
					cout<<setw(58)<<"Account successfully deleted..."<<endl;
					cout<<setw(62)<<"We're sorry to have dissapointed you..."<<endl;
					redirect(j);
					pointer = 1;
				}
			}
			else
			{
				for(int j=5; j>0; j--)
				{
					animate();
					cout<<setw(54)<<"Account not deleted..."<<endl;
					redirect(j);
					pointer = 0;
				}
			}
		}
	}
	else
	{
		for(int j=5; j>0; j--)
		{
			animate();
			cout<<setw(49)<<"Invalid Username..."<<endl<<endl;
			cout<<setw(47)<<"Logging Out and"<<endl;
			redirect(j);
			pointer = 1;
		}
	}
	return pointer;
}
void look()
{
	Budge B1;
	textbackground(2);  //Green Background
	textcolor(63);      //White Text
	ofstream f1("c:\\animart\\users.dat", ios::app);
	f1.close();
	ifstream f2("c:\\animart\\users.dat");
	while(f2.read((char *)&usr, sizeof(usr)))
	{
		members++;
	}
	f2.close();
	f2.open("c:\\animart\\budget.dat");
	while(f2.read((char *)&B1, sizeof(B1)))
		B.budget = B1.budget;
	second:
	animate();
	int main_ch;
	cout<<setw(51)<<"Welcome to ANIMART..!!"<<endl<<setw(53)<<"Anithing.Anitime.Aniwhere."<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<setw(42)<<"1.Sign In"<<endl;
	cout<<setw(42)<<"2.Sign Up"<<endl;
	cout<<setw(39)<<"3.Exit"<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<setw(52)<<"Please Enter your choice:";
	cin>>main_ch;
	switch (main_ch)
	{
		case 1: signin(members, B);
						goto second;

		case 2: signup(members, B);
						goto second;

		case 3: 			if(ext(B))
							exit(0);
						goto second;

		default:cout<<"\n\n\n"<<setw(55)<<"Invalid choice!!!"<<"\n";
						for(int i=5; i>0; i--)
						{
							cout<<setw(47)<<"Redirecting in "<<i<<" seconds...";
							delay(1000);
						}
						goto second;
	}
}
void main()
{
	//homepage();
	look();
}
int use()
{
	animate();
	here:
	int c, point = 1, cursor = 5;
	User u1, u2[30];
	char us[30];
	ifstream fin("c:\\animart\\users.dat");
	cout<<setw(6);
	for(int i=1; i<=70; i++)
	{
		cout<<"*";
	}
	for(i=1; i<=11; i++)
	{
		cout<<endl;
		if(i==5)
			cout<<setw(6)<<"*"<<setw(42)<<"1.LIST USERS"<<setw(27)<<"*";
		else if(i==6)
			cout<<setw(6)<<"*"<<setw(43)<<"2.DELETE USER"<<setw(26)<<"*";
		else if(i==7)
			cout<<setw(6)<<"*"<<setw(36)<<"3.BACK"<<setw(33)<<"*";
	}
	cout<<endl<<setw(6);
	for(i=1; i<=70; i++)
	{
		cout<<"*";
	}
	cout<<endl<<endl<<setw(50)<<"Enter your choice: ";
	cin>>c;
	if(c==1)
	{
		animate();
		again:
		cout<<"User Names\n";
		cout<<"----------\n";
		int ind = 0, choice;
		while(fin.read((char *)&u1, sizeof(u1)))
		{
			u2[ind] = u1;
			if(ind%11==0)
				gotoxy(41, 8);
			cout<<ind+1<<"."<<u2[ind].nm()<<endl;
			ind++;
		}
		fin.close();
		int k = ind+1;
		gotoxy(69, cursor);
		cout<<k<<") Back";
		gotoxy(1, k+10);
		cout<<"Select appropriate number to see details : ";
		cin>>choice;
		animate();
		if(choice <= k)
		{
			if(choice <= k-1)
			{
				gotoxy(30, 10);
				u2[choice - 1].disp();
				cout<<"\nPress any key to go back...";
				getch();
				animate();
				goto again;
			}
			else if(choice == k)
			{
				animate();
				goto here;
			}
		}
		else
		{
			animate();
			cout<<"Invalid Choice...\n";
			cursor = 6;
			goto again;
		}
	}
	else if(c==2)
	{
		cout<<"Enter Name of User to be deleted: ";
		gets(us);
		ofstream fout("c:\\animart\\newusers.dat");
		int flag = 1, mark = 0, f = 1;
		while(fin.read((char *)&u1, sizeof(u1)))
		{
			flag = 1;
			if(u1.ch_nm(us))
			{
				mark = 1;
				animate();
				cout<<"Enter your Username: ";
				gets(us);
				if(strcmp(us, "admin") == 0)
				{
					cout<<"Enter Password: ";
					stringinit(passw, 50);
					int detect = fieldEntry(passw, 17, 4, passn, 'p', sizeof(passw));
					if((detect) && (strcmp(passw, "admin")))
					{
						animate();
						yn:
						char s;
						cout<<"Are you sure you want to delete this user (y/n)? ";
						cin>>s;
						if((s == 'y') || (s == 'Y'))
						{
							flag = 0;
							f = 0;
						}
						else if((s == 'n') || (s == 'N'));
						else
						{
							animate();
							cout<<"Invalid Choice!!!";
							goto yn;
						}
					}
					else
					{
						for(int i=1; i<5; i++)
						{
							animate();
							cout<<"Invalid password!!!";
							redirect(i);
						}
						look();
					}
				}
				else
				{
					for(int i=1; i<5; i++)
					{
						animate();
						cout<<"Invalid username!!!";
						redirect(i);
					}
					look();
				}
			}
			if(flag)
				fout.write((char *)&u1, sizeof(u1));
		}
		remove("c:\\animart\\users.dat");
		rename("c:\\animart\\newusers.dat", "c:\\animart\\users.dat");
		if((mark))
		{
			gotoxy(30, 10);
			if(f == 0)
				cout<<"User successfully deleted!!!\n\n";
			else
				cout<<"User not deleted!!!\n\n";
		}
		else if(mark == 0)
		{
			gotoxy(30, 10);
			cout<<"No such user exists!!!\n\n";
		}
		cout<<setw(57)<<"Press any key to continue...";
		getch();
		animate();
		goto here;
	}
	else if(c==3)
		point = 1;
	else
	{
		animate();
		cout<<setw(32)<<"Invalid Choice!!!\n";
		cout<<setw(45)<<"Enter Again!!!\n";
		goto here;
	}
	return point;
}
/*int stock()
{
} */