#include "port.h"
#include <cstdlib>

#define DASH_SIGN "-"


Port::Port(String pattern): Field(pattern){
	/*
	 *copy constructor is empty as there is no need for a construtor
	 *a complete implementation is within Field class
	 *port class was introduced in order to explicitly implement 
	 *set_value and match_value methods of a given port
	 */

}



bool Port::set_value(String val){
	String* substrings;
	size_t size = 0;
	
	val.split(DASH_SIGN,&substrings,&size);
	
	if (size != PORT_SEGMENTS){
		//means there was not any 2 segments which to define the expected range
		if (0 != size){
		/* if size == 0 then substr was not allocated*/
			delete[] substrings;
		}
		return false;
		
	}
	
	range[0] = substrings[0].trim().to_integer();
	range[1] = substrings[1].trim().to_integer();
	
	delete[] substrings;
	
	if(range[0] > range[PORT_SEGMENTS-1]){
		return false;
	}
	else{
		return true;
	}

}





bool Port::match_value(String val) const{
	int packet_value = val.trim().to_integer(); // port number recieved from field 
	
	//fillet
	return ( (range[0] <= packet_value) && (packet_value <= range[1]));
}
