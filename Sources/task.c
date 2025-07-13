#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "input_utils.h"

/**
 * @brief Fills a Task structure with validated user input.
 *
 * Uses safe input functions to avoid buffer overflow and invalid entries:
 * - readInt() for numeric inputs like ID
 * - readIntInRange() for validated enum selection (priority, status)
 * - readString() for title and description (supports spaces)
 *
 * @param task Pointer to a Task structure to populate.
 */
void fillTask(Task *task) {
    if (!task) return;

    printf("\n> Fill the task information:\n");

    // Task ID
    task->id = readInt("  ID: ");

    // Task Title
    readString("  Title (max 50 characters): ", task->title, sizeof(task->title));

    // Task Description
    readString("  Description (max 200 characters): ", task->description, sizeof(task->description));

    // Task Priority using enum
    task->priority = (Priority)readIntInRange("  Priority (1 = High, 2 = Medium, 3 = Low): ", PRIORITY_HIGH, PRIORITY_LOW);

    // Task Status using enum
    task->status = (Status)readIntInRange("  Status (1 = Not Started, 2 = In Progress, 3 = Finished): ", STATUS_NOT_STARTED, STATUS_FINISHED);
}

/**
 * @brief Prints the contents of a single Task in a formatted way.
 *
 * Uses switch statements for enum-based fields to increase readability.
 *
 * @param task Pointer to a Task structure to print.
 */
void printTask(Task *task) {
    if (!task) {
        printf("No task to display.\n");
        return;
    }

    printf("> Task Information:\n");
    printf("  ID          : %d\n", task->id);
    printf("  Title       : %s\n", task->title);
    printf("  Description : %s\n", task->description);

    // Priority
    printf("  Priority    : ");
    switch (task->priority) {
        case PRIORITY_HIGH:   printf("HIGH\n"); break;
        case PRIORITY_MEDIUM: printf("MEDIUM\n"); break;
        case PRIORITY_LOW:    printf("LOW\n"); break;
        default:              printf("UNKNOWN\n"); break;
    }

    // Status
    printf("  Status      : ");
    switch (task->status) {
        case STATUS_NOT_STARTED: printf("Not Started\n"); break;
        case STATUS_IN_PROGRESS: printf("In Progress\n"); break;
        case STATUS_FINISHED:    printf("Finished\n"); break;
        default:                 printf("Unknown\n"); break;
    }
}
