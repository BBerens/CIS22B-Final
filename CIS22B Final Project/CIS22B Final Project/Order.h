#ifndef __ORDER_H__
#define __ORDER_H__

#include "Book.h"

class Order
{
private:
	Book * books[100];
	int quantity[100];
	int items;
public:
	Order();
	void addBook(Book *, int);
	Book * getBook(int) const;
	int getQuantity(int) const;
	int getNumBooks(void) const;
};

#endif