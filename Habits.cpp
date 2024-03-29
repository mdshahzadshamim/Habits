#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <io.h>
using namespace std;

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    char repeat = 1;
    try
    {
        pqxx::connection conn("dbname=test user=postgres password=postgres port=5432");

        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT * FROM habits WHERE date_ymd = CURRENT_DATE");
        txn.commit();

        if(result.empty())
        {
            pqxx::work txn1(conn);
            txn1.exec("INSERT INTO habits (date_ymd) VALUES (CURRENT_DATE)");
            txn1.commit();
        }
        while(repeat != 'n')
        {
            int habit = 0, sum1 = 22, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0;

            system("cls");

            pqxx::work txnq(conn);
            pqxx::result resultq = txnq.exec("SELECT SUM(discrete_maths), SUM(leet_code_1), SUM(systems_design), "
                                                    "SUM(leet_code_2), SUM(cpp), SUM(leet_code_3) FROM habits");
            txnq.commit();

            // SELECT SUM(discrete_maths), SUM(leet_code_1), SUM(systems_design), SUM(leet_code_2), SUM(cpp), SUM(leet_code_3) FROM habits;

            sum1 += resultq[0][0].as<int>();
            sum2 += resultq[0][1].as<int>();
            sum3 += resultq[0][2].as<int>();
            sum4 += resultq[0][3].as<int>();
            sum5 += resultq[0][4].as<int>();
            sum6 += resultq[0][5].as<int>();

            cout << endl << "\n\n\n\t\t\t\tH\tA\tB\tI\tT\tS\n\n\n";

            cout << setw(30) << left << "\t\t\t\t1 - Discrete Mathematics" << sum1 << endl;
            cout << setw(30) << left << "\t\t\t\t2 - LeetCode Day 1" << sum2 << endl;
            cout << setw(30) << left << "\t\t\t\t3 - Systems Design" << sum3 << endl;
            cout << setw(30) << left << "\t\t\t\t4 - LeetCode Day 2" << sum4<< endl;
            cout << setw(30) << left << "\t\t\t\t5 - C++ Programming" << sum5 << endl;
            cout << setw(30) << left << "\t\t\t\t6 - LeetCode Day 3" << sum6 << endl;

            // Note - It's a personalized app so you need to change the habit names here 
            // And in the database, if you want to access it using sql directly
            // You can add/remove number of cases accordingly

            cout << "\n\n\t\t\t\tHabit Completed:\t";
            cin >> habit;
            clearInputBuffer();
            pqxx::work txn1(conn);
            switch (habit)
            {
                case 1:
                    txn1.exec("UPDATE habits SET discrete_maths = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                case 2:
                    txn1.exec("UPDATE habits SET leet_code_1 = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                case 3:
                    txn1.exec("UPDATE habits SET systems_design = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                case 4:
                    txn1.exec("UPDATE habits SET leet_code_2 = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                case 5:
                    txn1.exec("UPDATE habits SET cpp = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                case 6:
                    txn1.exec("UPDATE habits SET leet_code_3 = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                default:
                    break;
            }
            habit = 0;
            // txn1.commit();
            cout << "\n\n\t\t\t\tRepeat Habits(n)\t";
            repeat = std::cin.get();
        }
    }
    catch (const exception& e)
    {
        std::cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
