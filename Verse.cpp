#include"Verse.h"

string Verse::getVerseText() const
{
	return verseText;
}
VerseKey Verse::getVerseKey() const
{
	return verseKey;
}
void Verse::setVerseText(string verseText)
{
	if (verseText[0] == ' ')
	{
		verseText.erase(0, 1);
	}
	this->verseText = verseText;
}
void Verse::setVerseKey(VerseKey& verseKey)
{
	this->verseKey = verseKey;
}