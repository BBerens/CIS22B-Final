#define _CRT_SECURE_NO_WARNINGS
#ifndef __INVENTORY_CPP__
#define __INVENTORY_CPP__

#include "Inventory.h"


Inventory::Inventory(void)
{
	numBooks = 0;
	numUsedBooks = 0;
	readBooksFromFile();
	for (int i = 0; i < 8; i++)
	{
		lists[i] = new Book*[numBooks];
		lists[i] = generateAttributeList(i);
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
	for (int k = 0; k < numUsedBooks; k++)
	{
		delete usedBooks[k];
	}
}

Book* Inventory::addBook(void)
{
	// when we add a new book we should generate a new dynamically allocated array of book pointers(books)
	Book* newBook;
	newBook = new Book(); // temporary, need to do this with dynamic allocation
	books[numBooks] = newBook;
	newBook->setBookNumber(numBooks);
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

Book** Inventory::generateAttributeList(int attribute)
{
	Book** attributeList;
	int startScan;
	int minIndex;
	Book * minValue;
	attributeList = new Book*[numBooks + numUsedBooks];
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
	return attributeList;
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
	//delete []lists;
	for (int i = 0; i < 8; i++)
	{
		lists[i] = new Book*[numBooks];
		lists[i] = generateAttributeList(i);
		//generateAttributeList(i, lists[i]);
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
	int deleteBookNum =deletionBook->getBookNumber();
	delete books[deleteBookNum];
	--numBooks;
	for (int i = deleteBookNum; i < numBooks; i++)
	{
		books[i] = books[i + 1];
	}
	updateLists();
}

