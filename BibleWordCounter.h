#pragma once

#include"Map.hpp"
#include"VerseKey.h"
#include"Verse.h"
#include"Bible.h"
#include<string>

class BibleWordCounter : public Bible::IVisitor
{
	public:
		BibleWordCounter(std::string);
		virtual void visit(VerseKey&, Verse&);
		int getWordCount();
	private:
		std::string wordToBeCounted;
		int wordCount;
};