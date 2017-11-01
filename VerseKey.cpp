#include"VerseKey.h"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;

bool VerseKey::operator==(const VerseKey& rValue) const
{
	bool result = true;
	if (book != rValue.book)
	{
		result = false;
	}
	else if (chapter != rValue.chapter)
	{
		result = false;
	}
	else if (verseNumber != rValue.verseNumber)
	{
		result = false;
	}
	return result;
}

void VerseKey::setBook(string book) 
{
	this->book = book;
}

void VerseKey::setChapter(int chapter)
{
	this->chapter = chapter;
}

void VerseKey::setVerseNumber(int verseNumber)
{
	this->verseNumber = verseNumber;
}

string VerseKey::getBook()
{
	return book;
}

std::istream& operator>>(std::istream& cin, VerseKey& rValue)
{
	string book;
	int chapter, verseNumber;
	cout << "Which book?" << endl;
	cin >> book;
	if (book == "1" || book == "2" || book == "3")
	{
		string bookName;
		cin >> bookName;
		book += " " + bookName;
	}
	cout << "Which chapter?" << endl;
	cin >> chapter;
	cout << "Which verse?" << endl;
	cin >> verseNumber;

	rValue.setBook(book);
	rValue.setChapter(chapter);
	rValue.setVerseNumber(verseNumber);
	return cin;
}