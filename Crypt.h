#pragma once
#pragma warning(disable:4996)

#include <stdlib.h>
#include <string.h>


/*
*Compile in "RELEASE" mode! This should work with optimization enabled.
*NOTE:You only need to decrypt ONCE for every encrypted string!!!
*By calling __DECRYPT64 more than one time on a string, you will actually encrypt it back.
*/

//How much to shift our letters.The default value is based on the time this gets compiled.
#define __SHIFT_KEY (__TIME__[0] - '0' + __TIME__[1] - '0' + __TIME__[3] - '0' + __TIME__[4] - '0' + __TIME__[6] - '0' + __TIME__[7] - '0')

/*Shift letters by __SHIFT_KEY ammount, append \0 to our strings and write them as single characters.
*EG: A normal string = "This is normal". As single characters our string will look like this = { 'T', 'h', 'i', 's', ... }
*By writting our strings as an 'array of characters', as above, they won't show up in our .exe file.
*However, after decrypting our strings, they will be visible in memory.
*/
#define __ENCRYPT64(__String) \
(__String)[0] + __SHIFT_KEY, (__String)[1] + __SHIFT_KEY, (__String)[2] + __SHIFT_KEY, (__String)[3] + __SHIFT_KEY,		\
(__String)[4] + __SHIFT_KEY, (__String)[5] + __SHIFT_KEY, (__String)[6] + __SHIFT_KEY, (__String)[7] + __SHIFT_KEY,		\
(__String)[8] + __SHIFT_KEY, (__String)[9] + __SHIFT_KEY, (__String)[10] + __SHIFT_KEY, (__String)[11] + __SHIFT_KEY,	\
(__String)[12] + __SHIFT_KEY, (__String)[13] + __SHIFT_KEY, (__String)[14] + __SHIFT_KEY, (__String)[15] + __SHIFT_KEY,	\
(__String)[16] + __SHIFT_KEY, (__String)[17] + __SHIFT_KEY, (__String)[18] + __SHIFT_KEY, (__String)[19] + __SHIFT_KEY,	\
(__String)[20] + __SHIFT_KEY, (__String)[21] + __SHIFT_KEY, (__String)[22] + __SHIFT_KEY, (__String)[23] + __SHIFT_KEY,	\
(__String)[24] + __SHIFT_KEY, (__String)[25] + __SHIFT_KEY, (__String)[26] + __SHIFT_KEY, (__String)[27] + __SHIFT_KEY,	\
(__String)[28] + __SHIFT_KEY, (__String)[29] + __SHIFT_KEY, (__String)[30] + __SHIFT_KEY, (__String)[31] + __SHIFT_KEY,	\
(__String)[32] + __SHIFT_KEY, (__String)[33] + __SHIFT_KEY, (__String)[34] + __SHIFT_KEY, (__String)[35] + __SHIFT_KEY,	\
(__String)[36] + __SHIFT_KEY, (__String)[37] + __SHIFT_KEY, (__String)[38] + __SHIFT_KEY, (__String)[39] + __SHIFT_KEY,	\
(__String)[40] + __SHIFT_KEY, (__String)[41] + __SHIFT_KEY, (__String)[42] + __SHIFT_KEY, (__String)[43] + __SHIFT_KEY,	\
(__String)[44] + __SHIFT_KEY, (__String)[45] + __SHIFT_KEY, (__String)[46] + __SHIFT_KEY, (__String)[47] + __SHIFT_KEY,	\
(__String)[48] + __SHIFT_KEY, (__String)[49] + __SHIFT_KEY, (__String)[50] + __SHIFT_KEY, (__String)[51] + __SHIFT_KEY,	\
(__String)[52] + __SHIFT_KEY, (__String)[53] + __SHIFT_KEY, (__String)[54] + __SHIFT_KEY, (__String)[55] + __SHIFT_KEY,	\
(__String)[56] + __SHIFT_KEY, (__String)[57] + __SHIFT_KEY, (__String)[58] + __SHIFT_KEY, (__String)[59] + __SHIFT_KEY,	\
(__String)[60] + __SHIFT_KEY, (__String)[61] + __SHIFT_KEY, (__String)[62] + __SHIFT_KEY, (__String)[63] + __SHIFT_KEY,	'\0'

//Concatenate string terminators to our __String. We are doing this in order to accept strings with less than 64 characters.
#define __SHIFT64(__String) { __ENCRYPT64(__String"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0") }

/*Attempt to decrypt the string and return it as a pointer.
*NOTE:It decrypts the original string and returns a pointer to the first element of the decrypted string.
*In order to prevent changing the original string, just remove the last 2 lines before the return from this function.
BEWARE, by doing this, you will have to free the memory by yourself whenever you call this function!
*/
char * __DECRYPT64(char *EncryptedString)
{
	char *NormalizedString = (char *)calloc(64, sizeof(char));
	int index = 0;

	for (int i = 0; i < 64; i++)
	{
		char NormalizedChar = EncryptedString[i] - __SHIFT_KEY;
		if (NormalizedChar)
			NormalizedString[index++] = NormalizedChar;
	}

	NormalizedString = (char *)realloc(NormalizedString, index * sizeof(char) + 1);

	strcpy(EncryptedString, NormalizedString);
	free(NormalizedString);

	return EncryptedString;
}