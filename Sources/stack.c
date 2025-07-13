#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define MAX_STACK_SIZE 10

/**
 * @brief Creates a new empty stack.
 *
 * Allocates memory for the stack and initializes it with no tasks.
 *
 * @return Pointer to the new Stack, or NULL if allocation fails.
 */
Stack* stack_create() {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

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
void stack_push(Stack *stack, Task *task, TaskPosition position, int target_id) {
    if (!stack || !task) return;

    // If stack is full, remove oldest task (bottom of stack)
    if (stack->size >= MAX_STACK_SIZE) {
        StackNode *current = stack->top;
        StackNode *prev = NULL;
        while (current->next) {
            prev = current;
            current = current->next;
        }
        if (prev) {
            prev->next = NULL;
            free(current->task);
            free(current);
            stack->size--;
        }
    }

    StackNode *node = malloc(sizeof(StackNode));
    if (!node) return;
    node->task = task;
    node->position = position;
    node->target_id = target_id;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

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
Task* stack_pop(Stack *stack, TaskPosition *position, int *target_id) {
    if (!stack || !stack->top) return NULL;
    StackNode *node = stack->top;
    Task *task = node->task;
    *position = node->position;
    *target_id = node->target_id;
    stack->top = node->next;
    free(node);
    stack->size--;
    return task;
}

/**
 * @brief Peeks at the top task on the stack without removing it.
 *
 * @param stack Pointer to the stack.
 * @return Pointer to the top Task, or NULL if the stack is empty.
 */
Task* stack_peek(Stack *stack) {
    if (!stack || !stack->top) return NULL;
    return stack->top->task;
}

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack Pointer to the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int stack_isEmpty(Stack *stack) {
    return !stack || !stack->top;
}

/**
 * @brief Returns the number of tasks in the stack.
 *
 * @param stack Pointer to the stack.
 * @return Number of tasks in the stack.
 */
int stack_getSize(Stack *stack) {
    return stack ? stack->size : 0;
}

/**
 * @brief Clears all tasks from the stack.
 *
 * Frees all tasks and nodes in the stack, resetting it to empty.
 *
 * @param stack Pointer to the stack.
 */
void stack_clear(Stack *stack) {
    while (!stack_isEmpty(stack)) {
        TaskPosition pos;
        int target_id;
        Task *task = stack_pop(stack, &pos, &target_id);
        free(task);
    }
}

/**
 * @brief Frees the stack and all its tasks.
 *
 * Clears all tasks and frees the stack structure itself.
 *
 * @param stack Pointer to the stack.
 */
void stack_free(Stack *stack) {
    stack_clear(stack);
    free(stack);
}
