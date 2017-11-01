#include"Bible.h"
#include"BibleWordCounter.h"
#include"PigLatinTranslator.h"
#include<iostream>

using std::cout;
using std::endl;

void main()
{
	Bible& bible = Bible::getInstance();
	VerseKey verseKey;
	verseKey.setBook("Genesis");
	verseKey.setChapter(1);
	verseKey.setVerseNumber(2);

	try 
	{
		cout << "Using an iterator staring at Genesis 1:2." << endl;
		auto i = bible.getIterator(verseKey);
		cout << "Genesis 1:2 is:" << endl;
		cout << (*i).getVerseText() << endl << endl;
		cout << "If I decrement the iterator, it will display Genesis 1:1." << endl;
		i--;
		cout << "Genesis 1:1 is:" << endl;
		cout << (*i).getVerseText() << endl << endl;
		cout << "If I decrement the iterator again, it will wrap to the end of the Bible." << endl;
		i--;
		cout << "Displaying the last verse of the Bible:" << endl;
		cout << (*i).getVerseText() << endl << endl;
		cout << "If I increment the iterator, it will wrap to the beginning of the Bible." << endl;
		i++;
		cout << "Displaying the first verse of the Bible:" << endl;
		cout << (*i).getVerseText() << endl;

		cout << "---------------------------------------------------" << endl;
		cout << "Using the word counter visitor, I will look for the number of occurences of \"covenant\" in the King James Bible." << endl;
		BibleWordCounter wordCounter("Covenant");
		bible.visit(wordCounter);
		cout << "Covenant should occur in the King James Bible 292 times." << endl;
		cout << "According to the visitor, covenant appears " << wordCounter.getWordCount() << " times." << endl;
		cout << "---------------------------------------------------" << endl;

		cout << "My pig latin translator visitor will translate each verse of the Bible into pig latin." << endl;
		cout << "Visiting..." << endl;
		PigLatinTranslator translator;
		bible.visit(translator);

		verseKey.setBook("John");
		verseKey.setChapter(3);
		verseKey.setVerseNumber(16);
		cout << "John 3:16 in pig latin is:" << endl;
		cout << ((Verse) bible[verseKey]).getVerseText() << endl;
	}
	catch (std::range_error e)
	{
		cout << e.what();
	}
}

