#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Book.h"
#include "UsedBook.h"
#include "Inventory.h"
#include "Order.h"
#include <ctime>
#include <string>
#include <cstring>
#define TAX_RATE .0875
#define MAX_SEARCH_RESULTS 100


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
time_t convertDate(string);


Inventory inventory;
// create enum data type to hold data for book attributes
enum bookAttribute { ISBN, TITLE, AUTHOR, PUBLISHER, WHOLESALE_COST, RETAIL_PRICE, DATE_ADDED, QUANTITY};


int main(void)
{
	int menuOption = -1;
	string userInput;
	system("mode 120, 50");	// sets command prompt 100 chars wide and 50 chars tall
	//using while loop to prompt user to select the module they want to work with
	while (menuOption != 4)	// while user does not select to exit the program
	{
		displayMainMenu();	// draws the main menu and prompts user to select an option
		getline(cin, userInput);	// get user's selection
		if (userInput.length() == 1 && isdigit(userInput[0]))	// check a single char was entered and that is was a digit
			menuOption = stoi(userInput);	// convert the string to an int and store it in menuOption
		switch (menuOption)
		{
		case (1) :
			cashierModule();	// go to cashier module
			break;
		case (2) :
			inventoryModule();	// go to inventory module
			break;
		case (3) :
			reportModule();		// go to report module
			break;
		case (4) :
			break;		// User selected to exit, will fall through and exit while loop
		default:
			// Prompt user to enter a valid choice
			cout << "That is not a valid choice. Please select from the menu.";
			system("pause");
		}
	}
	inventory.writeBooks();	// write books to file
	return 0;
}

void cashierModule(void)	// allows cashier to place orders and displays receipt
{
	Order newOrder;		// declares a new order to be filled with books
	displayCashierScreen(&newOrder);	// draws cashier screen and prompts user for entries
}


// draws the main menu
void displayMainMenu(void)
{

	system("cls");	// clear the screen
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
	string userInput;

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

	// cin.ignore();

	// Test Code
	// *************************************************************************************************************//
	Book ** searchResults;

	while (1){
		int numBooksFound;
		bool tryAgain = true;
		int bookSelection;
		searchResults = new Book*[MAX_SEARCH_RESULTS];	// dynamically allocates an array to store search results

		cout << "Enter [EXIT] if you are ready to checkout or [CANCEL] to cancel the order." << endl;
		cout << "Please enter the ISBN of the book you are buying: ";
		getline(cin, newInput);
		cout << "************************************************************************************************************************" << endl;
		numBooksFound = inventory.strSearch(ISBN, newInput, searchResults);	//pass the attribute to search by, the value, and the array to store results to search algorithm
		if (newInput == "EXIT" || newInput == "CANCEL")
			break;
		else{
			// store the number of books found
			if (numBooksFound == 0)	// search found no books with that substring
			{
				cout << "No books found with \"" << newInput << "\" in their " << ISBN << endl;	// let the user know nothing was found
				system("pause");	// pause to let them read the results
			}
			else
			{
				for (int i = 0; i < numBooksFound; i++)	// for each book found (stored in searchResults)
				{
					cout << setw(3) << right << i + 1 << " ";	// add a result number to facilitate user selecting a book
					searchResults[i]->printCashier();	// print each book to screen 
				}
				cout << endl << "************************************************************************************************************************"
					<< "Select the book you would like to view by its number on the left:";	// prompt user to pick a book to look at
				while (tryAgain)	// loop until exception is not thrown
				{
					try{
						getline(cin, userInput);	// get user's selection
						bookSelection = stoi(userInput);	// convert the string to an int and store it in menuOption, possible exception thrown here if user did not enter a number
						if (bookSelection > numBooksFound || bookSelection < 1)	// user can only select from the books displayed on screen
						{
							string stringException = "That is not a valid book number. Try again.";
							throw stringException;
						}
						tryAgain = false;
					}
					catch (string stringException)	// catches invalid book number entered and prompts user
					{
						cout << stringException;
					}
					catch (...)	// catches a non-number user entry and prompts them to try again
					{
						cout << "That is not a valid book number. Try again:";
					}
				}

				currentBook = searchResults[bookSelection - 1];

				while (1){
					cout << "Please enter the quantity of " << currentBook->getTitle() << " that you wish to buy:";
					try{
						getline(cin, userInput);
						purchaseQuantity = stoi(userInput);

						if (purchaseQuantity > currentBook->getQuantity()){
							cout << "This is an invalid entry" << endl;
						}
						else{
							currentOrder->addBook(currentBook, purchaseQuantity);
							break;
						}
					}
					catch (...)
					{
						cout << "That is not a valid quanity." << endl;
					}

				}

				currentBook->setQuantity(currentBook->getQuantity() - purchaseQuantity); // Subtract the quantity of books being purchased

			}
			delete[] searchResults;	// delete the dynamically allocated searchResults array
			system("cls");
		}
	}
	// ****************************************************************************************************************
	// End test




	// Loop for user order
	/*
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
				try{
					getline(cin, userInput);
					purchaseQuantity = stoi(userInput);

					if (purchaseQuantity > currentBook->getQuantity()){
						cout << "This is an invalid entry" << endl;
					}
					else{
						currentOrder->addBook(currentBook, purchaseQuantity);
						break;
					}
				}
				catch (...)
				{
					cout << "That is not a valid quanity." << endl;
				}
				
			}

			currentBook->setQuantity(currentBook->getQuantity() - purchaseQuantity); // Subtract the quantity of books being purchased
			// cout << "The new quantity of this book is " << currentBook->getQuantity() << endl;
			cin.ignore();
		}
		

		else{
			cout << "This ISBN is invalid, please try another ISBN: " << endl;
		}
	}
	*/

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

	// return to cashier module
}

void inventoryModule(void)	// handles all manual book operations such as searching, adding, deleting, and editing
{
	string userInput;
	int menuOption = -1;
	while (menuOption != 5)		// until the user selects to go to previous menu (5)
	{
		displayInventoryMenu();	// draw inventory menu and prompt user input
		getline(cin, userInput);	// get user's selection
		if (userInput.length() == 1 && isdigit(userInput[0]))	// check a single char was entered and that is was a digit
			menuOption = stoi(userInput);	// convert the string to an int and store it in menuOption
		switch (menuOption)	// based on user input go to correct function
		{
		case (1) :	// user selected to search for books
			bookLookup();	// go to bookLookup module
			break;
		case (2) :
			displayAddNewBook();	// go to add New book module
			break;
		case (3) :
			displayAddUsedBook();	// go to add Used book module
			break;
		case (4) :
			displayDeleteBook();	// go to delete book module
			break;
		case (5) :
			break;		// user selected to return to previous menu will fall out of while loop
		default:
			// prompt user of invalid selection
			cout << "That is not a valid option. Please select from the menu.";
		}
	}
	// returns to main menu
}

void bookLookup(void)
{
	/*
		Draws bookLookup screen to prompt user to select an attribute to search for a book by
		Loops until user selects 5 to exit back to inventory menu
	*/
	int attributeSelection = -1;
	string userInput;
	
	while (attributeSelection != 5) {	// until the user selects to exit the bookloop screen (5)
		displayBookLookup();	// draw bookLookup screen where user selects attribute to search for book with
		getline(cin, userInput);	// get user's selection
		if (userInput.length() == 1 && isdigit(userInput[0]))	// check a single char was entered and that is was a digit
		{
			attributeSelection = stoi(userInput);	// convert the string to an int and store it in menuOption
			if (attributeSelection != 5) // user has not selected to return to the previous menu
				displayAttributeSearch(attributeSelection - 1);	// subtract one to convert from option on menu to corresponding attribute and go to attribute search screen
		}
	} 
	// returns to inventory module
}

void displayAttributeSearch(int attribute)
{
	string attributeStr;
	string inputValue;
	string userInput;
	Book ** searchResults;
	bool tryAgain = true;	
	int bookSelection; 
	int attributeSelection = -1;
	int numBooksFound;

	switch (attribute)	// from the attribute passed store the correllating string for printing to screen to attributeStr
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

	system("cls");	// clear the screen and draw the top portion of the search screen
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                   " << attributeStr << " Search" << endl;	// prints the attribute we are searching by
	cout << "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*  Enter the " << attributeStr << " to search for: ";
	getline(cin, inputValue, '\n');	// get the user's input
	cout << "************************************************************************************************************************"
		<< "                                                                          New/                Wholesale  Retail   Date  "
		<< " #  ISBN           Title                     Author         Publisher     Used Condition Qty    Cost     Price    Added "
		<< "************************************************************************************************************************";
	searchResults = new Book*[MAX_SEARCH_RESULTS];	// dynamically allocates an array to store search results
	numBooksFound = inventory.strSearch(attribute, inputValue, searchResults);	//pass the attribute to search by, the value, and the array to store results to search algorithm
	// store the number of books found
	if (numBooksFound == 0)	// search found no books with that substring
	{
		cout << "No books found with \"" << inputValue << "\" in their " << attributeStr << endl;	// let the user know nothing was found
		system("pause");	// pause to let them read the results
	}
	else
	{
		for (int i = 0; i < numBooksFound; i++)	// for each book found (stored in searchResults)
		{
			cout << setw(3) << right << i + 1 << " ";	// add a result number to facilitate user selecting a book
			searchResults[i]->print();	// print each book to screen 
		}
		cout << "************************************************************************************************************************"
			<< "Select the book you would like to view by its number on the left:";	// prompt user to pick a book to look at
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				getline(cin, userInput);	// get user's selection
				bookSelection = stoi(userInput);	// convert the string to an int and store it in menuOption, possible exception thrown here if user did not enter a number
				if (bookSelection > numBooksFound || bookSelection < 1)	// user can only select from the books displayed on screen
				{
					string stringException = "That is not a valid book number. Try again.";
					throw stringException;
				}
				tryAgain = false;
			}
			catch (string stringException)	// catches invalid book number entered and prompts user
			{
				cout << stringException;
			}
			catch (...)	// catches a non-number user entry and prompts them to try again
			{
				cout << "That is not a valid book number. Try again:";
			}
		}

		while (attributeSelection != 9)	// stay on bookInformation screen until user selects to exit (9)
		{
			displayBookInformationScreen(searchResults[bookSelection - 1]);	// pass book to bookInformation screen to prompt user if they want to edit an attribute
			getline(cin, userInput);	// get user's selection
			if (userInput.length() == 1 && isdigit(userInput[0]))	// check a single char was entered and that is was a digit
			{
				attributeSelection = stoi(userInput);	// convert the string to an int and store it in menuOption
				if (attributeSelection > 0 && attributeSelection < 9)	// if the user selects one of the attributes to be edited..
				{
					editBook(searchResults[bookSelection - 1], attributeSelection);	// pass the book and attribute to be edited to editBook
				}
			}
		}
	}
	delete[] searchResults;	// delete the dynamically allocated searchResults array
	// returns to bookLookup
}

void editBook(Book * editBook, int attribute)
{
	// given a book and an int this screen will prompt the user to enter the new value they want the attribute to be
	string tempStr;
	long long tempISBN;
	int tempInt;
	time_t tempDate;
	double tempDouble;
	bool tryAgain = true;
	
	system("cls");	// clear screen and print current book information for reference 
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
		<< "*  Book Type:          " << setw(96) << editBook->getBookType() << "*"
	    << "************************************************************************************************************************";
	switch (attribute)
	{
	case (1) :	// ISBN selected
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new 13 ISBN for this book: ";
				getline(cin, tempStr);	// get user input
				if (tempStr.length() != 13)	// we only accept 13 digit ISBNs for our database
				{
					string stringException = "Only 13 digit ISBNs are accepted. Please check the number of digits and try again.";	// create exception string
					throw stringException;	// throw string exception
				}
				tempISBN = stoll(tempStr);	// possible general exception thrown here if user did not enter a valid long long integer number
				tryAgain = false;	// only executes if exception is not thrown
			}

			catch (string stringException)	// catches string exception for wrong length entry and prompts user to try again.
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exception due to wrong format and prompts user to try again
			{
				cout << "That is not a valid ISBN. Enter the 13 digit ISBN and press enter." << endl;
			}
		}
		editBook->setIsbn(tempISBN);	// set the ISBN for the book
		break;
	case (2) :
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Title for this book: ";
				getline(cin, tempStr);
				if (tempStr.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions with tabs
			{
				cout << stringException << endl;
			}
		}
		editBook->setTitle(tempStr);	// set the title for the book
		break;
	case (3) :
		 while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Author for this book: ";
				getline(cin, tempStr);
				if (tempStr.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings 
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions with tabs
			{
				cout << stringException << endl;
			}
		}
		editBook->setAuthor(tempStr);	// set the author for the book
		break;
	case (4) :
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Publisher for this book: ";
				getline(cin, tempStr);
				if (tempStr.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings 
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions
			{
				cout << stringException << endl;
			}
		}
		editBook->setPublisher(tempStr);	// set the publisher for the book
		break;
	case(5) :
		cout << "Enter the date the book was added in MM/DD/YY format. Include the '/':";
		getline(cin, tempStr);
		tempDate = convertDate(tempStr);	// exception handling is within the convertDate function. Converts a string to time_t datatype for storage
		editBook->setDateAdded(tempDate);	// set the date added (time_t) for the book
		break;
	case(6) :
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Quantity On-hand for this book: ";
				getline(cin, tempStr);
				tempInt = stoi(tempStr);	// possibility to throw a general exception here if a non integer number is entered
				if (tempInt < 0)	// Quantity cannot be a negative number
					string stringException = "Quantity on-hand must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Quantity On-hand format. Quanity On-hand must be a positive integer. Try again" << endl;
			}
		}
		editBook->setQuantity(tempInt);
		break;
	case(7) :
		
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Wholesale Cost for this book: ";
				getline(cin, tempStr);
				tempDouble = stod(tempStr);	// possibility to throw a general exception here if a non double(or int) number is entered
				if (tempDouble < 0)	// Wholesale Cost cannot be a negative number
					string stringException = "Wholesale Cost must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Wholesale Cost format. Wholesale Cost must be a positive double. Try again" << endl;
			}
		}
		editBook->setWholesaleCost(tempDouble);
	case(8) :
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Retail Price for this book: ";
				getline(cin, tempStr);
				tempDouble = stod(tempStr);	// possibility to throw a general exception here if a non double(or int) number is entered
				if (tempDouble < 0)	// Retail Price cannot be a negative number
					string stringException = "Retail Price must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Retail Price format. Retail Price must be a positive double. Try again" << endl;
			}
		}
		editBook->setRetailPrice(tempDouble);
	case(9) :
		break;	// user selected to exit. will fall out of while loop
	default:
		cout << "That is not a valid option. Please try again.";
		system("pause");
	}
	inventory.updateLists();	// after changing an attribute, we need to resort the attribute lists
	// returns to displayAttributeSearch screen
}
void displayBookLookup(void)
{
	system("cls");	// clear screen and draw booklookup screen
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
	bool tryAgain = true;
	long long tempISBN;
	double tempDouble;
	int tempInt;
	system("cls"); // clear screen and draw top portion of add new book screen
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
		<< "*                                                                                                                      *";
	while (tryAgain)	// loop until exception is not thrown
	{
		try{
			cout << "Enter the new 13 ISBN for the book to be added: ";
			getline(cin, tempStr);
			if (tempStr.length() != 13)	// we only accept 13 digit ISBNs
			{
				string stringException = "Only 13 digit ISBNs are accepted. Please check the number of digits and try again.";
				throw stringException;
			}
			tempISBN = stoll(tempStr);	// possible general exceptin thrown here if valid long long was not entered.
			tryAgain = false;	// only executes if no exception is thrown
		}
		catch (string stringException)	// catches string exceptions for incorrect ISBN length
		{
			cout << stringException << endl;
		}
		catch (...)	// catches general exception for invalid ISBN format
		{
			cout << "That is not a valid ISBN. Enter the 13 digit ISBN and press enter." << endl;
		}
	}
	tryAgain = true;
	currentBook = inventory.searchAttribute(ISBN, tempStr);	// pass int corresponding to ISBN and search ISBN if this book already exists
	if (currentBook != nullptr)	// if a book is returned it means one with that ISBN already exists
	{
		// tell the user a book with that ISBN already exists and show them its information
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
		// let user look at information and tell them they can edit it through the book search screen, pause so they can read it.
	}
	else
	{
		currentBook = inventory.addBook();	// add a new book through inventory using default constructor.
		currentBook->setIsbn(stoll(tempStr));	// set ISBN for the book we already checked that it is valid
		cout << "*                                                                                                                      *"
			<< "*  No book with that ISBN could be located in the database. A new book will be created.                                *"
			<< "************************************************************************************************************************"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Title for this book: ";
				getline(cin, userInput);
				if (userInput.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions with tabs
			{
				cout << stringException << endl;
			}
		}
		tryAgain = true;
		currentBook->setTitle(userInput);	// set title for the book
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the name of the author of the book: ";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Author for this book: ";
				getline(cin, userInput);
				if (userInput.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings 
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions with tabs
			{
				cout << stringException << endl;
			}
		}
		tryAgain = true;
		currentBook->setAuthor(userInput);	// set author for the book
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the publisher of the book: ";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Publisher for this book: ";
				getline(cin, userInput);
				if (userInput.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings 
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions
			{
				cout << stringException << endl;
			}
		}
		tryAgain = true;
		currentBook->setPublisher(userInput);	// set publisher for book
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *";
			
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "*   Enter the wholesale cost of the book: ";
				getline(cin, userInput);
				tempDouble = stod(userInput);	// possibility to throw a general exception here if a non double(or int) number is entered
				if (tempDouble < 0)	// Wholesale Cost cannot be a negative number
					string stringException = "Wholesale Cost must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Wholesale Cost format. Wholesale Cost must be a positive double. Try again" << endl;
			}
		}
		currentBook->setWholesaleCost(tempDouble);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "*   Enter the retail price of the book: ";
				getline(cin, userInput);
				tempDouble = stod(userInput);	// possibility to throw a general exception here if a non double(or int) number is entered
				if (tempDouble < 0)	// Retail Price cannot be a negative number
					string stringException = "Retail Price must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Retail Price format. Retail Price must be a positive double. Try again" << endl;
			}
		}
		currentBook->setRetailPrice(tempDouble);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "*   Enter the quantity of books on-hand: ";
				getline(cin, userInput);
				tempInt = stoi(userInput);	// possibility to throw a general exception here if a non integer number is entered
				if (tempInt < 0)	// Quantity cannot be a negative number
					string stringException = "Quantity on-hand must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Quantity On-hand format. Quanity On-hand must be a positive integer. Try again" << endl;
			}
		}
		currentBook->setQuantity(tempInt);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                          Book has been added to the database                                         *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "************************************************************************************************************************";
		system("pause");	// Give user feedback that book has been added and pause to let them read it
	}
	inventory.updateLists();	//	now that there is a new book we need to update our attribute lists
	//returns to inventory module
}

void displayAddUsedBook(void)
{
	string userInput;
	Book* currentBook;
	UsedBook* newUsedBook;
	string tempStr;
	int tempInt;
	int condition;
	long long tempISBN;
	double tempDouble;
	bool tryAgain = true;
	system("cls");	// clear the screen and print the top of the add used book screen
	cout << "************************************************************************************************************************"
		<< "*                                                                                                                      *"
		<< "*                                                Serendipity Booksellers                                               *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                   Add a Used Book                                                    *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *";
	while (tryAgain)	// loop until exception is not thrown
	{
		try{
			cout << "Enter the new 13 ISBN for the book to be added: ";
			getline(cin, tempStr);
			if (tempStr.length() != 13)	// we only accept 13 digit ISBNs
			{
				string stringException = "Only 13 digit ISBNs are accepted. Please check the number of digits and try again.";
				throw stringException;
			}
			tempISBN = stoll(tempStr);	// possible general exceptin thrown here if valid long long was not entered.
			tryAgain = false;	// only executes if no exception is thrown
		}
		catch (string stringException)	// catches string exceptions for incorrect ISBN length
		{
			cout << stringException << endl;
		}
		catch (...)	// catches general exception for invalid ISBN format
		{
			cout << "That is not a valid ISBN. Enter the 13 digit ISBN and press enter." << endl;
		}
	}
	
	currentBook = inventory.searchAttribute(ISBN, tempStr);	// pass int corresponding to ISBN and search ISBN if this book already exists
	if (currentBook != nullptr)	// if a book is returned it means one with that ISBN already exists
	{
		//print out the found book's information for user reference
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
			// ask the user if they want to make a used copy of the found book
		getline(cin, tempStr);	// get user input
		if (tempStr == "Y" || tempStr == "y")	// if y or Y are entered..
		{
			newUsedBook = inventory.addUsedBook(currentBook);	// usedBook constructor through inventory.addUsedBook will use attributes of currentBook to initialize the usedBook.
			cout << "*                                                                                                                      *"
				<< "*                                                                                                                      *"
				<< "*                                                                                                                      *";
			
			tryAgain = true; 
			while (tryAgain)	// loop until exception is not thrown
			{
				try{
					cout << "*   Enter the quantity of books on-hand: ";
					getline(cin, userInput);
					tempInt = stoi(userInput);	// possibility to throw a general exception here if a non integer number is entered
					if (tempInt < 0)	// Quantity cannot be a negative number
						string stringException = "Quantity on-hand must be a positive number. Try again.";	// create exception string
					tryAgain = false;	// only executes if no exception is thrown
				}
				catch (string stringException)	// catches string exceptions for quantity < 0
				{
					cout << stringException << endl;
				}
				catch (...)	// catches general exceptions for invalid format
				{
					cout << "Invalid Quantity On-hand format. Quanity On-hand must be a positive integer. Try again" << endl;
				}
			}
			currentBook->setQuantity(tempInt);	// set book quantity
			// Prompt user to enter the 
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
			tryAgain = true;
			while (tryAgain)	// loop until exception is not thrown
			{
				try{
					getline(cin, userInput);	// get user's selection
					condition = stoi(userInput);	// convert the string to an int and store it in menuOption, possible exception thrown here if user did not enter a number
					if (condition > 4 || condition < 1)	// user can only select from the conditions displayed on screen
					{
						string stringException = "That is not a valid condition. Try again.";
						throw stringException;
					}
					tryAgain = false;
				}
				catch (string stringException)	// catches invalid book number entered and prompts user
				{
					cout << stringException << endl;
				}
				catch (...)	// catches a non-number user entry and prompts them to try again
				{
					cout << "That is not a valid book number. Try again:" << endl;
				}
			}
			newUsedBook->setCondition(condition);	// set book condition
		}
	}
	else
	{
		newUsedBook = inventory.addUsedBook();	// construct a new used book through inventory.addUsedBook
		newUsedBook->setIsbn(tempISBN);	// set book ISBN already ensured it was a good value
		// tell user that we are creating a new usedbook in the database
		cout << "*                                                                                                                      *"
			<< "*  No book with that ISBN could be located in the database. A new book will be created.                                *"
			<< "************************************************************************************************************************"
			<< "*                                                                                                                      *";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Title for this book: ";
				getline(cin, userInput);
				if (userInput.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions with tabs
			{
				cout << stringException << endl;
			}
		}
		tryAgain = true;
		newUsedBook->setTitle(userInput);	// set title for the book
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the name of the author of the book: ";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Author for this book: ";
				getline(cin, userInput);
				if (userInput.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings 
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions with tabs
			{
				cout << stringException << endl;
			}
		}
		tryAgain = true;
		newUsedBook->setAuthor(userInput);	// set author for the book
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*   Enter the publisher of the book: ";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "Enter the new Publisher for this book: ";
				getline(cin, userInput);
				if (userInput.find('\t') != -1)	// our database is tab separated so we can't accept tabs in strings 
					string stringException = "Tab characters are not accepted in this entry. Try again without the tab.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions
			{
				cout << stringException << endl;
			}
		}
		tryAgain = true;
		newUsedBook->setPublisher(userInput);	// set publisher for book
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *";

		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "*   Enter the wholesale cost of the book: ";
				getline(cin, userInput);
				tempDouble = stod(userInput);	// possibility to throw a general exception here if a non double(or int) number is entered
				if (tempDouble < 0)	// Wholesale Cost cannot be a negative number
					string stringException = "Wholesale Cost must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Wholesale Cost format. Wholesale Cost must be a positive double. Try again" << endl;
			}
		}
		newUsedBook->setWholesaleCost(tempDouble);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "*   Enter the retail price of the book: ";
				getline(cin, userInput);
				tempDouble = stod(userInput);	// possibility to throw a general exception here if a non double(or int) number is entered
				if (tempDouble < 0)	// Retail Price cannot be a negative number
					string stringException = "Retail Price must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Retail Price format. Retail Price must be a positive double. Try again" << endl;
			}
		}
		newUsedBook->setRetailPrice(tempDouble);
		cout << "*                                                                                                                      *"
			<< "*                                                                                                                      *"
			<< "*                                                                                                                      *";
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				cout << "*   Enter the quantity of books on-hand: ";
				getline(cin, userInput);
				tempInt = stoi(userInput);	// possibility to throw a general exception here if a non integer number is entered
				if (tempInt < 0)	// Quantity cannot be a negative number
					string stringException = "Quantity on-hand must be a positive number. Try again.";	// create exception string
				tryAgain = false;	// only executes if no exception is thrown
			}
			catch (string stringException)	// catches string exceptions for quantity < 0
			{
				cout << stringException << endl;
			}
			catch (...)	// catches general exceptions for invalid format
			{
				cout << "Invalid Quantity On-hand format. Quanity On-hand must be a positive integer. Try again" << endl;
			}
		}
		newUsedBook->setQuantity(tempInt);
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
		tryAgain = true;
		while (tryAgain)	// loop until exception is not thrown
		{
			try{
				getline(cin, userInput);	// get user's selection
				condition = stoi(userInput);	// convert the string to an int and store it in menuOption, possible exception thrown here if user did not enter a number
				if (condition > 4 || condition < 1)	// user can only select from the conditions displayed on screen
				{
					string stringException = "That is not a valid condition. Try again.";
					throw stringException;
				}
				tryAgain = false;
			}
			catch (string stringException)	// catches invalid book number entered and prompts user
			{
				cout << stringException << endl;
			}
			catch (...)	// catches a non-number user entry and prompts them to try again
			{
				cout << "That is not a valid book number. Try again:" << endl;
			}
		}
		newUsedBook->setCondition(condition);	// set book condition
	}
	inventory.updateLists();	// After adding a book we need to resort the attribute lists
	// returns to inventory module
}

void displayInventoryMenu(void)
{
	system("cls");	// clear screen and draw inventory menu
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
	system("cls");	// clear screen and draw information for book passed as an argument
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
		<< "************************************************************************************************************************";
	// returns to previous menu
}

void reportModule(void)
{
	// used to print reports sorted by various reports
	string userInput;
	int menuOption = -1;
	
	while (menuOption != 9)		// loop until the user chooses to exit (9)
	{
		displayReportsMenu();	// draw reports menu to show user what reports are available and prompt them to select one
		getline(cin, userInput);	// get user's selection
		if (userInput.length() == 1 && isdigit(userInput[0]))	// check a single char was entered and that is was a digit else fall through back to display
		{
			menuOption = stoi(userInput);	// convert the string to an int and store it in menuOption
			if (menuOption >= 1 && menuOption < 9)	// if the user entered one of the attributes on the screen..
				displayReport(menuOption);	// pass the menuOption to display report to display that attribute report
		}
	}
	// return to main menu
}
void displayReportsMenu(void)
{
	system("cls");	// clear screen and draw reports menu
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
		<< "*                                                8. Listing by Quantity                                                *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                9. Return to the Main Menu                                            *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************"
		<< " Enter your choice:";

}

void displayReport(int listSelection)
{
	// take the listselection and convert it to an attribute ( subtract 1) 
	// get the corresponding attribute list and write each book in order to screen

	Book** bookList = inventory.getAttributeList(listSelection - 1);	// pass attribute (listSelection -1) to get sorted attribute list back
	system("cls");	// clear screen and draw header to screen
	cout << "************************************************************************************************************************"
		<< "                                                                          New/                Wholesale  Retail   Date  "
		<< " #  ISBN           Title                     Author         Publisher     Used Condition Qty    Cost     Price    Added "
		<< "************************************************************************************************************************";
	for (int i = 0; i < inventory.getNumBooks()+inventory.getNumUsedBooks(); i++)	//	step through each book in the sorted attribute list (combined new and used books)
	{
		cout << setw(3) << right << i + 1 << " ";	// print the listing number (just for display purposes)
		bookList[i]->print();	// call print function. This function is overridden usedBook class so it will print different for new and used books
	}
	system("pause");	// pause to allow user to read the report
	// return displayReportMenu
}

void displayDeleteBook(void)
{
	// guides user through deleting a book
	string tempStr;
	int tempInt;
	Book ** searchResults;
	Book * deletionBook;
	UsedBook * usedDeletionBook;
	long long tempISBN;
	bool tryAgain = true;
	int numResults;

	system("cls");	// clear screen and draw top of book deletion screen.
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
		<< "*                                                                                                                      *";
	while (tryAgain)	// loop until exception is not thrown
	{
		try{
			cout << "*  Enter the ISBN of the book to be deleted: ";
			getline(cin, tempStr);
			tempISBN = stoll(tempStr);	// possible general exceptin thrown here if valid long long was not entered.
			tryAgain = false;	// only executes if no exception is thrown
		}
		catch (...)	// catches general exception for invalid ISBN format
		{
			cout << "That is not a valid ISBN. Enter the 13 digit ISBN and press enter." << endl;
		}
	}
	searchResults = new Book*[MAX_SEARCH_RESULTS];	// dynamically allocates an array to store search results
	numResults = inventory.strSearch(ISBN, tempStr, searchResults);	// pass ISBN (0), ISBN to search for, and searchResults list to strSearch for matching ISBNs
	// print the index reference for user to read results
	cout << "The following books match that ISBN:                                                                                    "
		<< "************************************************************************************************************************"
		<< "                                                                          New/                Wholesale Retail   Date   "
		<< "# ISBN           Title                      Author         Publisher      Used  Condition Qty   Cost     Price   Added  "
		<< "************************************************************************************************************************";
	for (int i = 0; i < numResults; i++)	// for each found book..
	{
		cout << setw(3) << right << i + 1 << " ";	// print book reference number for user to select book from list
		searchResults[i]->print();	// print each books data
	}
	cout << "************************************************************************************************************************"
		<< "Select the book you would like to delete using the number on the far left: ";
	tryAgain = true;
	while (tryAgain)	// loop until exception is not thrown
	{
		try{
			getline(cin, tempStr);	// get user's selection
			tempInt = stoi(tempStr);	// convert the string to an int and store it in tempInt, possible exception thrown here if user did not enter a number
			if (tempInt > numResults || tempInt < 1)	// user can only select from the books displayed on screen
			{
				string stringException = "That is not a valid book number. Try again.";
				throw stringException;
			}
			tryAgain = false;
		}
		catch (string stringException)	// catches invalid book number entered and prompts user
		{
			cout << stringException;
		}
		catch (...)	// catches a non-number user entry and prompts them to try again
		{
			cout << "That is not a valid book number. Try again:";
		}
	}
	deletionBook = searchResults[tempInt-1];	// set deletion book equal to the option selected by the user
	system("cls");	// clear screen and redraw with book information
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
		<< "*                                    Type [YES] to delete or anything else to cancel                                   *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "*                                                                                                                      *"
		<< "************************************************************************************************************************";
	// Menu asked if user really wants to delete the book. only the characters YES get a book deleted
	getline(cin, tempStr);
	if (tempStr == "YES")	// user really wants to delete the book
	{
		inventory.deleteBook(deletionBook);	// pass book to inventory to be deleted.
		cout << "************************************************************************************************************************"
			<< "*                                                                                                                      *"
			<< "*                                               Book was deleted                                                       *"
			<< "*                                                                                                                      *"
			<< "************************************************************************************************************************";
		system("pause");	// pause to view results
	}
	else // user selected not to delete book it was cancelled.
	{
		cout << "************************************************************************************************************************"
			<< "*                                                                                                                      *"
			<< "*                                             Book was not deleted                                                     *"
			<< "*                                                                                                                      *"
			<< "************************************************************************************************************************";
		system("pause");	// pause to view results
	}
	delete[] searchResults;	// delete the dynamically allocated array storing search results
}


time_t convertDate(string inString)
{
	/*
	Takes a string in MM/DD/YY format and returns a time_t format.
	Performs checks to ensure that format matches and prompts user to re-enter if not
	Exception will be thrown if input format cannot be parsed
	*/
	string dateString = inString;
	struct tm tm;
	time_t convertedTime;
	string tempMonth, tempDay, tempYear;
	int pos;
	bool tryAgain = true;
	string exceptionString;

	while (tryAgain)	// loop until exception is not thrown
	{
		try{
			if (dateString.length() != 8)
			{
				exceptionString = "The date entered is too short or too long.  Make sure to use MM/DD/YY format. Put a '0' in front of single digit days.";
				throw exceptionString;	// throw exception
			}
			pos = dateString.find('/');	// find the position that the first '/' occurs
			if (pos != 2)
			{
				exceptionString = "The month entered was invalid. Make sure to use MM/DD/YY format. Put a '0' in front of single digit months.";
				throw exceptionString;	// throw exception
			}
			tempMonth = dateString.substr(0, pos);	// create a substring of chars up to '/' but not including				
			dateString.erase(0, pos + 1);	// delete chars up to and including '/'
			pos = dateString.find('/');	// find the position that the next '/' occurs
			if (pos != 2)
			{
				exceptionString = "The day entered was invalid. Make sure to use MM/DD/YY format. Put a '0' in front of single digit months.";
				throw exceptionString;	// throw exception
			}
			tempDay = dateString.substr(0, pos);	// create a substring of chars up to '/' but not including		
			dateString.erase(0, pos + 1);	// delete chars up to and including '/'
			tempYear = dateString;
			istringstream ss(tempMonth + ":" + tempDay + ":" + tempYear + ":" + "12:00:00");	// combine time information into a stringstream to be parsed by get_time
			ss >> get_time(&tm, "%m:%d:%y:%H:%M:%S");	// parse the stringstream into tm using the format provided
			if (ss.fail())
			{
				exceptionString = "The date entered was invalid. Make sure to use MM/DD/YY format. Put a '0' in front of single digit months.";
				throw exceptionString;
			}
			convertedTime = mktime(&tm);	// convert the struct tm to time_t
			tryAgain = false;
		}
		catch (string exceptionString){	
			cout << exceptionString << endl;	// print thrown exception
			cout << "Enter the date the book was added in MM/DD/YY format. Include the '/':";	// Prompt user to properly enter the date
			getline(cin, dateString);	// gets user's input
		}
	}
	return convertedTime;	// return converted time_t
}