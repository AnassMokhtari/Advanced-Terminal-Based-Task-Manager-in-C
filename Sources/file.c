#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "task.h"
#include "list.h"
#include "stack.h"
#include "tree.h"

#define FILENAME "tasks.dat"

/**
 * @brief Saves all tasks in the list to a binary file.
 *
 * Writes each task to "tasks.dat" in binary format.
 *
 * @param head Pointer to the head of the list.
 */
void file_saveTasks(List *head) {
    FILE *file = fopen(FILENAME, "wb");
    if (!file) {
        printf("Failed to open file for saving.\n");
        return;
    }

    List *current = head;
    int count = 0;
    while (current) {
        count++;
        current = current->next;
    }

    fwrite(&count, sizeof(int), 1, file);
    current = head;
    while (current) {
        fwrite(current->task, sizeof(Task), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Saving tasks to file");
    loadingBar(10);
    printf("Tasks saved successfully.\n");
}

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
List* file_loadTasks(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("No saved tasks found or failed to open file.\n");
        return head;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        printf("Error reading task count.\n");
        return head;
    }

    list_freeAll(head, stack, id_tree, priority_tree, status_tree);
    head = NULL;

    for (int i = 0; i < count; i++) {
        Task *new_task = malloc(sizeof(Task));
        if (!new_task) {
            printf("Failed to allocate memory for task.\n");
            continue;
        }
        if (fread(new_task, sizeof(Task), 1, file) != 1) {
            free(new_task);
            printf("Error reading task data.\n");
            continue;
        }

        List *new_node = malloc(sizeof(List));
        if (!new_node) {
            free(new_task);
            printf("Failed to allocate memory for list node.\n");
            continue;
        }

        new_node->task = new_task;
        new_node->next = head;
        head = new_node;
        listCounter_increment();
        tree_insert(id_tree, new_task);
        tree_insert(priority_tree, new_task);
        tree_insert(status_tree, new_task);
    }

    fclose(file);
    printf("Loading tasks from file");
    loadingBar(10);
    printf("Tasks loaded successfully.\n");
    return head;
}
