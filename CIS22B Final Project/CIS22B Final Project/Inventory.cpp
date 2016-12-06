#define _CRT_SECURE_NO_WARNINGS
#ifndef __INVENTORY_CPP__
#define __INVENTORY_CPP__

#include "Inventory.h"


Inventory::Inventory(void)
{
	numBooks = 0;
	numUsedBooks = 0;
	books = new Book*[bookArrSize];
	usedBooks = new UsedBook*[usedBookArrSize];
	readBooksFromFile();
	for (int i = 0; i < 8; i++)
	{
		lists[i] = new Book*[numBooks + numUsedBooks];
		generateAttributeList(i, lists[i]);
	}
}

Inventory::~Inventory()
{
	for (int i = 0; i < 8; i++)
	{
		delete lists[i];
	}
	for (int j = 0; j < numBooks; j++)
	{
		delete books[j];
	}
	delete[] books;
	for (int k = 0; k < numUsedBooks; k++)
	{
		delete usedBooks[k];
	}
	delete[] usedBooks;
	_CrtDumpMemoryLeaks();
}

Book* Inventory::addBook(void)
{
	// when we add a new book we should generate a new dynamically allocated array of book pointers(books)
	Book* newBook;
	newBook = new Book(); // temporary, need to do this with dynamic allocation
	books[numBooks] = newBook;
	newBook->setBookNumber(numBooks);
	numBooks++;
	if (numBooks >= bookArrSize - 2)
	{
		increaseNewArrSize();
	}
	return newBook;
}

UsedBook* Inventory::addUsedBook(int condition)
{
	UsedBook* newUsedBook;
	newUsedBook = new UsedBook(condition); 
	usedBooks[numUsedBooks] = newUsedBook;
	newUsedBook->setBookNumber(numUsedBooks);
	numUsedBooks++;
	if (numUsedBooks >= usedBookArrSize - 2)
	{
		increaseUsedArrSize();
	}
	return newUsedBook;
}

UsedBook* Inventory::addUsedBook(Book* newBook)
{
	UsedBook* newUsedBook;
	newUsedBook = new UsedBook(newBook);
	usedBooks[numUsedBooks] = newUsedBook;
	newUsedBook->setBookNumber(numUsedBooks);
	numUsedBooks++;
	if (numUsedBooks >= usedBookArrSize - 2)
	{
		increaseUsedArrSize();
	}
	return newUsedBook;
}
UsedBook* Inventory::addUsedBook(void)
{

	UsedBook* newUsedBook;
	newUsedBook = new UsedBook(); 
	usedBooks[numUsedBooks] = newUsedBook;
	newUsedBook->setBookNumber(numUsedBooks);
	numUsedBooks++;
	if (numUsedBooks >= usedBookArrSize - 2)
	{
		increaseUsedArrSize();
	}
	return newUsedBook;
}

Book* Inventory::getBook(int index)	// temporary
{
	return books[index];
}

void Inventory::readBooksFromFile()
{
	Book* bookPtr;
	UsedBook* usedBookPtr;
	fstream bookDatabase;
	int newBooks, usedBooks;

	bookDatabase.open("BookDatabase.txt", ios::in);
	bookDatabase >> newBooks;
	bookDatabase.ignore(20, '\n'); // ignore the rest of the line
	for (int i = 0; i < newBooks; i++)
	{
		bookPtr = addBook();
		bookDatabase >> *bookPtr;
		bookDatabase.ignore();	// should ignore the '\n' character
	}
	
	bookDatabase >> usedBooks;
	bookDatabase.ignore(20, '\n');
	for (int j = 0; j < usedBooks; j++)
	{
		usedBookPtr = addUsedBook();
		bookDatabase >> *usedBookPtr;
	}

	bookDatabase.close();
}
void Inventory::writeBooks()
{
	fstream bookDatabase;
	bookDatabase.open("BookDatabase.txt", ios::out);
	bookDatabase << numBooks << " New Books" << endl;
	for (int i = 0; i < numBooks; i++)
	{
		bookDatabase << *books[i] << endl;
	}
	bookDatabase << numUsedBooks << " Used Books" << endl;
	for (int j = 0; j < numUsedBooks; j++)
	{
		bookDatabase << *usedBooks[j] << endl;
	}
	bookDatabase.close();
}

void Inventory::generateAttributeList(int attribute, Book** attributeList)
{

	int startScan;
	int minIndex;
	Book * minValue;
	for (int i = 0; i < numBooks; i++)
	{
		attributeList[i] = books[i];
	}
	for (int j = 0; j < numUsedBooks; j++)
	{
		attributeList[j + numBooks] = usedBooks[j];
	}
	for (startScan = 0; startScan < numBooks + numUsedBooks - 1; startScan++)
	{
		minIndex = startScan;
		minValue = attributeList[startScan];
		for (int j = startScan +1; j < numBooks + numUsedBooks; j++)
		{
			if (attributeList[j]->getAttribute(attribute) < minValue->getAttribute(attribute))
			{
				minIndex = j;
				minValue = attributeList[j];
			}
		}
		attributeList[minIndex] = attributeList[startScan];
		attributeList[startScan] = minValue;
	}
}

Book** Inventory::getAttributeList(int attribute)
{
	return lists[attribute];
}

int Inventory::getNumBooks(void)
{
	return numBooks;
}

Book * Inventory::searchAttribute(int attribute, string value) const 
{
	int first = 0; // First array element
	int last = numBooks + numUsedBooks - 1; // Last array element
	int	middle; // Mid point of search
	int position = -1; // Position of search value
	bool found = false; // Flag
	while (!found && first <= last)
	{
		middle = (first + last) / 2; // Calculate mid point
		if (lists[attribute][middle]->getAttribute(attribute) == value) // If value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (lists[attribute][middle]->getAttribute(attribute) > value) // If value is in lower half
			last = middle - 1;
		else
			first = middle + 1; // If value is in upper half
	}
	if (found)
		return lists[attribute][position];
	else
		return nullptr;
}
#endif

void Inventory::updateLists()
{
	for (int i = 0; i < 8; i++)
	{
		delete lists[i];
		lists[i] = new Book*[numBooks + numUsedBooks];
		generateAttributeList(i, lists[i]);		
	}
}

int Inventory::strSearch(int attribute, string value, Book** searchList)
{
	string tempStr;
	int counter = 0;
	for (int i = 0; i < numBooks; i++)
	{
		tempStr = books[i]->getAttribute(attribute);
		if (tempStr.find(value) != -1)
		{
			searchList[counter++]=books[i];
		}
	}
	return counter;
}

int Inventory::getNumUsedBooks(void) const
{
	return numUsedBooks;
}

void Inventory::deleteBook(Book* deletionBook)
{
	Book** tempBooks;
	tempBooks = new Book*;
	int deleteBookNum =deletionBook->getBookNumber(); // get the book number of the book to be deleted
	delete books[deleteBookNum];	// delete that book
	--numBooks;		// decrement the number of books
	for (int i = deleteBookNum; i < numBooks; i++)	// start at where the book was deleted and copy each book pointer from the index one more
	{
		books[i] = books[i + 1];
	}
	updateLists();	// update all the sorted lists to account for the deleted book
}

void Inventory::increaseNewArrSize()
{
	bookArrSize *= 2;	// double the size of the book array
	Book** tempBooks = new Book*[bookArrSize];
	for (int i = 0; i < numBooks; i++)
	{
		tempBooks[i] = books[i];
	}
	delete[] books;
	books = new Book*[bookArrSize];
	for (int i = 0; i < numBooks; i++)
	{
		books[i] = tempBooks[i];
	}
	delete[] tempBooks;
}

void Inventory::increaseUsedArrSize()
{
	usedBookArrSize *= 2;	// double the size of the book array
	UsedBook** tempBooks = new UsedBook*[usedBookArrSize];
	for (int i = 0; i < numUsedBooks; i++)
	{
		tempBooks[i] = usedBooks[i];
	}
	delete[] usedBooks;
	usedBooks = new UsedBook*[usedBookArrSize];
	for (int i = 0; i < usedBookArrSize; i++)
	{
		usedBooks[i] = tempBooks[i];
	}
	delete[] tempBooks;
}