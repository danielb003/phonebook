#include "addressbook_array.h"

/**
* Note this file is NOT to contain console output,
* meaning printf's are NOT to be present in this file.
*/

AddressBookArray * createAddressBookArray()
{
    /**
     * Allocates and initialises a new AddressBookArray.
     * malloc or calloc are expected to be used to create the
     * AddressBookArray memory.
     * 
     * If memory cannot be allocated for the array NULL is returned.
     * 
     * Note telephones should be initialised to NULL.
     */
	AddressBookArray * addressBookArray = malloc(sizeof(*addressBookArray));
	if(addressBookArray == NULL) {
		printf("\nUnable to malloc addressBookArray");
		return NULL;
	}
	addressBookArray->size = 0;
	addressBookArray->telephones = NULL;

    	return addressBookArray;
}

void freeAddressBookArray(AddressBookArray * array)
{
    /**
     * Free's all telephones within the array and the AddressBookArray itself.
     */
	if(array != NULL) {
		int i;
		for(i=0; i<array->size; i++) {
			free(array->telephones[i]);
		}
		free(array);
	}
}

Boolean addTelephone(AddressBookArray * array, char * telephone)
{
    /**
     * Adds the provided telephone to the telephones array and returns TRUE.
     * 
     * If the telephone memory cannot be allocated
     * then FALSE is returned.
     * 
     */
	char * newTelephone = malloc(TELEPHONE_LENGTH);	
	strcpy(newTelephone,telephone);

	array->telephones = realloc(array->telephones,
				sizeof(*array->telephones) * (array->size + 1));
	if(array->telephones == NULL) {
		printf("\nrealloc of telephones failed!");
		return FALSE;
	}

	array->telephones[array->size] = newTelephone;
	array->size++;

    	return TRUE;
}

Boolean removeTelephone(AddressBookArray * array, char * telephone)
{
   /**
    * Removes the provided telephone from the telephones array and
    * returns TRUE.
    * 
    * If the telephone does not exist or memory cannot be reallocated
    * then FALSE is returned.
    * 
    */
	int i, getIndex;
	Boolean validRemove = FALSE;

	for(i=0; i<array->size; i++) {
		if(strcmp(array->telephones[i],telephone) == 0) {
			validRemove = TRUE;
			getIndex = i;	
		}
	}
	
	if(validRemove == FALSE) {
		return FALSE;
	}
	if(array->size > 1) {
		for(i=getIndex; i<array->size; i++) {
			array->telephones[i] = array->telephones[i+1];
			if(i == array->size-1 && validRemove == TRUE) {
				array->telephones = realloc(array->telephones,
						sizeof(*array->telephones) * (array->size - 1));
				if(array->telephones == NULL) {
					printf("\nrealloc of telephones failed!");
					return FALSE;
				}
				array->size--;
				free(array->telephones[i+1]); 
			}
		}
	} else {
		array->size--;
		free(array->telephones[0]);
		free(array->telephones);
		array->telephones = NULL;
	}

    	return TRUE;
}

char * findTelephone(AddressBookArray * array, char * telephone)
{
    /**
     * Returns the telephone that matches the telephone provided.
     * 
     * If no telephone exists then NULL is returned.
     */

    return NULL;
}
