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

    // Constructor to initialize a transaction with the given type, amount, category, and description
    // The date is automatically set to the current date
    Transaction(Type type, double amount, const string& category, const string& description)
        : type(type), amount(amount), category(category), description(description), date(getCurrentDate()) {}

    // Function to get the current date in YYYY-MM-DD format
    string getCurrentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);

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
             << "Amount: $" << amount << ", "
             << "Category: " << category << ", "
             << "Description: " << description << endl;
    }

private:
    Type type; // Type of transaction (INCOME or EXPENSE)
    double amount; // Amount of the transaction
    string category; // Category of the transaction (e.g., "Food", "Rent")
    string description; // Description of the transaction
    string date; // Date of the transaction in YYYY-MM-DD format
};

// BudgetManager class definition
// The BudgetManager class manages a collection of transactions, providing functionality to add, display, and report on transactions
class BudgetManager {
public:
    // Constructor to initialize the BudgetManager with a specified filename for data persistence
    BudgetManager(const string& filename) : filename(filename) {
        loadTransactions(); // Load transactions from the file on initialization
    }

    // Function to add a transaction to the budget manager
    // This function also saves the transaction to a file for persistence
    void addTransaction(const Transaction::Type type, const double amount, const string& category, const string& description) {
        Transaction transaction(type, amount, category, description); // Create a new transaction
        transactions.push_back(transaction); // Add the transaction to the vector
        saveTransaction(transaction); // Save the transaction to the file
    }

    // Function to display all transactions in the budget manager
    void displayAllTransactions() const {
        cout << "\n--- All Transactions ---\n";
        for (const auto& transaction : transactions) {
            transaction.display(); // Display each transaction
        }
    }

    // Function to display transactions filtered by a specific category
    void displayTransactionsByCategory(const string& category) const {
        cout << "\n--- Transactions for Category: " << category << " ---\n";
        for (const auto& transaction : transactions) {
            if (transaction.getCategory() == category) {
                transaction.display(); // Display only transactions matching the category
            }
        }
    }

    // Function to generate a financial report, showing total income, total expenses, and net balance
    void generateReport() const {
        double totalIncome = 0.0, totalExpense = 0.0;
        for (const auto& transaction : transactions) {
            if (transaction.getType() == Transaction::Type::INCOME) {
                totalIncome += transaction.getAmount();
            } else {
                totalExpense += transaction.getAmount();
            }
        }
        cout << "\n--- Financial Report ---\n"
             << "Total Income: $" << totalIncome << endl
             << "Total Expense: $" << totalExpense << endl
             << "Net Balance: $" << (totalIncome - totalExpense) << endl;
    }

private:
    vector<Transaction> transactions; // Vector to store all transactions
    string filename; // Filename for data persistence

    // Function to load transactions from a file
    // This function is called during initialization to restore previous session data
    void loadTransactions() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string typeStr, category, description, dateStr;
                double amount;
                ss >> typeStr >> amount >> category >> description;
                Transaction::Type type = (typeStr == "Income") ? Transaction::Type::INCOME : Transaction::Type::EXPENSE;
                transactions.emplace_back(type, amount, category, description);
            }
            file.close();
        }
    }

    // Function to save a transaction to a file
    // This function appends the transaction data to the specified file for persistence
    void saveTransaction(const Transaction& transaction) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << (transaction.getType() == Transaction::Type::INCOME ? "Income" : "Expense") << " "
                 << transaction.getAmount() << " "
                 << transaction.getCategory() << " "
                 << transaction.getDescription() << endl;
            file.close();
        }
    }
};

// Function to display the main menu options to the user
void displayMenu() {
    cout << "\n--- Personal Budgeting App ---\n"
         << "1. Add Income\n"
         << "2. Add Expense\n"
         << "3. View All Transactions\n"
         << "4. View Transactions by Category\n"
         << "5. Generate Financial Report\n"
         << "6. Exit\n"
         << "Enter your choice: ";
}

// Main function to run the application
// This function manages user input and handles the main application loop
int main() {
    BudgetManager budgetManager("transactions.txt"); // Create a BudgetManager instance with a specified filename
    int choice; // Variable to store user choice
    do {
        displayMenu(); // Display the menu options
        cin >> choice; // Get user input

        switch (choice) {
            case 1: {
                double amount;
                string category, description;
                cout << "Enter income amount: $";
                cin >> amount;
                cin.ignore(); // Ignore leftover newline character
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter description: ";
                getline(cin, description);
                budgetManager.addTransaction(Transaction::Type::INCOME, amount, category, description); // Add income transaction
                break;
            }
            case 2: {
                double amount;
                string category, description;
                cout << "Enter expense amount: $";
                cin >> amount;
                cin.ignore(); // Ignore leftover newline character
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter description: ";
                getline(cin, description);
                budgetManager.addTransaction(Transaction::Type::EXPENSE, amount, category, description); // Add expense transaction
                break;
            }
            case 3:
                budgetManager.displayAllTransactions(); // Display all transactions
                break;
            case 4: {
                string category;
                cout << "Enter category to filter: ";
                cin.ignore(); // Ignore leftover newline character
                getline(cin, category);
                budgetManager.displayTransactionsByCategory(category); // Display transactions filtered by category
                break;
            }
            case 5:
                budgetManager.generateReport(); // Generate financial report
                break;
            case 6:
                cout << "Exiting the application. Goodbye!" << endl; // Exit the application
                break;
            default:
                cout << "Invalid choice. Please try again." << endl; // Handle invalid input
                break;
        }
    } while (choice != 6); // Repeat the loop until the user chooses to exit

    return 0; // Return success
}
