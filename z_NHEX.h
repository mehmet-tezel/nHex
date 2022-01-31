/*
	This software is owned by unxp3cted.
	You can change and use as you wish.
	(Provided that the source is specified)
*/

#include <string.h>

#if _MSC_FULL_VER // checks if compiling on visual studio 
#pragma warning(disable : 4996) 
#define _CRT_SECURE_NO_WARNINGS
#endif

void AsciiToHex(char* input, char* output, char* hex);
void HexToAscii(char* input, char* output);

char* RAsciiToHex(char* input); // returnable
//char* RHexToAscii(char* input); // returnable

char HEXPRESS(char first, char second);

void ReadBinPrintHex(const char* fileName);

unsigned char* ReadBin(const char* fileName);

signed char WriteBin(const char* fileName, const char* string);
signed char ConvertString(int arg1, const char* arg2[], unsigned int arg2Index, const char* mode);
signed char ConvertHex(int arg1, const char* arg2[], unsigned int arg2Index, const char* mode);

/* The function reads the input variable and passes it to the 
*  output variable one by one according to the hexadecimal number system
*/
void AsciiToHex(char* input, char* output, char* hex) 
{
	int loop, len;
	int i, j, k = 0, l = 0;

	i = 0;
	loop = 0;

	while (input[loop] != '\0')
	{
		sprintf(&output[i], "%02X", input[loop]);
		loop += 1;
		i += 2;
	}

	output[i++] = '\0';
	len = strlen(output);

	for (j = 0; j < len + len/2 - 1; ++j)
	{
		++k;

		hex[j] = output[l];

		if (k == 3)
		{
			hex[j] = ' ';
			k = 0;
			--l;
		}
		++l;
	}

	hex[j++] = '\0';
}

char* RAsciiToHex(char* input)
{
	size_t len = strlen(input);
	char* hex = (char*)malloc(len); // don't forget to deallocate

	for (int i = 0, j = 0; i < len; ++i, j += 2)
		sprintf(hex + j, "%02x", input[i] & 0xff);

	return hex; 
}

/* Creates an array by converting the characters
*  taken from the HEXPRESS function into ASCII
*/
void HexToAscii(char* input, char* output)
{
	size_t len = strlen(input);

	int k = 0, i, j = 0;

	for (i = 0; i < len + len / 2 - 1; ++i) {
		output[i] = HEXPRESS(input[k], input[k + 1]);
		k += 3;
	}
	output[i] = '\0';
}

// not tested yet
/*char* RHexToAscii(char* input)
{
	char* output = {'\0'}; // use malloc

	size_t len = strlen(input);

	int k = 0, i;

	for (i = 0; i < len + len / 2 - 1; ++i) {
		output[i] = HEXPRESS(input[k], input[k + 1]);
		k += 3;
	}
	output[i] = '\0';

	return output;
}*/

/* Combines the 1st digit and 2nd digit of the hex code and
*  translates according to hexadecimal number system
*/
char HEXPRESS(char FirstValue, char SecondValue)
{
	char hex[5], *zero = NULL;
	hex[0] = '0';
	hex[1] = 'x';
	hex[2] = FirstValue;
	hex[3] = SecondValue;
	hex[4] = '\0';

    return strtol(hex, zero, 16); // zero or 0
}

/* Read the file binary and output it hexadecimal*/
void ReadBinPrintHex(const char* fileName)
{
	FILE* file;

	file = fopen(fileName, "r+b");
	if (file == NULL)
	{
		printf("File could not be opened!\n");
		return NULL;
	}
	else
	{
		/* We go to the end of the file to find out the size of the file. */
		fseek(file, 0L, SEEK_END);
		size_t sz = ftell(file); // file size
		rewind(file); // Returns to the beginning of the file

		unsigned char* ch = (unsigned char*)malloc(sz);

		const size_t fileSize = fread(ch, sizeof(unsigned char), sz, file);

		for (int i = 0; i < (sz / sizeof(unsigned char)); i++)
		{
			printf("%X ", (int)ch[i]);
		}

		free(ch);
		fclose(file);
	}
}

/* Reads the file as binary and returns (unsigned char*)*/
unsigned char* ReadBin(const char* fileName)
{
	FILE* file;

	file = fopen(fileName, "r+b");
	if (file == NULL)
	{
		printf("File could not be opened!\n");
		return NULL;
	}
	else
	{
		/* We go to the end of the file to find out the size of the file. */
		fseek(file, 0L, SEEK_END);
		size_t sz = ftell(file); // file size
		rewind(file); // Returns to the beginning of the file

		unsigned char* ch = (unsigned char*)malloc(sz);
		unsigned char* str = (unsigned char*)malloc(sz);

		const size_t fileSize = fread(ch, sizeof(unsigned char), sz, file);

		int i = 0;

		for (; i < (fileSize / sizeof(unsigned char)); ++i)
		{
			str[i] = ch[i];
		}

		str[i] = '\0';

		free(ch); // don't forget to deallocate str variable after using the function
		fclose(file);

		return str;
	}
}

signed char WriteBin(const char* fileName, const char* string)
{
	FILE* file;
	signed char status = 1;

	file = fopen(fileName, "w+b");
	if (file == NULL)
	{
		printf("File could not be opened!\n");
		status = 0;
		return NULL;
	}
	else
	{
		fprintf(file, "%s", string);
		fclose(file);
		return status;
	}
}


/* Converts string to hex */
signed char ConvertString(int arg1, const char* arg2[], unsigned int arg2Index, const char* mode)
{
	signed char success = 1;

	for (int i = 3; i < arg1; ++i)
	{
		size_t len = strlen(arg2[i]);
		char* string = (char*)malloc(len * 2 + len);
		char* hex = (char*)malloc(len * 2 + len);
		AsciiToHex(arg2[i], string, hex);

		if (mode == "p") { printf("%s ", hex); }
		else if (mode == "w")
		{
			if (!WriteBin(arg2[arg2Index], hex))
				success = 0;
		}
		else { success = 0; }

		free(string);
		free(hex);
	}

	return success;
}

/* broken for multiple arguments
*  HexToAscii needs fix */
signed char ConvertHex(int arg1, const char* arg2[], unsigned int arg2Index, const char* mode)
{
	signed char success = 1;

	for (int i = 3; i < arg1; ++i)
	{
		size_t len = strlen(arg2[i]);
		char* string = (char*)malloc(len * 2 + len);
		HexToAscii(arg2[i], string);

		if (mode == "p") { printf("%s ", string); }
		else if (mode == "w")
		{
			if (!WriteBin(arg2[arg2Index], string))
				success = 0;
		}
		else { success = 0; }

		free(string);
	}

	return success;
}
