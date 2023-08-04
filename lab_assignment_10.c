#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* next[27]; 
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *node = pTrie;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index;
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            index = word[i] - 'a';
        }
        else
        {
            index = 26; 
        }

        if (node->next[index] == NULL)
        {
            node->next[index] = (struct Trie *)malloc(sizeof(struct Trie));
            node->next[index]->count = 0;

            for (int j = 0; j < 27; ++j)
            {
                node->next[index]->next[j] = NULL;
            }
        }
        node = node->next[index];
    }
    node->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *node = pTrie;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index;
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            index = word[i] - 'a';
        }
        else
        {
            index = 26; 
        }

        if (node->next[index] == NULL)
            return 0; 

        node = node->next[index];
    }
    return node->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie)
    {
        for (int i = 0; i < 27; i++)
        {
            deallocateTrie(pTrie->next[i]);
        }
        free(pTrie);
    }
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *newTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (newTrie)
    {
        newTrie->count = 0;
        for (int i = 0; i < 27; i++)
        {
            newTrie->next[i] = NULL;
        }
    }
    return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    int numWords = 0;
    char buffer[256];

    
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = 0; 
        pInWords[numWords] = strdup(buffer); 
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}