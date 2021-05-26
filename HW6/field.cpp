
#include "field.h"
#include <iostream>
#include <cstring>

#define DELIM ",="

/* copy constructor, no default constructor
 * we used this-> notation instead of pattern=pattern as the lefthandside
 * part is pattern of this whereas the righthandside part is
 * the given element, String pattern. we didnt want to mix up with names
 */
Field::Field(String pattern){
	this->pattern=pattern;
}

Field::~Field(){
	/* String destructor will destruct String pattern
	 * as it has been initiated there and will be called upon a destructor
	 */
}


	/*
	 * set_value and match_value
	 * virtual method, will not be explicitly addressed here
	 * port and ip will address each case for itself
	 */
	
	

bool Field::match(String packet){

	String *substrings;
	size_t size = 0;
	packet.split(DELIM,&substrings,&size);

	if(size == 0){ //empty packet
		delete[] substrings;
		return false;
	}

	int i;
	for(i=0; i<(int)size; i++){
		substrings[i].trim();
		substrings[i+1].trim();
		if(pattern.equals(substrings[i]) && match_value(substrings[i+1])){
			delete[] substrings;
			return true;

		}
	}
	delete[] substrings;
	return false;





}
