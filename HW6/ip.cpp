
#include "ip.h"
#include "string.h"


#define MASK_SEGMENTS 2
#define IP_SEGMENTS 4
#define SLASH_SIGN "/"
#define MAX_MASK 32
#define MIN_MASK 0
#define IP_ERROR (-1)
#define DOT_SIGN "."
#define IP_SEG_SIZE 8


Ip::Ip(String pattern): Field(pattern){
	/*
	 *copy constructor is empty as there is no need for a construtor
	 *a complete implementation is within Field class
	 *ip class was introduced in order to explicitly implement
	 *set_value and match_value methods of a given port
	 */

}

bool Ip::set_value(String val){
	String* substrings;
	size_t size=0;

	val.split(SLASH_SIGN,&substrings,&size);

	if(size != MASK_SEGMENTS){
		delete[] substrings;
		return false;
	}
	mask = substrings[MASK_SEGMENTS-1].trim().to_integer();

	if (mask > MAX_MASK || mask < MIN_MASK){
		delete[] substrings;
		return false;
	}

	int bitmask = (1<< (IP_SEG_SIZE*IP_SEGMENTS-mask))-1;

	given_ip = united_ip(substrings[0].trim());
	// we'll have to define return error value for latter function, currently 0
	// disputed
	if (given_ip == IP_ERROR){
		delete[] substrings;
		return false;
	}

	low_feasible_ip= given_ip & (~bitmask);
	high_feasible_ip= given_ip | bitmask;



	return true;

}


bool Ip::match_value(String val) const{

	int ip_to_check = united_ip(val.trim());
	if(ip_to_check == IP_ERROR){
		return false;
	}
	if (low_feasible_ip <= ip_to_check && ip_to_check <= high_feasible_ip){
		return true;
	}
	return false;
}


int Ip::united_ip(String ip_to_unite) const{
	String* substrings;
	size_t size;

	ip_to_unite.split(DOT_SIGN,&substrings,&size);

	if (size != IP_SEGMENTS){
		delete[] substrings;
		return IP_ERROR;
	}

	int ip_to_return=0;
	int i;

	for(i=0; i<IP_SEGMENTS;i++){
		ip_to_return+=(substrings[i].trim().to_integer())<<(IP_SEG_SIZE*(i));
	}
	return ip_to_return;
}
