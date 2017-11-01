#pragma once
#include"Map.hpp"
#include"Verse.h"
#include"VerseKey.h"

class Bible: public util::Map<VerseKey, Verse>
{
	public:
		static Bible& getInstance();
	private:
		static Bible* bible;
		Bible();
		Bible(Bible&) = delete;
};