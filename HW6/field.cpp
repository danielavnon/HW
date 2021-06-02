

#include "field.h"
#include <iostream>
#include <cstring>

#define DELIM ",="
#define DOUBLE 2

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

	String *substr;
	size_t size = 0;
	packet.split(DELIM,&substr,&size);

	if(size == 0){ //empty packet
		delete[] substr;
		return false;
	}

	int i;
	for(i=0; i<(int)size; i+=DOUBLE){
        if(pattern.equals(substr[i].trim()) && match_value(substr[i+1].trim())){
			delete[] substr;
			return true;

		}
	}
	delete[] substr;
	return false;





}
