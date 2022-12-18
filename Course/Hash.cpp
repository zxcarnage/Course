#define _CRT_SECURE_NO_WARNINGS
#include "Hash.h"
#include <iostream>
#include "Hash.h"

int receivingExistCode(int charNum)
{
	charNum += 256;
	while (!((charNum <= 57 && charNum >= 48) || (charNum <= 90 && charNum >= 65) || (charNum <= 122 && charNum >= 97)))
	{
		if (charNum < 48) charNum += 24;
		else charNum -= 47;
	}
	return charNum;
}

void hashIt(char* hashPassword, char* password, char* salt)
{
	char hash[50] = { '\0' };
	char passwordInternal[50];
	unsigned int mply;
	unsigned int div;
	unsigned int rotateLeft;
	unsigned int passwordSize;

	memset(passwordInternal, 0, 50);
	strcpy(passwordInternal, password);


	strcat(passwordInternal, salt);
	passwordSize = strlen(passwordInternal);

	if (passwordSize % 2 != 0) strcat(passwordInternal, "s");

	for (unsigned int i = 0, j = 0; i < passwordSize; i += 2)
	{

		mply = passwordInternal[i] * passwordInternal[i + 1];
		div = passwordInternal[i] / passwordInternal[i + 1];
		rotateLeft = (mply + div) << 4; 

		hash[j] = receivingExistCode(rotateLeft); 
		j++;
	}
	strcpy(hashPassword, hash);
}