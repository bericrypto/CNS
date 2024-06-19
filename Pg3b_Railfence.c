#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void encryptMessage(char *str, int rails);
void decryptMessage(char *str, int rails);

int main() {
    char str[1000];
    int rails;

    printf("Enter a Secret Message:");
    gets(str); // Note: gets() is unsafe, consider using fgets() instead

    printf("Enter number of rails:");
    scanf("%d", &rails);
    encryptMessage(str, rails);
    decryptMessage(str, rails);
    return 0;
}

void encryptMessage(char *str, int rails) {
    int i, j, len, count, code[100][1000]; // Increased array sizes for more flexibility
    len = strlen(str);

    for(i = 0; i < rails; i++) {
        for(j = 0; j < len; j++) {
            code[i][j] = 0; // Initialize the code array
        }
    }

    count = 0;
    j = 0;
    while(j < len) {
        if(count % 2 == 0) {
            for(i = 0; i < rails; i++) {
                if(j < len) // Check if j is still within the message length
                    code[i][j] = (int)str[j]; // Store the ASCII value of the character
                j++;
            }
        } else {
            for(i = rails - 2; i > 0; i--) {
                if(j < len) // Check if j is still within the message length
                    code[i][j] = (int)str[j]; // Store the ASCII value of the character
                j++;
            }
        }
        count++;
    }

    // Display the rail fence pattern
    printf("Rail Fence Pattern:\n");
    for(i = 0; i < rails; i++) {
        for(j = 0; j < len; j++) {
            if(code[i][j] != 0)
                printf("%c ", code[i][j]); // Print the character
            else
                printf("  "); // Print space if the cell is empty
        }
        printf("\n");
    }

    // Print encrypted message
    printf("Encrypted Message: ");
    for(i = 0; i < rails; i++) {
        for(j = 0; j < len; j++) {
            if(code[i][j] != 0)
                printf("%c", (char)code[i][j]); // Print the character
        }
    }
    printf("\n");
}

void decryptMessage(char *str, int rails) {
    int i, j, len, count, k, code[100][1000]; // Increased array sizes for more flexibility
    len = strlen(str);

    for(i = 0; i < rails; i++) {
        for(j = 0; j < len; j++) {
            code[i][j] = 0; // Initialize the code array
        }
    }

    count = 0;
    j = 0;
    while(j < len) {
        if(count % 2 == 0) {
            for(i = 0; i < rails; i++) {
                if(j < len) // Check if j is still within the message length
                    code[i][j] = 1; // Mark the cell as occupied
                j++;
            }
        } else {
            for(i = rails - 2; i > 0; i--) {
                if(j < len) // Check if j is still within the message length
                    code[i][j] = 1; // Mark the cell as occupied
                j++;
            }
        }
        count++;
    }

    // Fill the rail fence with the characters from the encrypted message
    k = 0;
    for(i = 0; i < rails; i++) {
        for(j = 0; j < len; j++) {
            if(code[i][j] == 1) {
                code[i][j] = (int)str[k]; // Store the character in the cell
                k++;
            }
        }
    }

    // Print decrypted message
    printf("Decrypted Message: ");
    count = 0;
    j = 0;
    while(j < len) {
        if(count % 2 == 0) {
            for(i = 0; i < rails; i++) {
                if(code[i][j] != 0) { // Check if the cell is occupied
                    printf("%c", (char)code[i][j]); // Print the character
                    j++;
                }
            }
        } else {
            for(i = rails - 2; i > 0; i--) {
                if(code[i][j] != 0) { // Check if the cell is occupied
                    printf("%c", (char)code[i][j]); // Print the character
                    j++;
                }
            }
        }
        count++;
    }
    printf("\n");
}