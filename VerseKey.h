#pragma once
#include<string>
#include<iostream>

using std::string;

class VerseKey
{
	public:
		bool operator==(const VerseKey&) const;
		void setBook(string);
		void setChapter(int);
		void setVerseNumber(int);
		string getBook();
	private:
		string book;
		int chapter;
		int verseNumber;
};

std::istream& operator>>(std::istream&, VerseKey&);