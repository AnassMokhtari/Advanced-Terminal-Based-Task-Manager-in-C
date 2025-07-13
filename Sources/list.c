#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "list.h"
#include "task.h"
#include "input_utils.h"
#include "stack.h"
#include "tree.h"

static int list_counter = 0;

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
void loadingBar(int total) {
    printf(" [");
    for (int i = 0; i < total; i++) {
        fflush(stdout);
        Sleep(100);
        printf(".");
    }
    printf("] Done!\n");
    Sleep(500);
}

/**
 * @brief Increments the task counter.
 */
void listCounter_increment() {
    list_counter++;
}

/**
 * @brief Decrements the task counter.
 */
void listCounter_decrement() {
    if (list_counter > 0)
        list_counter--;
}

/**
 * @brief Returns the current count of tasks in the list.
 *
 * @return Number of tasks in the list.
 */
int listCounter_get() {
    return list_counter;
}

/**
 * @brief Resets the task counter to zero.
 */
void listCounter_reset() {
    list_counter = 0;
}

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
List* list_addToHead(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    List *new_node = malloc(sizeof(List));
    if (!new_node) {
        printf("Failed to allocate memory for new node.\n");
        return head;
    }

    Task *new_task = malloc(sizeof(Task));
    if (!new_task) {
        printf("Failed to allocate memory for task.\n");
        free(new_node);
        return head;
    }

    fillTask(new_task);
    new_node->task = new_task;
    new_node->next = head;
    listCounter_increment();
    tree_insert(id_tree, new_task);
    tree_insert(priority_tree, new_task);
    tree_insert(status_tree, new_task);

    printf("\nSaving your task");
    loadingBar(10);
    return new_node;
}

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
void list_addToEnd(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    if (head == NULL) {
        printf("The list has not been initialized.\n");
        return;
    }

    Task *new_task = malloc(sizeof(Task));
    if (!new_task) {
        printf("Failed to allocate memory for task.\n");
        return;
    }

    fillTask(new_task);
    List *new_node = malloc(sizeof(List));
    if (!new_node) {
        printf("Failed to allocate memory for list node.\n");
        free(new_task);
        return;
    }

    new_node->task = new_task;
    new_node->next = NULL;
    List *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    listCounter_increment();
    tree_insert(id_tree, new_task);
    tree_insert(priority_tree, new_task);
    tree_insert(status_tree, new_task);

    printf("\nSaving your task");
    loadingBar(10);
}

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
void list_addToMiddle(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    if (head == NULL) {
        printf("The list is not initialized.\n");
        return;
    }

    int target_id = readInt("Enter the ID of the task to insert after: ");
    List *current = head;
    while (current != NULL && current->task->id != target_id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Task with ID %d not found.\n", target_id);
        return;
    }

    Task *new_task = malloc(sizeof(Task));
    if (!new_task) {
        printf("Failed to allocate memory for new task.\n");
        return;
    }

    fillTask(new_task);
    List *new_node = malloc(sizeof(List));
    if (!new_node) {
        printf("Failed to allocate memory for new node.\n");
        free(new_task);
        return;
    }

    new_node->task = new_task;
    new_node->next = current->next;
    current->next = new_node;
    listCounter_increment();
    tree_insert(id_tree, new_task);
    tree_insert(priority_tree, new_task);
    tree_insert(status_tree, new_task);

    printf("\nSaving your task");
    loadingBar(10);
}

/**
 * @brief Prints all tasks in the linked list.
 *
 * Traverses the list from head to tail and prints each task using printTask().
 *
 * @param head Pointer to the head of the list.
 */
void list_printAll(List *head) {
    if (head == NULL) {
        printf("No tasks to display. List is empty.\n");
        return;
    }

    int index = 1;
    List *current = head;
    printf("\n> Task List:\n");
    printf("---------------------------------\n");

    while (current != NULL) {
        printf("\nTask #%d:\n", index);
        printTask(current->task);
        current = current->next;
        index++;
    }

    printf("\nTotal tasks: %d\n\n", listCounter_get());
}

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
List* list_removeFromHead(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    if (head == NULL) {
        printf("List is already empty.\n");
        return NULL;
    }

    List *temp = head;
    stack_push(stack, temp->task, POS_HEAD, 0);
    head = head->next;
    free(temp);
    listCounter_decrement();

    printf("Removing the task");
    loadingBar(10);
    return head;
}

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
void list_removeFromEnd(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    if (head == NULL) {
        printf("List is already empty.\n");
        return;
    }

    if (head->next == NULL) {
        stack_push(stack, head->task, POS_HEAD, 0);
        free(head);
        head = NULL;
        listCounter_decrement();
        printf("Removing the task");
        loadingBar(10);
        return;
    }

    List *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    stack_push(stack, current->next->task, POS_END, 0);
    free(current->next);
    current->next = NULL;
    listCounter_decrement();

    printf("Removing the task");
    loadingBar(10);
}

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
List* list_removeByID(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    int target_id = readInt("Enter the ID of the task to remove: ");
    if (head->task->id == target_id) {
        stack_push(stack, head->task, POS_HEAD, 0);
        List *new_head = head->next;
        free(head);
        listCounter_decrement();
        printf("Removing the task");
        loadingBar(10);
        printf("Task with ID %d removed (it was at the head).\n", target_id);
        return new_head;
    }

    List *current = head;
    int prev_id = current->task->id;
    while (current->next != NULL && current->next->task->id != target_id) {
        prev_id = current->task->id;
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Task with ID %d not found.\n", target_id);
        return head;
    }

    List *to_delete = current->next;
    stack_push(stack, to_delete->task, POS_MIDDLE, prev_id);
    current->next = to_delete->next;
    free(to_delete);
    listCounter_decrement();

    printf("Removing the task");
    loadingBar(10);
    printf("Task with ID %d removed successfully.\n", target_id);
    return head;
}

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
void list_freeAll(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    List *temp;
    while (head != NULL) {
        temp = head;
        stack_push(stack, temp->task, POS_HEAD, 0);
        head = head->next;
        free(temp);
    }

    printf("Removing all tasks ");
    loadingBar(20);
    printf("All tasks cleared and moved to stack.\n");
    listCounter_reset();
}

/**
 * @brief Checks if a task ID exists in the list.
 *
 * @param head Pointer to the head of the list.
 * @param id The ID to check for.
 * @return 1 if the ID exists, 0 otherwise.
 */
int list_hasID(List *head, int id) {
    List *current = head;
    while (current != NULL) {
        if (current->task->id == id) return 1;
        current = current->next;
    }
    return 0;
}

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
List* list_restoreTask(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    TaskPosition position;
    int target_id;
    Task *task = stack_pop(stack, &position, &target_id);
    if (!task) {
        printf("No tasks to undo.\n");
        return head;
    }

    // Check for ID conflict
    if (list_hasID(head, task->id)) {
        printf("Task ID %d already exists. Enter a new ID: ", task->id);
        task->id = readInt("  New ID: ");
        while (list_hasID(head, task->id)) {
            printf("Task ID %d already exists. Enter a different ID: ", task->id);
            task->id = readInt("  New ID: ");
        }
    }

    List *new_node = malloc(sizeof(List));
    if (!new_node) {
        printf("Failed to allocate memory for new node.\n");
        stack_push(stack, task, position, target_id);
        return head;
    }

    new_node->task = task;

    if (position == POS_HEAD || head == NULL) {
        new_node->next = head;
        listCounter_increment();
        tree_insert(id_tree, task);
        tree_insert(priority_tree, task);
        tree_insert(status_tree, task);
        printf("Restoring task with ID %d to head", task->id);
        loadingBar(10);
        printf("Task restored successfully.\n");
        return new_node;
    } else if (position == POS_END) {
        new_node->next = NULL;
        List *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        listCounter_increment();
        tree_insert(id_tree, task);
        tree_insert(priority_tree, task);
        tree_insert(status_tree, task);
        printf("Restoring task with ID %d to end", task->id);
        loadingBar(10);
        printf("Task restored successfully.\n");
        return head;
    } else { // POS_MIDDLE
        List *current = head;
        while (current != NULL && current->task->id != target_id) {
            current = current->next;
        }
        if (current == NULL) {
            new_node->next = head;
            listCounter_increment();
            tree_insert(id_tree, task);
            tree_insert(priority_tree, task);
            tree_insert(status_tree, task);
            printf("Restoring task with ID %d to head (target ID %d not found)", task->id, target_id);
            loadingBar(10);
            printf("Task restored successfully.\n");
            return new_node;
        }
        new_node->next = current->next;
        current->next = new_node;
        listCounter_increment();
        tree_insert(id_tree, task);
        tree_insert(priority_tree, task);
        tree_insert(status_tree, task);
        printf("Restoring task with ID %d after ID %d", task->id, target_id);
        loadingBar(10);
        printf("Task restored successfully.\n");
        return head;
    }
}

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
void list_updateTask(List *head, Stack *stack, Tree *id_tree, Tree *priority_tree, Tree *status_tree) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    int target_id = readInt("Enter the ID of the task to update: ");
    List *current = head;
    while (current != NULL && current->task->id != target_id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Task with ID %d not found.\n", target_id);
        return;
    }

    printf("\n> Updating Task ID %d\n", target_id);
    current->task->priority = (Priority)readIntInRange("  New Priority (1 = High, 2 = Medium, 3 = Low): ", PRIORITY_HIGH, PRIORITY_LOW);
    current->task->status = (Status)readIntInRange("  New Status (1 = Not Started, 2 = In Progress, 3 = Finished): ", STATUS_NOT_STARTED, STATUS_FINISHED);

    // Rebuild priority and status trees
    tree_free(priority_tree);
    tree_free(status_tree);
    *priority_tree = *tree_create(KEY_PRIORITY);
    *status_tree = *tree_create(KEY_STATUS);
    List *temp = head;
    while (temp != NULL) {
        tree_insert(priority_tree, temp->task);
        tree_insert(status_tree, temp->task);
        temp = temp->next;
    }

    printf("Updating task");
    loadingBar(10);
    printf("Task updated successfully.\n");
}
