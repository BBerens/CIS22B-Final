#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ctime>
#include <iostream>
#include <iomanip>


using namespace std;

class Book
{
protected:
	long long isbn;		
	string title;
	string author;
	string publisher;
	int quantity;
	int bookNumber;
	double wholesaleCost;
	double retailPrice;
	time_t dateAdded;
	int bookType;
	enum bookAttribute { ISBN, TITLE, AUTHOR, PUBLISHER, WHOLESALE_COST, RETAIL_PRICE, DATE_ADDED, QUANTITY };
	// bookAttribute enum is used in getAttribute function to tell what attribute you want to get

public:
	static unsigned int numBooks;
	Book();	// Default Constructor
	Book(long long);	// Overloaded Constructor
	virtual ~Book(){};	// Destructor

	// Setters
	void setIsbn(long long);
	void setTitle(string);
	void setAuthor(string);
	void setPublisher(string);
	void setQuantity(int);
	void setWholesaleCost(double);
	void setRetailPrice(double);
	void setDateAdded(time_t);
	void setBookNumber(int);

	// Getters
	long long getIsbn(void) const;
	string getTitle(void) const;
	string getAuthor(void) const;
	string getPublisher(void) const;
	time_t getDateAdded(void) const;		// used to write to file
	int getQuantity(void) const;
	virtual double getWholesaleCost(void) const;	
	virtual double getRetailPrice(void) const;
	int getBookNumber(void) const;
	virtual string getBookType(void) const;
	string getDateAddedStr(void) const;		// used to print readable dates
	string getAttribute(int) const;
	
	 

	virtual void print(void);	// prints book attributes to stream
	friend fstream& operator << (fstream&, Book&);	// left shift operator overload
	friend fstream& operator >> (fstream&, Book&);	// right shift operator overload
	virtual void printCashier(void);
};

#endif