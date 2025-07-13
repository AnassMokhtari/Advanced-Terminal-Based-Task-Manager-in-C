#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "task.h"
#include "list.h"
#include "input_utils.h"
#include "stack.h"
#include "tree.h"
#include "file.h"

/**
 * @brief Clears the terminal screen.
 *
 * Uses system("cls") on Windows or system("clear") on other platforms.
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Main function to run the Task Manager program.
 *
 * Initializes the linked list, undo stack, and BSTs, and provides a menu-driven interface
 * for adding, removing, viewing, sorting, saving, loading, and updating tasks.
 *
 * @return 0 on successful exit.
 */
int main() {
    int choice1, choice2;

    List *head_list = NULL;
    Stack *undo_stack = stack_create();
    Tree *id_tree = tree_create(KEY_ID);
    Tree *priority_tree = tree_create(KEY_PRIORITY);
    Tree *status_tree = tree_create(KEY_STATUS);

    if (!undo_stack || !id_tree || !priority_tree || !status_tree) {
        printf("Failed to initialize data structures.\n");
        return 1;
    }

    // Load tasks at startup
    head_list = file_loadTasks(head_list, undo_stack, id_tree, priority_tree, status_tree);
    Sleep(1000);

    do {
        clearScreen();
        printf("\n> Advanced Terminal-Based Task Manager in C \n\n");
        printf("  1. Add a task\n");
        printf("  2. Remove a task\n");
        printf("  3. Show all tasks\n");
        printf("  4. Show tasks sorted\n");
        printf("  5. Save tasks to file\n");
        printf("  6. Load tasks from file\n");
        printf("  7. Update a task\n");
        printf("  0. Quit\n\n");

        choice1 = readInt("Choice: ");

        switch (choice1) {
            case 1:
                do {
                    clearScreen();
                    printf("\n> Add a Task \n\n");
                    printf("  1. Add to the head of the list\n");
                    printf("  2. Add to the middle of the list\n");
                    printf("  3. Add to the end of the list\n");
                    printf("  4. Return to main menu\n\n");

                    choice2 = readInt("Choice: ");

                    switch (choice2) {
                        case 1:
                            clearScreen();
                            printf("\n> Adding a Task to the Head \n");
                            head_list = list_addToHead(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            Sleep(1000);
                            break;
                        case 2:
                            clearScreen();
                            printf("\n> Adding a Task to the Middle \n");
                            list_addToMiddle(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            Sleep(1000);
                            break;
                        case 3:
                            clearScreen();
                            printf("\n> Adding a Task to the End \n");
                            list_addToEnd(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            Sleep(1000);
                            break;
                        case 4:
                            printf("\n> Returning to main menu...");
                            Sleep(1000);
                            break;
                        default:
                            printf("\nInvalid choice. Try again.\n");
                            Sleep(1000);
                            break;
                    }
                } while (choice2 != 4);
                break;

            case 2:
                do {
                    clearScreen();
                    printf("\n> Remove a Task \n\n");
                    printf("  1. Remove from the head\n");
                    printf("  2. Remove from the end\n");
                    printf("  3. Remove by ID\n");
                    printf("  4. Clear entire list\n");
                    printf("  5. Undo last removal (%d available", stack_getSize(undo_stack));
                    Task *next_task = stack_peek(undo_stack);
                    if (next_task) printf(", next ID: %d)\n", next_task->id);
                    else printf(")\n");
                    printf("  6. Clear undo stack\n");
                    printf("  7. Return to main menu\n\n");

                    choice2 = readInt("Choice: ");

                    switch (choice2) {
                        case 1:
                            clearScreen();
                            printf("\n> Removing task from head...\n");
                            head_list = list_removeFromHead(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            Sleep(1000);
                            break;
                        case 2:
                            clearScreen();
                            printf("\n> Removing task from end...\n");
                            list_removeFromEnd(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            Sleep(1000);
                            break;
                        case 3:
                            clearScreen();
                            printf("\n> Removing task by ID...\n");
                            head_list = list_removeByID(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            Sleep(1000);
                            break;
                        case 4:
                            clearScreen();
                            printf("\n> Clearing entire list...\n");
                            list_freeAll(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            head_list = NULL;
                            Sleep(1000);
                            break;
                        case 5:
                            clearScreen();
                            printf("\n> Undoing last removal...\n");
                            head_list = list_restoreTask(head_list, undo_stack, id_tree, priority_tree, status_tree);
                            Sleep(1000);
                            break;
                        case 6:
                            clearScreen();
                            printf("\n> Clearing undo stack...\n");
                            stack_clear(undo_stack);
                            printf("Undo stack cleared");
                            loadingBar(10);
                            Sleep(1000);
                            undo_stack = stack_create();
                            break;
                        case 7:
                            printf("\n> Returning to main menu...");
                            Sleep(1000);
                            break;
                        default:
                            printf("\nInvalid choice. Try again.\n");
                            Sleep(1000);
                            break;
                    }
                } while (choice2 != 7);
                break;

            case 3:
                clearScreen();
                list_printAll(head_list);
                system("pause");
                break;

            case 4:
                clearScreen();
                printf("\n> Show Tasks Sorted \n\n");
                printf("  1. Sort by ID\n");
                printf("  2. Sort by Priority\n");
                printf("  3. Sort by Status\n");
                printf("  4. Return to main menu\n\n");

                choice2 = readInt("Choice: ");
                switch (choice2) {
                    case 1:
                        clearScreen();
                        tree_printInorder(id_tree);
                        system("pause");
                        break;
                    case 2:
                        clearScreen();
                        tree_printInorder(priority_tree);
                        system("pause");
                        break;
                    case 3:
                        clearScreen();
                        tree_printInorder(status_tree);
                        system("pause");
                        break;
                    case 4:
                        printf("\n> Returning to main menu...");
                        Sleep(1000);
                        break;
                    default:
                        printf("\nInvalid choice. Try again.\n");
                        Sleep(1000);
                        break;
                    }
                break;

            case 5:
                clearScreen();
                printf("\n> Saving tasks to file...\n");
                file_saveTasks(head_list);
                Sleep(1000);
                break;

            case 6:
                clearScreen();
                printf("\n> Loading tasks from file...\n");
                head_list = file_loadTasks(head_list, undo_stack, id_tree, priority_tree, status_tree);
                Sleep(1000);
                break;

            case 7:
                clearScreen();
                printf("\n> Updating a Task \n");
                list_updateTask(head_list, undo_stack, id_tree, priority_tree, status_tree);
                Sleep(1000);
                break;

            case 0:
                clearScreen();
                printf("\nExiting Task Manager. Goodbye!\n");
                Sleep(1000);
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
                Sleep(1000);
                break;
        }
    } while (choice1 != 0);

    list_freeAll(head_list, undo_stack, id_tree, priority_tree, status_tree);
    stack_free(undo_stack);
    tree_free(id_tree);
    tree_free(priority_tree);
    tree_free(status_tree);
    return 0;
}
