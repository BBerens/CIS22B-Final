#define _CRT_SECURE_NO_WARNINGS
#include "UsedBook.h"

UsedBook::UsedBook() : Book(){};
UsedBook::UsedBook(int n1) : Book()
{ 
	bookCondition = static_cast<condition>(n1); 
}

UsedBook::UsedBook(Book* bookPtr) : Book()
{
	isbn = bookPtr->getIsbn();
	title = bookPtr->getTitle();
	author = bookPtr->getAuthor();
	publisher = bookPtr->getPublisher();
	quantity = bookPtr->getQuantity();
	wholesaleCost = bookPtr->Book::getWholesaleCost();
	retailPrice = bookPtr->Book::getRetailPrice();
	dateAdded = bookPtr->getDateAdded();
}

UsedBook::~UsedBook(){ Book::~Book(); }

void UsedBook::setCondition(int n1)
{
	bookCondition = static_cast<condition>(n1);
}
int UsedBook::getCondition(void) const
{
	return bookCondition;
}

double UsedBook::getRetailPrice(void) const
{
	return retailPrice * (0.8 - (bookCondition * 0.1));
}

double UsedBook::getWholesaleCost(void) const
{
	return retailPrice * 0.25;
}

fstream& operator << (fstream& file, UsedBook& outBook)
{
	file << (Book)outBook;
	file << '\t' << outBook.bookCondition;
	return file;
}

fstream& operator >> (fstream& file, UsedBook& inBook)
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
	getline(file, tempStr, '\n');
	inBook.bookCondition = static_cast<UsedBook::condition>(stoi(tempStr));
	return file;
}

void UsedBook::print(void)
{
	cout << setw(13) << left << isbn;
	cout << "  " << setw(26) << left << title.substr(0, 25);
	cout << setw(15) << left << author.substr(0, 14);
	cout << setw(13) << left << publisher.substr(0, 13);
	cout << " Used  ";
	switch (bookCondition)
	{
	case(LIKE_NEW) :
		cout << "Like New ";
		break;
	case(GOOD) :
		cout << "Good     ";
		break;
	case(FAIR) :
		cout << "Fair     ";
		break;
	case(POOR) :
		cout << "Poor     ";
		break;
	default:
		cout << "         ";
	}
	cout << setw(3) << quantity;
	cout << "  $" << right << fixed << setw(6) << setprecision(2) << getWholesaleCost();
	cout << "   $" << fixed << setw(6) << setprecision(2) << getRetailPrice();
	cout << setw(9) << right << getDateAddedStr() << endl;
}

void UsedBook::printCashier(void)
{
	cout << setw(13) << left << isbn;
	cout << "  " << setw(26) << left << title.substr(0, 25);
	cout << setw(15) << left << author.substr(0, 14);
	cout << setw(13) << left << publisher.substr(0, 13);
	cout << " Used  ";
	switch (bookCondition)
	{
	case(LIKE_NEW) :
		cout << "Like New ";
		break;
	case(GOOD) :
		cout << "Good     ";
		break;
	case(FAIR) :
		cout << "Fair     ";
		break;
	case(POOR) :
		cout << "Poor     ";
		break;
	default:
		cout << "         ";
	}
	cout << "   $" << fixed << setw(6) << setprecision(2) << getRetailPrice();
	cout << setw(9) << right << getDateAddedStr() << endl;
}