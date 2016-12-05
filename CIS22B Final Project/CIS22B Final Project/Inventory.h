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
	int bookArrSize = 100;
	int usedBookArrSize = 100;
	Book** books = new Book*[bookArrSize];	// unsorted array, in order of when they were added
	UsedBook** usedBooks = new UsedBook*[usedBookArrSize];
	int numBooks;
	int numUsedBooks;
	Book ** lists[8];
public:
	Inventory(void);
	virtual ~Inventory();
	Book* addBook(void);
	UsedBook* addUsedBook(void);
	UsedBook* addUsedBook(int);
	Book* getBook(int);	// temporary
	int getNumUsedBooks(void) const;

	// Temporarily commented out
	// Book** searchAuthor(string);
	// Book** searchTitle(string);
	// Book** searchIsbn(long long);
	// Book** searchPublisher(string);

	void writeBooks(void);
	void readBooksFromFile(void);
	Book** generateAttributeList(int);
	Book** getAttributeList(int);
	int getNumBooks(void);
	Book * searchAttribute(int, string) const;
	void Inventory::updateLists();
	int strSearch(int, string, Book**);
	void deleteBook(Book*);

	void increaseArrSize();

};
#endif
