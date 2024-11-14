#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORY_SIZE 1024  // Define maximum memory size
#define MAX_INSTRUCTION_LENGTH 20  // Max length of an instruction line

char memory[MAX_MEMORY_SIZE][MAX_INSTRUCTION_LENGTH];  // Memory array to store instructions

// Function to load ALP program into memory
int load_ALP_to_memory(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", filename);
        return -1;
    }

    int memory_index = 0;  // Memory address pointer
    char instruction[MAX_INSTRUCTION_LENGTH];

    // Read instructions line by line and load them into memory
    while (fgets(instruction, MAX_INSTRUCTION_LENGTH, file) != NULL) {
        // Remove newline character from instruction
        instruction[strcspn(instruction, "\n")] = '\0';

        if (memory_index >= MAX_MEMORY_SIZE) {
            printf("Error: Memory overflow. Program size exceeds available memory.\n");
            fclose(file);
            return -1;
        }

        // Store the instruction in memory
        strncpy(memory[memory_index], instruction, MAX_INSTRUCTION_LENGTH);
        memory_index++;
    }

    fclose(file);
    return memory_index;  // Return number of instructions loaded into memory
}

// Function to display the loaded instructions in memory
void display_memory(int num_instructions) {
    printf("\nLoaded Program in Main Memory:\n");
    printf("--------------------------------\n");
    printf("Address\tInstruction\n");
    printf("--------------------------------\n");

    for (int i = 0; i < num_instructions; i++) {
        printf("%04d\t%s\n", i, memory[i]);
    }
}

int main() {
    const char *filename = "ALP_program.txt";  // Input file containing the ALP program

    // Load ALP program into memory
    int num_instructions = load_ALP_to_memory(filename);
    if (num_instructions == -1) {
        printf("Failed to load ALP program.\n");
        return 1;
    }

    // Display the contents of memory
    display_memory(num_instructions);

    return 0;
}
