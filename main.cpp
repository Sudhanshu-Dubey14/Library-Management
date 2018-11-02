//****************************************************************************************************//
//HEADER FILES USED IN PROJECT
//****************************************************************************************************//

#include<fstream>
#include "conio.h"
#include<stdio.h>
//#include<process.h>
//tried using stdlib.h instead of process.h :suraj
//#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<iostream>

using namespace std;

//****************************************************************************************************//
//CLASSES USED IN PROJECT
//****************************************************************************************************//

class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	 {
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nEnter The book no.";
		cin>>bno;
		cout<<"\n\nEnter The Name of The Book ";
		cin>>bname;
		cout<<"\n\nEnter The Author's Name ";
		cin>>aname;
		cout<<"\n\n\nBook Created..";
	 }
	void show_book()
	 {
		cout<<"\nBook no. : ";
		cout<<bno;
		cout<<"\nBook Name : ";
		puts(bname);
		cout<<"Author Name : ";
		puts(aname);
	 }

	void modify_book()
	 {
	 	cout<<"\nBook no. : "<<bno;
		cout<<"\nModify Book Name : ";
		cin>>bname;
		cout<<"\nModify Author's Name of Book:";
		cin>>aname;
	 }
      char* retbno()
	 {
		return bno;
	 }
      void report()
	 {
	  cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	 }


};                               //CLASS BOOK ENDS HERE

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
  public:
	void create_student()
	 {
		cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter The admission no. ";
		cin>>admno;
		cout<<"\n\nEnter The Name of the student";
		cin>>name;
		token=0;
		stbno[0]='\0';
		cout<<"\n\nStudent Record Created..";
	 }
      void show_student()
	 {
		cout<<"\nAdmission no. : ";
		cout<<admno;
		cout<<"\nStudent Name : ";
		puts(name);
		cout<<"\nNo of Book issued : "<<token;
		if(token==1)
		{
			cout<<"\nBook No "<<stbno;
		}
	 }
      void modify_student()
	 {
	 	cout<<"\nAdmission no. : "<<admno;
		cout<<"\nModify Student Name : ";
		cin>>name;
	 }
      char* retadmno()
	 {
		return admno;
	 }
      char* retstbno()
	 {
		return stbno;
	 }
      int rettoken()
	 {
		return token;
	 }
      void addtoken()
	 {
		token=1;
	 }
      void resettoken()
	 {
		token=0;
	 }
      void getstbno(char t[])
	 {
		strcpy(stbno,t);
	 }
      void report()
	 {
       cout<<"\t"<<admno<<setw(20)<<name<<setw(10);
      cout<<token<<endl;
  }

};           				//CLASS STUDENT ENDS HERE

//**********************************************************//
//GLOBAL DECLARATION FOR STREAM OBJECT
//**********************************************************//

fstream fp,fp1;
book bk;
student st;

//**********************************************************//
//FUNCTIONS TO WRITE IN FILE
//**********************************************************//

void write_book()
 {
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	 {
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	 } while(ch=='y'||ch=='Y');
	fp.close();
 }
void write_student()
 {
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	} while(ch=='y'||ch=='Y');
	fp.close();
 }

//**********************************************************//
//FUNCTION TO READ SPECIFIC RECORD FROM FILE
//**********************************************************//

void display_spb(char n[])
 {
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	 {
		if(strcmp(bk.retbno(),n)==0)
		 {
			bk.show_book();
			flag=1;
		}
	 }
	fp.close();
	if(flag==0)
	 {
		cout<<"\n\nBook does not exist";
	 }
	cin.get();
 }
void display_sps(char n[])
 {
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	 {
		if((strcmp(st.retadmno(),n)==0))
		 {
			st.show_student();
			flag=1;
		 }
	 }
	fp.close();
	if(flag==0)
	 {
		cout<<"\n\nStudent does not exist";
	 }
	cin.get();
 }

//*****************************************************//
//FUNCTION TO MODIFY RECORD OF FILE
//*****************************************************//

void modify_book()
 {
	char n[6];
	int found=0;
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	 {
		if(strcmp(bk.retbno(),n)==0)
		 {
			bk.show_book();
cout<<"\nEnter The New Details of book";   cout<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
      fp.close();
	if(found==0)
	 {
		cout<<"\n\n Record Not Found ";
	 }
	cin.get();
 }

void modify_student()
 {
	char n[6];
	int found=0;
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	 {
		if(strcmp(st.retadmno(),n)==0)
		 {
			st.show_student();
		      cout<<"\nEnter The New Details of  student";
			cout<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
		      fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		 }
	 }
	fp.close();
	if(found==0)
	 {
		cout<<"\n\n Record Not Found ";
	 }
	cin.get();
 }



//********************************************************//
//FUNCTION TO DELETE RECORD OF FILE
//********************************************************//

void delete_student()
 {
	char n[6];
	int flag=0;
	cout<<"\n\n\n\tDELETE STUDENT...";
cout<<"\n\nEnter The admission no. of the Student you";
cout<<"want To Delete : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	 {
		if(strcmp(st.retadmno(),n)!=0)
		 {
			fp2.write((char*)&st,sizeof(student));
		 }
		else
		 {
			flag=1;
		 }
	 }
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
	 {
		cout<<"\n\n\tRecord Deleted ..";
	 }
	else
	 {
		cout<<"\n\nRecord not found";
	 }
	cin.get();
 }
void delete_book()
 {
	char n[6];
//	clrscr();
	cout<<"\n\n\n\tDELETE BOOK ...";
cout<<"\n\nEnter The Book no. of the Book You Want To ";        cout<<"Delete: ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)& bk,sizeof(book)))
	 {
		if(strcmp(bk.retbno(),n)!= 0)
		 {
			fp2.write((char*)&bk,sizeof(book));
	 	 }
	 }
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.get();
 }
//********************************************************//
//FUNCTION TO DISPLAY ALL STUDENTS LIST
//********************************************************//

void display_alls()
 {
// 	clrscr();
	fp.open("student.dat",ios::in);
	if(!fp)
	 {
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		cin.get();
		return;
	 }
      cout<<"\n\n\t\tSTUDENT LIST\n\n";
cout<<"##############################################\n";
	cout<<"\tAdmissionNo.";
	cout<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"##############################################\n";
	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}
	fp.close();
	cin.get();
}
//**********************************************************//
//FUNCTION TO DISPLAY BOOKS LIST
//**********************************************************//

void display_allb()
 {
//	clrscr();
	fp.open("book.dat",ios::in);
	if(!fp)
	 {
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		cin.get();
		return;
	 }
	cout<<"\n\n\t\tBook LIST\n\n";
	cout<<"##############################################\n";
	cout<<"BookNumber"<<setw(20)<<"BookName"<<setw(25);
	cout<<"Author\n";
	cout<<"##############################################\n";
	while(fp.read((char*)&bk,sizeof(book)))
	 {
		bk.report();
	 }
	fp.close();
	cin.get();
 }



//********************************************************//
//FUNCTION TO ISSUE BOOK
//********************************************************//

void book_issue()
 {
	char sn[6],bn[6];
	int found=0,flag=0;
//	clrscr();
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's admission no.";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student))&& found==0)
	 {
	   if(strcmp(st.retadmno(),sn)==0)
	    {
	      found=1;
	      if(st.rettoken()==0)
	       {
		   cout<<"\n\n\tEnter the book no. ";
		   cin>>bn;
		   while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
		    {
			    if(strcmp(bk.retbno(),bn)==0)
			     {
			        bk.show_book();
			        flag=1;
			        st.addtoken();
			        st.getstbno(bk.retbno());
			        int pos=-1*sizeof(st);
			        fp.seekp(pos,ios::cur);
                         fp.write((char*)&st,sizeof(student));
  cout<<"\n\n\t Book issued successfully";
  cout<<"\n\nPlease Note: Write current";
  cout<<"date in backside of book and";
  cout<<"submit within 15 days\n.";
  cout<<"Fine of Rs.1 for each day will be";
   cout<<"taken after 15 days period";
			     }
		     }
		    if(flag==0)
		    {	   cout<<"Book no. does not exist";    }
	     }
	    else
	    {
		  cout<<"You have not returned the last book.";
	        cout<<" Book can be issued only after returning the";
        cout<<"previous one.";
    }
       }
     if(found==0)
      {    cout<<"Student record not exist...";   }
     cin.get();
     fp.close();
     fp1.close();
 }}
//**********************************************************//
//FUNCTION TO DEPOSIT BOOK
//*********************************************************//

void book_deposit()
{
	char sn[6],bn[6];
	int found=0,flag=0,day,fine;
//	clrscr();
	cout<<"\n\nBOOK DEPOSIT ...";
	cout<<"\n\n\tEnter The student’s admission no.";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	 {
	  if(strcmp(st.retadmno(),sn)==0)
	   {
	   found=1;
	   if(st.rettoken()==1)
	    {
		while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
	      {
		   if(strcmp(bk.retbno(),st.retstbno())==0)
		    {
			bk.show_book();
			flag=1;
			cout<<"\n\nBook deposited in no. of days";
			cin>>day;
			if(day>15)
			 {
				 fine=(day-15)*1;
			       cout<<"\n\nFine has to deposited Rs";
				 cout<<fine;
			 }
			st.resettoken();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
		     cout<<"\n\n\t Book deposited successfully";
		    }
	      }
	     if(flag==0)
	      {
		    cout<<"Book no does not exist";
	      }
	     else
	      {
			cout<<"No book is issued..please check!!";
	      }
	   }
        }
      }
     if(found==0)
      cout<<"Student record not exist...";
     cin.get();
     fp.close();
     fp1.close();
   }






//***************************************************************//
//INTRODUCTION FUNCTION
//***************************************************************//

void intro()
 {
//	clrscr();
//	goto xy(25,11);
	cout<<"LIBRARY MANAGEMENT SYSTEM";
	cout<<"\n\nMADE BY : $udhanshu Dubey";
	cout<<"\n\nSCHOOL : KENDRIYA VIDYALAYA No.2 AFS HALWARA";
	cin.get();
 }

//***************************************************************//
//ADMINISTRATOR MENU FUNCTION
//***************************************************************//

void admin_menu()
 {
//	clrscr();
	int ch2;
	char num[6];
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.CREATE BOOK ";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t9.MODIFY BOOK ";
	cout<<"\n\n\t10.DELETE BOOK ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-11): ";
	cin>>ch2;
	switch(ch2)
	 {
	 case 1:    //clrscr();
			write_student();
			break;

	 case 2:    display_alls();
			break;

	 case 3:    //char num[6];
			//clrscr();
			cout<<"\n\n\tPlease Enter The Admission No. ";
			cin>>num;
			display_sps(num);
			break;

	 case 4:    modify_student();
			break;

	 case 5:    delete_student();
			break;

	 case 6: 	//clrscr();
			write_book();
			break;

	 case 7:    display_allb();
			break;

	 case 8:   // char num[6];
			//clrscr();
			cout<<"\n\n\tPlease Enter The book No. ";
			cin>>num;
			display_spb(num);
			break;

	 case 9:    modify_book();
			break;

	 case 10:   delete_book();
			break;

	 case 11: 	return;
			default:
			cout<<"\a";
	 }
	admin_menu();
 }
//***************************************************************//
//THE MAIN FUNCTION OF PROGRAM
//***************************************************************//

int main()
{
	char ch;
	intro();
	do
	{
		//clrscr();
		cout<<"\n\n\n\t MAIN MENU";
		cout<<"\n\n\t01. ADMINISTRATOR MENU";
		cout<<"\n\n\t02. BOOK ISSUE";
		cout<<"\n\n\t03. BOOK DEPOSIT";
		cout<<"\n\n\t04. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-4): ";
		cin>>ch;
		switch(ch)
		 {
			case '1':   //clrscr();
				 	admin_menu();
					break;
			case '2':   book_issue();
				 	break;

			case '3':   book_deposit();
				 	break;

			case '4':   return 0;

			default :   cout<<"\a";
		 }
	 } while(ch!='4');
 }

//**********************************************************//
//END OF CODE
//**********************************************************//
