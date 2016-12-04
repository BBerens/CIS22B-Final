// test SVN

#include "Order.h"

// Default Constructor
Order::Order()
{
	items = 0;
}

// Default Destructor
Order::~Order()
{
	;  
}

void Order::addBook(Book * newBook, int numberBooks)
{
	quantity[items] = numberBooks;
	orderBooks[items] = newBook;
	items++;
}
Book * Order::getBook(int itemNumber) const
{
	return orderBooks[itemNumber];
}
int Order::getQuantity(int itemNumber) const
{
	return quantity[itemNumber];
}

int Order::getNumBooks(void) const
{
	return items;
}