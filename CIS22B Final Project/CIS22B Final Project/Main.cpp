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
#define TAX_RATE .0875


using namespace std;

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
void displayEditBook(Book *);
void bookLookup(void);
Book* displayAttributeSearch(int);
void editBook(Book *, int);
void displayReport(int);

Inventory inventory;
enum bookAttribute { ISBN, TITLE, AUTHOR, PUBLISHER, WHOLESALE_COST, RETAIL_PRICE, DATE_ADDED };


int main(void)
{
	int menuOption = -1;
	system("mode 120, 50");	// sets command prompt 100 chars wide and 50 chars tall

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
		default:
			cout << "That is not a valid choice. Please select from the menu.";
			system("pause");
		}
	}
	inventory.writeBooks();
	return 0;
}

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
		<< "*                                      Serendipity Booksellers                                                         *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                             Main Menu                                                                *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                      1. Cashier Module                                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                      2. Inventory Database Module                                                    *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                      3. Report Module                                                                *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                      4. Exit                                                                         *"
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
	double total;
	int quantity;

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
	// Output cashier screen
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*   Serendipity Book Sellers                                                                                           *"
		<< "*                                                                                                                      *"
		<< "*   Date: " << dateStr << "			                                                                       *";

		// Collect user Input

	while (1)
	{
		// Collect user Input
		cout << "*   Please enter the ISBN of the book you are buying.                                                                  *";
		cout << "*	 Press q when you have completed the transaction.																	  \n*";
		cin.ignore();
		getline(cin, newInput);

		if (newInput == "q")
			break;

		else{
			// Pull book data from the inventory class
			currentBook = inventory.searchAttribute(ISBN, newInput);

			// Return book data and verify user input is correct.  Otherwise collect user input again.
			cout << "You entered the following book:" << endl;
			cout << "************************************************************************************************************************"
				<< "*  ISBN: " << currentBook->getIsbn() << endl;
			cout << "*  Title: " << currentBook->getTitle() << endl;
			cout << "*  Author: " << currentBook->getAuthor() << endl;
			cout << "*  Publisher: " << currentBook->getPublisher() << endl;
			cout << "*" << endl;


			cout << "Please enter the quantity of " << currentBook->getTitle() << " that you wish to buy.";
			cin >> quantity;

			currentOrder->addBook(currentBook, quantity);
			// Debug Statement
		}
	}

	// Keep this commented for now while testing

	while (bookCounter < currentOrder->getNumBooks())
	{
		currentBook = currentOrder->getBook(bookCounter);
		cout << fixed << setprecision(2);
		subtotal += currentOrder->getQuantity(bookCounter) * currentBook->getRetailPrice();
		bookCounter++;
	}

	total = subtotal * (1 + TAX_RATE);
	cout << "Your subtotal is: " << subtotal << endl;
	cout << "Your total cost today is: " << total << endl;
	cout << "Thank you for choosing serndepity books." << endl;

	/*
	while (bookCounter < currentOrder->getNumBooks())
	{
	currentBook = currentOrder->getBook(bookCounter);
	cout << "*" << setw(6) << currentOrder->getQuantity(bookCounter)
	<< setw(14) << currentBook->getIsbn()
	<< setw(60) << currentBook->getTitle()
	<< setw(8) << fixed << setprecision(2) << currentBook->getRetailPrice()
	<< setw(8) << fixed << setprecision(2) << currentOrder->getQuantity(bookCounter) * currentBook->getRetailPrice() << "*";
	bookCounter++;
	}
	*/

	system("pause");	// Debug Statement
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
	int menuOption = -1;
	int subMenuOption;
	Book * foundBook;
	while (menuOption != 5)
	{
		subMenuOption = -1;
		displayBookLookup();
		cin >> menuOption;
		cin.ignore();
		if (menuOption != 5) // Horrible. Needs to be done properly.
		{
			while (subMenuOption != 9)
			{
				foundBook = displayAttributeSearch(menuOption - 1);
				cin >> subMenuOption;
				cin.ignore();
				if (subMenuOption != 9)
					editBook(foundBook, subMenuOption);
			}
		}
	}
}

Book* displayAttributeSearch(int attribute)
{
	string attributeStr;
	string inputValue;
	Book * foundBook;

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
		return nullptr;
	}

	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                            " << attributeStr << " Search" << endl;
	cout << "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*  Enter the " << attributeStr << " to search for: ";
	getline(cin, inputValue, '\n');
	foundBook = inventory.searchAttribute(attribute, inputValue);
	if (foundBook != nullptr)
	{
		cout << "Here's an extra output to test the function: " << foundBook->getIsbn() << endl; // Debug Statement
		cout << "****************************************************************************************************"
			<< "*  ISBN: " << foundBook->getIsbn() << endl;
		cout << "*  Title: " << foundBook->getTitle() << endl;
		cout << "*  Author: " << foundBook->getAuthor() << endl;
		cout << "*  Publisher: " << foundBook->getPublisher() << endl;
		cout << "*  Date Added: " << foundBook->getDateAddedStr() << endl;
		cout << "*  Quantity On-hand: " << setw(4) << foundBook->getQuantity() << endl;
		cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << foundBook->getWholesaleCost() << endl;
		cout << "*  Retail Price: $" << fixed << setprecision(2) << foundBook->getRetailPrice() << endl;
		cout << "*" << endl;
		cout << "****************************************************************************************************"
			<< "*                                                                                                  *"
			<< "*                                                                                                  *"
			<< "*   Select the record you would like to change:                                                    *"
			<< "*                                                                                                  *"
			<< "*   1. ISBN                                                                                        *"
			<< "*                                                                                                  *"
			<< "*   2. Title                                                                                       *"
			<< "*                                                                                                  *"
			<< "*   3. Author                                                                                      *"
			<< "*                                                                                                  *"
			<< "*   4. Publisher                                                                                   *"
			<< "*                                                                                                  *"
			<< "*   5. Date Added                                                                                  *"
			<< "*                                                                                                  *"
			<< "*   6. Quantity On-Hand                                                                            *"
			<< "*                                                                                                  *"
			<< "*   7. Wholesale Cost                                                                              *"
			<< "*                                                                                                  *"
			<< "*   8. Retail Price                                                                                *"
			<< "*                                                                                                  *"
			<< "*   9. Return to Inventory Menu                                                                    *"
			<< "*                                                                                                  *"
			<< "*                                                                                                  *"
			<< "*                                                                                                  *"
			<< "****************************************************************************************************"
			<< "Enter Your Choice: ";
		return foundBook;
	}
	else
	{
		cout << "****************************************************************************************************"
			<< "  No book with that " << attributeStr << " was found. Press enter to try again." << endl;
		system("pause");
		return nullptr;
	}
}

void editBook(Book * editBook, int attribute)
{
	string tempStr;
	long long tempISBN;
	int tempInt;
	double tempDouble;
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                            ISBN Search                                           *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< "*  ISBN: " << editBook->getIsbn() << endl;
	cout << "*  Title: " << editBook->getTitle() << endl;
	cout << "*  Author: " << editBook->getAuthor() << endl;
	cout << "*  Publisher: " << editBook->getPublisher() << endl;
	cout << "*  Quantity On-hand: " << setw(4) << editBook->getQuantity() << endl;
	cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << editBook->getWholesaleCost() << endl;
	cout << "*  Retail Price: $" << fixed << setprecision(2) << editBook->getRetailPrice() << endl;
	cout << "*  Date Added: " << editBook->getDateAddedStr();
	cout << "*" << endl;
	cout << "****************************************************************************************************";
	switch (attribute)
	{
	case (1) :
		cout << "Enter the new ISBN for this book: ";
		cin >> tempISBN;
		editBook->setIsbn(tempISBN);
		inventory.generateAttributeList(ISBN);
		break;
	case (2) :
		cout << "Enter the new Title for this book: ";
		cin >> tempStr;
		editBook->setTitle(tempStr);
		//inventory.generateISBNList(); need to resort by title
		break;
	case (3) :
		cout << "Enter the new Author for this book: ";
		cin >> tempStr;
		editBook->setAuthor(tempStr);
		//inventory.generateISBNList(); need to resort by author
		break;
	case (4) :
		cout << "Enter the new Publisher for this book: ";
		cin >> tempStr;
		editBook->setPublisher(tempStr);
		//inventory.generateISBNList(); need to resort by publisher
		break;
	case(5) :
		//This is tricky. Need to get date added in specific format and convert it to time_t
		break;
	case(6) :
		cout << "Enter the new Quantity On-hand for this book: ";
		cin >> tempInt;
		editBook->setQuantity(tempInt);
		//inventory.generateISBNList(); need to resort by Quantity? Maybe not. This changes all the time. Sort when you need it
		break;
	case(7) :
		cout << "Enter the new Wholesale Cost for this book: ";
		cin >> tempDouble;
		editBook->setWholesaleCost(tempDouble);
		//inventory.generateISBNList(); need to resort by wholesale cost
	case(8) :
		cout << "Enter the new Retail Price for this book: ";
		cin >> tempDouble;
		editBook->setRetailPrice(tempDouble);
		//inventory.generateISBNList(); need to resort by retail price
	case(9) :
		break;
	default:
		cout << "That is not a valid option. Please try again.";
		system("pause");
	}
}
void displayBookLookup(void)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                            Book Lookup                                           *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                     Search by:                                                   *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      1. ISBN                                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      2. Title                                                    *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      3. Author                                                   *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      4. Publisher                                                *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      5. Return to Inventory Menu                                 *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************"
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
	while (userInput != "N" && userInput != "n" && userInput != "U" && userInput != "u")
	{
		cout << "That is not a valid entry.";
		cout << "Enter 'N' for a new book and 'U' for a used book and press enter: ";
		cin >> userInput;
	}
	if (userInput == "U" || userInput == "u")
	{
		cout << "Please enter the condition of the book from the menu and press enter." << endl;
		cout << "1: Like new, no visible damage." << endl;
		cout << "2: Good condition, small folds in pages, slightly worn cover." << endl;
		cout << "3. Fair condition, obvious sign of usage, crease in binding or cover." << endl;
		cout << "4. Poor condition, significant wear, possible water marks or ripped pages." << endl;
		cin >> condition;
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
}

void displayEditBook(Book * displayBook)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                         Book Information                                         *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*  ISBN: " << displayBook->getIsbn() << "*******************************************************************************"
		<< "*  Title: " << displayBook->getTitle() << "*" << endl; // need to ensure string is of a fixed length
	cout << "*  Author: " << displayBook->getAuthor() << "*" << endl; //need to ensure string is of a fixed length
	cout << "*  Publisher: " << displayBook->getPublisher() << "*" << endl;
	cout << "*  Date Added: " << displayBook->getDateAddedStr() << "*" << endl;
	cout << "*  Quantity On-hand: " << setw(4) << displayBook->getQuantity() << endl;
	cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << displayBook->getWholesaleCost() << endl;
	cout << "*  Retail Price: $" << fixed << setprecision(2) << displayBook->getRetailPrice() << endl;
	cout << "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   Select the record you would like to change:                                                    *"
		<< "*                                                                                                  *"
		<< "*   1. Title                                                                                       *"
		<< "*                                                                                                  *"
		<< "*   2. Author                                                                                      *"
		<< "*                                                                                                  *"
		<< "*   3. Publisher                                                                                   *"
		<< "*                                                                                                  *"
		<< "*   4. Date Added                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   5. Quantity On-Hand                                                                            *"
		<< "*                                                                                                  *"
		<< "*   6. Wholesale Cost                                                                              *"
		<< "*                                                                                                  *"
		<< "*   7. Retail Price                                                                                *"
		<< "*                                                                                                  *"
		<< "*   8. Return to Inventory Menu                                                                    *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************";
}
void displayInventoryMenu(void)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                          Inventory Menu                                          *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      1. Look Up a Book                                           *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      2. Add a Book                                               *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      3. Edit a Book's Record                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      4. Delete a Book                                            *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      5. Return to the Main Menu                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< " Enter Your Choice:";
}

void displayBookInformationScreen(Book * displayBook)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                         Book Information                                         *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*  ISBN: " << displayBook->getIsbn() << "*******************************************************************************"
		<< "*  Title: " << displayBook->getTitle() << "*" << endl; // need to ensure string is of a fixed length
	cout << "*  Author: " << displayBook->getAuthor() << "*" << endl; //need to ensure string is of a fixed length
	cout << "*  Publisher: " << displayBook->getPublisher() << "*" << endl;
	cout << "*  Date Added: " << displayBook->getDateAddedStr() << "*" << endl;
	cout << "*  Quantity On-hand: " << setw(4) << displayBook->getQuantity() << endl;
	cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << displayBook->getWholesaleCost() << endl;
	cout << "*  Retail Price: $" << fixed << setprecision(2) << displayBook->getRetailPrice() << endl;
	cout << "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   Select the record you would like to change:                                                    *"
		<< "*                                                                                                  *"
		<< "*   1. Title                                                                                       *"
		<< "*                                                                                                  *"
		<< "*   2. Author                                                                                      *"
		<< "*                                                                                                  *"
		<< "*   3. Publisher                                                                                   *"
		<< "*                                                                                                  *"
		<< "*   4. Date Added                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   5. Quantity On-Hand                                                                            *"
		<< "*                                                                                                  *"
		<< "*   6. Wholesale Cost                                                                              *"
		<< "*                                                                                                  *"
		<< "*   7. Retail Price                                                                                *"
		<< "*                                                                                                  *"
		<< "*   8. Return to Inventory Menu                                                                    *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************";
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
	cout << "*******************************************************************************" << endl
		<< "*                                                                             *" << endl
		<< "*                                                                             *" << endl
		<< "*                           Serendipity Booksellers                           *" << endl
		<< "*                                                                             *" << endl
		<< "*                                   Reports                                   *" << endl
		<< "*                                                                             *" << endl
		<< "*                                                                             *" << endl
		<< "*                         1. ISBN Listing                                     *" << endl
		<< "*                                                                             *" << endl
		<< "*                         2. Title Listing                                    *" << endl
		<< "*                                                                             *" << endl
		<< "*                         3. Inventory Retail Value                           *" << endl
		<< "*                                                                             *" << endl
		<< "*                         4. Listing by Quantity                              *" << endl
		<< "*                                                                             *" << endl
		<< "*                         5. Listing by Cost                                  *" << endl
		<< "*                                                                             *" << endl
		<< "*                         6. Listing by Age                                   *" << endl
		<< "*                                                                             *" << endl
		<< "*                         7. Return to the Main Menu                          *" << endl
		<< "*                                                                             *" << endl
		<< "*                         Enter Your Choice:                                  *" << endl
		<< "*                                                                             *" << endl
		<< "*******************************************************************************" << endl;
}

void displayReport(int listSelection)
{
	Book** bookList = inventory.getAttributeList(listSelection - 1);
	system("cls");
	cout << "New Books:" << endl
		<< "****************************************************************************************************"
		<< "                                                                            Wholesale Retail   Date "
		<< "# ISBN           Title                    Author         Publisher      Qty    Cost    Price   Added"
		<< "****************************************************************************************************";
	for (int i = 0; i < inventory.getNumBooks(); i++)
	{
		cout << i + 1 << " ";
		bookList[i]->print();
	}
	cout << endl << endl << "Used Books:" << endl
		<< "****************************************************************************************************"
		<< "                                                                                       Retail  Date "
		<< "# ISBN           Title                    Author         Publisher      Qty Condition  Price   Added"
		<< "****************************************************************************************************";
	system("pause");
}
