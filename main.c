#include <stdio.h>
#include <stdlib.h>
#include "z_NHEX.h"

int main(int argc, char* argv[]) {

	if (argc <= 1)
	{
		printf("Usage: nhex -help\n");
		return 1;
	}

	if (strcmp(argv[1], "-help") == 0)
	{
		printf("\nWELCOME TO NHEX MINI HEX EDITOR\n");
		printf("\n\t -s -h \"string\" => converts string ascii to hex\n");
		printf("\n\t -h -s \"hex\" => converts string hex to ascii\n");
		printf("\n\t -r -s -p \"filename\" => reads file and converts to hex\n");
		printf("\n\t -r -h -p \"filename\" => reads file and converts to string\n");
		printf("\n\t -w -s \"filename\" \"string\" => writes file and converts to hex\n");
		printf("\n\t -w -h \"filename\" \"hex\" => writes file and converts to string\n");
		printf("\n\t -r -s -w \"filename\" \"filename2\"\n\t => reads file and converts to hex in another file\n");
		printf("\n\t -r -h -w \"filename\" \"filename2\"\n\t => reads file and converts to string in another file\n");
		printf("\n\nEND OF THE NHEX HELP MENU\n");
		return 1;
	}

	if (strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "-s") == 0 && strcmp(argv[3], "-p") == 0 && argv[4] != NULL)
	{
		printf("\n");
		ReadBinPrintHex(argv[4]);
		printf("\n");
	}
	else if (strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "-h") == 0 && strcmp(argv[3], "-p") == 0 && argv[4] != NULL)
	{
		size_t len = strlen(argv[4]);
		unsigned char* str1;

		str1 = ReadBin(argv[4]);
		if (str1 == NULL)
			return 1;

		unsigned char* str2 = (unsigned char*)malloc(len);
		HexToAscii(str1, str2);
		printf("\n%s\n", str2);
		free(str1);
	}
	else if (strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "-s") == 0 && strcmp(argv[3], "-w") == 0 && argv[4] != NULL)
	{
		unsigned char* str1;
		str1 = ReadBin(argv[4]);

		if (str1 == NULL)
			return 1;

		size_t len = strlen(str1);

		unsigned char* str2 = (unsigned char*)malloc(1000);
		unsigned char* hex = (unsigned char*)malloc(1000);

		AsciiToHex(str1, str2, hex);
		
		if(WriteBin(argv[5], hex) == 1)
			printf("\nSuccessfully written to the file.\n");

		free(str2);
		free(hex);
	}
	else if (strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "-h") == 0 && strcmp(argv[3], "-w") == 0 && argv[4] != NULL)
	{
		unsigned char* str1;
		str1 = ReadBin(argv[4]);
		if (str1 == NULL)
			return 1;

		size_t len = strlen(str1);

		unsigned char* str2 = (unsigned char*)malloc(len*2 + len);

		HexToAscii(str1, str2);

		if (WriteBin(argv[5], str2) == 1)
			printf("\nSuccessfully written to the file.\n");

		free(str2);
	}
	else if (strcmp(argv[1], "-w") == 0 && strcmp(argv[2], "-s") == 0 && argv[3] != NULL)
	{
		if (ConvertString(argc, argv, 3, "w") == 1)
			printf("\nSuccessfully written to the file.\n");
	}
	else if (strcmp(argv[1], "-w") == 0 && strcmp(argv[2], "-h") == 0 && argv[3] != NULL)
	{
		if (ConvertHex(argc, argv, 3, "w") == 1)
			printf("\nSuccessfully written to the file.\n");
	}
	else if (strcmp(argv[1], "-h") == 0 && strcmp(argv[2], "-s") == 0 && argv[3] != NULL)
	{
		printf("\n");
		ConvertHex(argc, argv, 3, "p");
		printf("\n");
	}
	else if (strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-h") == 0 && argv[3] != NULL)
	{
		printf("\n");
		ConvertString(argc, argv, 3, "p");
		printf("\n");
	}
	else
	{
		printf("Invalid argument.\n");
	}

	return 0;
}
