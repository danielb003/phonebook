#include "addressbook_list.h"

/**
* Note this file is *NOT* to contain console output,
* meaning printf's are *NOT* to be present in this file.
*/

AddressBookList * createAddressBookList()
{
    /**
    * Allocates and initialises a new AddressBookList.
    * malloc or calloc are expected to be used to create the
    * AddressBookList memory.
    * 
    * If memory cannot be allocated for the list NULL is returned.
    * 
    */ 
	AddressBookList * addressBookList = malloc(sizeof(*addressBookList));
	if(addressBookList == NULL) {
		printf("\nUnable to malloc addressBookList");
		return NULL;
	}
	addressBookList->head = NULL;
	addressBookList->current = NULL;
	addressBookList->tail = NULL;
	addressBookList->size = 0;
		
	return addressBookList;
    	
}

void freeAddressBookList(AddressBookList * list)
{
    /**
     * Free's all nodes within the list and the AddressBookList itself.
     * 
     **/
	if(list != NULL) {
		free(list);
		list->size = 0;
	}

}

AddressBookNode * createAddressBookNode(int id, char * name)
{
    /**
    * Allocates and initialises a new AddressBookNode. 
    * 
    * If memory cannot be allocated for the node or array NULL is returned.
    **/
	AddressBookNode * addressBookNode = malloc(sizeof(*addressBookNode));
	if(addressBookNode == NULL) {
		printf("\nUnable to malloc addressBookNode");
		return NULL;
	}
	addressBookNode->id = id;
	strcpy(addressBookNode->name,name);
	addressBookNode->array = createAddressBookArray();
	addressBookNode->previousNode = NULL;
	addressBookNode->nextNode = NULL;

    	return addressBookNode;
}

void freeAddressBookNode(AddressBookNode * node)
{
    /**
    * Free's the array within the node and the AddressBookNode itself.
    **/
	freeAddressBookArray(node->array);

	if(node != NULL) {
		free(node);
	}
}

Boolean insertNode(AddressBookList * list, AddressBookNode * node)
{
    /**
     * Inserts the node into the list and returns TRUE.
     * 
     * If the list already contains a node with the same id
     * then FALSE is returned and the node is not inserted.
     **/
	AddressBookNode * temp = list->head;
	
	if(list->head == NULL) {
		list->head = node;
		list->current = node;
	        list->tail = node;
		return TRUE;
	}

	while(temp != NULL) {
		if(temp->id == node->id) {
			printf("id already exists!\naddress not inserted.");
			return FALSE;
		}
		temp = temp->nextNode;
	}
	
	list->tail->nextNode = node;
	node->previousNode = list->tail;
	list->tail = node;

	/*printf("list->size: %d\n",list->size);
	printf("list->temp->id: %d\n",list->tail->id);
	printf("list->temp->name: %s\n",list->tail->name);
	printf("list->temp->array->size: %d\n",list->tail->array->size);*/

    	return TRUE;
}

Boolean deleteCurrentNode(AddressBookList * list)
{
    /**
     * Delete's and free's the current node in the list and returns TRUE.
     * 
     * If the list has no nodes (i.e., there is no current node)
     * then FALSE is returned.
     */
	if(list->current == NULL) {
		return FALSE;
	}
	freeAddressBookNode(list->current);
    
    	return TRUE;
}

Boolean forward(AddressBookList * list, int forward)
{
    /**
     * Moves the current node forward in the list by the number provided
     * and returns TRUE.
     * 
     * If the current node cannot be moved forward by that many positions
     * then FALSE is returned and current remains unchanged.
     **/
	int i;
	AddressBookNode * temp = list->current;
	for(i=0; i<forward; i++) {
		if(temp->nextNode != NULL) {
			temp = temp->nextNode;
		} else {
			printf("forward failed!\n");
			return FALSE;
		}
	}
	list->current = temp;

    	return TRUE;
}

Boolean backward(AddressBookList * list, int backward)
{
    /**
    * Moves the current node backward in the list by the number provided
    * and returns TRUE.
    * 
    * If the current node cannot be moved backward by that many positions
    * then FALSE is returned and current remains unchanged.
    **/
	int i;
	AddressBookNode * temp = list->current;
	for(i=0; i<backward; i++) {
		if(temp->previousNode != NULL) {
			temp = temp->previousNode;
		} else {
			printf("backward failed!\n");
			return FALSE;
		}
	}
	list->current = temp;

        return TRUE;
}

AddressBookNode * findByID(AddressBookList * list, int id)
{
    /**
     * Returns the node that matches the id provided.
     * 
     * If no node with a matching id exists then NULL is returned.
     */

    return NULL;
}

AddressBookNode * findByName(AddressBookList * list, char * name)
{
    /**
    * Sets current to the first node that matches the name provided
    * and returns this node.
    * 
    * If no node with a matching name exists then NULL is returned
    * and current remains unchanged.
    **/
	AddressBookNode * temp = list->head;

	while(temp != NULL) {
		if(strcmp(temp->name,name) == 0) {
			list->current = temp;
			return temp;
		}
		temp = temp->nextNode;
	}
	
	printf(">Error: Unable to find node.");
    	return NULL;
}
