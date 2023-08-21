#include<iostream>
#include<stdio.h>
#include<string.h>
#include<windows.h>
using namespace std;
#include "header.cpp"
void printMenu(void){
	cout<<"\n-------------------------------------------------------------";
	cout<<"\n1.Insert";
	cout<<"\n2.Update";
	cout<<"\n3.Append";
	cout<<"\n4.Delete";
	cout<<"\n5.Undo";
	cout<<"\n6.Redo";
	cout<<"\n7.Show Data";
	cout<<"\n8.Save";
	cout<<"\n9.Exit";
	cout<<"\n--------------------------------------------------------------";
}
void input(int &c){
	cout<<"\nEnter Choice(1-9):";
	cin>>c;
	fflush(stdin);
}
void inputline(int &c){
	cout<<"\nEnter line number:";
	cin>>c;
	fflush(stdin);
}
void input1(char *str){
	cout<<"Enter String:";
	gets(str);
	fflush(stdin);
}
void input2(char *str,int &line){
	cout<<"\nEnter Row Number:";
	cin>>line;
	fflush(stdin);
	cout<<"Enter String:";
	gets(str);
}
int main(){
	char str[100];
	int line;
	int choice;
	while(true){
	  system("pause");
	  system("cls");
	  printMenu();
	  input(choice);
	  switch(choice){
	  	case 1:
	  		input1(str);
	  		insert(str);
	  		break;
	  	case 2:
	  		input2(str,line);
	  		update(line,str);
	  		break;
	  	case 3:
	  		input2(str,line);
	  		append(str,line);
	  		break;
	  	case 4:
	  		inputline(line);
	  		_delete(line);
	  		break;
	  	case 5:
	  		_undo();
	  		break;
	  	case 6:
	  		_redo();
	  		break;
	  	case 7:
	  		display();
	  		break;
	  	case 8:
	  		cout<<"Enter File Name:";
	  		gets(str);
	  		fflush(stdin);
	  		save(str);
	  		break;
	  	case 9:
	  		cout<<"\nBYE";
	  		return 1; 
		default:
	  		cout<<"\nEnter vailid choice(1-9)\n";
	  }	
	}
}