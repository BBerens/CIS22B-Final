#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "Book.h"
using namespace std;

class IsbnNode
{
	private:
		Book* book;
		IsbnNode* next = nullptr;
};
#endif
blah