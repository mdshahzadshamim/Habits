#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <io.h>
#include "Functions.h"
using namespace std;

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    Work w;
    Modify m;
    char repeat = 1;
    try
    {
        pqxx::connection conn("dbname=test user=postgres password=postgres port=5432");

        pqxx::work txn_count_cols(conn);
        pqxx::result cols = txn_count_cols.exec("SELECT COUNT(*) FROM information_schema.columns WHERE table_name = 'habits'");
        txn_count_cols.commit();

        int column = cols[0][0].as<int>(); // Note that this count includes the date too

        // -----------------------------column count extraction

        pqxx::work txn_count_names(conn);
        pqxx::result res_col_names = txn_count_names.exec("SELECT column_name FROM information_schema.columns WHERE "
                                                          "table_name = 'habits' AND table_schema = 'public'");
        txn_count_names.commit();

        vector<string> column_name;
        if (!res_col_names.empty())
            for (const auto &row : res_col_names)
                column_name.push_back(row[0].as<string>());

        // -----------------------------column names extraction

        pqxx::work txn_clean(conn);
        txn_clean.exec("DELETE FROM habits h WHERE (SELECT SUM((value::text)::integer) FROM jsonb_each_text(to_jsonb(h) - 'date_ymd')) = 0");
        txn_clean.commit();

        // -----------------------------previous junk deletion

        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT * FROM habits WHERE date_ymd = CURRENT_DATE");
        txn.commit();

        if (result.empty())
        {
            pqxx::work txn1(conn);
            txn1.exec("INSERT INTO habits (date_ymd) VALUES (CURRENT_DATE)");
            txn1.commit();

        }
        // -----------------------------initialization through current date

        while (repeat != 'n')
        {
            vector<int> sum;
            for (int i = 1; i < column; i++)
            {
                pqxx::work txnq(conn);
                pqxx::result resultq = txnq.exec_params("SELECT SUM($1) FROM habits", column_name[i]);
                txnq.commit();

                if (!resultq.empty())
                {
                    int temp = resultq[0][0].as<int>();
                    sum.push_back(temp);
                }
            }
            sum[0] += 22; // Previous Streak

            // -----------------------------streak counts extraction

            vector<int> n;
            for (int i = 1; i < column; i++)
            {
                pqxx::work txnc(conn);
                pqxx::result resultc = txnc.exec_params("SELECT $1 FROM habits WHERE date_ymd = CURRENT_DATE", column_name[i]);
                txnc.commit();

                if (!resultc.empty())
                {
                    int temp = resultc[0][0].as<int>();
                    n.push_back(temp);
                }

                // const pqxx::row &row = resultc[0];
                //     for (pqxx::row::size_type col = 0; col < row.size(); ++col)
                //         n.push_back(row[col].as<int>());
            }

            // -----------------------------today's data extraction

            pqxx::work day_count(conn);
            pqxx::result dc = day_count.exec("SELECT COUNT(*) FROM (SELECT date_ymd, (SELECT SUM((value::text)::integer) FROM jsonb_each_text(to_jsonb(h) - 'date_ymd')) " 
                                                "AS sum_values FROM habits h) subquery WHERE sum_values > 0");
            day_count.commit();

            int d_c = dc[0][0].as<int>();

            // -----------------------------workdays count extraction

            system("cls");

            cout << endl
                 << "\n\n\n\t\t\t\tH\tA\tB\tI\tT\tS\n\n\n";

            cout << setw(33) << left << "\t\t\t\t#   SUBJECT" << setw(10) << left << "STREAK" << "TODAY\n"
                 << endl;

            for (int i = 0; i < column - 1; i++)
                cout << "\t\t\t\t" << i + 1 << " - " << setw(27) << left << w.display(column_name[i + 1]) << setw(10) << left << sum[i] << n[i] << endl;

            cout << endl;
            cout << setw(35) << left << "\t\t\t\tX - LeetCode Total" << setw(10) << left << sum[1] + sum[3] + sum[5] << endl;

            // cout << endl;
            cout << setw(35) << left << "\t\t\t\tN - Workdays Total" << setw(10) << left << d_c << endl;

            // -----------------------------CURRENT VALUES - DISPLAY

            // Note - It's a personalized app so you need to change the habit names here
            // And in the database, if you want to access it using sql directly
            // You can add/remove number of cases accordingly

            int habit = 0, count = 0;

            cout << "\n\n\t\t\t\tHabit Completed:\t";
            cin >> habit;
            clearInputBuffer();
            pqxx::work txn1(conn);

            // if (habit > 0 && habit < column+1)
            // {
            //     int maxval = w.maxVal(conn, column_name[habit]);
            //     if (maxval > 1)
            //     {
            //         cout << "\n\n\t\t\t\tCount:\t\t";
            //         count = 0;
            //         cin >> count;
            //         clearInputBuffer();
            //         txn1.exec_params("UPDATE habits SET $1 = $2 WHERE date_ymd = CURRENT_DATE", column_name[habit], count);
            //         txn1.commit();
            //     }
            //     else
            //     {
            //         txn1.exec_params("UPDATE habits SET $1 = 1 WHERE date_ymd = CURRENT_DATE", column_name[habit]);
            //         txn1.commit();
            //     }
            // }

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
            case 7:
                txn1.exec("UPDATE habits SET full_stack = 1 WHERE date_ymd = CURRENT_DATE");
                txn1.commit();
                break;
            case 8:
                txn1.exec("UPDATE habits SET algorithms = 1 WHERE date_ymd = CURRENT_DATE");
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
    catch (const exception &e)
    {
        std::cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
