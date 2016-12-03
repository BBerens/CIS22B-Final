#define _CRT_SECURE_NO_WARNINGS
#include "Edition.h"
#include <ctime>
#include <fstream>

Edition::Edition(void)
{
	quantity = 0;
	dateAdded = time(NULL);
}

Edition::Edition(long long isbnIn)
{
	isbn = isbnIn;
	quantity = 0;
	dateAdded = time(NULL);
}
string Edition::getDateAddedStr(void) const
{
	char dateStr[26];
	ctime_s(dateStr, sizeof(dateStr), &dateAdded);
	return dateStr;
}

void Edition::writeToFile(fstream & file)
{
	file << isbn << ",";
	file << title << ",";
	file << author << ",";
	file << publisher << ",";
	file << wholesaleCost << ",";
	file << retailPrice << ",";
	file << dateAdded << endl;
}

fstream& operator << (fstream& file, Edition& outEdition)
{
	file << outEdition.isbn << ",";
	file << outEdition.title << ",";
	file << outEdition.author << ",";
	file << outEdition.publisher << ",";
	file << outEdition.wholesaleCost << ",";
	file << outEdition.retailPrice << ",";
	file << outEdition.dateAdded << endl;
	return file;
}

fstream& operator >> (fstream& file, Edition& inEdition)
{
	long long tempIsbn;
	string tempStr;
	double tempDouble;
	time_t tempDate;

	getline(file, tempStr, ',');
	if (tempStr != "")
	{
		tempIsbn = stoll(tempStr, nullptr, 10);
		inEdition.isbn = tempIsbn;
		getline(file, tempStr, ',');	// messes up if there is a ',' in the title, need to choose a different char
		inEdition.title = tempStr;
		getline(file, tempStr, ',');
		inEdition.author = tempStr;
		getline(file, tempStr, ',');
		inEdition.publisher = tempStr;
		getline(file, tempStr, ',');
		tempDouble = stod(tempStr, nullptr);
		inEdition.wholesaleCost = tempDouble;
		getline(file, tempStr, ',');
		tempDouble = stod(tempStr, nullptr);
		inEdition.retailPrice = tempDouble;
		getline(file, tempStr, '\n');
		tempIsbn = stoll(tempStr, nullptr, 10);
		tempDate = static_cast<time_t>(tempIsbn);
		inEdition.dateAdded = tempDate;
	}
	return file;
}



time_t Edition::getDateAdded(void) const { return dateAdded; }
void Edition::setDateAdded(time_t value){ dateAdded = value; }
void Edition::setIsbn(long long value){ isbn = value; }
long long Edition::getIsbn(void) const{ return isbn; }
void Edition::setPublisher(string value){ publisher = value; }
string Edition::getPublisher(void) const{ return publisher; }

void Edition::setQuantity(int value){ quantity = value; }
int Edition::getQuantity(void) const{ return quantity; }
void Edition::setWholesaleCost(double value){ wholesaleCost = value; }
double Edition::getWholesaleCost(void) const{ return wholesaleCost; }
void Edition::setRetailPrice(double value){ retailPrice = value; }
double Edition::getRetailPrice(void) const { return retailPrice; }

string Edition::getAttribute(int input) const
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
		output = to_string(wholesaleCost);
		break;
	case (RETAIL_PRICE) :
		output = to_string(retailPrice);
		break;
	case(DATE_ADDED) :
		output = to_string(dateAdded);
		break;
	default:
		output = "error";
	}
	return output;
}