#include"Bible.h"
#include<fstream>
#include<sstream>
#include<iostream>

using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

Bible* Bible::bible = NULL;

Bible::Bible()
{
	ifstream fin("Bible.txt");
	string line;
	string bookNumber, bookInput;
	string book;
	int chapter, verseNumber;
	string verseText;

	do
	{
		getline(fin, line);
		istringstream sin(line);
		sin >> bookInput;
		if (bookInput == "Book")
		{
			book = bookInput;
			sin >> bookNumber;
			getline(sin, book);
			book.erase(0, 1);
		}
		else
		{
			chapter = stoi(bookInput);
			sin >> verseNumber;
			getline(sin, verseText);

			VerseKey newVerseKey;
			newVerseKey.setBook(book);
			newVerseKey.setChapter(chapter);
			newVerseKey.setVerseNumber(verseNumber);

			Verse newVerse;
			newVerse.setVerseKey(newVerseKey);
			newVerse.setVerseText(verseText);

			(*this)[newVerseKey] = newVerse;
		}
	} while (!fin.eof());
}

Bible& Bible::getInstance()
{
	if (bible == NULL)
	{
		bible = new Bible();
	}
	return *bible;
}