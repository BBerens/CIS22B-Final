#ifndef __INVENTORY_CPP__
#define __INVENTORY_CPP__

#include "Inventory.h"
#include "Book.h"
#include <fstream>

Inventory::Inventory(void)
{
	numBooks = 0;
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

Book* Inventory::getBook(int index)	// temporary
{
	return books[index];
}

void Inventory::readBooksFromFile()
{
	Book* bookPtr;
	fstream bookDatabase;

	bookDatabase.open("BookDatabase.txt", ios::in);

	do
	{
		bookPtr = addBook();		
	} while (bookDatabase >> *bookPtr);
	delete books[numBooks--];
	bookDatabase.close();
}
void Inventory::writeBooks()
{
	fstream bookDatabase;
	bookDatabase.open("BookDatabase.txt", ios::out);
	for (int i = 0; i < numBooks; i++)
	{
		bookDatabase << *books[i];
	}
	bookDatabase.close();

}

Book ** Inventory::generateAttributeList(int attribute)
{
	int lowerLimit;
	int smallIndex;
	Book * temp;
	Book ** tempList = nullptr;
	tempList = new Book*;
	for (int i = 0; i < numBooks; i++)
	{
		tempList[i] = books[i];

	}
	for (int i = 0; i < numBooks; i++)
	{
		lowerLimit = i;
		smallIndex = lowerLimit;
		for (int j = lowerLimit; j < numBooks; j++)
		{
			if (tempList[j]->getAttribute(attribute) < tempList[smallIndex]->getAttribute(attribute))
			{
				smallIndex = j;
			}
			temp = tempList[lowerLimit];
			tempList[lowerLimit] = tempList[smallIndex];
			tempList[smallIndex] = temp;
		}
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

