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
	double wholesaleCost;
	double retailPrice;
	time_t dateAdded;
	enum bookAttribute { ISBN, TITLE, AUTHOR, PUBLISHER, WHOLESALE_COST, RETAIL_PRICE, DATE_ADDED };

public:
	static unsigned int numBooks;
	Book();	// Default Constructor
	Book(long long);	// Overloaded Constructor
	virtual ~Book();			// Destructor

	// Setters
	void setIsbn(long long);
	void setTitle(string);
	void setAuthor(string);
	void setPublisher(string);
	void setQuantity(int);
	void setWholesaleCost(double);
	void setRetailPrice(double);
	void setDateAdded(time_t);

	// Getters
	long long getIsbn(void) const;
	string getTitle(void) const;
	string getAuthor(void) const;
	string getPublisher(void) const;
	string getDateAddedStr(void) const;
	time_t getDateAdded(void) const;
	int getQuantity(void) const;
	double getWholesaleCost(void) const;
	virtual double getRetailPrice(void) const;
	string getAttribute(int) const;

	virtual void print(void);
	void writeToFile(fstream&);
	friend fstream& operator << (fstream&, Book&);
	friend fstream& operator >> (fstream&, Book&);
	friend void sortIsbnArray(Book* array[], int size);
	friend void sortTitleArray(Book* array[], int size);
	friend void sortRetailValueArray(Book* array[], int size);
	friend void sortQuantityArray(Book* array[], int size);
	friend void sortWholesaleCostArray(Book* array[], int size);
	friend void sortAgeArray(Book* array[], int size);
};

#endif