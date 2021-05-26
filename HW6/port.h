#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "field.h"

#define PORT_SEGMENTS 2
/*
the range is 2 as there are 2 expected numbers within the given range
for example 22-30, there are 2 numbers: 22, 30
*/
class Port : public Field{
	
private:
	short range[PORT_SEGMENTS];

	
public:
	
	Port(String pattern);
	bool set_value(String val);
	bool match_value(String val) const;
	
};
#endif
