#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/

	int i;
	hashLink* temp;

	assert(ht);

	for(i = 0; i < ht->tableSize; i++) {

		while(ht->table[i]) {

			temp = ht->table[i];
			ht->table[i] = ht->table[i]->next;
			free(temp);

		}

	}

	free(ht->table);

}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/

	hashLink* newLink = (hashLink*)malloc(sizeof(hashLink));
	int index = (int)(labs(stringHash2(k)) % ht->tableSize);

	if(!containsKey(ht, k)) {

		newLink->key = k;
		newLink->value = v;

		newLink->next = ht->table[index];
		ht->table[index] = newLink;

		ht->count++;
		

	} else {

		*atMap(ht, k) = v;

	}

}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/

	int index, hash;
	hashLink* curr;

	assert(ht);
	assert(ht->table);

	hash = stringHash2(k);
	index = (int)(labs(hash) % ht->tableSize);

	curr = ht->table[index];

	while(curr) {

		if(stringHash2(curr->key) == hash) return &(curr->value);

		curr = curr->next;

	}

	return 0;

}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/

	int index, hash;
	hashLink* curr;

	assert(ht);
	assert(ht->table);

	hash = stringHash2(k);
	index = (int)(labs(hash) % ht->tableSize);

	curr = ht->table[index];

	while(curr) {

		if(stringHash2(curr->key) == hash) return 1;

		curr = curr->next;

	}

	return 0;

}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/

	int index, hash;
	hashLink* curr, * prev;

	assert(ht);
	assert(ht->table);

	hash = stringHash2(k);
	index = (int)(labs(hash) % ht->tableSize);
	
	curr = ht->table[index];

	while(curr) {

		if(stringHash2(curr->key) == hash) {
			prev->next = curr->next;
			free(curr);
			return;
		}

		prev = curr;
		curr = curr->next;

	}

}

int sizeMap (struct hashMap *ht)
{  /*write this*/

	assert(ht);
	assert(ht->table);

	return ht->count;

}

int capacityMap(struct hashMap *ht)
{  /*write this*/

	assert(ht);
	assert(ht->table);

	return ht->tableSize;

}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/

	int count = 0, i;

	assert(ht);
	assert(ht->table);

	for(i = 0; i < ht->tableSize; i++) if(ht->table[i] == 0) count++;

	return count;

}

float tableLoad(struct hashMap *ht)
{  /*write this*/

	assert(ht);
	assert(ht->table);

	return (float)ht->count / ht->tableSize;

}
