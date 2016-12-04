#ifndef __ORDER_H__
#define __ORDER_H__

#include "Book.h"

class Order
{
private:
	Book * orderBooks[100]; 
	int quantity[100]; // quantity of each book purchased
	int items; // Total number of books
public:
	Order();
	~Order();
	void addBook(Book *, int);
	Book * getBook(int) const;
	int getQuantity(int) const;
	int getNumBooks(void) const;
};

#endif