#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include<fstream>
#include<algorithm>
#include<vector>
#include<Windows.h>
#include<list>

using namespace std;

string ch, s1, s2, s3, s4, s5, The_SSN;
string Name_Of_Ministries[] = { "Ministry of Interior", "Ministry of Electricity",
"Ministry of Health and population", "Ministry of Education" };

class Person	//Abstract class
{
public:
	string user_name, SSN_PW, name;
	Person() :user_name(""), SSN_PW(""), name(""){};
	virtual void sign_up(string s1, string s2, string s3) = 0;
	friend ostream& operator<<(ostream&, const Person&);
};
ostream& operator<<(ostream& os, const Person& P)
{
	os << "SSN: " << P.SSN_PW << "\tName: " << P.name;	return os;
}

class Citizen : public Person
{
public:
	Citizen() :Person(){};
	static int Citiz_Num;
	void sign_up(string s1, string s2, string s3)
	{
		user_name = s1;
		SSN_PW = The_SSN = s2;
		name = s3;
		Citiz_Num++;
	};
	bool sign_in(string s1, string s2)
	{
		if ((s1 == user_name&&s2 == SSN_PW))
		{
			The_SSN = SSN_PW;
			return true;
		}
		else
			return false;
	}
};
int Citizen::Citiz_Num = 0;

class Ministry
{
protected:
	string Location, Phone, Email, Minister;
public:
	static int Count_Ministry;
	static string Prime_Minister;
	Ministry() : Location(""), Phone(""), Email(""), Minister(""){};
	void Add_Min()
	{
		cout << "Enter the minister name    : "; cin >> s2; this->Minister = s2;
		cout << "Enter the ministry location: "; cin >> s3; this->Location = s3;
		cout << "Enter the ministry phone   : "; cin >> s4; this->Phone = s4;
		cout << "Enter the ministry Email   : "; cin >> s5; this->Email = s5;
		this->Count_Ministry++;
	}
	void Edit_Min()
	{
		cout << "1- The Minister Name    : " << this->Minister << endl;
		cout << "2- The Ministry Location: " << this->Location << endl;
		cout << "3- The Ministry Phone   : " << this->Phone << endl;
		cout << "4- The Ministry Email   : " << this->Email << endl;
		cout << "Enter the num of the info you want to edit: "; cin >> ch;
		if (ch == "1")
		{
			cout << "Enter the new minister name :";  cin >> s1; this->Minister = s1;
		}
		else if (ch == "2")
		{
			cout << "Enter the new ministry location :"; cin >> s2; this->Location = s2;
		}
		else if (ch == "3")
		{
			cout << "Enter the new ministry phone :"; cin >> s3; this->Phone = s3;
		}
		else if (ch == "4")
		{
			cout << "Enter the new ministry Email :"; cin >> s4; this->Email = s4;
		}
		else
		{
			cout << "Unavailable Choice\n";
			return;
		}
		cout << "The" << Name_Of_Ministries[stoi(ch) - 1] << "has been Edited.\n";
		cout << "Edit another info (y/n):"; cin >> ch;
		if (ch == "y" || ch == "Y")
		{
			system("cls");
			Edit_Min();
		}
	}
	virtual void Display_Data() = 0;
	friend void Load();
	friend void Save();
};
void Delete_Min(Ministry *&m)
{
	m = NULL;
	Ministry::Count_Ministry--;
}
int Ministry::Count_Ministry = 0;
string Ministry::Prime_Minister = "";

class SSN_Card
{
public:
	string SSN, Name, Address, Job;
	int Start_Year, Expire_Year;
};
class Min_Interior :public Ministry
{
	void Display_Data()
	{
		cout << "The Prime Minister    : " << this->Prime_Minister
			<< "\nThe Minister Name     : " << this->Minister
			<< "\nThe Ministry Location : " << this->Location
			<< "\nThe Ministry Phone    : " << this->Phone
			<< "\nThe Ministry Email    : " << this->Email << "\n";
	}
};
class Civil_Status_Dep :public Min_Interior
{
public:
	vector<SSN_Card> Cards;
	Civil_Status_Dep() :Min_Interior(){}
	//Owner
	void Add_Citizen(Citizen c)
	{
		for (unsigned i = 0; i < this->Cards.size(); i++)
		{
			if (this->Cards[i].SSN == c.SSN_PW)
			{
				cout << "A Card with this SSN is Already Exist\n"; return;
			}
		}
		this->Cards.push_back(SSN_Card());
		Cards.back().SSN = c.SSN_PW;
		Cards.back().Name = c.name;
		cout << "Citizen's SSN: " << Cards.back().SSN << "\n";
		cout << "Citizen's Name: " << Cards.back().Name << "\n";
		cout << "Enter The Current Year: "; cin >> Cards.back().Start_Year;
		cout << "Enter Citizen's Address: "; cin >> Cards.back().Address;
		cout << "Enter Job: "; cin >> Cards.back().Job;
		Cards.back().Expire_Year = Cards.back().Start_Year + 7;
		cout << "This SSN Card has been added\n";
	}
	void Remove_Citizen(string ssn)
	{
		for (unsigned i = 0; i < this->Cards.size(); i++)
		{
			if (this->Cards[i].SSN == ssn)
			{
				this->Cards.erase(this->Cards.begin() + i);	break;
			}
		}
	}
	//Citizen
	void Renew_SSN(string ssn)
	{
		for (unsigned i = 0; i < Cards.size(); i++)
		{
			if (Cards[i].SSN == ssn)
			{
				cout << "Do you want to\t1-Renew Expire Date\t2-Change your current Address\t3-Change Job\t4-View Your Data?\nEnter Choice: "; cin >> ch;
				if (ch == "1")
				{
					cout << "Enter Current Year: "; cin >> Cards[i].Start_Year; Cards[i].Expire_Year = Cards[i].Start_Year + 7; cout << "Renewed...\n";
				}
				else if (ch == "2")
				{
					cout << "Enter Your New Address: "; cin >> Cards[i].Address; cout << "Renewed...\n";
				}
				else if (ch == "3")
				{
					cout << "Enter Your Job: "; cin >> Cards[i].Job; cout << "Renewed...\n";
				}
				else if (ch == "4")
				{
					cout << "SSN: " << Cards[i].SSN << "\nName: " << Cards[i].Name << "\nAddress: "
						<< Cards[i].Address << "\nJob: " << Cards[i].Job << "\nExpire Year: " << Cards[i].Expire_Year << endl;
				}
				return;
			}
		}
		cout << "No SSN Cards With Your SSN" << endl;
	}
	friend void Load();
	friend void Save();
};

class Bills_Form
{
public:
	string SSN, Bill;
	bool Paid;
};
class Min_Electricity_And_Energy :public Ministry
{
	void Display_Data()
	{
		cout << "The Prime Minister    : " << this->Prime_Minister
			<< "\nThe Minister Name     : " << this->Minister
			<< "\nThe Ministry Location : " << this->Location
			<< "\nThe Ministry Phone    : " << this->Phone
			<< "\nThe Ministry Email    : " << this->Email << "\n";
	}
};
class Elec_Bill_Dep : public Min_Electricity_And_Energy
{
	vector<Bills_Form> Bills;
public:
	//Owner
	Elec_Bill_Dep() :Min_Electricity_And_Energy(){}
	void Add_Bill(Citizen c)
	{
		for (unsigned i = 0; i < Bills.size(); i++)
		{
			if (c.SSN_PW == Bills[i].SSN)
			{
				cout << "The Bill= " << Bills[i].Bill << "\nDo You Want to Edit it?<y/n>\nEnter Choice: "; cin >> ch;
				if (ch == "y" || ch == "Y")
				{
					cout << "Enter Bill: "; cin >> Bills[i].Bill;
					Bills[i].Paid = false;
					cout << "This Electricity Bill has been edited\n";
					return;
				}
				else
				{
					return;
				}
			}
		}
		Bills.push_back(Bills_Form());
		Bills.back().SSN = c.SSN_PW;
		cout << "Enter Bill: "; cin >> Bills.back().Bill;
		Bills.back().Paid = false;
		cout << "This Electricity Bill has been added\n";
	}
	void get_Bill(Citizen c)
	{
		for (unsigned i = 0; i < Bills.size(); i++)
		{
			if (Bills[i].SSN == c.SSN_PW)
			{
				cout << "The Bill= " << Bills[i].Bill << " LE\n";
				if (Bills[i].Paid)
				{
					cout << "Paid" << endl;
				}
				else
				{
					cout << "Not Paid" << endl;
				}
				return;
			}
		}
		cout << "No Electricity Bill for this citizen.." << endl;
	}
	//Citizen
	void Check_Bill(string ssn)
	{
		for (unsigned i = 0; i < Bills.size(); i++)
		{
			if (Bills[i].SSN == ssn)
			{
				cout << "Your Bill is =" << Bills[i].Bill << " LE\n";
				cout << "Do You Want to Pay it? <y/n>\nEnter Choice: ";  cin >> ch;
				if (ch == "Y" || ch == "y")
				if (Bills[i].Paid)
					cout << "Already Paid.." << endl;
				else
				{
					Bills[i].Paid = true;
					cout << "Your Bill is Paid Succefully..\n";
				}
				return;
			}
		}
		cout << "You have no Electricity Bill.." << endl;
	}
	friend void Load();
	friend void Save();
};

class Blood_Bank
{
public:
	string Blood_Type, Hospital_Name;
	int Quantity;
};
class Min_Health_And_Population : public Ministry
{
	void Display_Data()
	{
		cout << "The Prime Minister    : " << this->Prime_Minister
			<< "\nThe Minister Name     : " << this->Minister
			<< "\nThe Ministry Location : " << this->Location
			<< "\nThe Ministry Phone    : " << this->Phone
			<< "\nThe Ministry Email    : " << this->Email << "\n";
	}
};
class Health_Dep :public Min_Health_And_Population
{
	vector<Blood_Bank> Blood_Types;
	string B_Type;
	unsigned Check;
	unsigned Exist(string B_type)
	{
		unsigned i;
		for (i = 0; i < Blood_Types.size(); i++)
		{
			if (Blood_Types[i].Blood_Type == B_type)
			{
				return i;
			}
		}
		return i;
	}
public:
	Health_Dep() :Min_Health_And_Population(){}
	//Owner
	void Add_or_Edit_Type()
	{
		cout << "Enter the Blood Type: "; cin >> B_Type;
		Check = Exist(B_Type);
		if (Check >= 0 && Check < Blood_Types.size())
		{
			cout << "B_type Already Existed...\n Do You Want to Edit it?<Y/N>\nEnter Choice: "; cin >> ch;
			if (ch == "y" || ch == "Y")
			{
				cout << "Enter Quantity: "; cin >> Blood_Types[Check].Quantity;
				cout << "Enter Hospital Name: "; cin >> Blood_Types[Check].Hospital_Name;
			}
			else
			{
				return;
			}
		}
		else
		{
			Blood_Types.push_back(Blood_Bank());
			Blood_Types.back().Blood_Type = B_Type;
			cout << "Enter Quantity: "; cin >> Blood_Types.back().Quantity;
			cout << "Enter Hospital Name: "; cin >> Blood_Types.back().Hospital_Name;
		}
	}
	void View_The_Blood_Bank()
	{
		if (Blood_Types.size())
		{
			system("cls");
			for (unsigned i = 0; i < Blood_Types.size(); i++)
			{
				cout << "Blood Type " << Blood_Types[i].Blood_Type << " Exist With Quantity= "
					<< Blood_Types[i].Quantity << " in " << Blood_Types[i].Hospital_Name << endl;
			}
		}
		else
		{
			cout << "There's No Avaliable Blood Types in the Bank\n";
		}
	}
	//Citizen
	void Search_B_Type()
	{
		cout << "Enter the Blood Type: ";  cin >> B_Type;
		Check = Exist(B_Type);
		if (Check >= 0 && Check < Blood_Types.size())
		{
			cout << "Blood Type " << B_Type << " Exist With Quantity= "
				<< Blood_Types[Check].Quantity << " in " << Blood_Types[Check].Hospital_Name << endl;
		}
		else cout << "Blood Type is not Found...\n";
	}
	friend void Load();
	friend void Save();
};

class Exams_Form
{
public:
	string Subject, Year;
};
class Min_Education :public Ministry
{
	void Display_Data()
	{
		cout << "The Prime Minister    : " << this->Prime_Minister
			<< "\nThe Minister Name     : " << this->Minister
			<< "\nThe Ministry Location : " << this->Location
			<< "\nThe Ministry Phone    : " << this->Phone
			<< "\nThe Ministry Email    : " << this->Email << "\n";
	}
};
class Prim_Dep : public Min_Education
{
	vector<Exams_Form> Prim_Exams;
	bool Search(string x, string y)
	{
		for (unsigned i = 0; i < Prim_Exams.size(); i++)
		{
			if ((Prim_Exams[i].Subject == x) && (Prim_Exams[i].Year == y))
			{
				return true;
			}
		}
		return false;
	}
public:
	void Add_Prim_Exam()
	{
		string yeaar, subjeect;
		cout << "Enter Exams's Year: "; cin >> yeaar;
		cout << "Enter Exam's Subject: "; cin >> subjeect;
		if (!Search(yeaar, subjeect))
		{
			Prim_Exams.push_back(Exams_Form());
			Prim_Exams.back().Year = yeaar;
			Prim_Exams.back().Subject = subjeect;
			cout << "The Exam has been added..\n";
		}
		else
		{
			cout << "This Exam is Already Exist..." << endl;
		}
	}
	void View_Prim_Exam()
	{
		if (Prim_Exams.size())
		{
			for (unsigned i = 0; i < Prim_Exams.size(); i++)
			{
				cout << Prim_Exams[i].Subject << " - " << Prim_Exams[i].Year;
				if (i != 0 && i % 3 == 0)
				{
					cout << "\n";
				}
				else
				{
					cout << "\t";
				}
			}
			if (Prim_Exams.size() % 3 != 0)
			{
				cout << "\n";
			}
		}
		else
		{
			cout << "There's no avaliable question papers for the primary stage\n";
		}
	}
	friend void Load();
	friend void Save();
};
class Prep_Dep : public Min_Education
{
	vector<Exams_Form> Prep_Exams;
	bool Search(string x, string y)
	{
		for (unsigned i = 0; i < Prep_Exams.size(); i++)
		{
			if ((Prep_Exams[i].Subject == x) && (Prep_Exams[i].Year == y))
			{
				return true;
			}
		}
		return false;
	}
public:
	void Add_Prep_Exam()
	{
		string yeaar, subjeect;
		cout << "Enter Exams's Year: "; cin >> yeaar;
		cout << "Enter Exam's Subject: "; cin >> subjeect;
		if (!Search(yeaar, subjeect))
		{
			Prep_Exams.push_back(Exams_Form());
			Prep_Exams.back().Year = yeaar;
			Prep_Exams.back().Subject = subjeect;
		}
		else
		{
			cout << "This Exam is Already Exist..." << endl;
		}
	}
	void View_Prep_Exam()
	{
		if (Prep_Exams.size())
		{
			for (unsigned i = 0; i < Prep_Exams.size(); i++)
			{
				cout << Prep_Exams[i].Subject << " - " << Prep_Exams[i].Year;
				if (i != 0 && i % 3 == 0)
				{
					cout << "\n";
				}
				else
				{
					cout << "\t";
				}
			}
			if (Prep_Exams.size() % 3 != 0)
			{
				cout << "\n";
			}
		}
		else
		{
			cout << "There's no avaliable question papers for the preparatory stage\n";
		}
	}
	friend void Load();
	friend void Save();
};
class Sec_Dep : public Min_Education
{
	vector<Exams_Form> Sec_Exams;
	bool Search(string x, string y)
	{
		for (unsigned i = 0; i < Sec_Exams.size(); i++)
		{
			if ((Sec_Exams[i].Subject == x) && (Sec_Exams[i].Year == y))
			{
				return true;
			}
		}
		return false;
	}
public:
	void Add_Sec_Exam()
	{
		string yeaar, subjeect;
		cout << "Enter Exams's Year: "; cin >> yeaar;
		cout << "Enter Exam's Subject: "; cin >> subjeect;
		if (!Search(yeaar, subjeect))
		{
			Sec_Exams.push_back(Exams_Form());
			Sec_Exams.back().Year = yeaar;
			Sec_Exams.back().Subject = subjeect;
		}
		else
		{
			cout << "This Exam is Already Exist..." << endl;
		}
	}
	void View_Sec_Exam()
	{
		if (Sec_Exams.size())
		{
			for (unsigned i = 0; i < Sec_Exams.size(); i++)
			{
				cout << Sec_Exams[i].Subject << " - " << Sec_Exams[i].Year;
				if (i != 0 && i % 3 == 0)
				{
					cout << "\n";
				}
				else
				{
					cout << "\t";
				}
			}
			if (Sec_Exams.size() % 3 != 0)
			{
				cout << "\n";
			}
		}
		else
		{
			cout << "There's no avaliable question papers for the secondary stage\n";
		}
	}
	friend void Load();
	friend void Save();
};

class Owner :public Person
{
public:
	void sign_up(string s1, string s2, string s3)
	{
		user_name = s1;
		SSN_PW = s2;
		Ministry::Prime_Minister = name = s3;
	}
	bool sign_in(string s1, string s2)
	{
		if (s1 == user_name&&s2 == SSN_PW)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

Owner own;
vector <Citizen> Citiz;
Ministry *Min_List[6];

void Load()
{
	ifstream f1("users.txt", ios::in);
	f1 >> s1 >> s2 >> s3;
	own.sign_up(s1, s2, s3);
	unsigned x; f1 >> x;
	for (unsigned i = 0; i < x; i++)
	{
		Citiz.push_back(Citizen());
		f1 >> Citiz[i].user_name >> Citiz[i].SSN_PW >> Citiz[i].name;
	}
	ifstream f2("ministries.txt", ios::in);
	Min_List[0] = new Civil_Status_Dep();
	Min_List[1] = new Elec_Bill_Dep();
	Min_List[2] = new Health_Dep();
	Min_List[3] = new Prim_Dep();
	Min_List[4] = new Prep_Dep();
	Min_List[5] = new Sec_Dep();
	for (int i = 0; i < 4; i++)
	{
		bool b; f2 >> b;
		f2 >> Min_List[i]->Minister >> Min_List[i]->Location >> Min_List[i]->Phone >> Min_List[i]->Email;
		if (!b)
		{
			Delete_Min(Min_List[i]);
		}
	}
}
void Save()
{
	ofstream f1("users.txt", ios::out);
	f1 << own.user_name << "\t" << own.SSN_PW << "\t" << own.name << "\n";
	f1 << Citiz.size() << endl;
	for (unsigned i = 0; i < Citiz.size(); i++)
	{
		f1 << Citiz[i].user_name << "\t" << Citiz[i].SSN_PW << "\t" << Citiz[i].name << "\n";
	}
	ofstream f2("ministries.txt", ios::out);
	for (int i = 0; i < 4; i++)
	{
		if (Min_List[i] == NULL)
		{
			f2 << 0;
		}
		else
		{
			f2 << 1;
		}
		f2 << "\n" << Min_List[i]->Minister << "\t" << Min_List[i]->Location
			<< "\t" << Min_List[i]->Phone << "\t" << Min_List[i]->Email << "\n";

	}
}

void E_Government_System();
void Owner_Menu()
{
	system("cls");
	cout << "***OWNER MENU***\n1-Add Ministry\n2-Edit Ministry\n" <<
		"3-Remove Ministry\n4-Control All Ministries\nGet Count:\t5-Ministries\t6-Citizens\n7-Log out\nEnter Choice: ";
	cin >> ch;
	system("cls");
	if (ch == "1")	//Add
	{
	Add_Menu:cout << "Which Ministry you Want to add:\n1- Ministry of Interior\n2- Ministry of "
		<< "Electricity and Energy\n3- Ministry of Health and Population\n4- Ministry of Education\n5- Back to Owner Menu\nEnter Choice: ";
			 cin >> ch;
			 if (stoi(ch) >= 1 && stoi(ch) <= 4 && Min_List[stoi(ch) - 1] != NULL)
			 {
				 cout << "The " << Name_Of_Ministries[stoi(ch) - 1] << " is already exist\n";
				 system("pause");
				 system("cls");
				 goto Add_Menu;
			 }
			 system("cls");
			 cout << "Adding " << Name_Of_Ministries[stoi(ch) - 1] << ":\n";
			 if (ch == "1")			//Ministry of Interior
			 {
				 Min_List[0] = new Civil_Status_Dep();
				 Min_List[0]->Add_Min();
			 }
			 else if (ch == "2")	//Ministry of Electricity and energy
			 {
				 Min_List[1] = new Elec_Bill_Dep();
				 Min_List[1]->Add_Min();
			 }
			 else if (ch == "3")	//Ministry of Health and population
			 {
				 Min_List[2] = new Health_Dep();
				 Min_List[2]->Add_Min();
			 }
			 else if (ch == "4")	//Ministry of Education
			 {
				 Min_List[3] = new Prim_Dep();
				 Min_List[4] = new Prep_Dep();
				 Min_List[5] = new Sec_Dep();
				 Min_List[3]->Add_Min();
			 }
			 else if (ch == "5")
			 {
				 Owner_Menu();
				 return;
			 }
			 else
				 goto Add_Menu;
			 cout << Name_Of_Ministries[stoi(ch) - 1] << " has been added.\n";
	}
	else if (ch == "2")	//Edit
	{
	Edit_Menu:cout << "Which ministry you want to edit:\n1- Ministry of Interior\n2- Ministry of "
		<< "Electricity and energy\n3- Ministry of Health and population\n4- Ministry of Education\n5- Back to Owner Menu\nEnter Choice: ";
			  cin >> ch;
			  if (stoi(ch) >= 1 && stoi(ch) <= 4)
			  {
				  if (Min_List[stoi(ch) - 1] != NULL)
				  {
					  system("cls");
					  cout << "Editing " << Name_Of_Ministries[stoi(ch) - 1] << ":\n";
					  Min_List[stoi(ch) - 1]->Edit_Min();
				  }
				  else
				  {
					  cout << "The " << Name_Of_Ministries[stoi(ch) - 1] << " isn't exist\n";
				  }
			  }
			  else if (ch == "5")
			  {
				  Owner_Menu();
				  return;
			  }
			  else
				  goto Edit_Menu;
	}
	else if (ch == "3")	//Delete
	{
	Delete_Menu:cout << "Which ministry you want to Delete:\n1- Ministry of Interior\n2- Ministry of "
		<< "Electricity and energy\n3- Ministry of Health and population\n4- Ministry of Education\n5- Back to Owner Menu\nEnter Choice: ";
				cin >> ch;
				if (stoi(ch) >= 1 && stoi(ch) <= 4)
				{
					if (Min_List[stoi(ch) - 1] != NULL)
					{
						Delete_Min(Min_List[stoi(ch) - 1]);
						cout << Name_Of_Ministries[stoi(ch) - 1] << " has been deleted.\n";
					}
					else
					{
						cout << "The " << Name_Of_Ministries[stoi(ch) - 1] << " isn't exist\n";
					}
				}
				else if (ch == "5")
				{
					Owner_Menu();
					return;
				}
				else
					goto Delete_Menu;
	}
	else if (ch == "4")	//Control
	{
	ShowAll_Menu:cout << "Which ministry you want to control:\n1- Ministry of Interior\n2- Ministry of "
		<< "Electricity and energy\n3- Ministry of Health and population\n4- Ministry of Education\n5- Back to Owner Menu\nEnter Choice: ";
				 cin >> ch;
				 if (stoi(ch) >= 1 && stoi(ch) <= 4 && Min_List[stoi(ch) - 1] == NULL)
				 {
					 cout << "The " << Name_Of_Ministries[stoi(ch) - 1] << " isn't exist\n";
					 system("pause");
					 system("cls");
					 goto ShowAll_Menu;
				 }
				 system("cls");
				 if (ch == "1")		//Ministry of Interior
				 {
					 cout << "Ministry of Interior:\nCivil status department:\n1-Add a Citizen's SSN Card\n2-Remove a Citizen's SSN Card\nEnter Choice: ";
					 cin >> ch; system("cls");
					 if (ch == "1")	//Add SSN Card
					 {
						 if (Citiz.size())
						 {
							 cout << "Citizens who registered on the system:\n";
							 for (unsigned i = 0; i < Citiz.size(); i++)
							 {
								 cout << i + 1 << "-" << Citiz[i] << "\n";
							 }
							 cout << "Choose the citizen you want to add a ssn card for him/her:\nEnter Choice: "; cin >> ch;
							 Civil_Status_Dep *Dp = dynamic_cast<Civil_Status_Dep*>(Min_List[0]);
							 Dp->Add_Citizen(Citiz[stoi(ch) - 1]);
							 Min_List[0] = Dp;
						 }
						 else
						 {
							 cout << "There's no citizens registered in the system yet!\n";
						 }
					 }
					 else if (ch == "2")	//Delete SSN Card
					 {
						 Civil_Status_Dep *Dp = dynamic_cast<Civil_Status_Dep*>(Min_List[0]);
						 if (Dp->Cards.size())
						 {
							 for (unsigned i = 0; i < Dp->Cards.size(); i++)
							 {
								 cout << i + 1 << "-" << Dp->Cards[i].Name << "\t" << Dp->Cards[i].SSN << "\n";
							 }
							 cout << "Choose the citizen you want to delete him/her ssn card:\nEnter Choice: "; cin >> ch;
							 cout << "Citizen Name: " << Dp->Cards[stoi(ch) - 1].Name << "\n";
							 cout << "Citizen SSN : " << Dp->Cards[stoi(ch) - 1].SSN << "\n";
							 Dp->Remove_Citizen(Dp->Cards[stoi(ch) - 1].SSN); Min_List[0] = Dp;
							 cout << "This SSN Card has been deleted\n";
						 }
						 else
						 {
							 cout << "There's no citizens has a SSN Card in the system yet!\n";
						 }
					 }
				 }
				 else if (ch == "2")	//Ministry of Electricity and energy
				 {
					 cout << "Ministry of Electricity and energy:\nElectricity Bill department:\n1-Add a Citizen's Bill\n2-Get a Citizen's Bill\nEnter Choice: ";
					 cin >> ch;
					 if (ch == "1")
					 {
						 if (Citiz.size())
						 {
							 system("cls");
							 cout << "Citizens who registered on the system:\n";
							 for (unsigned i = 0; i < Citiz.size(); i++)
							 {
								 cout << i + 1 << "-" << Citiz[i] << "\n";
							 }
							 cout << "Choose the citizen you want to add a Electricity Bill for him/her:\n"; cin >> ch;
							 cout << "Citizen Name: " << Citiz[stoi(ch) - 1].name << "\n";
							 cout << "Citizen SSN : " << Citiz[stoi(ch) - 1].SSN_PW << "\n";
							 Elec_Bill_Dep *Dp = dynamic_cast<Elec_Bill_Dep*>(Min_List[1]);
							 Dp->Add_Bill(Citiz[stoi(ch) - 1]); Min_List[1] = Dp;
						 }
						 else
						 {
							 cout << "There's no citizens registered in the system yet!\n";
						 }
					 }
					 else if (ch == "2")
					 {
						 if (Citiz.size())
						 {
							 system("cls");
							 cout << "Citizens who registered on the system:\n";
							 for (unsigned i = 0; i < Citiz.size(); i++)
							 {
								 cout << i + 1 << "-" << Citiz[i] << "\n";
							 }
							 cout << "Choose the citizen you want to check his/her Electricity Bill:\n"; cin >> ch;
							 cout << "Citizen Name: " << Citiz[stoi(ch) - 1].name << "\n";
							 cout << "Citizen SSN : " << Citiz[stoi(ch) - 1].SSN_PW << "\n";
							 Elec_Bill_Dep *Dp = dynamic_cast<Elec_Bill_Dep*>(Min_List[1]); Dp->get_Bill(Citiz[stoi(ch) - 1]);
						 }
						 else
						 {
							 cout << "There's no citizens registered in the system yet!\n";
						 }
					 }
				 }
				 else if (ch == "3")	//Ministry of Health and population
				 {
					 cout << "Ministry of Health and population:\nBlood Bank Department:\n1-Add/Edit a Blood type\n2-View All Avaliable Blood Types\nEnter Choice: ";
					 cin >> ch;
					 if (ch == "1")
					 {
						 Health_Dep *Dp = dynamic_cast<Health_Dep*>(Min_List[2]);
						 Dp->Add_or_Edit_Type(); Min_List[2] = Dp;
					 }
					 else if (ch == "2")
					 {
						 Health_Dep *Dp = dynamic_cast<Health_Dep*>(Min_List[2]);
						 Dp->View_The_Blood_Bank();
					 }
				 }
				 else if (ch == "4")	//Ministry of Education
				 {
					 cout << "Ministry of Education:\n1- Primary Stage Department\n2- Preparatory Stage Department\n3- Secondary Stage Department\nEnter Choice: ";
					 cin >> ch; system("cls");
					 if (ch == "1")	//primary stage
					 {
						 cout << "Ministry of Education:\nPrimary Stage Department:\n1-Add an exam question paper\n2-View Last year's exams question papers.\nEnter Choice: ";
						 cin >> ch; system("cls");
						 if (ch == "1")
						 {
							 Prim_Dep *Dp = dynamic_cast<Prim_Dep*>(Min_List[3]);
							 Dp->Add_Prim_Exam(); Min_List[3] = Dp;
						 }
						 else if (ch == "2")
						 {
							 Prim_Dep *Dp = dynamic_cast<Prim_Dep*>(Min_List[3]);
							 Dp->View_Prim_Exam();
						 }
					 }
					 else if (ch == "2")	//preparatory stage
					 {
						 cout << "Ministry of Education:\nPreparatory Stage Department:\n1-Add an exam question paper\n2-View Last year's exams question papers.\nEnter Choice: ";
						 cin >> ch; system("cls");
						 if (ch == "1")
						 {
							 Prep_Dep *Dp = dynamic_cast<Prep_Dep*>(Min_List[4]);
							 Dp->Add_Prep_Exam(); Min_List[4] = Dp;
						 }
						 else if (ch == "2")
						 {
							 Prep_Dep *Dp = dynamic_cast<Prep_Dep*>(Min_List[4]);
							 Dp->View_Prep_Exam();
						 }
					 }
					 else if (ch == "3")	//secondary stage
					 {
						 cout << "Ministry of Education:\nSecondary Stage Department:\n1-Add an exam question paper\n2-View Last year's exams question papers.\nEnter Choice: ";
						 cin >> ch; system("cls");
						 if (ch == "1")
						 {
							 Sec_Dep *Dp = dynamic_cast<Sec_Dep*>(Min_List[5]);
							 Dp->Add_Sec_Exam(); Min_List[5] = Dp;
						 }
						 else if (ch == "2")
						 {
							 Sec_Dep *Dp = dynamic_cast<Sec_Dep*>(Min_List[5]);
							 Dp->View_Sec_Exam();
						 }
					 }
				 }
				 else if (ch == "5")
				 {
					 Owner_Menu();
					 return;
				 }
				 else
					 goto ShowAll_Menu;
	}
	else if (ch == "5")	//Ministries count
	{
		cout << "There's " << Ministry::Count_Ministry << " ministries.\n";
	}
	else if (ch == "6")	//Citizens count
	{
		cout << "There's " << Citizen::Citiz_Num << " citizens.\n";
	}
	else if (ch == "7")
	{
		E_Government_System();
		return;
	}
	else
	{
		Owner_Menu();
		return;
	}
	system("pause");
	Owner_Menu();
}
void Citizen_Menu()
{
	system("cls");
	cout << "***CITIZEN MENU***\n1- Ministry of Interior\n2- Ministry of "
		<< "Electricity and energy\n3- Ministry of Health and population\n4- Ministry of Education\n5- Log out\nEnter Choice: ";
	cin >> ch;
	if (stoi(ch) >= 1 && stoi(ch) <= 4 && Min_List[stoi(ch) - 1] == NULL)
	{
		cout << "The " << Name_Of_Ministries[stoi(ch) - 1] << " isn't exist\n";
		system("pause");
		system("cls");
		Citizen_Menu();
		return;
	}
	system("cls");
	if (ch == "1")	//	Ministry of Interior
	{
		cout << "1-Display data about the Ministry of Interior\n2-Renew your SSN Card\nEnter Choice: "; cin >> ch;
		if (ch == "1")
		{
			Min_List[0]->Display_Data();
		}
		else if (ch == "2")
		{
			Civil_Status_Dep *Dp = dynamic_cast<Civil_Status_Dep*>(Min_List[0]);
			Dp->Renew_SSN(The_SSN); Min_List[0] = Dp;
		}
	}
	else if (ch == "2")	//	Ministry of Electricity and energy
	{
		cout << "1-Display Data about the Ministry of Electricity and Energy\n2-Check & Pay your bill\nEnter Choice: "; cin >> ch;
		if (ch == "1")
		{
			Min_List[1]->Display_Data();
		}
		else if (ch == "2")
		{
			Elec_Bill_Dep *Dp = dynamic_cast<Elec_Bill_Dep*>(Min_List[1]);
			Dp->Check_Bill(The_SSN); Min_List[1] = Dp;
		}
	}
	else if (ch == "3")	//	Ministry of Health and population
	{
		cout << "1-Display Data about the Ministry of Health and Population\n2-Search for a Certain Blood Yype\nEnter Choice: "; cin >> ch;
		if (ch == "1")
		{
			Min_List[2]->Display_Data();
		}
		else if (ch == "2")
		{
			Health_Dep *Dp = dynamic_cast<Health_Dep*>(Min_List[2]);
			Dp->Search_B_Type();
		}
	}
	else if (ch == "4")	//	Ministry of Education
	{
		system("cls");
		cout << "1-Display data about the Ministry of Education\nCheck Exams:"
			<< "\n2-Primary Stage\n3-Preparatory Stage\n4-Secondary Stage\nEnter Choice: "; cin >> ch;
		if (ch == "1")
		{
			Min_List[3]->Display_Data();
		}
		else if (ch == "2")
		{
			Prim_Dep *Dp = dynamic_cast<Prim_Dep*>(Min_List[3]);
			Dp->View_Prim_Exam();
		}
		else if (ch == "3")
		{
			Prep_Dep *Dp = dynamic_cast<Prep_Dep*>(Min_List[4]);
			Dp->View_Prep_Exam();
		}
		else if (ch == "4")
		{
			Sec_Dep *Dp = dynamic_cast<Sec_Dep*>(Min_List[5]);
			Dp->View_Sec_Exam();
		}
	}
	else if (ch == "5")
	{
		E_Government_System();
		return;
	}
	else
	{
		Citizen_Menu();
		return;
	}
	system("pause");
	Citizen_Menu();
}
void E_Government_System()
{
	system("cls");
	cout << "Welcome to the E-government system:\n\n1-Owner\n2-Citizen\n3-Exit\n-----------\nEnter Choice: "; cin >> ch;
	if (ch == "1")	//Owner
	{
	Owner_window:
		system("cls");
		cout << "Owner window:\n\n1-Sign in\n2-Sign up\n3-Return to Main Menu\nEnter Choice: ";	cin >> ch;
		if (ch == "1")	//Sign in
		{
			system("cls");
			cout << "Owner Sign IN:\n";
			cout << "Enter User Name: "; cin >> s1;
			cout << "Enter Password	: "; cin >> s2;
			if (own.sign_in(s1, s2))
			{
				Owner_Menu();
			}
			else
			{
				cout << "Wrong User Name or Password...\n", system("pause");
				goto Owner_window;
			}
		}
		else if (ch == "2")	//Sign up
		{
			system("cls");
			cout << "Owner Sign UP:\n";
			cout << "Enter User Name: "; cin >> s1;
			cout << "Enter Password	: "; cin >> s2;
			cout << "Enter Your Name: "; cin >> s3;
			own.sign_up(s1, s2, s3);
			Owner_Menu();
		}
		else if (ch == "3")
		{
			E_Government_System();
		}
		else
		{
			goto Owner_window;
		}
	}
	else if (ch == "2")	//Citizen
	{
	Citizen_window:
		system("cls");
		cout << "Citizen window:\n\n1-Sign in\n2-Sign up\n3-Return to Main Menu\nEnter Choice: "; 	cin >> ch;
		if (ch == "1")	//Sign in
		{
			system("cls");
			cout << "Citizen Sign IN:\n";
			cout << "Enter User Name: "; cin >> s1;
			cout << "Enter Password	: "; cin >> s2;
			for (unsigned i = 0; i < Citiz.size(); i++)
			if (Citiz[i].sign_in(s1, s2))
			{
				Citizen_Menu();
				return;
			}
			cout << "Wrong User Name or Password...\n"; system("pause");
			goto Citizen_window;
		}
		else if (ch == "2")	//Sign up
		{
			system("cls");
			cout << "Citizen Sign UP:\n";
			cout << "Enter User Name: "; cin >> s1;
			cout << "Enter Password	: "; cin >> s2;
			cout << "Enter Your Name: "; cin >> s3;
			Citiz.push_back(Citizen());
			Citiz.back().sign_up(s1, s2, s3);
			Citizen_Menu();
		}
		else if (ch == "3")
		{
			E_Government_System();
		}
		else
		{
			system("cls");
			goto Citizen_window;
		}
	}
	else if (ch == "3")
	{
		cout << "\nThank you.\n";
	}
	else
	{
		E_Government_System();
	}
}
void main()
{
	//Load();
	E_Government_System();
	//Save();
}
//End of E-Government 🖐🖐