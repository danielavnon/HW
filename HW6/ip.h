#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "field.h"

/*
the range is 2 as there are 2 expected numbers within the given range
for example 22-30, there are 2 numbers: 22, 30
*/
class Ip : public Field{
	
private:
	int low
	int high
	// these two integers are referenced, disputed
	
public:
	Ip(String pattern);
	bool set_value(String val);
	bool match_value(String val) const;
	
};
#endif
