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

        pqxx::work txn_clean(conn);
            txn_clean.exec("DELETE FROM habits WHERE discrete_maths = 0 AND leet_code_1 = 0 "
                        "AND systems_design = 0 AND leet_code_2 = 0 AND computer_networks = 0 "
                        "AND leet_code_3 = 0");
            txn_clean.commit();

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
            int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0;
            int count = 0;

            system("cls");

            pqxx::work txnq(conn);
            pqxx::result resultq = txnq.exec("SELECT SUM(discrete_maths), SUM(leet_code_1), SUM(systems_design), "
                                        "SUM(leet_code_2), SUM(computer_networks), SUM(leet_code_3) FROM habits");
            txnq.commit();

            // SELECT SUM(discrete_maths), SUM(leet_code_1), SUM(systems_design), SUM(leet_code_2), SUM(cpp), SUM(leet_code_3) FROM habits;

            sum1 += resultq[0][0].as<int>();
            sum2 += resultq[0][1].as<int>();
            sum3 += resultq[0][2].as<int>();
            sum4 += resultq[0][3].as<int>();
            sum5 += resultq[0][4].as<int>();
            sum6 += resultq[0][5].as<int>();

            // -----------------------------counted sterak

            pqxx::work txnc(conn);
            pqxx::result resultc = txnc.exec("SELECT discrete_maths, leet_code_1, systems_design, leet_code_2, "
                                                    "computer_networks, leet_code_3 FROM habits WHERE date_ymd = CURRENT_DATE");
            txnc.commit();

            n1 = resultc[0][0].as<int>();
            n2 = resultc[0][1].as<int>();
            n3 = resultc[0][2].as<int>();
            n4 = resultc[0][3].as<int>();
            n5 = resultc[0][4].as<int>();
            n6 = resultc[0][5].as<int>();

            // -----------------------------accessed todays data

            cout << endl << "\n\n\n\t\t\t\tH\tA\tB\tI\tT\tS\n\n\n";

            cout << setw(33) << left << "\t\t\t\t#   SUBJECT"               << setw(10) << left << "STREAK" <<  "TODAY\n" << endl;

            cout << setw(35) << left << "\t\t\t\t1 - Discrete Mathematics"  << setw(10) << left << sum1       << n1       << endl;
            cout << setw(35) << left << "\t\t\t\t2 - LeetCode Day 1"        << setw(10) << left << sum2       << n2       << endl;
            cout << setw(35) << left << "\t\t\t\t3 - Systems Design"        << setw(10) << left << sum3       << n3       << endl;
            cout << setw(35) << left << "\t\t\t\t4 - LeetCode Day 2"        << setw(10) << left << sum4       << n4       << endl;
            cout << setw(35) << left << "\t\t\t\t5 - Computer Networks"     << setw(10) << left << sum5       << n5       << endl;
            cout << setw(35) << left << "\t\t\t\t6 - LeetCode Day 3"        << setw(10) << left << sum6       << n6       << endl;
            cout << endl;
            cout << setw(35) << left << "\t\t\t\tX - LeetCode Total"        << setw(10) << left << sum2+sum4+sum6         << endl;


            pqxx::work day_count(conn);
            pqxx::result dc = day_count.exec("SELECT COUNT(date_ymd) FROM habits WHERE discrete_maths != 0 OR leet_code_1 != 0 "
                        "OR systems_design != 0 OR leet_code_2 != 0 OR computer_networks != 0 "
                        "OR leet_code_3 != 0");
            day_count.commit();

            int d_c = dc[0][0].as<int>();

            cout << endl;
            cout << setw(35) << left << "\t\t\t\tN - Days Total"            << setw(10) << left << d_c                    << endl;

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
                    cout << "\n\n\t\t\t\tCount:\t\t";
                    count = 0;
                    cin >> count;
                    clearInputBuffer();
                    txn1.exec_params("UPDATE habits SET leet_code_1 = $1 WHERE date_ymd = CURRENT_DATE", count);
                    txn1.commit();
                    break;
                case 3:
                    txn1.exec("UPDATE habits SET systems_design = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                case 4:
                    cout << "\n\n\t\t\t\tCount:\t\t";
                    count = 0;
                    cin >> count;
                    clearInputBuffer();
                    txn1.exec_params("UPDATE habits SET leet_code_2 = $1 WHERE date_ymd = CURRENT_DATE", count);
                    txn1.commit();
                    break;
                case 5:
                    txn1.exec("UPDATE habits SET computer_networks = 1 WHERE date_ymd = CURRENT_DATE");
                    txn1.commit();
                    break;
                case 6:
                    cout << "\n\n\t\t\t\tCount:\t\t";
                    count = 0;
                    cin >> count;
                    clearInputBuffer();
                    txn1.exec_params("UPDATE habits SET leet_code_3 = $1 WHERE date_ymd = CURRENT_DATE", count);
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
