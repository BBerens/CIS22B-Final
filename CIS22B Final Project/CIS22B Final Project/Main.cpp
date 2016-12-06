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
void displayAddNewBook(void);
void displayAddUsedBook(void);
void displayDeleteBook(void);
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

void cashierModule(void)
{
	Order newOrder;
	displayCashierScreen(&newOrder);
}


// display main menu
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
	int initialQuantity;

	// Declare variables for cashier input
	string newInput = ""; // Input book

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

	// Loop for user order
	while (newInput != "EXIT" && newInput != "CANCEL")
	{
		// Collect user Input
		cout << "Enter [EXIT] if you are ready to checkout or [CANCEL] to cancel the order." << endl;
		cout << "Please enter the ISBN of the book you are buying: ";
		getline(cin, newInput);

		// Pull book data from the inventory class
		currentBook = inventory.searchAttribute(ISBN, newInput);

		if (currentBook != nullptr){
			// Return book data and verify user input is correct.  Otherwise collect user input again.
			cout << "You entered the following book:" << endl;
			cout << "ISBN: " << currentBook->getIsbn() << endl;
			cout << "Title: " << currentBook->getTitle() << endl;
			cout << "Author: " << currentBook->getAuthor() << endl;
			cout << "Publisher: " << currentBook->getPublisher() << endl;

			while (1){
				cout << "Please enter the quantity of " << currentBook->getTitle() << " that you wish to buy:";
				cin >> purchaseQuantity;

				if (purchaseQuantity > currentBook->getQuantity()){
					cout << "This is an invalid entry" << endl;
				}
				else{
					currentOrder->addBook(currentBook, purchaseQuantity);
					break;
				}


			}

				// currentOrder->addBook(currentBook, purchaseQuantity);  // Add the current book to current order

				// Exception handling for purchaseQuantity input
				// This needs to be improved.  User needs to re-enter the ISBN to get back to the quantity screen
				/*
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
				*/

			currentBook->setQuantity(currentBook->getQuantity() - purchaseQuantity); // Subtract the quantity of books being purchased
			// cout << "The new quantity of this book is " << currentBook->getQuantity() << endl;
			cin.ignore();
		}
		

		else{
			cout << "This ISBN is invalid, please try another ISBN: " << endl;
		}
	}

	// Check if ordered was canceled
	if (newInput == "CANCEL"){
		
		// Reset book quantity to originally book quantity
		while (bookCounter < currentOrder->getNumBooks()){
			currentBook = currentOrder->getBook(bookCounter);
			currentBook->setQuantity(currentBook->getQuantity() + currentOrder->getQuantity(bookCounter));
			bookCounter++;
		}
		cout << "Your order has been canceled." << endl;
		system("pause");
	}

	else if (newInput == "EXIT" && currentOrder->getNumBooks() != 0){
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
		bookCounter = 0;
		while (bookCounter < currentOrder->getNumBooks())
		{
			currentBook = currentOrder->getBook(bookCounter);
			cout << fixed << setprecision(2);
			cout << "*" << setw(5) << right << currentOrder->getQuantity(bookCounter)
				<< setw(17) << right << currentBook->getIsbn() << "  "
				<< setw(33) << left << currentBook->getTitle().substr(0, 32)
				<< "$" << setw(14) << currentBook->getRetailPrice() << "     ";
			lineTotal = currentOrder->getQuantity(bookCounter) * currentBook->getRetailPrice();
			// currentBook->setQuantity(currentBook->getQuantity() - currentOrder->getQuantity(bookCounter)); // Subtract the quantity of books being purchased
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

	else{
		system("pause");
	}
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
			displayAddNewBook();
			break;
		case (3) :
			displayAddUsedBook();
			break;
		case (4) :
			displayDeleteBook();
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
	//Book * foundBook;
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
		<< "                                                                          New/                Wholesale  Retail   Date  "
		<< " #  ISBN           Title                     Author         Publisher     Used Condition Qty    Cost     Price    Added "
		<< "************************************************************************************************************************";
	searchResults = new Book*;
	numBooksFound = inventory.strSearch(attribute, inputValue, searchResults);
	if (numBooksFound == 0)
	{
		cout << "No Books Found" << endl;
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
		else{
			displayBookLookup();
		}
	}
}

void editBook(Book * editBook, int attribute)
{
	string tempStr;
	long long tempISBN;
	int tempInt;
	double tempDouble;
	//tm tempDate;
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
		<< "*  ISBN:               " << left << setw(96) << editBook->getIsbn() << "*"
		<< "*  Title:              " << setw(96) << editBook->getTitle().substr(0, 109) << "*"
		<< "*  Author:             " << setw(96) << editBook->getAuthor() << "*"
		<< "*  Publisher:          " << setw(96) << editBook->getPublisher() << "*"
		<< "*  Date Added:         " << setw(96) << editBook->getDateAddedStr() << "*"
		<< "*  Quantity On-hand:   " << setw(96) << editBook->getQuantity() << "*"
		<< "*  Wholesale Cost:    $" << setw(96) << fixed << setprecision(2) << editBook->getWholesaleCost() << "*"
		<< "*  Retail Price:      $" << setw(96) << fixed << setprecision(2) << editBook->getRetailPrice() << "*"
		<< "*                                                                                                                      *"
	    << "************************************************************************************************************************";
	switch (attribute)
	{
	case (1) :
		cout << "Enter the new ISBN for this book: ";
		getline(cin, tempStr);
		tempISBN = stoll(tempStr);
		editBook->setIsbn(tempISBN);
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
		cout << "Enter the date the book was added in MM/DD/YY format. Include the '/':";
		getline(cin, tempStr);
		// Need to parse the input string and store each data point in the tm struct
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

void displayAddNewBook(void)
{
	string userInput;
	Book* currentBook;
	string tempStr;
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                    Add a New Book                                                    *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "* Enter the 13 digit ISBN for the book to be added: ";

	getline(cin, tempStr);
	currentBook = inventory.searchAttribute(ISBN, tempStr);
	if (currentBook != nullptr)
	{
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "* A book with that ISBN is in the database with the following information:                                             *"
			<< "************************************************************************************************************************"
			<< "*  ISBN:               " << left << setw(96) << currentBook->getIsbn() << "*"
			<< "*  Title:              " << setw(96) << currentBook->getTitle().substr(0, 109) << "*"
			<< "*  Author:             " << setw(96) << currentBook->getAuthor() << "*"
			<< "*  Publisher:          " << setw(96) << currentBook->getPublisher() << "*"
			<< "*  Date Added:         " << setw(96) << currentBook->getDateAddedStr() << "*"
			<< "*  Quantity On-hand:   " << setw(96) << currentBook->getQuantity() << "*"
			<< "*  Wholesale Cost:    $" << setw(96) << fixed << setprecision(2) << currentBook->getWholesaleCost() << "*"
			<< "*  Retail Price:      $" << setw(96) << fixed << setprecision(2) << currentBook->getRetailPrice() << "*"
			<< "*                                                                                                                      *"
			<< "************************************************************************************************************************"
			<< "* If you wish to edit the book go through the Search Books Menu" << endl;
		system("pause");
	}
	else
	{
		currentBook = inventory.addBook();
		currentBook->setIsbn(stoll(tempStr));
		cout << "*                                                                                                                      *"
			<< "*  No book with that ISBN could be located in the database. A new book will be created.                                *"
			<< "************************************************************************************************************************"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the title of the book : ";
		getline(cin, userInput);
		currentBook->setTitle(userInput);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the name of the author of the book: ";
		getline(cin, userInput);
		currentBook->setAuthor(userInput);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the publisher of the book: ";
		getline(cin, userInput);
		currentBook->setPublisher(userInput);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the wholesale cost of the book: ";
		getline(cin, userInput);
		currentBook->setWholesaleCost(stod(userInput));
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the retail price of the book: ";
		getline(cin, userInput);
		currentBook->setRetailPrice(stod(userInput));
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the quantity of books on-hand: ";
		getline(cin, userInput);
		currentBook->setQuantity(stoi(userInput));
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                          Book has been added to the database                                         *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "************************************************************************************************************************";
		system("pause");
	}
	inventory.updateLists();
}

void displayAddUsedBook(void)
{
	string userInput;
	Book* currentBook;
	UsedBook* newUsedBook;
	string tempStr;
	int condition;
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                   Add a Used Book                                                    *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "* Enter the 13 digit ISBN for the book to be added: ";

	getline(cin, tempStr);
	currentBook = inventory.searchAttribute(ISBN, tempStr);
	if (currentBook != nullptr)
	{
		cout << "*                                                                                                                      *"
			<< "* A book with that ISBN is in the database with the following information:                                             *" 
			<< "************************************************************************************************************************"
			<< "*  ISBN:               " << left << setw(96) << currentBook->getIsbn() << "*"
			<< "*  Title:              " << setw(96) << currentBook->getTitle().substr(0, 109) << "*"
			<< "*  Author:             " << setw(96) << currentBook->getAuthor() << "*"
			<< "*  Publisher:          " << setw(96) << currentBook->getPublisher() << "*"
			<< "*  Date Added:         " << setw(96) << currentBook->getDateAddedStr() << "*"
			<< "*  Quantity On-hand:   " << setw(96) << currentBook->getQuantity() << "*"
			<< "*  Wholesale Cost:    $" << setw(96) << fixed << setprecision(2) << currentBook->getWholesaleCost() << "*"
			<< "*  Retail Price:      $" << setw(96) << fixed << setprecision(2) << currentBook->getRetailPrice() << "*"
			<< "*                                                                                                                      *"
			<< "************************************************************************************************************************"
			<< "* Add a used copy of this book? Y/N: ";
		getline(cin, tempStr);
		if (tempStr == "Y" || tempStr == "y")
		{
			newUsedBook = inventory.addUsedBook(currentBook);
			cout << "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*   Enter the Quantity of books on-hand:";
			getline(cin, tempStr);
			newUsedBook->setQuantity(stoi(tempStr));
			cout << "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*   Please enter the condition of the book from the menu and press enter.                                              *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*   1: Like new, no visible damage.                                                                                    *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*   2: Good condition, small folds in pages, slightly worn cover.                                                      *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*   3. Fair condition, obvious sign of usage, crease in binding or cover.                                              *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*   4. Poor condition, significant wear, possible water marks or ripped pages.                                         *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "************************************************************************************************************************";
			cout << "Enter the condition: ";
			getline(cin, tempStr);
			condition = stoi(tempStr);
			newUsedBook->setCondition(condition);			
		}
	}
	else
	{
		newUsedBook = inventory.addUsedBook();
		newUsedBook->setIsbn(stoll(tempStr));
		cout << "*                                                                                                                      *" 
			<< "*  No book with that ISBN could be located in the database. A new book will be created.                                *"
			<< "************************************************************************************************************************"
			<< "*                                                                                                                      *"
			<< "*   Enter the title of the book : ";
		getline(cin, userInput); 
		newUsedBook->setTitle(userInput);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the name of the author of the book: ";
		getline(cin, userInput);
		newUsedBook->setAuthor(userInput);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the publisher of the book: ";
		getline(cin, userInput);
		newUsedBook->setPublisher(userInput);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the wholesale cost of the book: ";
		getline(cin, userInput);
		newUsedBook->setWholesaleCost(stod(userInput));
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the retail price of the book: ";
		getline(cin, userInput);
		newUsedBook->setRetailPrice(stod(userInput));
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the quantity of books on-hand: ";
		getline(cin, userInput);
		newUsedBook->setQuantity(stoi(userInput));
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Please enter the condition of the book from the menu below and press enter.                                        *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   1: Like new, no visible damage.                                                                                    *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   2: Good condition, small folds in pages, slightly worn cover.                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   3. Fair condition, obvious sign of usage, crease in binding or cover.                                              *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   4. Poor condition, significant wear, possible water marks or ripped pages.                                         *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "************************************************************************************************************************"
			<< "Enter the condition: ";
		getline(cin, userInput);
		condition = stoi(userInput);
		newUsedBook->setCondition(condition);
	}
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
		<< "*                                                2. Add a New Book                                                     *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                3. Add a Used Book                                                    *"
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
		<< "*  ISBN:               " << left << setw(96) << displayBook->getIsbn() << "*"
		<< "*  Title:              " << setw(96) << displayBook->getTitle().substr(0, 109) << "*"
		<< "*  Author:             " << setw(96) << displayBook->getAuthor() << "*"
		<< "*  Publisher:          " << setw(96) << displayBook->getPublisher() << "*"
		<< "*  Date Added:         " << setw(96) << displayBook->getDateAddedStr() << "*"
		<< "*  Quantity On-hand:   " << setw(96) << displayBook->getQuantity() << "*"
		<< "*  Wholesale Cost:    $" << setw(96) << fixed << setprecision(2) << displayBook->getWholesaleCost() << "*"
		<< "*  Retail Price:      $" << setw(96) << fixed << setprecision(2) << displayBook->getRetailPrice() << "*"
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
		<< "                                                                          New/                Wholesale  Retail   Date  "
		<< " #  ISBN           Title                     Author         Publisher     Used Condition Qty    Cost     Price    Added "
		<< "************************************************************************************************************************";
	for (int i = 0; i < inventory.getNumBooks()+inventory.getNumUsedBooks(); i++)
	{
		cout << setw(3) << right << i + 1 << " ";
		bookList[i]->print();
	}
	system("pause");
}

void displayDeleteBook(void)
{
	string tempStr;
	int tempInt;
	Book ** searchResults = new Book*;
	Book * deletionBook;
	int numResults;
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                     Book Deletion                                                    *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*  Enter the ISBN of the book to be deleted: ";
	getline(cin, tempStr);
	numResults = inventory.strSearch(ISBN, tempStr, searchResults);
	cout << "The following books match that ISBN:                                                                                    "
		<< "************************************************************************************************************************"
		<< "                                                                          New/                Wholesale Retail   Date   "
		<< "# ISBN           Title                      Author         Publisher      Used  Condition Qty   Cost     Price   Added  "
		<< "************************************************************************************************************************";
	for (int i = 0; i < numResults; i++)
	{
		cout << i + 1 << " ";
		searchResults[i]->print();
	}
	cout << "************************************************************************************************************************"
		<< "Select the book you would like to delete using the number on the far left: ";
	getline(cin, tempStr);
	tempInt = stoi(tempStr);
	deletionBook = searchResults[tempInt-1];
	system("cls");
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                     Book Deletion                                                    *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< "*  ISBN: " << left << setw(110) << deletionBook->getIsbn() << "*"
		<< "*  Title: " << setw(109) << deletionBook->getTitle().substr(0, 109) << "*"
		<< "*  Author: " << setw(108) << deletionBook->getAuthor() << "*"
		<< "*  Publisher: " << setw(105) << deletionBook->getPublisher() << "*"
		<< "*  Date Added: " << setw(104) << deletionBook->getDateAddedStr() << "*"
		<< "*  Quantity On-hand: " << setw(98) << deletionBook->getQuantity() << "*"
		<< "*  Wholesale Cost: $" << setw(99) << fixed << setprecision(2) << deletionBook->getWholesaleCost() << "*"
		<< "*  Retail Price: $" << setw(101) << fixed << setprecision(2) << deletionBook->getRetailPrice() << "*"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                      Are you sure you want to delete this book?                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                       Enter [YES] to delete or [NO] to cancel                                        *"
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
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************";
	getline(cin, tempStr);
	if (tempStr == "YES")
	{
		inventory.deleteBook(deletionBook);
	}

}
