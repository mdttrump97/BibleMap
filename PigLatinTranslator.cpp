#include "PigLatinTranslator.h"
#include<sstream>
#include<iostream>

PigLatinTranslator::PigLatinTranslator()
{
}

void PigLatinTranslator::visit(VerseKey& verseKey, Verse& verse)
{
	string pastBook;
	string newVerseText;
	string beginningOfWord;
	Verse newVerse;
	newVerse = verse;
	std::istringstream sin(verse.getVerseText());
	std::string verseWord;
	sin >> verseWord;
	
	do
	{
		if (verseWord != "?")
		{
			bool wasUpper = false;
			string endPunctuation;
			bool hasEndPunctuation = false;
			int numberOfInitialConsonants = 0;
			int i = 0;
			while (!(verseWord[i] == 'a' || verseWord[i] == 'e' || verseWord[i] == 'i' || verseWord[i] == 'o' || verseWord[i] == 'u' ||
				verseWord[i] == 'A' || verseWord[i] == 'E' || verseWord[i] == 'I' || verseWord[i] == 'O' || verseWord[i] == 'U' || verseWord[i] == 'y' || verseWord[i] == 'Y'))
			{
				i++;
				numberOfInitialConsonants++;
			}
			if (isupper(verseWord[0]))
			{
				wasUpper = true;
				verseWord[0] = tolower(verseWord[0]);
			}
			if (ispunct(verseWord[verseWord.length() - 1]))
			{
				hasEndPunctuation = true;
				endPunctuation = verseWord[verseWord.length() - 1];
				verseWord = verseWord.substr(0, verseWord.length() - 1);
			}
			if (numberOfInitialConsonants > 0)
			{
				string initialConsonants = verseWord.substr(0, numberOfInitialConsonants);
				verseWord = verseWord.substr(numberOfInitialConsonants, verseWord.length() - 1);
				verseWord += initialConsonants;
				verseWord += "ay";
			}
			else
			{
				verseWord += "way";
			}
			if (hasEndPunctuation)
			{
				verseWord += endPunctuation;
			}
			if (wasUpper)
			{
				verseWord[0] = toupper(verseWord[0]);
			}

			newVerseText += verseWord + " ";
		}
		sin >> verseWord;
	} while (!sin.fail());
	//::cout << newVerseText << std::endl;
	verse.setVerseText(newVerseText);
}
