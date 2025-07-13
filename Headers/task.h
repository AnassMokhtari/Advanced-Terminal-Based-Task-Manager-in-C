#ifndef TASK_H
#define TASK_H

/**
 * @brief Enum for task priority levels.
 */
typedef enum {
    PRIORITY_HIGH = 1,
    PRIORITY_MEDIUM = 2,
    PRIORITY_LOW = 3
} Priority;

/**
 * @brief Enum for task status levels.
 */
typedef enum {
    STATUS_NOT_STARTED = 1,
    STATUS_IN_PROGRESS = 2,
    STATUS_FINISHED = 3
} Status;

/**
 * @brief Structure to represent a task with its attributes.
 */
typedef struct Task {
    int id;                    // Unique identifier for the task
    char title[50];            // Task title (max 50 characters)
    char description[200];     // Task description (max 200 characters)
    Priority priority;         // Task priority (HIGH, MEDIUM, LOW)
    Status status;             // Task status (NOT_STARTED, IN_PROGRESS, FINISHED)
} Task;

/**
 * @brief Fills a Task structure with validated user input.
 *
 * Uses safe input functions to avoid buffer overflow and invalid entries:
 * - readInt() for numeric inputs like ID
 * - readIntInRange() for validated enum selection (priority, status)
 * - readString() for title and description (supports spaces)
 *
 * @param task Pointer to the Task structure to populate.
 */
void fillTask(Task *task);

/**
 * @brief Prints the contents of a single Task in a formatted way.
 *
 * Uses switch statements for enum-based fields to increase readability.
 *
 * @param task Pointer to the Task structure to print.
 */
void printTask(Task *task);

#endif
