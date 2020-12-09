// HEADER FILES USED IN PROJECT

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

// CLASS USED IN PROJECT
class student_details
{
	int roll;
	char name[50];
	int phy, chem, math, eng, cs;
	double percent;
	char grade;
	void calculate();	//calculate() function is to calculate grade
public:
	void data();		//getdata() function is to accept data from user
	void show() const;	//showdata() function is to show data on screen
	void tabular() const;//show_tabular() function is to show tabular data
	int rerollno() const;
}; //class ends here


void student_details::calculate()
{
	percent=(phy+chem+math+eng+cs)/5.0;
	if(percent>=60)
		grade='A';
	else if(percent>=50)
		grade='B';
	else if(percent>=33)
		grade='C';
	else
		grade='F';
}

void student_details::data()
{
	cout<<"\nEnter The roll number of student ";
	cin>>roll;
	cout<<"\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in Physics out of 100 : ";
	cin>>phy;
	cout<<"\nEnter The marks in Chemistry out of 100 : ";
	cin>>chem;
	cout<<"\nEnter The marks in Maths out of 100 : ";
	cin>>math;
	cout<<"\nEnter The marks in English out of 100 : ";
	cin>>eng;
	cout<<"\nEnter The marks in Computer Science out of 100 : ";
	cin>>cs;
	calculate();
}

void student_details::show() const
{
	cout<<"\nRoll number of student : "<<roll;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<phy;
	cout<<"\nMarks in Chemistry : "<<chem;
	cout<<"\nMarks in Maths : "<<math;
	cout<<"\nMarks in English : "<<eng;
	cout<<"\nMarks in Computer Science :"<<cs;
	cout<<"\nPercentage of the student is  :"<<percent;
	cout<<"\nGrade of the student is :"<<grade;
}

void student_details::tabular() const
{
	cout<<roll<<setw(10)<<" "<<name<<setw(10)<<phy<<setw(10)<<chem<<setw(10)<<math<<setw(10)
		<<eng<<setw(10)<<cs<<setw(10)<<percent<<setw(10)<<grade<<endl;
}

int  student_details::rerollno() const
{
	return roll;
}
//    	FUNCTION FOR INTRODUCTION


void intro()
{
	cout<<"\n\n\t\t  STUDENT";
	cout<<"\n\t\tREPORT CARD";
	cout<<"\n\t\t HANDLING";
	cout<<"\n\n\t\t -PROJECT-";
	cout<<"\n\nMADE BY : AYUSHI SHRIYAL";
	cout<<"\nBRANCH : B.Tech(CSE)";
	cout<<"\nSECTION : E";
	cout<<"\nUNI. ROLL NO. : 2014615";
	cout<<"\nCLASS ROLL NO. : 22";
	cout<<"\nUNIVERSITY : GRAPHIC ERA UNIVERSITY";
	cin.get();
}


//    	Declaration of function used in the program

void write();	//write the record in binary file
void display_all();	//read all records from binary file
void display_sp(int);	//to accept rollno and read record from binary file
void modify(int);	//to accept rollno and update record of binary file
void del_student(int);	//to accept rollno and delete selected records from binary file
void class_result();	//to show all records in tabular format from binary file
void result();		//to show result menu
void intro();		//to show the first screen
void entry_menu();	//to show entry menu on screen

//    	function to write in file
void write()
{
	student_details st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.data();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student_details));
	outFile.close();
    	cout<<"\n\n The Student record has been created ";
	cin.ignore();
	cin.get();
}


//    	function to read all records from file

void display_all()
{
	student_details st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not open!! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL THE STUDENT RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_details)))
	{
		st.show();
		cout<<"\n\n----------------------------------\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


//    	function to read any specific record from file

void display_sp(int n)
{
	student_details st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not open!! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_details)))
	{
		if(st.rerollno()==n)
		{
	  		 st.show();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}


//    	function to modify record of file
void modify(int n)
{
	bool found=false;
	student_details st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not open!! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student_details));
		if(st.rerollno()==n)
		{
			st.show();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.data();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student_details));
		    	cout<<"\n\n\t Your Record after modification is Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\nThe desired  Record Not Found ";
	cin.ignore();
	cin.get();
}


//    	function to delete record of file
void del_student(int n)
{
	student_details st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not open!! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_details)))
	{
		if(st.rerollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student_details));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


//    	function to display all students grade report
void class_result()
{
	student_details st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not open!! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"---------------------------------------------------------------------------------------\n";
	cout<<"Roll No.     Name      Physics   Chemistry   Maths   English   CS   Percentage   Grade"<<endl;
	cout<<"---------------------------------------------------------------------------------------\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_details)))
	{
		st.tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}


//    	function to display result menu
void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\t 'THE RESULT MENU'";
	cout<<"\n\n\t1. See the result of particular student";
	cout<<"\n\t2. If you wish to see the result of whole class";
	cout<<"\n\t3. Back to the Main Menu";
	cout<<"\n\n\tEnter your Choice(1/2/3) ? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	cout<<"\n\n\tEnter the Roll Number Of the Student : "; cin>>rno;
				display_sp(rno); break;
	case '2' :	class_result(); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

//    	THE MAIN FUNCTION OF PROGRAM

int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program gives output of decimal number up-to two decimal places
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\t   ''THE MAIN MENU'' ";
		cout<<"\n\n\t1- THE RESULT MENU";
		cout<<"\n\t2- THE ENTRY/EDIT MENU";
		cout<<"\n\t3- EXIT";
		cout<<"\n\n\tOption(1/2/3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}
//    	ENTRY / EDIT MENU FUNCTION
void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tTHE ENTRY MENU";
	cout<<"\n\n\t1.DO YOU WANT TO CREATE A STUDENT RECORD";
	cout<<"\n\t2.DO YOU WANT TO DISPLAY ALL THE STUDENTS RECORDS";
	cout<<"\n\t3.DO YOU WANT TO MOFIFY THE STUDENT RECORD ";
	cout<<"\n\t4.DO YOU WANT TO SEARCH THE STUDENT RECORD";
	cout<<"\n\t5.DO YOU WANT TO DELETE THE STUDENT RECORD";
	cout<<"\n\t6.DO YOUNWANT TO BACK TO THE MAIN MENU";
	cout<<"\n\n\tSELECT FROM(1-6) WHAT YOU WISH TO DO ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number of the student "; cin>>num;
			modify(num);break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number of the student "; cin>>num;
			display_sp(num); break;
    case '5':	cout<<"\n\n\tPlease Enter The roll number of the student"; cin>>num;
			del_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
//End of the project

