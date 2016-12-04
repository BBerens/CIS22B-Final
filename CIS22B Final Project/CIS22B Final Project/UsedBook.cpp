#define _CRT_SECURE_NO_WARNINGS
#include "UsedBook.h"

UsedBook::UsedBook() : Book(){};
UsedBook::UsedBook(int n1) : Book()
{ 
	bookCondition = static_cast<condition>(n1); 
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
	return retailPrice * 0.8 - (bookCondition * 0.1);
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
	cout << setw(13) << isbn;
	cout << "  " << setw(25) << left << title.substr(0, 25);
	cout << setw(15) << left << author.substr(0, 15);
	cout << setw(15) << left << publisher.substr(0, 15);
	cout << " " << setw(3) << quantity;
	cout << " ";
	switch (bookCondition)
	{
	case(LIKE_NEW) :
		cout << "Like New";
		break;
	case(GOOD) :
		cout << "Good    ";
		break;
	case(FAIR) :
		cout << "Fair    ";
		break;
	case(POOR) :
		cout << "Poor    ";
		break;
	default:
		cout << "        ";
	}
	cout << " " << fixed << setprecision(2) << retailPrice;
	cout << " " << setw(10) << getDateAddedStr() << endl;
}