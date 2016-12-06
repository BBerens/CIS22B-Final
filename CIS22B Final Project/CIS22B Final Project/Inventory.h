#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Book.h"
#include "UsedBook.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Inventory
{
private:
	int bookArrSize = 10;
	int usedBookArrSize = 10;
	Book** books;	// unsorted array, in order of when they were added
	UsedBook** usedBooks;
	int numBooks;
	int numUsedBooks;
	Book ** lists[8];
public:
	Inventory(void);
	virtual ~Inventory();
	Book* addBook(void);
	UsedBook* addUsedBook(void);
	UsedBook* addUsedBook(int);
	UsedBook* addUsedBook(Book*);
	Book* getBook(int);	// temporary
	int getNumUsedBooks(void) const;

	// Temporarily commented out
	// Book** searchAuthor(string);
	// Book** searchTitle(string);
	// Book** searchIsbn(long long);
	// Book** searchPublisher(string);

	void writeBooks(void);
	void readBooksFromFile(void);
	void generateAttributeList(int, Book**);
	Book** getAttributeList(int);
	int getNumBooks(void);
	Book* searchAttribute(int, string) const;
	void updateLists();
	int strSearch(int, string, Book**);
	void deleteBook(Book*);

	void increaseNewArrSize();
	void increaseUsedArrSize();

};
#endif
