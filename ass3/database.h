#ifndef DATABASE_H
#define DATABASE_H

using namespace std;

// Your database class definition goes here

template <class value> class Database {

  public:
    Database();
    ~Database();

    int numRecords() const;
    int numSelected() const;

    void write(ostream& out, DBScope scope) const;
    void read(istream& in);
    void deleteRecords(DBScope scope);

    void selectAll();
    void deselectAll();

    void select(DBSelectOperation selOp, const string& attr,
DBQueryOperator op, const value& val);
    
    int numSelected_ = 0;
    
    vector<Record<value>> records_;
};

#include "database.tem"

#endif
