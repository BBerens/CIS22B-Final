#define _CRT_SECURE_NO_WARNINGS
#ifndef __INVENTORY_CPP__
#define __INVENTORY_CPP__

#include "Inventory.h"


Inventory::Inventory(void)
{
	numBooks = 0;
	numUsedBooks = 0;
	readBooksFromFile();
	for (int i = 0; i <= 7; i++)
	{
		lists[i] = new Book*[numBooks];
		lists[i] = generateAttributeList(i);
	}
}

Inventory::~Inventory()
{
	for (int i = 0; i < numBooks; i++)
	{
		delete books[i];
	}
}

Book* Inventory::addBook(void)
{
	// when we add a new book we should generate a new dynamically allocated array of book pointers(books)
	Book* newBook;
	newBook = new Book(); // temporary, need to do this with dynamic allocation
	books[numBooks] = newBook;
	numBooks++;
	return newBook;
}

UsedBook* Inventory::addUsedBook(int condition)
{
	// when we add a new book we should generate a new dynamically allocated array of book pointers(books)
	UsedBook* newUsedBook;
	newUsedBook = new UsedBook(condition); // temporary, need to do this with dynamic allocation
	usedBooks[numUsedBooks] = newUsedBook;
	numUsedBooks++;
	return newUsedBook;
}

UsedBook* Inventory::addUsedBook(void)
{
	// when we add a new book we should generate a new dynamically allocated array of book pointers(books)
	UsedBook* newUsedBook;
	newUsedBook = new UsedBook(); // temporary, need to do this with dynamic allocation
	usedBooks[numUsedBooks] = newUsedBook;
	numUsedBooks++;
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

Book ** Inventory::generateAttributeList(int attribute)
{
	
	int startScan;
	int minIndex;
	Book * minValue;
	Book ** tempList;
	tempList = new Book*[numBooks+numUsedBooks];
	for (int i = 0; i < numBooks; i++)
	{
		tempList[i] = books[i];
	}
	for (startScan = 0; startScan < numBooks - 1; startScan++)
	{
		minIndex = startScan;
		minValue = tempList[startScan];
		for (int j = startScan +1; j < numBooks; j++)
		{
			if (tempList[j]->getAttribute(attribute) < minValue->getAttribute(attribute))
			{
				minIndex = j;
				minValue = tempList[j];
			}
		}
		tempList[minIndex] = tempList[startScan];
		tempList[startScan] = minValue;
	}
	return tempList;
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
	int last = numBooks - 1; // Last array element
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
	for (int i = 0; i <= 7; i++)
	{
		delete *lists[i];
		lists[i] = new Book*[numBooks];
		lists[i] = generateAttributeList(i);
	}
}

