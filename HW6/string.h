#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <iostream>
#include <cstring>

class String {
    char *data;
    size_t length;

public:

    /**
     * @brief Initiates an empty string
     */
    String();

    /**
     * @brief Initiates string from other string
     */
    String(const String &str);

    /**
     * @brief Initiates a string from char array
     */
    String(const char *str);


    ~String();

    /**
     * @brief Changes this from String
     */
    String& operator=(const String &rhs);

    /**
     * @brief Changes this from char array
     */
    String& operator=(const char *str);

    /**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
    bool equals(const String &rhs) const;

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool equals(const char *rhs) const;

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    void split(const char *delimiters, String **output, size_t *size) const;

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int to_integer() const;

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String trim() const;
    
        /**
     * @brief allocates and copy a new string
     * @param *str a pointer to a given string
     * @param size the size of the given string
     * @return a pointer to a string which is a copy of the
     * given string
     */
    char* allocate_and_copy(const char* str,int size);

};


#endif
