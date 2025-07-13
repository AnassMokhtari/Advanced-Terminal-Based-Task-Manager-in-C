#ifndef FILE_H
#define FILE_H

#include "list.h"

/**
 * @brief Saves all tasks in the list to a binary file.
 *
 * Writes each task to "tasks.dat" in binary format.
 *
 * @param head Pointer to the head of the list.
 */
void file_saveTasks(List *head);

/**
 * @brief Loads tasks from a binary file into the list.
 *
 * Reads tasks from "tasks.dat" and reconstructs the list, updating BSTs and counter.
 *
 * @param head Pointer to the head of the list.
 * @param stack Pointer to the undo stack.
 * @param id_tree Pointer to the BST sorted by ID.
 * @param priority_tree Pointer to the BST sorted by priority.
 * @param status_tree Pointer to the BST sorted by status.
 * @return New head of the list.
 */
List* file_loadTasks(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree);

#endif
