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
	static unsigned int usedBooks;
	UsedBook();
	UsedBook(int);
	UsedBook(Book*);
	~UsedBook();
	
	void setCondition(int);
	int getCondition(void) const;

	double getWholesaleCost(void) const;
	double getRetailPrice(void) const;

	virtual void print(void);
	virtual void printCashier(void);
	friend fstream& operator << (fstream&, UsedBook&);
	friend fstream& operator >> (fstream&, UsedBook&);
};

#endif