#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 31

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

// Fill out this structure
struct HashType
{
	struct RecordType record;
	char status;	

};

struct Linkedlist{
	struct HashType hash;
	struct Linkedlist* next;
};

// Compute the hash function
int hash(int x)
{

	 return x % (SIZE/2);

}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n");
}
// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct Linkedlist *pHashArray, int hashSz)
{
	int i;

	printf("\nRecords from Hash Table:\n");
	for (i=0;i<hashSz;++i){
		struct Linkedlist *temp = pHashArray + i;
		if (temp->hash.status != 'e') 
        {
            printf("Index %d:\n", i);

            while (temp != NULL)
            {
                printf("\tID: %d \tName: %c \tOrder: %d\n", temp->hash.record.id, temp->hash.record.name, temp->hash.record.order);

                temp = temp->next;
			}
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct Linkedlist *arr = malloc(sizeof(struct Linkedlist)*SIZE);

	for (int i = 0; i < SIZE; i++)
    {
        arr[i].hash.status = 'e'; // 'e' indicates the slot is empty
        arr[i].next = NULL;
    }

    for (int i = 0; i < recordSz; i++)
    {
        int index = hash(pRecords[i].id);

        if (arr[index].hash.status == 'e')
        {
            arr[index].hash.record = pRecords[i];
            arr[index].hash.status = 'f'; 
            arr[index].next = NULL;
        }
        else
        {
            struct Linkedlist* newNode = malloc(sizeof(struct Linkedlist));
            newNode->hash.record = pRecords[i];
            newNode->hash.status = 'f';
            newNode->next = arr[index].next;
            arr[index].next = newNode;
        }
    }

    
    displayRecordsInHash(arr, SIZE);

    
    for (int i = 0; i < SIZE; i++)
    {
        struct Linkedlist* temp = arr[i].next;
        while (temp != NULL)
        {
            struct Linkedlist* nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }
    }
    free(arr);

   
    free(pRecords);

    return 0;
}