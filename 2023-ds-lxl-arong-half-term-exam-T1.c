#include <stdio.h>
#define touint(c) (((c)&0x1f) - 1)
#define alphabet(c) (('a' <= (c) && (c) <= 'z') || ('A' <= (c) && (c) <= 'Z'))
#define tolower(c) ((c)|0x20)

int main(int argc, char const* argv[])
{
    char s[51];
    fgets(s, 51, stdin);
    int hash_check[26] = {}, len = 0;
    for (unsigned int i = 0; s[i] != '\n' && s[i] != '\0'; i++) {
        if (alphabet(s[i])) {
            if (!hash_check[touint(s[i])]) {
                hash_check[touint(s[i])] = 1;
                s[len++] = tolower(s[i]);
            }
        }
    }
    // inverse
    for (unsigned int i = 0; i < len / 2; i++) {
        s[i] ^= s[len - 1 - i];
        s[len - 1 - i] ^= s[i];
        s[i] ^= s[len - 1 - i];
    }
    // get rest alphabet
    int j = 25;
    for (unsigned int i = len; i < 26; i++) {
        while (~j && hash_check[j])
            j--;
        s[i] = j-- + 'a';
    }
    // output
    for (unsigned int i = 0; i < 26; i++) {
        printf("%c %c\n", i + 'a', s[i]);
    }
    return 0;
}