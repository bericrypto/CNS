#include <stdio.h>
#include <string.h>

#define MOD 26

// Function to calculate determinant of a 2x2 matrix
int determinant_2x2(int matrix[2][2]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
    if (det < 0) det += MOD; // Ensure non-negative result
    return det;
}

// Function to calculate determinant of a 3x3 matrix
int determinant_3x3(int matrix[3][3]) {
    int det = (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
               matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
               matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])) % MOD;
    if (det < 0) det += MOD; // Ensure non-negative result
    return det;
}

// Function to calculate modular inverse of a number
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
    return -1;
}

// Function to encrypt a message using Hill cipher
void encrypt(int matrix_size, int matrix[][matrix_size], char plaintext[], char ciphertext[]) {
    int len = matrix_size;
    int temp[len];
    int n = strlen(plaintext);
    // Ensure plaintext length is a multiple of matrix size
    while (n % len != 0) {
        plaintext[n++] = 'x';
    }
    plaintext[n] = '\0';
    for (int i = 0; plaintext[i] != '\0'; i += len) {
        for (int j = 0; j < len; j++) {
            temp[j] = 0;
            for (int k = 0; k < len; k++) {
                temp[j] += (matrix[j][k] * (plaintext[i + k] - 'a')) % MOD;
                temp[j] %= MOD;
            }
            ciphertext[i + j] = temp[j] + 'a';
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Function to decrypt a message using Hill cipher
void decrypt(int matrix_size, int matrix[][matrix_size], char ciphertext[], char decrypted_text[]) {
    int len = matrix_size;
    int inverse_matrix[len][len];

    // Calculating determinant and modular inverse
    int det = matrix_size == 2 ? determinant_2x2(matrix) : determinant_3x3(matrix);
    int inv_det = mod_inverse(det, MOD);

    // Check if modular inverse exists
    if (inv_det == -1) {
        printf("Modular inverse does not exist for the determinant. Cannot decrypt.\n");
        return;
    }

    // Finding inverse of matrix
    if (matrix_size == 2) {
        inverse_matrix[0][0] = matrix[1][1];
        inverse_matrix[0][1] = -matrix[0][1];
        inverse_matrix[1][0] = -matrix[1][0];
        inverse_matrix[1][1] = matrix[0][0];
    } else {
        // Adjugate matrix method to find the inverse for a 3x3 matrix
        inverse_matrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) % MOD;
        inverse_matrix[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) % MOD;
        inverse_matrix[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) % MOD;
        inverse_matrix[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) % MOD;
        inverse_matrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) % MOD;
        inverse_matrix[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) % MOD;
        inverse_matrix[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) % MOD;
        inverse_matrix[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) % MOD;
        inverse_matrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
    }

    // Applying modular inverse
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            inverse_matrix[i][j] = (inverse_matrix[i][j] * inv_det) % MOD;
            if (inverse_matrix[i][j] < 0)
                inverse_matrix[i][j] += MOD;
        }
    }

    // Decrypting ciphertext
    encrypt(matrix_size, inverse_matrix, ciphertext, decrypted_text);
}

int main() {
    int matrix_size;
    printf("Enter the size of the matrix (2 or 3): ");
    scanf("%d", &matrix_size);

    if (matrix_size != 2 && matrix_size != 3) {
        printf("Invalid matrix size\n");
        return 1;
    }

    int matrix[matrix_size][matrix_size];
    printf("Enter the elements of the %dx%d matrix:\n", matrix_size, matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    char plaintext[100], ciphertext[100], decrypted_text[100];
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    encrypt(matrix_size, matrix, plaintext, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(matrix_size, matrix, ciphertext, decrypted_text);
    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}
