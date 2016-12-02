// test SVN

#include "Order.h"

Order::Order()
{
	items = 0;
}
void Order::addBook(Book * newBook, int numberBooks)
{
	quantity[items] = numberBooks;
	books[items] = newBook;
	items++;
}
Book * Order::getBook(int itemNumber) const
{
	return books[itemNumber];
}
int Order::getQuantity(int itemNumber) const
{
	return quantity[itemNumber];
}

int Order::getNumBooks(void) const
{
	return items;
}