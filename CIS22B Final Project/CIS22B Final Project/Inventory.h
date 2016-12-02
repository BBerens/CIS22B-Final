#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Book.h"
#include <string>


using namespace std;

class Inventory
{
private:
	Book* books[100];	// unsorted array, in order of when they were added
	int numBooks;
	Book ** lists[7];
public:
	Inventory(void);
	virtual ~Inventory();
	Book* addBook(void);
	Book* getBook(int);	// temporary
	Book** searchAuthor(string);
	Book** searchTitle(string);
	Book** searchIsbn(long long);
	Book** searchPublisher(string);
	void writeBooks(void);
	void readBooksFromFile(void);
	Book** generateAttributeList(int);
	Book** getAttributeList(int);
	int getNumBooks(void);
	Book * searchAttribute(int, string) const;

};
#endif
