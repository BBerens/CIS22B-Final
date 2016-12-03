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
	string tempStr;
	file >> (Book)inBook;
	getline(file, tempStr, '\n');
	inBook.bookCondition = static_cast<UsedBook::condition>(stoi(tempStr));
	return file;
}