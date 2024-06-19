#include <stdio.h>

int key1[8], key2[8], mode;

void leftShift(int key[10], int shifts);
void generateKeys(int key[10]);
void sboxFunction(int sr[4], int xor[8]);
void encryptDecrypt(int pt[8], int k1[8], int k2[8]);

void leftShift(int key[10], int shifts) {
    int temp1, temp2;
    for (int j = 0; j < shifts; j++) {
        // Left shift first half
        temp1 = key[0];
        for (int i = 0; i < 4; i++) {
            key[i] = key[i + 1];
        }
        key[4] = temp1;
        
        // Left shift second half
        temp2 = key[5];
        for (int i = 5; i < 9; i++) {
            key[i] = key[i + 1];
        }
        key[9] = temp2;
    }
}

void generateKeys(int key[10]) {
    int p10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
    int keyP10[10];

    // Apply P10 permutation
    for (int i = 0; i < 10; i++) {
        keyP10[i] = key[p10[i] - 1];
    }

    // Left shift
    leftShift(keyP10, 1);

    // Generate Key1
    printf("Key1: ");
    for (int i = 0; i < 8; i++) {
        key1[i] = keyP10[p8[i] - 1];
        printf("%d", key1[i]);
    }
    printf("\n");

    // Left shift again
    leftShift(keyP10, 2);

    // Generate Key2
    printf("Key2: ");
    for (int i = 0; i < 8; i++) {
        key2[i] = keyP10[p8[i] - 1];
        printf("%d", key2[i]);
    }
    printf("\n");
}

void sboxFunction(int sr[4], int xor[8]) {
    int s0[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    int s1[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    int row, col, s0Val, s1Val;

    // Calculate S-Box S0
    row = xor[0] * 2 + xor[3];
    col = xor[1] * 2 + xor[2];
    s0Val = s0[row][col];

    // Calculate S-Box S1
    row = xor[4] * 2 + xor[7];
    col = xor[5] * 2 + xor[6];
    s1Val = s1[row][col];

    // Convert S-Box results to 2-bit binary
    sr[0] = (s0Val & 2) >> 1;
    sr[1] = s0Val & 1;
    sr[2] = (s1Val & 2) >> 1;
    sr[3] = s1Val & 1;
}

void encryptDecrypt(int pt[8], int k1[8], int k2[8]) {
    int ip[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    int ep[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    int p4[4] = {2, 4, 3, 1};
    int invIP[8] = {4, 1, 3, 5, 7, 2, 8, 6};

    int temp[8], sr[4], xor[8], result[8];

    // Initial permutation
    for (int i = 0; i < 8; i++) {
        temp[i] = pt[ip[i] - 1];
    }

    // First half expansion and permutation
    for (int i = 0; i < 8; i++) {
        xor[i] = temp[ep[i] - 1];
    }

    // XOR with key1
    for (int i = 0; i < 8; i++) {
        xor[i] ^= k1[i];
    }

    // S-Box function
    sboxFunction(sr, xor);

    // P4 permutation and swap
    for (int i = 0; i < 4; i++) {
        result[i] = sr[p4[i] - 1] ^ temp[i];
        result[i + 4] = temp[i + 4];
    }

    // Second half expansion and permutation
    for (int i = 0; i < 8; i++) {
        xor[i] = result[ep[i] - 1];
    }

    // XOR with key2
    for (int i = 0; i < 8; i++) {
        xor[i] ^= k2[i];
    }

    // S-Box function
    sboxFunction(sr, xor);

    // P4 permutation
    for (int i = 0; i < 4; i++) {
        result[i + 4] = sr[p4[i] - 1] ^ result[i + 4];
        result[i] = sr[p4[i] - 1];
    }

    // Inverse initial permutation
    for (int i = 0; i < 8; i++) {
        pt[i] = result[invIP[i] - 1];
    }

    // Output encrypted/decrypted text
    if (mode == 1) {
        printf("Encrypted text: ");
    } else {
        printf("Decrypted text: ");
    }
    for (int i = 0; i < 8; i++) {
        printf("%d", pt[i]);
    }
    printf("\n");
}

int main() {
    int key[10], pt[8];

    // Plain text input
    printf("Enter the 8-bit text in binary with spaces: ");
    for (int i = 0; i < 8; i++) {
        scanf("%d", &pt[i]);
    }

    // Key input
    printf("Enter the 10-bit key in binary with spaces: ");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &key[i]);
    }

    // Displaying plaintext and key
    printf("The 8-bit text: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", pt[i]);
    }
    printf("\nThe 10-bit key: ");
    for (int i = 0; i < 10; i++) {
        printf("%d", key[i]);
    }
    printf("\n");

    // Choosing mode
    printf("Enter 1 for encryption or 2 for decryption: ");
    scanf("%d", &mode);

    // Key generation
    generateKeys(key);

    // Encryption or decryption
    if (mode == 1) {
        encryptDecrypt(pt, key1, key2);
    } else if (mode == 2) {
        encryptDecrypt(pt, key2, key1);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}
