#pragma once
#include"Map.hpp"
#include"Bible.h"
class PigLatinTranslator : public Bible::IVisitor
{
	public:
		PigLatinTranslator();
		void visit(VerseKey&, Verse&);
};

