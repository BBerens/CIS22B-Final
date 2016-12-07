#ifndef __USEDBOOK_H__
#define __USEDBOOK_H__

#include "Book.h"
#include <fstream>
using namespace std;

class UsedBook : public Book
{
private:
	enum condition { LIKE_NEW, GOOD, FAIR, POOR };
	condition bookCondition;
public:
	UsedBook();		// default constructor
	UsedBook(int);	// constructor to initialize condition
	UsedBook(Book*);	// constructor to initialize from an already constructed book 
	virtual ~UsedBook(){};	// destructor
	
	//Setters
	void setCondition(int);

	//Getters
	int getCondition(void) const;
	virtual double getWholesaleCost(void) const;	// overridden from Book class
	virtual double getRetailPrice(void) const;		// overridden from Book class
	virtual string getBookType(void) const;			// overridden from Book class
	virtual void print(void);		// overridden from Book class
	virtual void printCashier(void);
	friend fstream& operator << (fstream&, UsedBook&);	// overload left shift operator to write to file
	friend fstream& operator >> (fstream&, UsedBook&);	// overload right shift operator to read from file
};

#endif