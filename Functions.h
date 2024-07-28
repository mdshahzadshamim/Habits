#pragma once
#include <iostream>
#include <pqxx/pqxx>
using namespace std;
class Work
{
    public:
        string display(const string&);
        void checkIn(pqxx::connection& conn);
        int maxVal(pqxx::connection& conn, const string& col);
};
class Modify
{
    public:
        void createHabit(pqxx::connection& conn);
        void updateHabit(pqxx::connection& conn);
        void dropHabit(pqxx::connection& conn);
};