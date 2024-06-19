#include <stdio.h>

// Function to perform encryption
void encrypt(char plaintext[], char key[], char ciphertext[]) {
    for (int i = 0, j = 0; i < strlen(plaintext); i++, j++) {
        if (j >= strlen(key)) {
            j = 0;
        }
        int shift = toupper(key[j]) - 'A';
        char encryptedChar = ((toupper(plaintext[i]) - 'A' + shift) % 26) + 'A';
        ciphertext[i] = encryptedChar;
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the string
}

// Function to perform decryption
void decrypt(char ciphertext[], char key[], char decryptedtext[]) {
    for (int i = 0, j = 0; i < strlen(ciphertext); i++, j++) {
        if (j >= strlen(key)) {
            j = 0;
        }
        int shift = toupper(key[j]) - 'A';
        char decryptedChar = ((toupper(ciphertext[i]) - 'A' - shift + 26) % 26) + 'A';
        decryptedtext[i] = decryptedChar;
    }
    decryptedtext[strlen(ciphertext)] = '\0'; // Null-terminate the string
}

int main() {
    char plaintext[128];
    char key[16];
    char ciphertext[128];
    char decryptedtext[128];
    
    printf("\nEnter the plaintext (up to 128 characters): ");
    scanf(" %[^\n]", plaintext); // Read input with spaces
    printf("Enter the key (up to 16 characters): ");
    scanf(" %[^\n]", key);

    printf("\nVigenere Table:\n");
    for(int i=0; i<26; i++){
        char a = 'A'+i;
        for(int j=0;j<26;j++){
            if((a+j)>'Z'){
                printf("%c ",a+j-26);
            }
            else{
                printf("%c ",a+j);
            }
        }
        printf("\n");
    }
    // Perform encryption
    encrypt(plaintext, key, ciphertext);
    printf("Cipher Text: %s\n", ciphertext);
    
    // Perform decryption
    decrypt(ciphertext, key, decryptedtext);
    printf("Deciphered Text: %s\n", decryptedtext);

    return 0;
}
