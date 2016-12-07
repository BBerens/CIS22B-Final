#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <ctime>	// needed for time functionality associated with dateAdded
#include <fstream>	// needed for << and >> operator overloading
 
Book::Book(void)	// default constructor
{
	quantity = 0;	// initialize to 0 copies on-hand
	dateAdded= time(NULL);	// set time to time of construction (dateAdded)
}

Book::Book(long long isbnIn)	// constructor initializing ISBN
{
	isbn = isbnIn;	// set ISBN 
	quantity = 0;	// initiliaze to 0 copies on-hand
	dateAdded = time(NULL);	// // set time to time of construction (dateAdded)
}

// Setters
void Book::setIsbn(long long value){ isbn = value; }
void Book::setTitle(string value){ title = value; }
void Book::setAuthor(string value){ author = value; }
void Book::setPublisher(string value){ publisher = value; }
void Book::setQuantity(int value){ quantity = value; }
void Book::setWholesaleCost(double value){ wholesaleCost = value; }
void Book::setRetailPrice(double value){ retailPrice = value; }
void Book::setDateAdded(time_t value){ dateAdded = value; }
void Book::setBookNumber(int bookNum){ bookNumber = bookNum; }

// Getters
long long Book::getIsbn(void) const{ return isbn; }
string Book::getTitle(void) const{ return title; }
string Book::getAuthor(void) const{ return author; }
string Book::getPublisher(void) const{ return publisher; }
time_t Book::getDateAdded(void) const { return dateAdded; }
int Book::getQuantity(void) const{ return quantity; }
double Book::getWholesaleCost(void) const{ return wholesaleCost; }
double Book::getRetailPrice(void) const { return retailPrice; }
int Book::getBookNumber(void) const { return bookNumber; }
string Book::getBookType(void) const { return "New"; }
string Book::getDateAddedStr(void) const
{
	char dateStr[8];	// allocate a char array
	struct tm dateInfo;		// declare a tm struct
	localtime_s(&dateInfo, &dateAdded);	// convert dateAdded in time_t datatype to dateInfo in tm struct
	strftime(dateStr, 8, "%d%b%y", &dateInfo);	// convert dateInfo in tm format to char array dateStr as defined by "%d%b%y"
	return dateStr;		// return char array
}

// takes an int parameter which is associated with a specific attribute
// selects the correct attribute and converts to string if necessary
string Book::getAttribute(int input) const
{
	string output;	// what we return
	switch (input)	// switch on the parameter
	{
	case (ISBN) :
		output = to_string(isbn);	//convert from long long to string
		break;
	case (TITLE) :
		output = title;
		break;
	case (AUTHOR) :
		output = author;
		break;
	case (PUBLISHER) :
		output = publisher;
		break;
	case (WHOLESALE_COST) :
		output = to_string(getWholesaleCost());	// convert from double to string
		break;
	case (RETAIL_PRICE) :
		output = to_string(getRetailPrice());	// convert from double to string
		break;
	case(DATE_ADDED) :
		output = to_string(dateAdded);		// convert from time_t to string (note this is not the same as getDateAddedStr) this returns the digits of time_t to string
		break;
	case(QUANTITY) :
		output = to_string(quantity);	// convert from int to string
		break;
	default:
		output = "error";	// something went wrong and you asked for an incorrect attribute
	}
	return output;
}

// overload the left shift operator to write book attributes to file
fstream& operator << (fstream& file, Book& outBook)		
{
	// data attributes are tab-delimited
	file << outBook.isbn << '\t';
	file << outBook.title << '\t';
	file << outBook.author << '\t';
	file << outBook.publisher << '\t';
	file << outBook.quantity << '\t';
	file << outBook.wholesaleCost << '\t';
	file << outBook.retailPrice << '\t';
	file << outBook.dateAdded << '\t';
	return file;
}

// overload the right shift operator to read in book attributes from a file to a book
fstream& operator >> (fstream& file, Book& inBook)		
{
	
	long long tempLongLong;
	string tempStr;
	int tempInt;
	double tempDouble;
	time_t tempDate;

	// each attribute is tab delimited so we read to each tab. convert and store the value and discard the tab
	getline(file, tempStr, '\t');
	tempLongLong = stoll(tempStr, nullptr, 10);	// convert to long long base 10
	inBook.isbn = tempLongLong;
	getline(file, tempStr, '\t');
	inBook.title = tempStr;
	getline(file, tempStr, '\t');
	inBook.author = tempStr;
	getline(file, tempStr, '\t');
	inBook.publisher = tempStr;
	getline(file, tempStr, '\t');
	tempInt = stoi(tempStr);
	inBook.quantity = tempInt;
	getline(file, tempStr, '\t');
	tempDouble = stod(tempStr, nullptr);	// convert to double
	inBook.wholesaleCost = tempDouble;
	getline(file, tempStr, '\t');
	tempDouble = stod(tempStr, nullptr);	// conver to double
	inBook.retailPrice = tempDouble;
	getline(file, tempStr, '\t');
	tempLongLong = stoll(tempStr, nullptr, 10);	// convert to long long base 10
	tempDate = static_cast<time_t>(tempLongLong);	// cast long long to time_t format
	inBook.dateAdded = tempDate;
	return file;
}

void Book::print(void)
{
	cout << setw(13) << isbn;
	cout << "  " << setw(26) << left << title.substr(0,25);
	cout << setw(15) << left << author.substr(0, 14);
	cout << setw(13) << left << publisher.substr(0, 13);
	cout << " New            " << setw(3) << quantity;
	cout << "  $" << right << fixed << setw(6) << setprecision(2) << wholesaleCost;
	cout << "   $" << fixed << setw(6) << setprecision(2) << retailPrice;
	cout << right << setw(9) << getDateAddedStr() << endl;
}

void Book::printCashier(void)
{
	cout << setw(13) << isbn;
	cout << "  " << setw(26) << left << title.substr(0, 25);
	cout << setw(15) << left << author.substr(0, 14);
	cout << setw(20) << left << publisher.substr(0, 13) << setw(10) << "New";
	cout << "  $" << fixed << setw(6) << setprecision(2) << retailPrice;
	cout << right << setw(9) << getDateAddedStr() << endl;
}