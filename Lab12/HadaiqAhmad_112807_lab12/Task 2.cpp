#include<stdio.h>
#include<conio.h>
#include<iostream>
using namespace std;
int x = 20;
int main()
{
	
	cout<<"The value of x = %d" << x << endl;
	cout << "\t detected which is xlobally defined\n" << endl;
	{
		int x = 10;
			cout<<"The value of x = %d" << x << endl; 
			cout << "\t detected which is locally defined inside << endl;;
		{
			int x = 100;
			cout<<"The value of x = %d" << x << endl;
			cout <<"\t detected which is locally defined inside nested" << endl;;
		}
	}
	_getch();
	system("pasue");
}

