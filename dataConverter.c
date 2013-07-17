#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataConverter.h"

char* trimLeadZeros(char *input) /*Goes through entire string and removes the leading 0s from the solution*/
{
	int length, i;
	while(input[0] - '0' == 0)
	{
		length=strlen(input);
		for (i=0; i < length; i++)
			input[i] = input[i+1];
	}
	return input;
}

double binToDec(char *inputData) /*Converts the binary number to decimal and returns a type double.*/
{
	char *decimal = strtok(inputData,"."); /*Processes the left side of the decimal point (if there is one) first.*/
	int stringLength = strlen(decimal);
	double value = 0;
	int i;
	int finalDigit;
	int powerCount = 0;
	for(i = stringLength; i > 0; i--)
	{
		finalDigit = decimal[i-1] -'0'; /*Converts digit to an integer.*/
		value = finalDigit*(pow(2,powerCount)) + value; /*Calculates the value of that digit based on it's position*/
		powerCount++;
	}
	decimal = strtok(NULL, ".");
	if(decimal != NULL) /*If there is any value after the decimal place, repeat the same steps as above but for the right side.*/
	{
		powerCount = 1;
		stringLength = strlen(decimal);
		for(i = 0; i < stringLength; i++)
		{
			finalDigit = decimal[i] - '0';
			value = finalDigit/pow(2,powerCount) + value;
			powerCount++;
		}
	}
	return value; /*Returns the number in base 10 as type double.*/
}

char* hexLookup(char *padInput) /*Function which takes an input string and converts it's value to hex.*/
{
	char *hexValue;
	char hexCompare[5];
	char *hexAnswer = (char *)malloc(3);
	int j;
	int k = 0;
	int padLength = strlen(padInput);
	for(j = 0; j != padLength; j++) /*Iterates through the input string and copies it's values 4 at a time to another string.*/
	{
		hexCompare[k] = padInput[j];
		k++;
		if(k == 4) /*Once the new string has 4 digits, it looks up the value in hex of those 4 digits using strcmp.*/
		{
			hexCompare[4] = '\0';
			if(strcmp(hexCompare,"0000") == 0)
				hexValue = "0\0";
			if(strcmp(hexCompare,"0001") == 0)
				hexValue = "1\0";
			if(strcmp(hexCompare,"0010") == 0)
				hexValue = "2\0";
			if(strcmp(hexCompare,"0011") == 0)
				hexValue = "3\0";
			if(strcmp(hexCompare,"0100") == 0)
				hexValue = "4\0";
			if(strcmp(hexCompare,"0101") == 0)
				hexValue = "5\0";
			if(strcmp(hexCompare,"0110") == 0)
				hexValue = "6\0";
			if(strcmp(hexCompare,"0111") == 0)
				hexValue = "7\0";
			if(strcmp(hexCompare,"1000") == 0)
				hexValue = "8\0";
			if(strcmp(hexCompare,"1001") == 0)
				hexValue = "9\0";
			if(strcmp(hexCompare,"1010") == 0)
				hexValue = "A\0";
			if(strcmp(hexCompare,"1011") == 0)
				hexValue = "B\0";
			if(strcmp(hexCompare,"1100") == 0)
				hexValue = "C\0";
			if(strcmp(hexCompare,"1101") == 0)
				hexValue = "D\0";
			if(strcmp(hexCompare,"1110") == 0)
				hexValue = "E\0";
			if(strcmp(hexCompare,"1111") == 0)
				hexValue = "F\0";
			strcat(hexAnswer,hexValue); /*Appends the hexValue to a string hexAnswer and restarts the process for the next grouping of 4 digits.*/
			k = 0;
		}
	}
	return hexAnswer; /*Returns the string hexAnswer.*/
}

char* octLookup(char *padInput) /*Function which acts the same way as hexLookup except groups numbers in 3's and converts the digits to octal.*/
{
	char *octValue;
	char octCompare[5];
	char *octAnswer = (char *)malloc(2);
	int j;
	int k = 0;
	int padLength = strlen(padInput);
	for(j = 0; j != padLength; j++)
	{
		octCompare[k] = padInput[j];
		k++;
		if(k == 3)
		{
			octCompare[3] = '\0';
			if(strcmp(octCompare,"000") == 0)
				octValue = "0\0";
			if(strcmp(octCompare,"001") == 0)
				octValue = "1\0";
			if(strcmp(octCompare,"010") == 0)
				octValue = "2\0";
			if(strcmp(octCompare,"011") == 0)
				octValue = "3\0";
			if(strcmp(octCompare,"100") == 0)
				octValue = "4\0";
			if(strcmp(octCompare,"101") == 0)
				octValue = "5\0";
			if(strcmp(octCompare,"110") == 0)
				octValue = "6\0";
			if(strcmp(octCompare,"111") == 0)
				octValue = "7\0";
			strcat(octAnswer,octValue);
			k = 0;
		}
	}
	return octAnswer;
}

char* binToHex(char *inputData) /*Function which converts binary to hex.*/
{
	char *padInput;
	char *decimal = strtok(inputData,".");
	char *hexFinalAnswer = (char *)malloc(8);
	int stringLength = strlen(decimal);
	char* pad =(char *)malloc(stringLength+4);
	int i, padCount = 0;
	while (stringLength %4 != 0) /*This while loop determines how many leading 0's need to be appended to the input string so that the numbers can be evenly grouped into 4s.*/
	{
		padCount++;
		stringLength++;
	}
	for(i = 0; i != padCount; i++)
		pad[i] = '0';
	pad[i]='\0';
	padInput = strcat(pad,decimal);
	hexFinalAnswer = hexLookup(padInput); /*Once the 0s have been padded to the input string, the function is sent to hexLookup to return the hex value.*/
	decimal = strtok(NULL, ".");
	if(decimal != NULL) /*Function works the same as above but for the right hand side of the decimal point, appending the padded 0s AFTER the input instead of before.*/
	{
		hexFinalAnswer = strcat(hexFinalAnswer,".");
		stringLength = strlen(decimal);
		padCount = 0;
		while (stringLength %4 != 0)
		{
			padCount++;
			stringLength++;
		}
		for(i = 0; i != padCount; i++)
			pad[i] = '0';
		pad[i]='\0';
		padInput = strcat(decimal,pad);
		strcat(hexFinalAnswer,hexLookup(padInput));
	}
	if((hexFinalAnswer[0] != 'A' && hexFinalAnswer[0] != 'B' && hexFinalAnswer[0] != 'C' && hexFinalAnswer[0] != 'D' && hexFinalAnswer[0] != 'E' && hexFinalAnswer[0] != 'F') && (hexFinalAnswer[0] == 0 && hexFinalAnswer[1] == '.' && hexFinalAnswer[2] == 0)) /*Ensures that any 0 input returns 0, regardless of any abnormalities that may occur in another part of the function*/
		return ("0");
	if(strcmp(hexFinalAnswer,"0") == 0)
		return("0");
	else
		strcpy(hexFinalAnswer,trimLeadZeros(hexFinalAnswer)); /*If the value of the input isn't 0, the final answer in hex is returned without padded 0s.*/
	return hexFinalAnswer;
}

char* binToOct(char *inputData) /*Function which converts binary to octal. This function is identical to bintoHex except this pads the input so that its length is a multiple of 3.*/
{
	char *padInput;
	char *decimal = strtok(inputData,".");
	char *octFinalAnswer = (char *)malloc(10);
	int stringLength = strlen(decimal);
	char* pad =(char *)malloc(stringLength+3);
	int i, padCount = 0;
	while (stringLength % 3 != 0)
	{
		padCount++;
		stringLength++;
	}
	for(i = 0; i != padCount; i++)
		pad[i] = '0';
	pad[i]='\0';
	padInput = strcat(pad,decimal);
	octFinalAnswer = octLookup(padInput);
	decimal = strtok(NULL, ".");
	if(decimal != NULL)
	{
		octFinalAnswer = strcat(octFinalAnswer,".");
		stringLength = strlen(decimal);
		padCount = 0;
		while (stringLength % 3 != 0)
		{
			padCount++;
			stringLength++;
		}
		for(i = 0; i != padCount; i++)
			pad[i] = '0';
		pad[i]='\0';
		padInput = strcat(decimal,pad);
		octFinalAnswer = strcat(octFinalAnswer,octLookup(padInput));
	}
	if(strcmp(octFinalAnswer,"0") == 0)
		return("0");
	else
		strcpy(octFinalAnswer,trimLeadZeros(octFinalAnswer));
	if(atoi(octFinalAnswer)==0)
		return("0");
	return octFinalAnswer;
}

char* dectoBin(char *inputData) /*Function which converts a decimal number to binary.*/
{
	char *decimal = strtok(inputData,".");
	int stringLength = strlen(decimal);
	double doubleNumber;
	int binLength = 64;
	int i = 0, number = 0;
	int j, reverseCount;
	int powerCount = stringLength - 1; /*Computes the place value of the first number in the string. IE: 123 is of length 3 and powerCount is 2. The number 1 is equivalent to 1*(10^2) or 100*/
	char *binFinalAnswer = (char *)malloc(binLength);
	char *reverseBin = (char *)malloc(binLength);
	for (i = 0; i < stringLength; i++)
	{
		number = number + (decimal[i] - '0')*pow(10,powerCount); /*Adds to the integer number, the digit by digit value of the input string.*/
		powerCount--;
	}
	i = 0;
	while (number > 0) /*While the number is greater than 0, the modulo math is done to compute the binary value.*/
	{
		binFinalAnswer[i] = (char)(number % 2) + '0';
		i++;
		number = number/2;
	}
	for(reverseCount = 0; reverseCount != i; reverseCount++) /*The binary output is in reverse with LSB on the left. This for loop reverses the values so that MSB is on the left.*/
		reverseBin[reverseCount] = binFinalAnswer[i-reverseCount-1];
	strcpy(binFinalAnswer, reverseBin); /*To keep string consistent, the value of reverseBin is copied over to binFinalAnswer to make it more clear what is going on.*/
	memset(reverseBin, '\0',32); /*Ensures reverseBin is empty and no values remain in the string in case it is used later in the function.*/
	decimal = strtok(NULL,".");
	if(decimal != NULL) /*If there are numbers after the decimal point in the input.*/
	{
		binFinalAnswer[i] = '.'; /*Inserts the decimal point at the proper spot in the final string returned.*/
		stringLength = strlen(decimal);
		doubleNumber = 0;
		powerCount = -1; /*The first number after the decimal point has value 10^-1 and decreases as you proceed left to right.*/
		for(i = 0; i < stringLength; i++)
		{
			doubleNumber = doubleNumber + (decimal[i] - '0')*pow(10,powerCount);
			powerCount--;
		}
		j = 0;
		while(doubleNumber > 0) /*Does similar math as was done on the left side of the decimal point but instead is multiplying by 2.*/
		{
			doubleNumber = doubleNumber * 2;
			if(doubleNumber >= 1)
			{
				reverseBin[j] = '1';
				j++;
				doubleNumber = doubleNumber - 1;
				if(doubleNumber < pow(10,-10)) /*Because type doubles in C do not go to 0 but rather to an extremely small value, this if statement rounds a very small number to 0.*/
					doubleNumber = 0;
			}
			else
			{
				reverseBin[j] = '0';
				j++;
			}
		}
		strcat(binFinalAnswer,reverseBin); /*Because the binary values on the right hand side are in the right order, no reversal needs to be done here. The string can simply be concatenated onto the string created for the left side of the decimal point.*/
	}
	if(strcmp(binFinalAnswer,".") == 0 || strlen(binFinalAnswer) == 0) /*If the generated string has no length or the output string is just a decimal point, the value 0 is returned so all outputs are sensible.*/
		binFinalAnswer[0] = (char)(0) + '0';
	return binFinalAnswer;
}

char* hextoBin(char* inputData) /*Function which converts a hex number to binary.*/
{
	char *decimal = strtok(inputData,".");
	int hexLength = strlen(inputData) *4;
	int decimalLength;
	char *binFinalAnswer = (char *)malloc(hexLength);
	char *binValue = (char *)malloc(5);
	int i;
	while(decimal != NULL) /*Loops through the input string and for each hex value, creates a string of the correct binary value and appends that to the string binFinalAnswer.*/
	{
		decimalLength = strlen(decimal);
		for(i = 0; i < decimalLength; i++)
		{
			if(decimal[i] == '0')
			{
				binValue = "0000\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '1')
			{
				binValue = "0001\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '2')
			{
				binValue = "0010\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '3')
			{
				binValue = "0011\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '4')
			{
				binValue = "0100\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '5')
			{
				binValue = "0101\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '6')
			{
				binValue = "0110\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '7')
			{
				binValue = "0111\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '8')
			{
				binValue = "1000\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '9')
			{
				binValue = "1001\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == 'A' || decimal[i] == 'a')
			{
				binValue = "1010\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == 'B' || decimal[i] == 'b')
			{
				binValue = "1011\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == 'C' || decimal[i] == 'c')
			{
				binValue = "1100\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == 'D' || decimal[i] == 'd')
			{
				binValue = "1101\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == 'E' || decimal[i] == 'e')
			{
				binValue = "1110\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == 'F' || decimal[i] == 'f')
			{
				binValue = "1111\0";
				strcat(binFinalAnswer,binValue);
			}
		}
		decimal = strtok(NULL, ".");
		if(decimal != NULL) /*If there exists a decimal point in the input string, a . is appended at the end of binFinalAnswer, and the binary value of the hex number on the right side of the decimal point is then computed.*/
		{
			i = strlen(binFinalAnswer);
			binFinalAnswer[i] = '.' ;
		}
	}
	return binFinalAnswer; /*Returns the final string*/
}

char* octtoBin(char* inputData) /*Function which acts the same way as hextoBin but does it for converting an octal number to binary.*/
{
	char *decimal = strtok(inputData,".");
	int octLength = strlen(inputData) *3;
	int decimalLength;
	char *binFinalAnswer = (char *)malloc(octLength);
	char *binValue = (char *)malloc(4);
	int i;
	while(decimal != NULL)
	{
		decimalLength = strlen(decimal);
		for(i = 0; i < decimalLength; i++)
		{
			if(decimal[i] == '0')
			{
				binValue = "000\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '1')
			{
				binValue = "001\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '2')
			{
				binValue = "010\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '3')
			{
				binValue = "011\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '4')
			{
				binValue = "100\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '5')
			{
				binValue = "101\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '6')
			{
				binValue = "110\0";
				strcat(binFinalAnswer,binValue);
			}
			if(decimal[i] == '7')
			{
				binValue = "111\0";
				strcat(binFinalAnswer,binValue);
			}
		}
		decimal = strtok(NULL, ".");
		if(decimal != NULL)
		{
			i = strlen(binFinalAnswer);
			binFinalAnswer[i] = '.' ;
		}
	}
	return binFinalAnswer;
}

void help() /*Prints the help screen for the program and also exits the program whenever the function is run.*/
{
	printf("dataConverter Help:\ndataConverter <input_type: -b|d|h|o><input data><output_type:-b|d|h|o> where:\n-b: Binary\n-d: Decimal\n-h: Hex\n-o: Octal\n<input data>: can be a fraction. Max number of digits for Binary, Decimal, Octal is 8.\nMax number of digits for Hex is 4.\n");
	exit(0); /*Ensures proper termination of program.*/
}

int main(int argc, char *argv[])
{
	int i;
	int digitCount = 0;
	int inputLength;
	if(argc != 4) /*If no/too few input arguments are given, OR there's more than 3 arguments passed to the program:*/
	{
		fprintf(stderr,"Error: Invalid number of arguments passed.\n"); /*Standard error is printed and help function is run.*/
		help();
	}
	else
	{
		if(strcmp(argv[1],"-b") != 0 && strcmp(argv[1],"-d") != 0 && strcmp(argv[1],"-h") != 0 && strcmp(argv[1],"-o") != 0 && strcmp(argv[3],"-b") != 0 && strcmp(argv[3],"-d") != 0 && strcmp(argv[3],"-h") != 0 && strcmp(argv[3],"-o") != 0) /*Checks that both the input and output arguments are valid ones.*/
		{
			fprintf(stderr,"Error: Invalid input or output type argument given.\n");
			help();
		}
		else
		{
			if(strcmp(argv[1],"-b") == 0) /*If the input value is -b for binary:*/
			{
				inputLength = strlen(argv[2]);
				for(i = 0; i != inputLength; i++) /*Checks the valid input of 1s and 0s are given.*/
				{
					if (argv[2][i] != '0' && argv[2][i] != '1' && argv[2][i] != '.')
					{
						fprintf(stderr,"Error: Binary values can only consist of 1\'s or 0\'s.\n");
						help();
					}
					if(argv[2][i] != '.') /*Counts the number of digits to ensure the input length is not more than 8 (excluding the decimal point)*/
						digitCount++;
				}
				if(digitCount > 8)
				{
					fprintf(stderr,"Error: Maximum number of digits exceeded.\n");
					help();
				}
				if(strcmp(argv[3],"-b") == 0) /*If user wants to go from binary to binary, it prints the input string.*/
					printf("%s\n",argv[2]);
				if(strcmp(argv[3],"-d") == 0)
					printf("%G\n",binToDec(argv[2])); /*If the user wants to go from binary to decimal, it executes the correct function and prints type double with the proper number of decimal places.*/
				if(strcmp(argv[3],"-h") == 0)
					printf("%s\n",binToHex(argv[2]));
				if(strcmp(argv[3],"-o") == 0)
					printf("%s\n",binToOct(argv[2]));
			}
			if(strcmp(argv[1],"-d") == 0) /*If the input type is decimal, does the same checks as if the input type was binary but instead checks that each digit is a valid base 10 number.*/
			{
				inputLength = strlen(argv[2]);
				for(i = 0; i != inputLength; i++)
				{
					if (argv[2][i] != '0' && argv[2][i] != '1' && argv[2][i] != '2' && argv[2][i] != '3' && argv[2][i] != '4' && argv[2][i] != '5' && argv[2][i] != '6' && argv[2][i] != '7' && argv[2][i] != '8' && argv[2][i] != '9' && argv[2][i] != '.')
					{
						fprintf(stderr,"Error: Decimal values can only consist of 0-9.\n");
						help();
					}
					if(argv[2][i] != '.')
						digitCount++;
				}
				if(digitCount > 8)
				{
					fprintf(stderr,"Error: Maximum number of digits exceeded.\n");
					help();
				}
				else
				{
					if(strcmp(argv[3],"-b") == 0)
						printf("%s\n",dectoBin(argv[2]));
					if(strcmp(argv[3],"-d") == 0)
						printf("%s\n",argv[2]);
					if(strcmp(argv[3],"-h") == 0)
						printf("%s\n",binToHex(dectoBin(argv[2])));
					if(strcmp(argv[3],"-o") == 0)
						printf("%s\n",binToOct(dectoBin(argv[2])));
				}
			}
			if(strcmp(argv[1],"-h") == 0) /*See above comments. Performs the same checks but for hex values.*/
			{
				inputLength = strlen(argv[2]);
				for(i = 0; i != inputLength; i++)
				{
					if (argv[2][i] != '0' && argv[2][i] != '1' && argv[2][i] != '2' && argv[2][i] != '3' && argv[2][i] != '4' && argv[2][i] != '5' && argv[2][i] != '6' && argv[2][i] != '7' && argv[2][i] != '8' && argv[2][i] != '9' && argv[2][i] != 'a' && argv[2][i] != 'A' && argv[2][i] != 'b' && argv[2][i] != 'B' && argv[2][i] != 'c' && argv[2][i] != 'C' && argv[2][i] != 'd' && argv[2][i] != 'D' && argv[2][i] != 'e' && argv[2][i] != 'E' && argv[2][i] != 'f' && argv[2][i] != 'F' && argv[2][i] != '.')
					{
						fprintf(stderr,"Error: Hex values can only consist of 0-9 & A-F.\n");
						help();
					}
					if(argv[2][i] != '.')
						digitCount++;
				}
				if(digitCount > 4)
				{
					fprintf(stderr,"Error: Maximum number of digits exceeded.\n");
					help();
				}
				else
				{
					if(strcmp(argv[3],"-b") == 0)
						printf("%s\n",hextoBin(argv[2]));
					if(strcmp(argv[3],"-d") == 0)
						printf("%G\n",binToDec(hextoBin(argv[2])));
					if(strcmp(argv[3],"-h") == 0)
						printf("%s\n",argv[2]);
					if(strcmp(argv[3],"-o") == 0)
						printf("%s\n",binToOct(hextoBin(argv[2])));
				}
			}
			if(strcmp(argv[1],"-o") == 0) /*See above comments. Does the same checks but for octal numbers.*/
			{
				inputLength = strlen(argv[2]);
				for(i = 0; i != inputLength; i++)
				{
					if (argv[2][i] != '0' && argv[2][i] != '1' && argv[2][i] != '2' && argv[2][i] != '3' && argv[2][i] != '4' && argv[2][i] != '5' && argv[2][i] != '6' && argv[2][i] != '7' && argv[2][i] != '.')
					{
						fprintf(stderr,"Error: Octal values can only consist of 0-7.\n");
						help();
					}
					if(argv[2][i] != '.')
						digitCount++;
				}
				if(digitCount > 8)
				{
					fprintf(stderr,"Error: Maximum number of digits exceeded.\n");
					help();
				}
				else
				{
					if(strcmp(argv[3],"-b") == 0)
						printf("%s\n",octtoBin(argv[2]));
					if(strcmp(argv[3],"-d") == 0)
						printf("%G\n",binToDec(octtoBin(argv[2])));
					if(strcmp(argv[3],"-h") == 0)
						printf("%s\n",binToHex(octtoBin(argv[2])));
					if(strcmp(argv[3],"-o") == 0)
						printf("%s\n",argv[2]);
				}
			}
		}
	}
	return 0; /*In order to meet C standards, the main function must return an int. 0 indicates successful program execution.*/
}
