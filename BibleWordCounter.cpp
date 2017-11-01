#include"BibleWordCounter.h"
#include<sstream>

BibleWordCounter::BibleWordCounter(string wordToBeCounted) : wordToBeCounted(wordToBeCounted), wordCount(0)
{
}

void BibleWordCounter::visit(VerseKey& verseKey, Verse& verse)
{
	wordToBeCounted[0] = tolower(wordToBeCounted[0]);
	std::istringstream sin(verse.getVerseText());
	std::string testWord;
	sin >> testWord;
	do
	{
		testWord[0] = tolower(testWord[0]);
		if (testWord == wordToBeCounted)
		{
			wordCount++;
		}
		else if (testWord.substr(0, testWord.length() - 1) == wordToBeCounted && ispunct(testWord[testWord.length() - 1]))
		{
			string testString = testWord.substr(0, testWord.length() - 1);
			wordCount++;
		}
		sin >> testWord;
	} while (!sin.fail());
}

int BibleWordCounter::getWordCount()
{
	return wordCount;
}