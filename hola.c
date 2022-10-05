#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>

char* charToString(char c) {
    char* res = (char*) malloc(2 * sizeof(char));

    *res = c;
    res[1] = '\0';
    return res;
}

char* concatStrings(char* str0, char* str1) {

    int size0 = strlen(str0);
    int size1 = strlen(str1);
    int combinedSize = size0 + size1;

    char* res = (char*) malloc((combinedSize + 1) * sizeof(char));

    for (int i = 0; i < size0; i++)
    {
        res[i] = str0[i];
    }
    for (int i = 0; i < size1; i++)
    {
        res[i + size0] = str1[i];
    }
    res[combinedSize] = '\0';

    return res;
}


void println(char* str) {
    char* printed = concatStrings(str, "\n");
    printf(printed);

    free(printed);
}


void printChar(char c) {

    char* res = charToString(c);
    println(res);
    free(res);
}


void forEachChar(char* str, void action(char)) {
    for (char* c = str; *c != '\0'; c++)
    {
        action(*c);
    }
}


char charUppercase(char c) { return c & 0xDF; }
char charLowercase(char c) { return c | 0x20; }

bool charEquals(char c0, char c1) { return c0 == c1; }
bool charEqualsIgnorecase(char c0, char c1) { return charUppercase(c0) == charUppercase(c1); }


char* mapString(char* str, char transform(char)) {

    int origilnalSize = strlen(str);

    char* res = (char*) malloc((origilnalSize + 1) * sizeof(char));
    res[origilnalSize] = '\0';

    int n = 0;
    for (char c = str[n]; c != '\0'; c = str[++n])
    {
        res[n] = transform(c);
    }
    return res;
}

char* toUppercase(char* str) { return mapString(str, *charUppercase); }
char* toLowercase(char* str) { return mapString(str, *charLowercase); }


bool strEqualsBy(char* str0, char* str1, bool predicate(char, char)) {

    int str0len = strlen(str0);

    if (str0len != strlen(str1)) return false;
    if (str0len == 0) return true;
    
    int n = 0;
    for (
        char c0 = str0[0], c1 = str1[0]; 
        c0 != '\0'; 
        c0 = str0[++n], c1 = str1[n]
    ) {
        if (! predicate(c0, c1)) return false;
    }
    return true;
}


bool strEquals(char* str0, char* str1) {
    return strEqualsBy(str0, str1, *charEquals);
}


bool strEqualsIgnoreCase(char* str0, char* str1) {
    return strEqualsBy(str0, str1, *charEqualsIgnorecase);
}


void hr() {
    printf("------------------------------------------\n");
}

void withHr(void block(void)) {
    hr();
    block();
    hr();
}


int main(void)
{
    hr();

    char* txt = "pointerSSSS";
    
    println(txt);

    char* upper = toUppercase(txt);
    char* lower = toLowercase(txt);

    println(upper);
    println(lower);
    
    hr();

    char* str0 = "Hola ";
    println(str0);

    char* str1 = "mundo";
    println(str1);
    
    char* joined = concatStrings(str0, str1);
    println(joined);

    hr();

    char* hello0  = "HelLo wORlD";
    char* hello1  = "hELlo WoRLd";

    if (strEqualsIgnoreCase(hello0, hello1))
    {
        println("Both equals ignoring case");
    }
    

    hr();

    forEachChar("for each char print line", *printChar);

    hr();

    return 0;
}
