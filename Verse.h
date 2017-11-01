#pragma once
#include"VerseKey.h"

class Verse
{
	public:
		string getVerseText() const;
		VerseKey getVerseKey() const;
		void setVerseText(string);
		void setVerseKey(VerseKey&);
	private:
		VerseKey verseKey;
		string verseText;
};