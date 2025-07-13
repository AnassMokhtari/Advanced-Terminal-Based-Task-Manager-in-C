#ifndef STACK_H
#define STACK_H

#include "task.h"

/**
 * @brief Enum for task position in the linked list.
 */
typedef enum {
    POS_HEAD,    // Task was at the head
    POS_MIDDLE,  // Task was in the middle
    POS_END       // Task was at the end
} TaskPosition;

/**
 * @brief Structure for a stack node to store a task and its metadata.
 */
typedef struct StackNode {
    Task *task;              // Pointer to a Task
    TaskPosition position;   // Position in the original list (HEAD, MIDDLE, END)
    int target_id;           // ID of the task to insert after (for MIDDLE)
    struct StackNode *next;  // Pointer to next node in stack
} StackNode;

/**
 * @brief Structure for the stack to store deleted tasks for undo.
 */
typedef struct Stack {
    StackNode *top;          // Pointer to top of stack
    int size;                // Number of tasks in stack
} Stack;

/**
 * @brief Creates a new empty stack.
 *
 * Allocates memory for the stack and initializes it with no tasks.
 *
 * @return Pointer to the new Stack, or NULL if allocation fails.
 */
Stack* stack_create();

/**
 * @brief Pushes a task onto the stack with its position metadata.
 *
 * Stores the task along with its original position and target ID (for middle insertions).
 * Enforces a maximum stack size of 10, freeing the oldest task if necessary.
 *
 * @param stack Pointer to the stack.
 * @param task Pointer to the Task to push.
 * @param position The original position of the task in the list.
 * @param target_id ID of the task to insert after (for POS_MIDDLE).
 */
void stack_push(Stack *stack, Task *task, TaskPosition position, int target_id);

/**
 * @brief Pops a task from the stack along with its position metadata.
 *
 * Removes and returns the top task, along with its position and target ID.
 *
 * @param stack Pointer to the stack.
 * @param position Pointer to store the task's original position.
 * @param target_id Pointer to store the target ID (for POS_MIDDLE).
 * @return Pointer to the popped Task, or NULL if the stack is empty.
 */
Task* stack_pop(Stack *stack, TaskPosition *position, int *target_id);

/**
 * @brief Peeks at the top task on the stack without removing it.
 *
 * @param stack Pointer to the stack.
 * @return Pointer to the top Task, or NULL if the stack is empty.
 */
Task* stack_peek(Stack *stack);

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack Pointer to the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int stack_isEmpty(Stack *stack);

/**
 * @brief Returns the number of tasks in the stack.
 *
 * @param stack Pointer to the stack.
 * @return Number of tasks in the stack.
 */
int stack_getSize(Stack *stack);

/**
 * @brief Clears all tasks from the stack.
 *
 * Frees all tasks and nodes in the stack, resetting it to empty.
 *
 * @param stack Pointer to the stack.
 */
void stack_clear(Stack *stack);

/**
 * @brief Frees the stack and all its tasks.
 *
 * Clears all tasks and frees the stack structure itself.
 *
 * @param stack Pointer to the stack.
 */
void stack_free(Stack *stack);

#endif
