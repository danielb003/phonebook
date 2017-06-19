#include "addressbook.h"

/**
* This class is used for user input
**/

int main(int argc, char ** argv)
{
    	char input[INPUT_LENGTH+EXTRA_SPACES];
	char inputToken[20], inputToken2[20], inputToken3[20], inputToken4[20] = "";
	int i;
	Boolean done = FALSE, allowUnload = FALSE, commandLineArg = FALSE, isT2Digit = FALSE, isT4Digit = FALSE;
	AddressBookList * addressBookList;
	/*addressBookList->head = NULL;
	addressBookList->current = NULL;
	addressBookList->tail = NULL;*/
	
	if(argc > 1) {
		showStudentInformation();
		printf("\n> File name specified through the command-line arguement.\n");
		commandLineArg = TRUE;
		goto LOAD;
	}
		
	showStudentInformation();
	
	do {
		printf("\nEnter your command: ");
		if(!fgets(input, sizeof(input), stdin)) {
			return EXIT_SUCCESS;
		}
		sscanf(input,"%s %[^,],%[^,],%s", inputToken, inputToken2, inputToken3, inputToken4);
		/** Implemented to test tokenization
		  * printf(
		  * "Token 1: %s \n"
		  * "Token 2: %s \n"
		  * "Token 3: %s \n"
		  * "Token 4: %s \n", inputToken, inputToken2, inputToken3, inputToken4);
		  **/
		inputToken2[strlen(inputToken2) - 1] = '\0';
		for(i=0; i<strlen(inputToken2); i++) {
			if(isdigit(inputToken2[i])) {
				isT2Digit = TRUE;
			} else {
				isT2Digit = FALSE;
				break;
			}
		}
		for(i=0; i<strlen(inputToken4); i++) {
			if(isdigit(inputToken4[i])) {
				isT4Digit = TRUE;
			} else {
				isT4Digit = FALSE;
				break;
			}
		}
		/*inputToken2[strlen(inputToken2) - 1] = '\0';*/
		if(input[strlen(input) - 1] != '\n') {
			readRestOfLine();
			printf("Input too long");
			continue;
		} else {
			int moves = 0;
			int id;
			input[strlen(input) - 1] = '\0';
			if(strcmp(COMMAND_LOAD, inputToken) == 0 && strlen(inputToken2) > 0) {
				LOAD:if(commandLineArg == TRUE) {
					addressBookList = commandLoad(argv[1]);
					allowUnload = TRUE;
					commandLineArg = FALSE;
				} else {
					addressBookList = commandLoad(inputToken2);
					allowUnload = TRUE;
				}
			} else if(strcmp(COMMAND_UNLOAD, inputToken) == 0 && strlen(inputToken2) == 0) {
				printf("> This list is unloaded.");
				if(allowUnload == TRUE) {
					commandUnload(addressBookList);
					allowUnload = FALSE;
				}
			} else if(strcmp(COMMAND_DISPLAY, inputToken) == 0) {
				commandDisplay(addressBookList);
			} else if(strcmp(COMMAND_FORWARD, inputToken) == 0 && isT2Digit == TRUE) {
				moves = strtol(inputToken2,NULL,10);
				commandForward(addressBookList,moves);
			} else if(strcmp(COMMAND_BACKWARD, inputToken) == 0 && isT2Digit == TRUE) {	
				moves = strtol(inputToken2,NULL,10);
				commandBackward(addressBookList,moves);
			} else if(strcmp(COMMAND_INSERT, inputToken) == 0 && isT2Digit == TRUE && strlen(inputToken3) > 0 && isT4Digit == TRUE) {
				id = strtol(inputToken2,NULL,10);
				printf("id: %d",id);
				inputToken4[strlen(inputToken4)] = '\n';
				commandInsert(addressBookList,id,inputToken3,inputToken4);
			} else if(strcmp(COMMAND_ADD, inputToken) == 0 && strlen(inputToken2) == 10) {
				commandAdd(addressBookList,inputToken2);
			} else if(strcmp(COMMAND_FIND, inputToken) == 0 && strlen(inputToken2) > 0) {
				commandFind(addressBookList,inputToken2);
			} else if(strcmp(COMMAND_DELETE, inputToken) == 0) {
				commandDelete(addressBookList);
				printf("delete");
			} else if(strcmp(COMMAND_REMOVE, inputToken) == 0 && strlen(inputToken2) == 10) {
				commandRemove(addressBookList,inputToken2);
			} else if(strcmp(COMMAND_SORT, inputToken) == 0) {
				printf("sort");
			} else if(strcmp(COMMAND_SORT_NAME, inputToken) == 0) {
				printf("sort by name");
			} else if(strcmp(COMMAND_SORT_ID, inputToken) == 0) {
				printf("sort by id");
			} else if(strcmp(COMMAND_SAVE, inputToken) == 0 && strlen(inputToken2) > 0) {
				commandSave(addressBookList,inputToken2);
			} else if(strcmp(COMMAND_QUIT, inputToken) == 0) {
				done = TRUE;
			} else {
				printf("Invalid Input");
			}
		}
		memset(inputToken2,0,sizeof(inputToken2));
	} while(!done);

	printf("> Goodbye. \n\n");

	return EXIT_SUCCESS;
}

void showStudentInformation() 
{
	printf("\n-----------------------------------------------------------------");
	printf("\nStudent name: Daniel Bellino");
	printf("\nStudent number: s3399062");
	printf("\nAdvanced Programming Techniques, Assignment Two, Semester 1, 2017");
	printf("\n-----------------------------------------------------------------\n");
}
