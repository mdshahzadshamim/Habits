#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <io.h>
#include "Functions.h"
using namespace std;



string Work ::display(const string &col) // Displays Column Name Normally
{
    int n = col.size();
    string display;
    for (int i = 0; i < n; i++)
    {
        if (i == 0 || col[i - 1] == '_')
            display += toupper(col[i]);
        else if (col[i] == '_')
            display += ' ';
        else
            display += col[i];
    }
    return display;
}

void Work ::checkIn(pqxx::connection &conn)
{
    ;
}

int Work::maxVal(pqxx::connection &conn, const std::string &col)
{
    return 0;
}

void Modify ::createHabit(pqxx::connection &conn)
{
    ;
}

void Modify ::updateHabit(pqxx::connection &conn)
{
    ;
}

void Modify ::dropHabit(pqxx::connection &conn)
{
    ;
}

// void Functions :: hello()
// {
//     cout << endl;
//     cout << setw(35) << left << "\t\t\t\tF - Function Text: "        << setw(10) << left << "Normal Text"         << endl;
// }

// int Work ::maxVal(pqxx::connection &conn, const string &col)
// {
//     try
//     {
//         string col_name = "habits_" + col + "_check";
//         pqxx::work txn(conn);
//         pqxx::result output = txn.exec_params("SELECT regexp_replace(pg_get_constraintdef(oid), '^.*<=\\s*([0-9]+).*$', '\\1') AS max_value FROM pg_constraint"
//                                               " WHERE conrelid = 'habits'::regclass AND conname = '$1'",
//                                               col_name);
//         txn.commit();
//         int value = output[0][0].as<int>();
//         return value;
//     }
//     catch (const exception &e)
//     {
//         cerr << "Error: " << e.what() << endl;
//         return false;
//     }
// }

// int Work::maxVal(pqxx::connection &conn, const std::string &col)
// {
//     int count;
//     cout << "\n\n\t\t\t\tCount1:\t";
//     cin >> count;

//     std::string col_name = "habits_" + col + "_check";
//     cout << col_name << "ABC" << endl;
//     std::string str1 = "^.*<=\\s*([0-9]+).*$";
//     cout << str1 << endl;
//     std::string str2 = "\\1";
//     cout << str2 << endl;

//     cout << "\n\n\t\t\t\tCount2:\t";
//     cin >> count;

//     pqxx::work txn(conn);
//     std::string query = R"(
//         SELECT regexp_replace(pg_get_constraintdef(oid), '$1', '$2') AS max_value 
//         FROM pg_constraint 
//         WHERE conrelid = 'habits'::regclass 
//         AND conname = $3
//     )";

//     cout << "\n\n\t\t\t\tCount3:\t";
//     cin >> count;

//     pqxx::result output = txn.exec_params(query, str1, str2, col_name);
//     txn.commit();

//     cout << "\n\n\t\t\t\tCount4:\t";
//     cin >> count;

//     if (output.empty() || output[0][0].is_null())
//     {
//         throw std::runtime_error("No max value found for the given column");
//     }

//     int value = output[0][0].as<int>();
//     return value;
// }

// int Work ::maxVal(pqxx::connection &conn, const std::string &col)
// {
//     // Construct the constraint name based on the column name
//     std::string col_name = "habits_" + col + "_check";

//     // Create a transaction object
//     pqxx::work txn(conn);

//     // Define the query with a placeholder for the constraint name
//     std::string query = R"(
//         SELECT regexp_replace(
//             pg_get_constraintdef(oid), 
//             '^.*<=\s*([0-9]+).*$', 
//             '\1'
//         ) AS max_value
//         FROM pg_constraint
//         WHERE conrelid = 'habits'::regclass
//         AND conname = $1
//     )";

//     try
//     {
//         // Execute the query with the column name as a parameter
//         pqxx::result result = txn.exec_params(query, col_name);

//         // Commit the transaction
//         txn.commit();

//         // Check if the result is empty or null
//         if (result.empty() || result[0]["max_value"].is_null())
//         {
//             throw std::runtime_error("No max value found for the given column");
//         }

//         // Convert the result to integer and return
//         int value = result[0]["max_value"].as<int>();
//         return value;
//     }
//     catch (const std::exception &e)
//     {
//         // Rollback transaction in case of error
//         txn.abort();
//         std::cerr << "Query execution failed: " << e.what() << std::endl;
//         throw; // Re-throw the exception to be handled by the caller
//     }
// }

