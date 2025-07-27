//✅ TASK 4: Banking System 
//●​ Design classes for Customer, Account and Transaction with necessary attributes. 
//●​ Implement functions to create and manage customers and accounts. 
//●​ Include features for deposits, withdrawals and fund transfers. 
//●​ Store transaction history and allow users to view recent transactions. 
//●​ Display account information like balance and transaction details to customers

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

struct Transaction 
{
    string type;
    double amount;
    string note;

};

class Customer
{
    
    public:
    int customer_id;
    string name;

    Customer()
    {
      customer_id = 0 ;
      name = "" ;  
    } 

    Customer(int id, string n)
    {
        customer_id = id ;
        name = n ;
    }
};

class Account
{
    private:
    
    int acc_no;
    double balance;
    Customer owner;
    vector<Transaction> history;

    public:
    
    Account() : acc_no(0), balance(0.0), owner() {}
    
    Account(int accNo, Customer cust)
    {
        acc_no = accNo ;
        balance = 0 ;
        owner = cust ;  
    } 


    void deposit(double amount)
    {
        if (amount <= 0) 
        {
            cout <<"Invalid amount.\n";
            return;
        }

        balance += amount;
        
        history.push_back({"Deposit", amount,"Amount deposit"});
        cout <<"Deposit successful.\n";
    }

    bool withdraw(double amount)
    {
        if (amount <= 0 || amount > balance) 
        {
            cout <<"Invalid amount.\n";
            return false;
        }

        balance -= amount;
        
        history.push_back({"Withdraw", amount,"Amount withdrawn"});
        cout << "Withdraw successful.\n";
        return true;
    }

    
    bool transfer(Account& to, double amount) 
    {
        if (withdraw(amount))
        {
            to.deposit(amount);
            history.push_back({"Transfer", amount, "Ammmount Transferred to Account #" + to.getacc_noStr()});
            return true;
        }
        return false;
    }

    void show_history() const
    {

        cout<<"\nTransaction History for Account #" << acc_no << endl;
        
        for (const auto& t : history) 
        {
            cout <<left << setw(10) <<t.type << "Rupees" << setw(10)  << t.amount << "- " << t.note << endl;
        }
    }

    double get_balance() const { return balance; }
    int getacc_no() const { return acc_no; }
    string getacc_noStr() const { return to_string(acc_no); }
    string get_owner_name() const { return owner.name; }
};

map<int, Account> accounts;
int nextcustomer_id = 1;
int nextacc_no = 1001;

void create_acc()
{
    string name;
    cout <<"Enter customer name: ";
    cin.ignore();
    getline(cin, name);

    Customer cust(nextcustomer_id++, name);
    Account acc(nextacc_no++, cust);
    accounts[acc.getacc_no()] = acc;

    cout << "Account created successfully!" << endl ;
    cout << "Account Number: " << acc.getacc_no() << endl;
}

void deposit_ammount()
{
    int accNo;
    double amount;

    cout << "Enter account number: "; 
    cin >> accNo;
    
    cout <<"Enter amount to deposit: "; 
    cin >> amount;

    if (accounts.find(accNo) != accounts.end())
    {
        accounts[accNo].deposit(amount);
    }
    else
    {
        cout << "Account not found.\n";
    }
}

void withdraw_ammount() 
{
    int accNo;
    double amount;
    
    cout << "Enter account number: "; 
    cin >> accNo;
    
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (accounts.find(accNo) != accounts.end())
    {
        accounts[accNo].withdraw(amount);
    }
    else
    {    cout << "Account not found.\n";

    }
}


void transfer_funds() 
{
    
    int from_acc, to_acc;
    double amount;

    cout << "Enter sender's account number: "; 
    cin >> from_acc;
    
    cout << "Enter receiver's account number: "; 
    cin >> to_acc;
    
    cout << "Enter amount to transfer: "; 
    cin >> amount;

    if (accounts.find(from_acc) != accounts.end() && accounts.find(to_acc) != accounts.end())
    {
        accounts[from_acc].transfer(accounts[to_acc], amount);
    }
       else
    {   
        cout << "One or both accounts not found.\n";
    }
}

void show_acc_info()
{
    int accNo;
    
    cout << "Enter account number: ";
    cin >>accNo;

    if (accounts.find(accNo) != accounts.end()) 
    {
        Account& acc = accounts[accNo];
        
        cout << "\nAccount Holder: " << acc.get_owner_name() << endl;
        cout << "Account Number: " << acc.getacc_no() << endl;
        cout << "Balance: Rupees" << acc.get_balance() << endl;
        acc.show_history();
    } 
    
    else 
    {
        cout << "Account not found.\n";
    }
}

int main() 
{
    int choice;
    while (true)
    {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Info\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: create_acc();
            break;
            
            case 2: deposit_ammount();
            break;
            
            case 3: withdraw_ammount();
            break;
            
            case 4: transfer_funds();
            break;
            
            case 5: show_acc_info(); 
            break;
            
            case 6: cout << "Exiting...\n"; 
            return 0;
            
            default: 
            cout << "Invalid choice \n";
        }
    }

    return 0;
}
