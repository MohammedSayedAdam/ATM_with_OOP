#include <iostream>
#include <String>
#include <list>
#include <iterator>
using namespace std;
class Person
{
private:
	string Name;
	int Age;
	string Adderess;
	string Phone_Number;
public:
	Person()
	{
		this->Name = "";
		this->Adderess = "";
		this->Age = 0;
		this->Phone_Number = "";
	}
	Person(string name, int age, string address, string Ph_Num)
	{
		this->Name = name;
		this->Adderess = address;
		this->Age = age;
		this->Phone_Number = Ph_Num;
	}
};
class Transaction
{
public:
   virtual bool WithDraw(float amount) = 0;
   virtual bool Deposite(float amount) = 0;
   virtual float Check_Balance() = 0;
};
class ATM
{
private:
	float balance;
	string Location;
	int Ink_Amount;
	int Papers_Amount;
	int Machine_num;
public:
	ATM()
	{
		this->balance = 0;
		this->Ink_Amount = 0;
		this->Location = "";
		this->Papers_Amount = 0;
		this->Machine_num = 0;
	}
	ATM(int machine_num,float amount,int ink_amount,int papers_amount,string location)
	{
		this->Machine_num = machine_num;
		this->balance = amount;
		this->Ink_Amount = ink_amount;
		this->Location = Location;
		this->Papers_Amount = papers_amount;
	}
	void Add_Balance(int amount)
	{
		balance += amount;
	}
	void Minus_Balance(int amount)
	{
		if(amount <=balance)
			balance -= amount;;
	}
	float Get_Balance()
	{
		return balance;
	}
	bool Withdraw_Ink()
	{
		if (Ink_Amount > 0)
		{
			this->Ink_Amount -= 1;
			return true;
		}
		else
			cout << "Sorry this Machine Doesn't have Ink" << endl;
		return false;
	}
	bool Withdraw_Paper()
	{
		if (Papers_Amount > 0)
		{
			this->Papers_Amount -= 1;
			return true;
		}
		else
			cout << "Sorry this Machine Doesn't have papers to print" << endl;
		return false;
	}

};
class Technician: public Transaction, public Person
{
private:
	float salary;
	ATM atm;
public:
	Technician() :Person()
	{
		salary = 0;
		cout << "Technician is Created without paremeter" << endl;
	}
	Technician(float salary,string name,int age,string add,string ph):Person(name,age,add,ph)
	{
		this->salary = salary;
		cout << "Technician is Created with paremeter" << endl;
	}
    float Check_Balance() override
	{
		return 0;
	}
	bool WithDraw(float amount) override
	{
		return true;
	}
	bool Deposite(float amount) override
	{
		if (amount > 0)
		{
			atm.Add_Balance(amount);
			return true;
		}
		return false;
	}

};
class Customer:public Transaction,public Person
{
private:
	string Card_Num;
    float balance;
	string pin;
	ATM atm;
public:
	Customer():Person()
	{
		this->Card_Num = "";
		this->balance = 0;
		this->pin = "0000";
	}
	Customer(string Name,string pin,float balance,string card_num,int Age,string adderss,string Ph,ATM atm):Person(Name,Age,adderss,Ph)
	{
		this->balance = balance;
		this->pin = pin;
		this->Card_Num = card_num;
		this->atm = atm;
	}
	virtual float Check_Balance()
	{
		char y;
		cout << "Do You Want to Print Papper write y : ";
		cin >> y;
		if (y == 'y')
		{
			if (atm.Withdraw_Ink() && atm.Withdraw_Paper())
			{
				cout << "paper is printing " << endl;
				cout << "your balance is: " << this->balance << endl;
			}
			else
			{
				cout << "Transaction is Failed" << endl;
			}
		}
		return 0;
	}
	virtual bool WithDraw(float amount)
	{
		if (amount > 0&& amount<= balance)
		{
			if (atm.Withdraw_Ink() && atm.Withdraw_Paper())
			{
				atm.Minus_Balance(amount);
				balance -= amount;
				return true;
			}
			return false;
		}
		cout << "your Amount Must Be > 0 and less than Your balance" << endl;
		return false;
	}
	virtual bool Deposite(float amount)
	{
		if (amount > 0)
		{
			if (atm.Withdraw_Ink() && atm.Withdraw_Paper())
			{
				atm.Add_Balance(amount);
				balance += amount;
				return true;
			}
			return false;
		}
		return false;
	}
};

void main()
{
	Technician technician(1500.5, "mohammed", 25, "cairo Egy", "012545565");
	ATM atm(1, 50000, 15, 15, "Attaba");
	Customer c1("Mohammed", "1234", 14500, "24524", 25, "Cairo,Egypt", "0125446335", atm);
	Customer c2("Ahmed", "4444", 20000, "24524", 24, "Duha,Qater", "+565452524", atm);
	c1.WithDraw(50000001);
	system("pause");
}