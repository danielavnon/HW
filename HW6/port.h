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
	int range[PORT_SEGMENTS];

	
public:
	
	/**
     * @brief Default constructor using a given variable
     * @param pattern is a given String typed variable
     */
	Port(String pattern);
	
	/**
     * @brief sets the values to deter which Ip typed variable
     * satisfy firewall settings
     * @return true if set was complete, else false
     */
	virtual bool set_value(String val);
	
		/**
     * @brief checks if a given String typed variable is mathcing the
     * firewall settings
     * @return true if matching, else false
     */
	virtual bool match_value(String val) const;
	
};
#endif
