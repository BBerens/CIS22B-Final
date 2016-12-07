#define _CRT_SECURE_NO_WARNINGS
#ifndef __INVENTORY_CPP__
#define __INVENTORY_CPP__

#include "Inventory.h"


Inventory::Inventory(void)	// default constructor
{
	numBooks = 0;	// initialize number of new books to 0
	numUsedBooks = 0;	// initiliaze number of used books to 0
	books = new Book*[bookArrSize];		// declare a dynamically allocated array of book pointers of initial size (10)
	usedBooks = new UsedBook*[usedBookArrSize];		// declare a dynamically allocated array of used book pointers of initial size (10)
	readBooksFromFile();	// read in books from file (bookDatabase.txt) and populate books and usedbooks
	for (int i = 0; i < 8; i++)	// for each attribute list 
	{
		lists[i] = new Book*[numBooks + numUsedBooks];	// declare a dynamically allocated array of book pointer of the size to collect all new and used books
		generateAttributeList(i, lists[i]);	// populate the attribute lists with all used and new books and sort them
	}
}

Inventory::~Inventory()	// destructor
{
	for (int i = 0; i < 8; i++)	// for each attribute list, delete the pointer and the pointer arrays
	{
		delete[] lists[i];
	}
	for (int j = 0; j < numBooks; j++)	// for each new book delete it from books
	{
		delete books[j];
	}
	delete[] books;	// delete the books array
	for (int k = 0; k < numUsedBooks; k++)	// for each used book, delete it from usedBooks
	{
		delete usedBooks[k];
	}
	delete[] usedBooks;	// delete the usedBooks array
}

// adds a book and sets a pointer to it in books
Book* Inventory::addBook(void)
{
	Book* newBook;	// declare a book pointer
	newBook = new Book();	// dynamically allocate a book
	books[numBooks] = newBook;	// set next books pointer to new book
	newBook->setBookNumber(numBooks);	// set the bookNumber for the new book
	numBooks++;	// increment the number of books
	if (numBooks >= bookArrSize - 2)	// if the number of books starts approaching the size of the dynamically allocated array.
	{
		increaseNewArrSize();	// increase the size of the books array X2
	}
	return newBook;	
}

// adds a used book and sets next pointer to in usedBooks. Initializes wtih already constructed book
UsedBook* Inventory::addUsedBook(Book* newBook)
{
	UsedBook* newUsedBook;	// declare a usedBook pointer
	newUsedBook = new UsedBook(newBook);	// dynamically allocate a usedBook with all book attributes initialized
	usedBooks[numUsedBooks] = newUsedBook;	// set next usedBooks pointer to new used book 
	newUsedBook->setBookNumber(numUsedBooks);	// set the bookNumber for the new used book
	numUsedBooks++;	// increment the number of used books
	if (numUsedBooks >= usedBookArrSize - 2)	// if the number of used books starts approaching the size of the dynamically allocate array
	{
		increaseUsedArrSize();	// increase the size of the usedBooks array X2
	}
	return newUsedBook;
}

// adds a used book and sets the next pointer to it in usedBooks. 
UsedBook* Inventory::addUsedBook(void)
{

	UsedBook* newUsedBook;	// declare a usedBook pointer
	newUsedBook = new UsedBook();	// dynamically allocate a usedBook with all book attributes initialized
	usedBooks[numUsedBooks] = newUsedBook;	// set next usedBooks pointer to new used book 
	newUsedBook->setBookNumber(numUsedBooks);	// set the bookNumber for the new used book
	numUsedBooks++;		// increment the number of used books
	if (numUsedBooks >= usedBookArrSize - 2)	// if the number of used books starts approaching the size of the dynamically allocate array
	{
		increaseUsedArrSize();	// increase the size of the usedBooks array X2
	}
	return newUsedBook;
}

// read books from file and store them in books[] and usedbooks[]
void Inventory::readBooksFromFile()
{
	Book* bookPtr;
	UsedBook* usedBookPtr;
	fstream bookDatabase;
	int newBooks, usedBooks;

	bookDatabase.open("BookDatabase.txt", ios::in);	// open the file storing book data
	// if the file is not found, no books are read in. numBooks = numUsedBooks = 0
	if (bookDatabase >> newBooks)	// read in the number of new books
	{
		bookDatabase.ignore(20, '\n'); // ignore the rest of the line
		for (int i = 0; i < newBooks; i++)	// for each new book on file
		{
			bookPtr = addBook();	// allocate a new book
			bookDatabase >> *bookPtr;	// read in the data and set the book attributes
			bookDatabase.ignore();	// ignore the '\n' character
		}

		bookDatabase >> usedBooks;	// read in the number of used books
		bookDatabase.ignore(20, '\n');	// ignore hte rest of the line
		for (int j = 0; j < usedBooks; j++)	// for each used book on file
		{
			usedBookPtr = addUsedBook();	// allocate a used book
			bookDatabase >> *usedBookPtr;	// read in the data and set the used book's attributes
		}
	}
	bookDatabase.close();	// close the file
}

// write books[] and usedBooks[] to file before exiting the program
void Inventory::writeBooks()
{
	fstream bookDatabase;
	bookDatabase.open("BookDatabase.txt", ios::out);	// overwrites previous data
	bookDatabase << numBooks << " New Books" << endl;	// write number of new books and some flavor text
	for (int i = 0; i < numBooks; i++)	// for each book in books[]
	{
		bookDatabase << *books[i] << endl;	// write the book's attributes to file
	}
	bookDatabase << numUsedBooks << " Used Books" << endl;	// write number of used books and some flavor text
	for (int j = 0; j < numUsedBooks; j++)	// for each used book in usedBooks[]
	{
		bookDatabase << *usedBooks[j] << endl;	// write the book's attributes to file
	}
	bookDatabase.close();	// close the file
}

// copies all books from books[] and usedBooks[] to list then sorts them using selection sort based on attribute
void Inventory::generateAttributeList(int attribute, Book** attributeList)
{
	int startScan;
	int minIndex;
	Book * minValue;
	for (int i = 0; i < numBooks; i++)	// for each book in books[]
	{
		attributeList[i] = books[i];	// copy the pointer to attributeList
	}
	for (int j = 0; j < numUsedBooks; j++)	// for each used book in usedBooks[]
	{
		attributeList[j + numBooks] = usedBooks[j];	// copy the pointer to attributeList
	}

	// Selection Sort based on attribute that correlates with attribute int
	for (startScan = 0; startScan < numBooks + numUsedBooks - 1; startScan++)
	{
		minIndex = startScan;
		minValue = attributeList[startScan];
		for (int j = startScan + 1; j < numBooks + numUsedBooks; j++)
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

// returns specified attribute's sorted list
Book** Inventory::getAttributeList(int attribute)
{
	return lists[attribute];
}

int Inventory::getNumBooks(void){ return numBooks; }
int Inventory::getNumUsedBooks(void) const { return numUsedBooks; }

// search the books[] and usedBooks[] arrays for a book whose attribute matches value using Binary Search
Book * Inventory::searchAttribute(int attribute, string value) const 
{
	// Binary Search
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
	if (found)	// if a book is found return it
		return lists[attribute][position];
	else
		return nullptr;	// if not return nullptr to indicate failure
}
#endif

// after an attribute changes or a book is added or deleted this function is called to regenerate the sorted lists
void Inventory::updateLists()
{
	for (int i = 0; i < 8; i++)
	{
		delete lists[i];	// delete dynamically allocated list
		lists[i] = new Book*[numBooks + numUsedBooks];	// allocate a new array of book pointers at the size of all new and used books
		generateAttributeList(i, lists[i]);		// populate the new attribute list with all book pointer and sort by the respective attribute
	}
}

// search the given attributeList for all books that contain the given value substring. updates searchList and returns the number of books found
int Inventory::strSearch(int attribute, string value, Book** searchList)
{
	string tempStr;
	int counter = 0;
	for (int i = 0; i < numBooks; i++)	// for each book in books[]
	{
		tempStr = books[i]->getAttribute(attribute);	// get the appropriate attribute as a string
		if (tempStr.find(value) != -1)	// check if the value substring is with that attribute string
		{
			searchList[counter++]=books[i];	// if so, add the book to the searchResults and increment the found book counter
		}
	}
	for (int i = 0; i < numUsedBooks; i++)	// for each used book in usedBooks[]
	{
		tempStr = usedBooks[i]->getAttribute(attribute);	// get the appropriate attribute as a string
		if (tempStr.find(value) != -1)	// check if the value substring is with that attribute string
		{
			searchList[counter++] = usedBooks[i];	// if so, add the book to the searchResults and increment the found book counter
		}
	}
	return counter;
}

// deletes specified new book from books[], deletes the book, and resorts the attribute lists
void Inventory::deleteBook(Book* deletionBook)
{
	int deleteBookNum = deletionBook->getBookNumber(); // get the book number of the book to be deleted
	delete books[deleteBookNum];	// delete that book
	--numBooks;		// decrement the number of books
	for (int i = deleteBookNum; i < numBooks; i++)	// start at where the book was deleted and copy each book pointer from the index one more
	{
		books[i] = books[i + 1];
	}
	updateLists();	// update all the sorted lists to account for the deleted book
}

// reallocates memory to double the size of books[]
void Inventory::increaseNewArrSize()
{
	bookArrSize *= 2;	// double the size of the book array
	Book** tempBooks = new Book*[bookArrSize];	// dynamically allocate new array of book pointers with twice the memory
	for (int i = 0; i < numBooks; i++)	// for each book in books[]
	{
		tempBooks[i] = books[i];	// copy books to tempBooks[]
	}
	delete[] books;	// delete books[]
	books = new Book*[bookArrSize];	//  reallocate books[] with twice the memory
	for (int i = 0; i < numBooks; i++)	// copy each book back into books[]
	{
		books[i] = tempBooks[i];
	}
	delete[] tempBooks;	// delete temporary array of book pointers
}

// reallocates memory to double the size of books[]
void Inventory::increaseUsedArrSize()
{
	usedBookArrSize *= 2;	// double the size of the usedbook array
	UsedBook** tempBooks = new UsedBook*[usedBookArrSize];	// dynamically allocate new array of book pointers with twice the memory
	for (int i = 0; i < numUsedBooks; i++)	// for each book in usedBooks[]
	{
		tempBooks[i] = usedBooks[i];	// copy usedBooks to tempBooks[]
	}
	delete[] usedBooks;
	usedBooks = new UsedBook*[usedBookArrSize];		//  reallocate books[] with twice the memory
	for (int i = 0; i < usedBookArrSize; i++)	// copy each book back into usedBooks[]
	{
		usedBooks[i] = tempBooks[i];
	}
	delete[] tempBooks;	// delete temporary array of book pointers
}