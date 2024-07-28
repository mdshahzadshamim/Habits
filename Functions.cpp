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

