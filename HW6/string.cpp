#include "string.h"
#include <cstring>
#include <iostream>

char* allocate_and_copy(const char* str,int size);

String::String(){
	data = NULL;
	length = 0;
}

String::String(const String &str){
	length = str.length;
	data = allocate_and_copy(str.data,length);
}

String::String(const char *str){
	length = strlen(str);
	data = allocate_and_copy(str,length);
}

String::~String(){
	if(data != NULL){
		delete[] data;
	}
}

String& String::operator=(const String &rhs){
	if (this == &rhs){
		return *this;
	}
	delete[] data;
	length = rhs.length;
	data = allocate_and_copy(rhs.data,length);
	return *this;
}

String& String::operator=(const char *str){
	if(this->data == str){
		return *this;
	}
	delete[] data;
	length = strlen(str);
	data = allocate_and_copy(str,length);
	return *this;
}

bool String::equals(const String &rhs) const{
	
	if(this == &rhs){
		return true;
	}
	else return false;
}

bool String::equals(const char *rhs) const{
	
	if(this->data == rhs){
		return true;
	}
	else return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const{
	
	
	
}


int String::to_integer() const{
	
	
	
}

String String::trim() const{
	
	
}


char* allocate_and_copy(const char* str,int size){

	if(size == NULL){
		return NULL;
	}
	else return strcpy(new char[size+1],str);
}

