#ifndef LIST_H
#define LIST_H
#include "task.h"
#include "stack.h"
#include "tree.h"

/**
 * @brief Structure for a linked list node containing a task.
 */
typedef struct List {
    Task *task;           // Pointer to a dynamically allocated Task
    struct List *next;    // Pointer to the next node
} List;

/**
 * @brief Adds a new task to the head of the linked list.
 *
 * Allocates memory for a new List node and Task, fills the task with user input,
 * and inserts it at the head of the list. Updates the task counter and BSTs.
 *
 * @param head Pointer to the current head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 * @return New head of the list.
 */
List* list_addToHead(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Adds a new task to the end of the linked list.
 *
 * Allocates memory for a new List node and Task, fills the task with user input,
 * and appends it to the end of the list. Updates the task counter and BSTs.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 */
void list_addToEnd(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Adds a new task after a node with a given ID.
 *
 * Prompts for the ID of the task to insert after, allocates memory for a new List
 * node and Task, and inserts it. Updates the task counter and BSTs.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 */
void list_addToMiddle(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Prints all tasks in the linked list.
 *
 * Traverses the list from head to tail and prints each task using printTask().
 *
 * @param head Pointer to the head of the list.
 */
void list_printAll(List *head);

/**
 * @brief Removes the first task (head) from the list.
 *
 * Pushes the task to the undo stack and frees the List node. Updates the task counter.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 * @return New head of the list (could be NULL).
 */
List* list_removeFromHead(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Removes the last task from the list.
 *
 * Pushes the task to the undo stack and frees the List node. Updates the task counter.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 */
void list_removeFromEnd(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Removes a task by its ID.
 *
 * Prompts for the ID, pushes the task to the undo stack, and frees the List node.
 * Updates the task counter.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 * @return New head of the list (in case the head was removed).
 */
List* list_removeByID(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Frees all tasks and nodes in the list.
 *
 * Pushes all tasks to the undo stack and frees all List nodes. Resets the task counter.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 */
void list_freeAll(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Restores a task from the undo stack to its original position.
 *
 * Pops a task from the stack, checks for ID conflicts, and inserts it back into the list
 * at its original position (head, middle, or end). Updates the task counter and BSTs.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 * @return New head of the list (if restored to head).
 */
List* list_restoreTask(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Updates the priority and status of a task by its ID.
 *
 * Prompts for the task ID, updates its priority and status, and rebuilds the BSTs
 * to reflect the changes.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 */
void list_updateTask(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

/**
 * @brief Checks if a task ID exists in the list.
 *
 * @param head Pointer to the head of the list.
 * @param id The ID to check for.
 * @return 1 if the ID exists, 0 otherwise.
 */
int list_hasID(List *head, int id);

/**
 * @brief Increments the task counter.
 */
void listCounter_increment();

/**
 * @brief Decrements the task counter.
 */
void listCounter_decrement();

/**
 * @brief Returns the current count of tasks in the list.
 *
 * @return Number of tasks in the list.
 */
int listCounter_get();

/**
 * @brief Resets the task counter to zero.
 */
void listCounter_reset();

/**
 * @brief Displays a simple terminal-based loading animation.
 *
 * Prints a progress-style loading bar using dots (.) with a short delay
 * between each dot to simulate loading.
 *
 * Example Output:
 *  [..........] Done!
 *
 * @param total The number of dots to print (represents progress steps).
 */
void loadingBar(int total);

#endif
