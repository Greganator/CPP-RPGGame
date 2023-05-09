#include "Stats.h"

Stats::Stats()
	:Stats(0, 0, 0, 0)
{
}

Stats::Stats(int s, int d, int c, int m)
	: Str(s), Dex(d), Con(c), Mnd(m)
{
}

Stats Stats::operator+(const Stats other)
{

	Str += other.Str;
	Dex += other.Dex;
	Con += other.Con;
	Mnd += other.Mnd;

	return *this;
}

Stats Stats::operator*(const int i)
{
	Stats added;
	added.Str = Str * i;
	added.Dex = Dex * i;
	added.Con = Con * i;
	added.Mnd = Mnd * i;

	return added;
}
