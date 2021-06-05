#ifndef IP_H
#define IP_H

#include "string.h"
#include "field.h"

/*
the range is 2 as there are 2 expected numbers within the given range
for example 22-30, there are 2 numbers: 22, 30
*/
class Ip : public Field{
	
private:
	int low_feasible_ip;
	int high_feasible_ip;
	int mask;
	int given_ip;
	// these two integers are referenced, disputed
	
public:
	/**
     * @brief Default constructor using a given variable
     * @param pattern is a given String typed variable
     */
	Ip(String pattern);
	
	/**
     * @brief sets the values to deter which Ip typed variable
     * satisfy firewall settings
     * @return true if set was complete, else false
     */
	bool set_value(String val);
	
		/**
     * @brief checks if a given String typed variable is mathcing the
     * firewall settings
     * @return true if matching, else false
     */
	bool match_value(String val) const;
	
	/**
     * @brief convers a String typed which containes the ip in its compact form
     * @param ip_to_unite this is the variable which is to be converted
     * @return int which is the converted form of the ip.
     */
	int united_ip(String ip_to_unite) const; // an explanation is the cpp file
	
};
#endif
