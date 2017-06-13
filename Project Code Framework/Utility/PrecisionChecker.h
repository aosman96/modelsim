#ifndef _PRECISION_H
#define _PRECISION_H

#define precision 5

//Simple Function to check if the point is within precision range
//Warning : removing the inline keyword will cause alot of linker Redefinition errors !
inline bool WithinRange(int var,int target)
{
	return (var<=target+precision && var>=target-precision);
}

//Simple Function to check if the var is between x1 and x2
//Warning : removing the inline keyword will cause alot of linker Redefinition errors !
inline bool IsBetween(int x1,int x2,int var)
{
	return ((var<=x1 && var>=x2) || (var<=x2 && var>=x1));
}

#endif