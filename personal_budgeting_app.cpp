/*
 * Personal Budgeting App
 * ----------------------
 * Author: Mulenga Chituta
 * Date: July 28, 2024
 *
 * Overview:
 * The Personal Budgeting App is a console-based application written in C++ designed to assist users in managing their personal finances. 
 * The app provides features to track income and expenses, categorize transactions, and generate comprehensive financial reports.
 *
 * Key Features:
 * 1. **Add Income and Expenses**: Users can log various types of transactions including both income and expenses.
 * 2. **Categorize Transactions**: Each transaction can be categorized for better tracking and analysis.
 * 3. **View All Transactions**: Users can view a complete list of all transactions added to the app.
 * 4. **Filter by Category**: Allows users to filter transactions by specific categories.
 * 5. **Generate Financial Reports**: Generates reports displaying total income, total expenses, and net balance, aiding in budget analysis.
 * 6. **Data Persistence**: Transaction data is stored in a text file, ensuring that users can access their data even after closing the application.
 *
 * How It Works:
 * - The app uses a simple command-line interface (CLI) to interact with users, providing a straightforward menu for navigation.
 * - Transaction data is encapsulated within a `Transaction` class, which stores details such as type, amount, category, description, and date.
 * - The `BudgetManager` class handles operations related to transaction management, including loading, saving, and displaying transactions.
 *
 * Technical Details:
 * - The application is built using standard C++ libraries, ensuring compatibility across different systems.
 * - A vector data structure is used to store transaction objects, providing dynamic and efficient storage.
 * - File I/O operations are performed using fstream to achieve data persistence.
 * - Date handling is performed using the `ctime` library to automatically log the date of each transaction.
 *
 * Usage:
 * - To compile the application, use a C++ compiler such as g++. For example: `g++ -o PersonalBudgetingApp main.cpp`
 * - Run the compiled executable: `./PersonalBudgetingApp` (Linux/Mac) or `PersonalBudgetingApp.exe` (Windows).
 *
 * Future Enhancements:
 * - Implement a graphical user interface (GUI) for improved user interaction.
 * - Add features like budget goals, transaction search, and data export options.
 * - Implement encryption for enhanced data security.
 *
 * Note:
 * This project is a demonstration of fundamental C++ programming concepts including object-oriented programming, file handling, and basic data management.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

// Transaction class definition
// The Transaction class definiton represents a financial transaction (income or expense)
// It stores information such as transaction type, amount, category, description, and date
class Transaction {
    public:
        // Enum to differentiate between income and expense transactions
        enum class Type {INCOME, EXPENSE};

        // Constructor to initialize a transaction with the given type, amount, category, and description
        // The date is automatically set to the current date
        Transaction(Type type, double amount, const string& category, const string& description)
            : type(type), amount(amount), category(category), description(description), date(getCurrentDate) {}

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
}