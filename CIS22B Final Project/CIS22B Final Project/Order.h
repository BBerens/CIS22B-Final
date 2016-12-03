#ifndef __ORDER_H__
#define __ORDER_H__

#include "Book.h"

class Order
{
private:
	Book * books[100]; 
	int quantity[100]; // quantity of each book purchased
	int items; // Total number of books
public:
	Order();
	void addBook(Book *, int);
	Book * getBook(int) const;
	int getQuantity(int) const;
	int getNumBooks(void) const;
};

#endif