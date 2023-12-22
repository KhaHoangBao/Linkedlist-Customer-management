#include <iostream>
#include <iomanip>  // Required for setw function
#include <vector>
using namespace std;

// Transaction structure
struct Transaction {
    int transactionID;
    int AccountNumber;
    string date;
    string type;  // deposit or withdraw
    double amount;
};

// CustomerNode structure with transactions
struct CustomerNode {
    int AccountNumber;
    string Name;
    string Dob;
    string Email;
    string Address;
    string Phone;
    double Balance;
    vector<Transaction> transactionHistory;  // Vector to store transactions
    CustomerNode* next;  // Pointer to the next customer node in the linked list
};

// Declare head globally
CustomerNode* head = NULL;

// Function to check if a record already exists
bool check(int AccountNumber) {
    // Add your logic to check if the record exists
    return false; // Replace with actual implementation
}

// Function to insert the record
void Insert_Record(string Name, int AccountNumber, string Dob, string Email, string Address, string Phone, double Balance) {
    // if Record Already Exist
    if (check(AccountNumber)) {
        cout << "Customer with this record Already Exists\n";
        return;
    }

    // Create new Node to Insert Record
    CustomerNode* t = new CustomerNode();
    t->AccountNumber = AccountNumber;
    t->Name = Name;
    t->Dob = Dob;
    t->Email = Email;
    t->Address = Address;
    t->Phone = Phone;
    t->Balance = Balance;
    t->next = NULL;

    // Insert at Begin
    if (head == NULL || (head->AccountNumber >= t->AccountNumber)) {
        t->next = head;
        head = t;
    }

    // Insert at middle or End
    else {
        CustomerNode* c = head;
        while (c->next != NULL && c->next->AccountNumber < t->AccountNumber) {
            c = c->next;
        }
        t->next = c->next;
        c->next = t;
    }

    cout << "Record Inserted Successfully\n";
}

// Function to insert a transaction for a specific customer
void Insert_Transaction(int AccountNumber, const string& date, const string& type, double amount, const string& status) {
    // Find the customer with the given AccountNumber
    CustomerNode* current = head;
    while (current != nullptr && current->AccountNumber != AccountNumber) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Customer not found.\n";
        return;
    }

    // Create a new transaction
    Transaction newTransaction;
    newTransaction.transactionID = current->transactionHistory.size() + 1;
    newTransaction.date = date;
    newTransaction.type = type;
    newTransaction.amount = amount;
    newTransaction.AccountNumber = AccountNumber;

    // Update the customer's balance based on the transaction type
    if (type == "deposit") {
        current->Balance += amount;
    } else if (type == "withdraw") {
        // Check if there is sufficient balance before withdrawing
        if (current->Balance >= amount) {
            current->Balance -= amount;
        } else {
            cout << "Insufficient balance for withdrawal.\n";
            return;
        }
    } else {
        cout << "Invalid transaction type.\n";
        return;
    }

    // Add the new transaction to the customer's transaction history
    current->transactionHistory.push_back(newTransaction);

    cout << "Transaction successfully added.\n";
}

// Function to display all customer records
// Function to display all customer records in a table
void Show_CustomerRecords() {
    CustomerNode* current = head;

    cout << "\nCustomer Records:\n";
    cout << setw(15) << "Account Number" << setw(20) << "Name"
         << setw(15) << "Date of Birth" << setw(30) << "Email"
         << setw(30) << "Address" << setw(15) << "Phone"
         << setw(15) << "Balance" << endl;

    while (current != nullptr) {
        cout << setw(15) << current->AccountNumber << setw(20) << current->Name
             << setw(15) << current->Dob << setw(30) << current->Email
             << setw(30) << current->Address << setw(15) << current->Phone
             << setw(15) << current->Balance << endl;

        current = current->next;
    }
}

// Function to display transaction history for a specific customer in a table
// Function to display transaction history for a specific customer in a table
void Show_TransactionHistory(int AccountNumber) {
    CustomerNode* current = head;

    // Find the customer with the given AccountNumber
    while (current != nullptr && current->AccountNumber != AccountNumber) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Customer not found.\n";
        return;
    }

    cout << "\nTransaction History for Account Number " << AccountNumber << ":\n";
    cout << setw(15) << "Transaction ID" << setw(20) << "Date"
         << setw(15) << "Type" << setw(15) << "Amount" << endl;

    // Use iterator to loop through the transaction history
    for (auto it = current->transactionHistory.begin(); it != current->transactionHistory.end(); ++it) {
        const Transaction& transaction = *it;
        cout << setw(15) << transaction.transactionID << setw(20) << transaction.date
             << setw(15) << transaction.type << setw(15) << transaction.amount << endl;
    }
}

// Modify the Show_Record function to call these two functions
void Show_Record() {
    int showChoice;
    cout << "Choose what to display:\n";
    cout << "1. Customer Records\n";
    cout << "2. Transaction History\n";
    cin >> showChoice;

    if (showChoice == 1) {
        Show_CustomerRecords();
    } else if (showChoice == 2) {
        int accountNumber;
        cout << "Enter Account Number to view Transaction History: ";
        cin >> accountNumber;
        Show_TransactionHistory(accountNumber);
    } else {
        cout << "Invalid choice.\n";
    }
}


int main() {
    string Name, Dob, Address, Email;
    int AccountNumber;
    string Phone;
    double Balance;

    // Menu-driven program
    while (true) {
        cout << "\n\t\tWelcome to Customer Record Management System\n\n\tPress\n\t"
                "1 to create a new customer information Record\n\t"
                "2 to create a new transaction Record\n\t"
                "3 to view all Customer records\n\t"
                "4 to Exit\n";
        cout << "\nEnter your Choice\n";
        int Choice;

        // Enter Choice
        cin >> Choice;
        if (Choice == 1) {
            cout << "Enter Name of Customer\n";
            cin.ignore();
            getline(cin, Name);
            cout << "Enter Account Number of Customer\n";
            cin >> AccountNumber;
            cout << "Enter Dob of Customer \n";
            cin >> Dob;
            cout << "Enter Email of Customer\n";
            cin >> Email;
            cout << "Enter Address of Customer\n";
            cin >> Address;
            cout << "Enter Phone Number of Customer\n";
            cin >> Phone;
            cout << "Enter Balance amount of Customer\n";
            cin >> Balance;
            Insert_Record(Name, AccountNumber, Dob, Email, Address, Phone, Balance);
        } 
        
        else if (Choice == 2) {
            int transactionID;
            cout << "Enter Transaction ID \n";
            cin >> transactionID;
            cout << "Enter Account Number of Customer\n";
            cin >> AccountNumber;
            cout << "Enter the Date transaction begin\n";
            string date; // Declare date variable
            cin >> date;
            cout << "Enter the type of transaction \n";
            string type; // Declare type variable
            cin >> type;
            cout << "Enter the amount of transaction\n";
            double amount; // Declare amount variable
            cin >> amount;
            Insert_Transaction(AccountNumber, date, type, amount, ""); // status not used
        }

         else if (Choice == 3) {
            Show_Record();
        } else if (Choice == 4) {
            exit(0);
        } else {
            cout << "Invalid Choice. Try Again\n";
        }
    }
    return 0;
}
