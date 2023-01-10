// Implementation of modules
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

// Define a number for error return.
#define ERROR INT_MAX

// Functions #1 to #2: Convert string input to decimal number,
// else print out "Input error." and return ERROR.
long convertChar(int n, const char num[])
{
    // convert array to int for easier binary conversion.
    long decimalNum = 0;

    // Checks the validity of the string. 
    // If it does not fit, it will return error
    if (n > 4 || n < 1 || (num[0] == '0' && n > 1) || (num[0] == ' '))
    {
        return ERROR;
    }
    else
    {
        char *digit = NULL;
        decimalNum = strtol(num, &digit, 10);

        // If the digit string is not empty (containing non numeric values),
        // returns error.
        if (strlen(digit) != 0) return ERROR;
    }
    // Checks the range of the decimal number accordingly.
    return (decimalNum < -128 || decimalNum > 127) ? ERROR : decimalNum;
}

// Repeat function #1 for unsigned char.
long convertUnChar(int n, const char num[])
{
    long decimalNum = 0;

    if (n > 3 || n < 1 || (num[0] == '0' && n > 1) || (num[0] == ' '))
    {
        return ERROR;
    }
    else
    {
        char *digit = NULL;
        decimalNum = strtol(num, &digit, 10);

        if (strlen(digit) != 0) return ERROR;
    }
    // Checks for unsigned char range
    return (decimalNum < 0 || decimalNum > 255) ? ERROR : decimalNum;
}

// Function #3: Decimal to binary conversion.
char* binary(int dec)
{   
    int c, d, t;
    char *result;

    t = 0;
    // Allocate 8 bits for result. (Prints out 8 bits of binary number.)
    result = (char*)malloc(8+1); 

    if (result == NULL) exit(EXIT_FAILURE);

    for (c = 7 ; c >= 0 ; c--)
    {
        d = dec >> c; // Print along the number of bits (Shift.)
        // Checks the most significant bit
        if (d & 1) *(result + t) = 1 + '0';
        else *(result + t) = 0 + '0';

        t++;
    }
    *(result + t) = '\0';

    return result;
}

// Function #4: Check function for tests.
// Frees the results to avoid memory leak.
bool check(int dec,  char* expected) {
    char *binStr = binary(dec);
    bool valid = strcmp(binStr, expected) == 0;
    
    free(binStr);
    return valid;
}

// --------------------------------------------------------------
// Tests and user interface
// Taken from previous labs done with slight changes to fit needs of the test.

// Test #1 to #7: Test convert num strings from "-128" to "127".
void testConvert()
{
    assert(convertChar(4, "-128") == -128);
    assert(convertChar(3, "-17") == -17);
    assert(convertChar(2, "58") == 58);
    assert(convertChar(3, "100") == 100);
    assert(convertUnChar(1, "0") == 0);
    assert(convertUnChar(2, "99") == 99);
    assert(convertUnChar(3, "127") == 127);
}

// Test #8 to #15: Test range of different data types.
void testRange()
{
    assert(convertChar(4, "-255") == ERROR);
    assert(convertChar(3, "-15") == -15);
    assert(convertChar(3, "127") == 127);
    assert(convertChar(3, "129") == ERROR);
    assert(convertUnChar(2, "-4") == ERROR);
    assert(convertUnChar(2, "19") == 19);
    assert(convertUnChar(3, "127") == 127);
    assert(convertUnChar(3, "300") == ERROR);
}

// Test #16 to #22: Test number input.
void testValidity()
{
    assert(convertChar(4, "40.5") == ERROR);
    assert(convertChar(1, "x") == ERROR);
    assert(convertChar(4, "40x5") == ERROR);
    assert(convertUnChar(3, " 40") == ERROR);
    assert(convertUnChar(3, "-x0") == ERROR);
    assert(convertUnChar(3, "547") == ERROR);
    assert(convertUnChar(3, "040") == ERROR);
}

// Test #23 to #29: Test decimal to binary conversion.
void testBinary()
{
    assert(check(0, "00000000"));
    assert(check(7, "00000111"));
    assert(check(48, "00110000"));
    assert(check(127, "01111111"));
    assert(check(-1, "11111111"));
    assert(check(-36, "11011100"));
    assert(check(-128, "10000000"));
    assert(check(255, "11111111"));       
}

// Run the tests.
void test()
{
    testConvert();
    testRange();
    testValidity();
    testBinary();
    printf("All tests pass.\n");
}

// Deal with input and output. If there are no arguments call test.
// If there is 1 argument, the program runs the test.
// If there are more than 3 arguments, then check the arguments to match the type.
// Then, calculates and prints the binary conversion.
int main(int n, char *args[n])
{
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 3)
    {
        int resultsChar = convertChar(strlen(args[n-1]), args[n-1]);
        if(resultsChar == ERROR) {
            printf("Input error.\n");
            return 1;  
        }
        else if (strcmp(args[1], "char") == 0) {
            char*binstr=binary(resultsChar);
            printf("%s\n", binstr);
            // Frees the result.
            free(binstr);
        }
    }  
    else if (n == 4) {
        int resultsUnChar = convertUnChar(strlen(args[n-1]), args[n-1]);
        if (resultsUnChar == ERROR) {
            printf("Input error.\n");
            return 1; 
        }
        else if((strcmp(args[1], "unsigned") && strcmp(args[2], "char")) == 0) {
            char*binstr = binary(resultsUnChar);
            printf("%s\n", binstr);
            free(binstr);
        }
    }
        else
    {
        fprintf(stderr, "Input error.\n");
        return 1;
    }
    return 0;
}
