#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class BankAccount{
	private:
		string name;
		long long accountNumber;
		
	protected:
		float balance;
		
	public:
		BankAccount(string name_, long long acc_, float bal_)
		:name{name_}, accountNumber{acc_}, balance{bal_}
		{
			
		}
		
		void deposit(const float amount){
			if(amount > 0){
				this->balance += amount;
				cout << "Amount deposited successfully!" << endl;
			}else{
				cout << "Invalid amount" << balance << endl;
			}
		}
		
		void withdraw(const float amount){
			if(balance < 0){
				cout << "Invalid amount: " << amount << endl;
			}
			else if(this->balance - amount >0){
				this->balance -= amount;
			}else{
				cout << "Insufficient Balance!" << endl;
				cout << amount  << " withdrawn successfully" << endl;
			}
		}
		
		void displayAccount(){
			cout << "Name: " << this->name 
					<< " A/C No: " << this->accountNumber 
					<<  " Balance: " << fixed << setprecision(2) << this->balance << endl;
		}
		
		~BankAccount(){
			
		}
};

class SavingsAccount: public BankAccount{
	private:
		float interestRate;
	
	public:
		SavingsAccount(string name_, long long acc_, float bal_, float interest_)
		:BankAccount(name_, acc_, bal_), interestRate{interest_}{
			
		}
	
		void applyInterest(){
			this->balance += (this->balance*interestRate)/100;
			cout << "Interest accumulated: " << ((this->balance*interestRate)/100) << endl;
		}
		
		void withdraw(const float amount){
			if(balance < 0){
				cout << "Invalid amount: " << amount << endl;
			}
			else if(this->balance - amount-100 <0){
				cout << "Insufficient Balance!" << endl;
			}else{
				this->balance -= amount;
				cout << amount  << " withdrawn successfully" << endl;
			}
		}
		
		~SavingsAccount(){
		}
};	

class CheckingAccount: public BankAccount{
	private:
		float overdraftLimit;
		
	public:
		CheckingAccount(string name_, long long acc_, float bal_, float interest_)
		:BankAccount(name_, acc_, bal_), overdraftLimit{interest_}{
			
		}
		
		void withdraw(const float amount){
			if(balance < 0){
				cout << "Invalid amount: " << amount << endl;
			}
			else if(this->balance - amount-this->overdraftLimit <0){
				cout << "Insufficient Balance!" << endl;
			}else{
				this->balance -= amount;
				cout << amount  << " withdrawn successfully" << endl;
			}
		}
		
		~CheckingAccount(){
		}		
};

int main(){
	BankAccount* bc = new BankAccount("Vishal", 12345678, 0.0);
	{
		bc->deposit(-123);
		bc->deposit(0.0);
		bc->deposit(1000.0);
		
		bc->withdraw(-12);
		bc->withdraw(1023.0);
		bc->withdraw(800);
		
		bc->displayAccount();
		
		cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	}
	delete bc;
	bc = nullptr;
	SavingsAccount* abc = new SavingsAccount("Harsh", 12345679, 0.0, 3.2);
	{
		abc->deposit(-123);
		abc->deposit(0.0);
		abc->deposit(1000.0);
		
		abc->withdraw(-12);
		abc->withdraw(1023.0);
		abc->withdraw(800);
		
		abc->applyInterest();
		abc->displayAccount();
		
		cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	}
	BankAccount* cbac = abc;
	{
		cbac->deposit(-123);
		cbac->deposit(0.0);
		cbac->deposit(1000.0);
		
		cbac->withdraw(-12);
		cbac->withdraw(1023.0);
		cbac->withdraw(100);
		
		cbac->displayAccount();
		
		cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	}
	delete abc;
	abc = nullptr;
	CheckingAccount* cc = new CheckingAccount("Harsh", 12345679, 200, 300);
	{
		cc->deposit(-123);
		cc->deposit(0.0);
		cc->deposit(1100.0);
		
		cc->withdraw(-12);
		cc->withdraw(1300.0);
		cc->withdraw(1000);
		
		cc->displayAccount();
		
		cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	}
	return 0;
}
	
