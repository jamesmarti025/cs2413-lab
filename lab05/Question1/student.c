/*
Question 1: Two Sum

Description:
Given an array of integers nums and an integer target, return the indices
of the two numbers such that they add up to target.

You may assume that each input has exactly one solution, and you may not
use the same element twice.

For this lab, you should solve the problem using a hash-based idea.

Function:
int* twoSum(int* nums, int numsSize, int target, int* returnSize);

Notes:
- Return a dynamically allocated array of size 2.
- Set *returnSize = 2 before returning.
- The returned array will be freed by the caller.

Example:
Input:  nums = [2, 7, 11, 15], target = 9
Output: [0, 1]

Hint:
As you scan the array, for each nums[i], think about whether the value
(target - nums[i]) has already appeared before.
*/

#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

#define TABLE_SIZE 1009

static int hash(int key);
static void insert(Node* table[], int key, int value);
static int find(Node* table[], int key, int* value);
static void freeTable(Node* table[]);

/*
Return an array of size 2 containing the indices of the two numbers
whose sum equals target.
*/
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Node* table[TABLE_SIZE] = { NULL };

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex;

        if (find(table, complement, &complementIndex)) {
            int* result = (int*)malloc(2 * sizeof(int));
            result[0] = complementIndex;
            result[1] = i;
            *returnSize = 2;

            freeTable(table);
            return result;
        }

        insert(table, nums[i], i);
    }

    freeTable(table);
    *returnSize = 0;
    return NULL;
}

/*
Optional helper: compute a hash index for a key.
*/
static int hash(int key) {
    int h = key % TABLE_SIZE;
    return (h < 0) ? (h + TABLE_SIZE) : h;
}

/*
Optional helper: insert (key, value) into the hash table.
*/
static void insert(Node* table[], int key, int value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
}

/*
Optional helper: search for key in the hash table.
If found, store the associated value in *value and return 1.
Otherwise return 0.
*/
static int find(Node* table[], int key, int* value) {
    int index = hash(key);
    Node* curr = table[index];
    while (curr != NULL) {
        if (curr->key == key) {
            *value = curr->value;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

/*
Optional helper: free all memory used by the hash table.
*/
static void freeTable(Node* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        table[i] = NULL;
    }
}