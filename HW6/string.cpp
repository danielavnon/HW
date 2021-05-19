
char* String::allocate_and_copy(const char* str,int size){
	return strcpy(new char[size+1],str);
}

String::String(){
	

}


String:String(const String &str){
	
	length(str.len());
	data(allocate_and_copy(str.data, str.length));
	
}
String::String(const char *str){
	
	length = strlen(str);
	data = allocate_and_copy(str, length);
	
}

Srting::~String(){
	delete[] data;
}

String::String& operator=(const String &rhs){
	if (this == &rhs){
		return *this;
	}
	delete[] data;
	data = allocate_and_copy(rhs.data,rhs.length);
	length = rhs.length;
	return *this;
	
}

String::String& operator=(const char *str){
	if(this.data == str){
		return *this;
	}
	delete[] data;
	data = allocate_and_copy(str.data,str.length);
	length = str.length;
	return *this;
	
	
}

bool String::equals(const String &rhs) const{
	
	if(this == &rhs){
		return true;
	}
	else return false;
}

bool String::equals(const char *rhs) const{
	
	if(this.data == rhs){
		return true;
	}
	else return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const{
	
	
	
}


int String::to_integer() const{
	
	
	
}

String::String trim() const{
	
	
}
