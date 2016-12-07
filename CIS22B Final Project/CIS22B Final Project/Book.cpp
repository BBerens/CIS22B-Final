#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <ctime>
#include <fstream>
 
Book::Book(void)
{
	quantity = 0;
	dateAdded= time(NULL);
}

Book::Book(long long isbnIn)
{
	isbn = isbnIn;
	quantity = 0;
	dateAdded = time(NULL);
}

Book::~Book()
{
	;	// placeholder
}
string Book::getDateAddedStr(void) const
{ 
	char dateStr[8];
	struct tm dateInfo;
	localtime_s(&dateInfo, &dateAdded);
	strftime(dateStr, 8, "%d%b%y", &dateInfo);
	return dateStr;
}

void Book::writeToFile(fstream & file)
{
	file << isbn << '\t';
	file << title << '\t';
	file << author << '\t';
	file << publisher << '\t';
	file << quantity << '\t';
	file << wholesaleCost << '\t';
	file << retailPrice << '\t';
	file << dateAdded << endl;
}

fstream& operator << (fstream& file, Book& outBook)
{
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

fstream& operator >> (fstream& file, Book& inBook)
{
	long long tempIsbn;
	string tempStr;
	int tempInt;
	double tempDouble;
	time_t tempDate;

	getline(file, tempStr, '\t');
	tempIsbn = stoll(tempStr, nullptr, 10);
	inBook.isbn = tempIsbn;
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
	tempDouble = stod(tempStr, nullptr);
	inBook.wholesaleCost = tempDouble;
	getline(file, tempStr, '\t');
	tempDouble = stod(tempStr, nullptr);
	inBook.retailPrice = tempDouble;
	getline(file, tempStr, '\t');
	tempIsbn = stoll(tempStr, nullptr, 10);
	tempDate = static_cast<time_t>(tempIsbn);
	inBook.dateAdded = tempDate;
	return file;
}



time_t Book::getDateAdded(void) const { return dateAdded; }
void Book::setDateAdded(time_t value){ dateAdded = value; }
void Book::setIsbn(long long value){ isbn = value; }
long long Book::getIsbn(void) const{ return isbn; }
void Book::setTitle(string value){ title = value; }
string Book::getTitle(void) const{ return title; }
void Book::setAuthor(string value){ author = value; }
string Book::getAuthor(void) const{ return author; }
void Book::setPublisher(string value){ publisher = value; }
string Book::getPublisher(void) const{ return publisher; }

void Book::setQuantity(int value){ quantity = value; }
int Book::getQuantity(void) const{ return quantity; }
void Book::setWholesaleCost(double value){ wholesaleCost = value; }
double Book::getWholesaleCost(void) const{ return wholesaleCost; }
void Book::setRetailPrice(double value){ retailPrice = value; }
double Book::getRetailPrice(void) const { return retailPrice; }

string Book::getAttribute(int input) const
{
	string output;
	switch (input)
	{
	case (ISBN) :
		output = to_string(isbn);
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
		output = to_string(getWholesaleCost());
		break;
	case (RETAIL_PRICE) :
		output = to_string(getRetailPrice());
		break;
	case(DATE_ADDED) :
		output = to_string(dateAdded);
		break;
	case(QUANTITY) :
		output = to_string(quantity);
		break;
	default :
		output = "error";
	}
	return output;
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

void Book::setBookNumber(int bookNum)
{
	bookNumber = bookNum;
}

int Book::getBookNumber(void) const
{
	return bookNumber;
}

string Book::getBookType(void) const
{
	return "New";
}