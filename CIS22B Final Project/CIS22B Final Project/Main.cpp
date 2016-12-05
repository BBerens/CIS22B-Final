#define _CRT_SECURE_NO_WARNINGS
// CIS22B Final Project
// This is a test 
// This is another test
// Yet another test

#include <iostream>
#include <iomanip>
#include "Book.h"
#include "UsedBook.h"
#include "Inventory.h"
#include "Order.h"
#include <ctime>
#include <string>
#include <cstring>
#define TAX_RATE .0875


using namespace std;
// Function prototypes
void cashierModule(void);
void inventoryModule(void);
void reportModule(void);
void displayMainMenu(void);
void displayCashierScreen(Order *);
void displayInventoryMenu(void);
void displayBookInformationScreen(Book *);
void displayReportsMenu(void);
void displayBookLookup(void);
void displayAddBook(void);
void bookLookup(void);
void displayAttributeSearch(int);
void editBook(Book *, int);
void displayReport(int);
// access inventory class data 
Inventory inventory;
// create enum data type to hold data for book attributes
enum bookAttribute { ISBN, TITLE, AUTHOR, PUBLISHER, WHOLESALE_COST, RETAIL_PRICE, DATE_ADDED };


int main(void)
{
	int menuOption = -1;
	system("mode 120, 50");	// sets command prompt 100 chars wide and 50 chars tall
	//using while loop to prompt user to select the module they want to work with
	while (menuOption != 4)
	{
		displayMainMenu();
		cin >> menuOption;
		switch (menuOption)
		{
		case (1) :
			cashierModule();
			break;
		case (2) :
			inventoryModule();
			break;
		case (3) :
			reportModule();
			break;
		case (4) :
			break;
			// Prompt user to enter a valid choice
		default:
			cout << "That is not a valid choice. Please select from the menu.";
			system("pause");
		}
	}
	inventory.writeBooks();
	return 0;
}
// 
void cashierModule(void)
{
	Order newOrder;
	displayCashierScreen(&newOrder);
}



void displayMainMenu(void)
{
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                       Main Menu                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                1. Cashier Module                                                     *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                2. Inventory Database Module                                          *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                3. Report Module                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                4. Exit                                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< " Enter Your Choice:";

}

void displayCashierScreen(Order* currentOrder)
{
	// Create a book object for the current book
	Book * currentBook;

	// Create variables for total cost
	double subtotal = 0;
	double lineTotal = 0;
	double total;
	double tax;
	int purchaseQuantity;


	// Declare variables for cashier input
	string newInput; // Input book

	// Get the current system time
	time_t rawtime = time(NULL);
	struct tm now;
	localtime_s(&now, &rawtime);
	char dateStr[30];
	int bookCounter = 0; // Variable for below while loop
	strftime(dateStr, 30, "%d %b %Y %I:%M%p", &now);
	system("cls");
	// Collect user Input
	//cout << "Please enter the ISBN of the book you are buying: ";

	cin.ignore();

	while (1)
	{
		// Collect user Input
		cout << "Please enter the ISBN of the book you are buying: ";
		cout << "Enter [EXIT] if you are ready to checkout.";
		getline(cin, newInput);

		if (newInput == "EXIT")
			break;

		else{
			// Pull book data from the inventory class
			currentBook = inventory.searchAttribute(ISBN, newInput);

			if (currentBook != nullptr){
				// Return book data and verify user input is correct.  Otherwise collect user input again.
				cout << "You entered the following book:" << endl;
				cout << "ISBN: " << currentBook->getIsbn() << endl;
				cout << "Title: " << currentBook->getTitle() << endl;
				cout << "Author: " << currentBook->getAuthor() << endl;
				cout << "Publisher: " << currentBook->getPublisher() << endl;

				cout << "Please enter the quantity of " << currentBook->getTitle() << " that you wish to buy:";
				cin >> purchaseQuantity;
				try {

				if (purchaseQuantity > currentBook-> getQuantity()||purchaseQuantity < 0)
		//		if (!isdigit(purchaseQuantity))  // This is not working
					{
						string exceptionString = "Error: Invalid Quantity!";
						throw exceptionString;
					}

					currentOrder->addBook(currentBook, purchaseQuantity);
				}
				catch (string exceptionString)
				{
					cout << exceptionString << endl;
				}

				cin.ignore();
			}
			else{
				cout << "This ISBN is invalid, please try another ISBN: " << endl;
			}
		}
	}

	system("cls");
	// Display receipt
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*   Serendipity Book Sellers                                                                                           *"
		<< "*                                                                                                                      *"
		<< "*   Date: " << dateStr << "                                                                                          *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*   Qty   ISBN           Title                             Price               Total                                   *"
		<< "*   ___________________________________________________________________________________________________________________*";
	cout << endl;
	// using a while loop to call the function from order class
	while (bookCounter < currentOrder->getNumBooks())
	{
		currentBook = currentOrder->getBook(bookCounter);
		cout << fixed << setprecision(2);
		cout << "*" << setw(5) << right << currentOrder->getQuantity(bookCounter)
			<< setw(17) << right << currentBook->getIsbn() << "  "
			<< setw(33) << left << currentBook->getTitle().substr(0, 32)
			<< "$" << setw(14) << currentBook->getRetailPrice() << "     ";
		lineTotal = currentOrder->getQuantity(bookCounter) * currentBook->getRetailPrice();
		subtotal += currentOrder->getQuantity(bookCounter) * currentBook->getRetailPrice();
		bookCounter++;
		cout << "$" << setw(15) << lineTotal << "                         *";
		tax = subtotal*TAX_RATE;
		total = subtotal * (1 + TAX_RATE);
	}

	cout << "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                     Subtotal: $" << setw(6) << right
		<< subtotal << "                                                                                *"
		<< "*                     Tax:      $" << setw(6) << right
		<< tax << "                                                                                *"
		<< "*                     Total:    $" << setw(6) << right
		<< total << "                                                                                *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*  Thank You for Shopping at Serendipity!                                                                              *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< endl;
	system("pause");

}

void inventoryModule(void)
{
	int menuOption = -1;
	while (menuOption != 5)
	{
		displayInventoryMenu();
		cin >> menuOption;
		cin.ignore();
		switch (menuOption)
		{
		case (1) :
			bookLookup();
			break;
		case (2) :
			displayAddBook();
			break;
		case (3) :
			//displayEditBook();
			break;
		case (4) :
			break;
		case (5) :
			break;
		default:
			cout << "That is not a valid option. Please select from the menu.";
		}
	}
}

void bookLookup(void)
{
	int attributeSelection;
	Book * foundBook;
	displayBookLookup();
	cin >> attributeSelection;
	cin.ignore();
	while (attributeSelection != 5)
	{
		displayAttributeSearch(attributeSelection - 1);
		cin >> attributeSelection;
		cin.ignore();
	}
}

void displayAttributeSearch(int attribute)
{
	string attributeStr;
	string inputValue;
	Book ** searchResults;
	int bookSelection, attributeSelection;
	int numBooksFound;

	switch (attribute)
	{
	case (ISBN) :
		attributeStr = "ISBN";
		break;
	case (TITLE) :
		attributeStr = "Title";
		break;
	case (AUTHOR) :
		attributeStr = "Author";
		break;
	case (PUBLISHER) :
		attributeStr = "Publisher";
		break;
	case (WHOLESALE_COST) :
		attributeStr = "Wholesale Cost";
		break;
	case (RETAIL_PRICE) :
		attributeStr = "Retail Price";
		break;
	default:
		return;
	}

	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                   " << attributeStr << " Search" << endl;
	cout << "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*  Enter the " << attributeStr << " to search for: ";
	getline(cin, inputValue, '\n');
	cout << "************************************************************************************************************************"
		<< "                                                                          New/                Wholesale Retail   Date   "
		<< "# ISBN           Title                      Author         Publisher      Used  Condition Qty   Cost     Price   Added  "
		<< "************************************************************************************************************************";
	searchResults = new Book*;
	numBooksFound = inventory.strSearch(attribute, inputValue, searchResults);
	if (numBooksFound == 0)
	{
		cout << "No Books Found";
		system("pause");
		displayBookLookup();
	}
	else
	{
		for (int i = 0; i < numBooksFound; i++)
		{
			cout << i + 1 << " ";
			searchResults[i]->print();
		}
		cout << "************************************************************************************************************************"
			<< "Select the book you would like to view by its number on the left:";
		cin >> bookSelection;
		cin.ignore();
		displayBookInformationScreen(searchResults[bookSelection - 1]);
		cin >> attributeSelection;
		cin.ignore();
		if (attributeSelection != 9)
		{
			editBook(searchResults[bookSelection - 1], attributeSelection);
			displayBookLookup();
		}

		/*for (int i = 0; i < numBooksFound; i++)
		{
			delete searchResults[i];
		}*/
	}
}

void editBook(Book * editBook, int attribute)
{
	string tempStr;
	long long tempISBN;
	int tempInt;
	double tempDouble;
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                    Book Information                                                  *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< "*  ISBN: " << setw(110) << editBook->getIsbn() << "*"
		<< "*  Title: " << setw(109) << editBook->getTitle().substr(0, 109) << "*"
		<< "*  Author: " << setw(108) << editBook->getAuthor() << "*"
		<< "*  Publisher: " << setw(105) << editBook->getPublisher() << "*"
		<< "*  Date Added: " << setw(104) << editBook->getDateAddedStr() << "*"
		<< "*  Quantity On-hand: " << setw(98) << editBook->getQuantity() << "*"
		<< "*  Wholesale Cost: $" << setw(99) << fixed << setprecision(2) << editBook->getWholesaleCost() << "*"
		<< "*  Retail Price: $" << setw(101) << fixed << setprecision(2) << editBook->getRetailPrice() << "*"
		<< "*                                                                                                                      *"
	    << "************************************************************************************************************************";
	switch (attribute)
	{
	case (1) :
		cout << "Enter the new ISBN for this book: ";
		getline(cin, tempStr);
		tempISBN = stoll(tempStr);
		editBook->setIsbn(tempISBN);
		inventory.generateAttributeList(ISBN);
		break;
	case (2) :
		cout << "Enter the new Title for this book: ";
		getline(cin, tempStr);
		editBook->setTitle(tempStr);
		//inventory.generateISBNList(); need to resort by title
		break;
	case (3) :
		cout << "Enter the new Author for this book: ";
		getline(cin, tempStr);
		editBook->setAuthor(tempStr);
		//inventory.generateISBNList(); need to resort by author
		break;
	case (4) :
		cout << "Enter the new Publisher for this book: ";
		getline(cin, tempStr);
		editBook->setPublisher(tempStr);
		//inventory.generateISBNList(); need to resort by publisher
		break;
	case(5) :
		//This is tricky. Need to get date added in specific format and convert it to time_t
		break;
	case(6) :
		cout << "Enter the new Quantity On-hand for this book: ";
		getline(cin, tempStr);
		tempInt = stoi(tempStr);
		editBook->setQuantity(tempInt);
		//inventory.generateISBNList(); need to resort by Quantity? Maybe not. This changes all the time. Sort when you need it
		break;
	case(7) :
		cout << "Enter the new Wholesale Cost for this book: ";
		getline(cin, tempStr);
		tempDouble = stod(tempStr);
		editBook->setWholesaleCost(tempDouble);
		//inventory.generateISBNList(); need to resort by wholesale cost
	case(8) :
		cout << "Enter the new Retail Price for this book: ";
		getline(cin, tempStr);
		tempDouble = stod(tempStr);
		editBook->setRetailPrice(tempDouble);
		//inventory.generateISBNList(); need to resort by retail price
	case(9) :
		break;
	default:
		cout << "That is not a valid option. Please try again.";
		system("pause");
	}
	inventory.updateLists();
}
void displayBookLookup(void)
{
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                      Book Lookup                                                     *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                               Search by:                                                             *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                1. ISBN                                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                2. Title                                                              *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                3. Author                                                             *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                4. Publisher                                                          *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                5. Return to Previous Menu                                            *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< " Enter Your Choice:";
}

void displayAddBook(void)
{
	string userInput;
	Book* currentBook;
	int condition;
	system("cls");
	cout << "Enter 'N' for a new book and 'U' for a used book and press enter: ";
	cin >> userInput;
	cin.ignore();
	while (userInput != "N" && userInput != "n" && userInput != "U" && userInput != "u")
	{
		cout << "That is not a valid entry.";
		cout << "Enter 'N' for a new book and 'U' for a used book and press enter: ";
		cin >> userInput;
		cin.ignore();

	}
	if (userInput == "U" || userInput == "u")
	{
		cout << "Please enter the condition of the book from the menu and press enter." << endl;
		cout << "1: Like new, no visible damage." << endl;
		cout << "2: Good condition, small folds in pages, slightly worn cover." << endl;
		cout << "3. Fair condition, obvious sign of usage, crease in binding or cover." << endl;
		cout << "4. Poor condition, significant wear, possible water marks or ripped pages." << endl;
		cin >> condition;
		cin.ignore();
		currentBook = inventory.addUsedBook(condition);
	}
	else
	{
		currentBook = inventory.addBook();
	}
	cout << "Enter the 13 digit ISBN for the book to be added or press q and press enter to quit: ";
	getline(cin, userInput); // check for quit and follow up actions, also needs formatting
	currentBook->setIsbn(strtoll(userInput.c_str(), nullptr, 10)); // doesn't perform any checks on what the user inputs. Needs to be broken up
	cout << "Enter the title of the book or press q and press enter to quit: ";
	getline(cin, userInput); // check less than 200 chars. Or whatever the max is.
	currentBook->setTitle(userInput);
	cout << "Enter the name of the author of the book or press q and press enter to quit: "; // what do I do if they want to enter multiple authors?
	getline(cin, userInput);
	currentBook->setAuthor(userInput);
	cout << "Enter the publisher of the book or press q and press enter to quit: ";
	getline(cin, userInput);
	currentBook->setPublisher(userInput);
	cout << "Enter the wholesale cost of the book or press q and press enter to quit: ";
	getline(cin, userInput);
	currentBook->setWholesaleCost(strtod(userInput.c_str(), nullptr));
	cout << "Enter the retail price of the book or press q and press enter to quit: ";
	getline(cin, userInput);
	currentBook->setRetailPrice(strtod(userInput.c_str(), nullptr));
	inventory.updateLists();
}

void displayInventoryMenu(void)
{
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                    Inventory Menu                                                    *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                1. Search Books                                                       *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                2. Add a Book                                                         *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                3. Edit a Book's Record                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                4. Delete a Book                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                5. Return to the Main Menu                                            *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< " Enter Your Choice:";
}

void displayBookInformationScreen(Book * displayBook)
{
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                   Book Information                                                   *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< "*  ISBN: " << setw(110) << displayBook->getIsbn() << "*"
		<< "*  Title: " << setw(109) << displayBook->getTitle().substr(0,109) << "*"
	    << "*  Author: " << setw(108) << displayBook->getAuthor() << "*"
	    << "*  Publisher: " << setw(105) <<  displayBook->getPublisher() << "*"
	    << "*  Date Added: " << setw(104) << displayBook->getDateAddedStr() << "*"
	    << "*  Quantity On-hand: " << setw(98) << displayBook->getQuantity() << "*"
		<< "*  Wholesale Cost: $" << setw(99) << fixed << setprecision(2) << displayBook->getWholesaleCost() << "*"
		<< "*  Retail Price: $" << setw(101) << fixed << setprecision(2) << displayBook->getRetailPrice() << "*"
	    << "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*   Select the record you would like to change:                                                                        *"
		<< "*                                                                                                                      *"
		<< "*   1. ISBN                                                                                                            *"
		<< "*                                                                                                                      *"
		<< "*   2. Title                                                                                                           *"
		<< "*                                                                                                                      *"
		<< "*   3. Author                                                                                                          *"
		<< "*                                                                                                                      *"
		<< "*   4. Publisher                                                                                                       *"
		<< "*                                                                                                                      *"
		<< "*   5. Date Added                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*   6. Quantity On-Hand                                                                                                *"
		<< "*                                                                                                                      *"
		<< "*   7. Wholesale Cost                                                                                                  *"
		<< "*                                                                                                                      *"
		<< "*   8. Retail Price                                                                                                    *"
		<< "*                                                                                                                      *"
		<< "*   9. Return to Previous Menu                                                                                         *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************";
}

void reportModule(void)
{
	int menuOption;
	displayReportsMenu();
	cin >> menuOption;
	displayReport(menuOption);
}
void displayReportsMenu(void)
{
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                        Reports                                                       *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                1. ISBN Listing                                                       *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                2. Title Listing                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                3. Author Listing                                                     *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                4. Publisher Listing                                                  *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                5. Listing by Wholesale Cost                                          *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                6. Listing by Retail Price                                            *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                7. Listing by Age                                                     *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                8. Return to the Main Menu                                            *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< " Enter your choice:";

}

void displayReport(int listSelection)
{
	Book** bookList = inventory.getAttributeList(listSelection - 1);
	system("cls");
	cout << "************************************************************************************************************************"
		<< "                                                                          New/                Wholesale Retail   Date   "
		<< "# ISBN           Title                      Author         Publisher      Used  Condition Qty   Cost     Price   Added  "
		<< "************************************************************************************************************************";
	for (int i = 0; i < inventory.getNumBooks()+inventory.getNumUsedBooks(); i++)
	/*if (listSelection == 1)
	{
		sortIsbnArray(inventory.getAttributeList(listSelection - 1), (listSelection - 1));
	}
	if (listSelection == 2)
	{
		sortTitleArray(inventory.getAttributeList(listSelection - 1), (listSelection - 1));
	}
	if (listSelection == 3)
	{
		sortRetailValueArray(inventory.getAttributeList(listSelection - 1), (listSelection - 1));
	}
	if (listSelection == 4)
	{
		sortQuantityArray(inventory.getAttributeList(listSelection - 1), (listSelection - 1));
	}
	if (listSelection == 5)
	{
		sortWholesaleCostArray(inventory.getAttributeList(listSelection - 1), (listSelection - 1));
	}
	if (listSelection == 6)
	{
		sortAgeArray(inventory.getAttributeList(listSelection - 1), (listSelection - 1));
	}*/
	//for (int i = 0; i < inventory.getNumBooks(); i++)
	{
		cout << i + 1 << " ";
		bookList[i]->print();
	}
	system("pause");
}
/*
void sortIsbnArray(Book* array[], int size)
{
	bool swap;
	Book* temp;

	do
	{
		swap = false;
		for (int count = 0; count < (size - 1); count++)
		{
			if ((*array[count]).isbn > (*array[count + 1]).isbn)
			{
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}
void sortTitleArray(Book* array[], int size)
{
	bool swap;
	Book* temp;

	do
	{
		swap = false;
		for (int count = 0; count < (size - 1); count++)
		{
			if ((*array[count]).title > (*array[count + 1]).title)
			{
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}

//The result is the same as WholesaleCost sorting. Why??
void sortRetailValueArray(Book* array[], int size)
{
	bool swap;
	Book* temp;

	do
	{
		swap = false;
		for (int count = 0; count < (size - 1); count++)
		{
			if ((*array[count]).retailPrice > (*array[count + 1]).retailPrice)
			{
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}

void sortQuantityArray(Book* array[], int size)
{
	bool swap;
	Book* temp;

	do
	{
		swap = false;
		for (int count = 0; count < (size - 1); count++)
		{
			if ((*array[count]).quantity > (*array[count + 1]).quantity)
			{
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}
void sortWholesaleCostArray(Book* array[], int size)
{
	bool swap;
	Book* temp;

	do
	{
		swap = false;
		for (int count = 0; count < (size - 1); count++)
		{
			if ((*array[count]).wholesaleCost > (*array[count + 1]).wholesaleCost)
			{
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}
//Program will break if do Age sorting. Why??
void sortAgeArray(Book* array[], int size)
{
	bool swap;
	Book* temp;

	do
	{
		swap = false;
		for (int count = 0; count < (size - 1); count++)
		{
			if ((*array[count]).dateAdded > (*array[count + 1]).dateAdded)
			{
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}*/
//Also, our report module list is different from the instruction. Should we change our report list??
//I'm trying to fix the format of report module... 