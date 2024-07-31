#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

// Transaction class definition
// The Transaction class represents a financial transaction (income or expense)
// It stores information such as transaction type, amount, category, description, and date
class Transaction {
public:
    // Enum to differentiate between income and expense transactions
    enum class Type { INCOME, EXPENSE };

    // Member variables to store transaction details
    Type type;             // Transaction type (INCOME or EXPENSE)
    double amount;         // Amount of the transaction
    string category;       // Category of the transaction
    string description;    // Description of the transaction
    string date;           // Date of the transaction

    // Constructor to initialize a transaction with the given type, amount, category, and description
    // The date is automatically set to the current date
    Transaction(Type type, double amount, const string& category, const string& description)
        : type(type), amount(amount), category(category), description(description), date(getCurrentDate()) {}

    // Function to get the current date in YYYY-MM-DD format
    string getCurrentDate() const {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        stringstream ss;
        ss << 1900 + ltm->tm_year << "-"
           << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
           << setw(2) << setfill('0') << ltm->tm_mday;
        return ss.str();
    }

    // Accessor methods for the transaction attributes
    Type getType() const { return type; }
    double getAmount() const { return amount; }
    string getCategory() const { return category; }
    string getDescription() const { return description; }
    string getDate() const { return date; }

    // Function to display transaction details
    void display() const {
        cout << "Date: " << date << ", "
             << "Type: " << (type == Type::INCOME ? "Income" : "Expense") << ", "
             << "Amount: ZMW" << fixed << setprecision(2) << amount << ", "
             << "Category: " << category << ", "
             << "Description: " << description << endl;
    }
};