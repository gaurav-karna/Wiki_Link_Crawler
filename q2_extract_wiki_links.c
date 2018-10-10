// GAURAV KARNA
// ID - 260723118


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void myPrinter (char sentence[]) {
	// aux method verifies that the keywords given in A_2 are in the string
	const char *toCheck;
	const char *href;
	const char *title;
	toCheck = sentence;
	char the_href[100] = "<a href=\"/wiki/";
	char the_title[100] = "title=";
	// two pointers declared to feed into strstr method
	char *check1;
	char *check2;

	check1 = strstr(sentence, the_href);
	check2 = strstr(sentence, the_title);

	// if neither is NULL, we know that both substrings are found
	if ((check1 != NULL) && (check2 != NULL)) {
		// add 15 since that is the length of "<a href=\"/wiki/"
		// afte which the page_name will be found, until a '"' is reached 
		check1+=15;
		char toPrint = *check1;
		while (toPrint != '\"') {
			// keep printing chars of the page_name
			printf ("%c", toPrint);
			check1++;
			toPrint = *check1;
			// while condition ensures we do not take anything after the end of the page_name
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	// Various Error Checks to make sure arguments are correct
	if (argc != 2) {
		printf ("Only one argument (file name) required.\n");
		exit(1);
	}
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf ("The given file does not exist or it is empty. \n");
		exit(1);
	}
	// Initialize sample char and char array (string)
	char input_char = 'a';
	char sentence [5000];
	// iterate through every character in the file
	while ((input_char = fgetc(fp)) != EOF) {
		char check = input_char;
		// Match for any '<' and then 'a'
		if (check == '<') {
			if ((input_char = fgetc(fp)) != EOF) {
				char check = input_char;
				if (check == 'a') {
					// when a '<a' is found, it is safe to assume I may have a href
					sentence[0] = '<';
					sentence[1] = 'a';
					int cnt = 2;
					// initialize our string with the '<a' and keep storing chars until
					// I reach a '>', after which I know that the page_name will not be
					while ((input_char = fgetc(fp)) != EOF) {
						//check = *input_char;
						check = input_char;
						if (check == '>') {
							sentence[cnt] = '>';
							sentence[cnt++] = '\0';
							// adding the Null breaker, I feed the string into an aux method
							myPrinter(sentence);
							break;
						} else {
							sentence[cnt] = check;
							cnt++;
						}
					}
				}
			}
		}
	}
}



