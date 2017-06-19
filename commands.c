#include "commands.h"

AddressBookList * commandLoad(char * fileName)
{
    /** Loads the given file and returns a new AddressBookList.
      * 
      * If the file doesn't exist or corruption is found in the file
      * then NULL is returned.
      **/
	AddressBookList * addressBookList = createAddressBookList();
	AddressBookNode * addressBookNode;
	
	FILE *fp = fopen(fileName, "r");
	char inputLine[MAX_LINE_LENGTH];
	printf("> Opening the file %s.\n",fileName);
	
	if(fp == NULL) {
		printf("Error: Unable to find specified file.\n");
		return NULL;
	}
	if(addressBookList == NULL) {
		printf("addressBookList failed");
		return NULL;
	}

	printf("> Loading the file ...\n");	
	addressBookList->size = 0;
	while(fgets(inputLine,MAX_LINE_LENGTH,fp) != NULL) {
		if(*inputLine == '#') {
			continue;
		} else {
			char * pt;
			char * name;
			int id, dataCount = 0;
			Boolean boolean = FALSE;
			pt = strtok(inputLine,",");
			addressBookList->size++;
			while(pt != NULL) {
				if(dataCount == 0) {
					id = atoi(pt);	
				} else if(dataCount == 1) {
					name = pt;
					name[strcspn(name,"\n")] = 0;
					addressBookNode = createAddressBookNode(id,name);
				} else if(dataCount > 1) {
					pt[strcspn(pt,"\n")] = 0;
					boolean = addTelephone(addressBookNode->array,pt);
				}
				dataCount++;
				pt = strtok(NULL,",");
			}
			boolean = insertNode(addressBookList,addressBookNode);
		}
	}
	printf("> %d phone book entries have been loaded from the file\n",addressBookList->size);
	printf("> Closing the file.\n");
	fclose(fp);


   	return addressBookList;
}

void commandUnload(AddressBookList * list)
{
	AddressBookNode * temp = list->head;
		
	while(temp != NULL) {
		freeAddressBookNode(temp);
		temp = temp->nextNode;	
	}
	freeAddressBookList(list);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

void commandDisplay(AddressBookList * list)
{ 
	int i, serialCount = 0;
	AddressBookNode * temp = list->head;
	printf("---------------------------------------------\n");
	printf("| Pos | Serial | ID  | Name    | Telephones |\n");
	printf("---------------------------------------------\n");

	while(temp != NULL) {
		serialCount++;
		if(temp == list->current) {
			printf("| CUR | %-6d ",serialCount);
		} else {
			printf("|     | %-6d ",serialCount);
		}
		printf("| %d | %-7s | ",temp->id,temp->name);
		if(temp->array->size == 0) {
			printf("\n");
		} else {
			for(i = 0; i<temp->array->size; i++) {
				if(i < temp->array->size-1) {
					printf("%s,",temp->array->telephones[i]);
				} else {
					printf("%s\n",temp->array->telephones[i]);
				}
			}
		}
		temp = temp->nextNode;
	}

	printf("---------------------------------------------\n");
	printf("| Total phone book entries: %-3d             |\n",serialCount);
	printf("---------------------------------------------\n");
}

void commandForward(AddressBookList * list, int moves)
{ 
	Boolean done = FALSE;
	done = forward(list,moves);		
	printf("commandForward complete\ndone: %d\n",done);
}

void commandBackward(AddressBookList * list, int moves)
{ 
	Boolean done = FALSE;
	done = backward(list,moves);
	printf("commandBackward complete\ndone: %d\n",done);
}

void commandInsert(AddressBookList * list, int id, char * name, char * telephone)
{
	AddressBookNode * temp;
	Boolean boolean = FALSE;
	/** Test method arguements
	  * printf("id: %d\nname: %s\ntelephone: %s\n",id,name,telephone);
	  **/

	temp = createAddressBookNode(id,name);
	boolean = addTelephone(temp->array,telephone);
	boolean = insertNode(list,temp);
}

void commandAdd(AddressBookList * list, char * telephone)
{ 
	Boolean boolean = FALSE;
	if(list->current != NULL) {
		boolean = addTelephone(list->current->array,telephone);
	} else {
		printf("> Unable to add telephone.\n");
	}
}

void commandFind(AddressBookList * list, char * name)
{
	list->current = findByName(list,name);
}

void commandDelete(AddressBookList * list)
{ 
	Boolean boolean = FALSE;
	if(list->current != NULL) {
		boolean = deleteCurrentNode(list);
	} else {
		printf("> Unable to delete node.");
	}
}

void commandRemove(AddressBookList * list, char * telephone)
{ 
	Boolean boolean = FALSE;	
	if(list->current != NULL) {
		boolean = removeTelephone(list->current->array,telephone);
		if(boolean == FALSE) {
			printf("> Unable to remove telephone.\n");
		}
	} else {
		printf("> Unable to remove telephone.\n");
	}
}

void commandSort(
    AddressBookList * list,
    int sort(const void * node, const void * otherNode))
{
    /* Sort the nodes within list in ascending order using the
     * provided sort function to compare nodes.
     */
}

int compareName(const void * node, const void * otherNode)
{
    /* Compare node name with otherNode name.
     * 
     * return < 0 when node name is smaller than otherNode name.
     * return 0 when the names are equal.
     * return > 0 when node name is bigger than otherNode name.
     */
    return 0;
}

int compareID(const void * node, const void * otherNode)
{
    /* Compare node id with otherNode id.
     * 
     * return < 0 when node id is smaller than otherNode id.
     * return 0 when the ids are equal.
     * return > 0 when node id is bigger than otherNode id.
     */
    return 0;
}

void commandSave(AddressBookList * list, char * fileName)
{ 
	int i;
	FILE *fp = fopen(fileName,"w");
	AddressBookNode * temp;
	printf("> Opening file %s\n",fileName);

	if(fp == NULL) {
		printf("Error: Unable to find specified file.");
	} else {
		printf("> Writing list content to file...");
		temp = list->current;
		while(temp != NULL) {
			fprintf(fp,"%d,%s",temp->id,temp->name);
			if(temp->array->size == 0) {
				fprintf(fp,"\n");
			} else {
				for(i=0; i<temp->array->size; i++) {
					if(i < temp->array->size-1) {
						fprintf(fp,",%s",temp->array->telephones[i]);
					} else {
						fprintf(fp,",%s\n",temp->array->telephones[i]);
					}
				}
			}
			temp = temp->nextNode;
		}
	}
	printf("\nClosing file.");	
	fclose(fp);
}
