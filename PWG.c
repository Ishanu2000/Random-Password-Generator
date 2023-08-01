// CT/2020/007 - Udayanga W.P.I

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 64

int getRandomNumber(int min, int max) {
#ifdef _WIN32
    unsigned int number;
    rand_s(&number);
    return min + (number % (max - min + 1));
#else
    return min + (arc4random_uniform(max - min + 1));
#endif
}

void shuffleArray(char* array, int size) {
    for (int i = size - 1; i > 0; --i) {
        int j = getRandomNumber(0, i);
        char temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void generatePassword(char* password, int length, int useUppercase, int useLowercase, int useDigits, int useSpecialChars) {
    const char uppercaseChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lowercaseChars[] = "abcdefghijklmnopqrstuvwxyz";
    const char digitChars[] = "0123456789";
    const char specialChars[] = "!@#$%^&*()_-+=[]{}|\\:;\"'<>?,./";

    char charset[MAX_PASSWORD_LENGTH];
    int charsetSize = 0;

    if (useUppercase) {
        strcpy(charset + charsetSize, uppercaseChars);
        charsetSize += strlen(uppercaseChars);
    }
    if (useLowercase) {
        strcpy(charset + charsetSize, lowercaseChars);
        charsetSize += strlen(lowercaseChars);
    }
    if (useDigits) {
        strcpy(charset + charsetSize, digitChars);
        charsetSize += strlen(digitChars);
    }
    if (useSpecialChars) {
        strcpy(charset + charsetSize, specialChars);
        charsetSize += strlen(specialChars);
    }

    if (charsetSize == 0) {
        printf("Error: You must select at least one character type.\n");
        exit(1);
    }

    shuffleArray(charset, charsetSize);

    for (int i = 0; i < length; ++i) {
        password[i] = charset[getRandomNumber(0, charsetSize - 1)];
    }

    password[length] = '\0';
}

int evaluatePasswordStrength(const char* password) {
    int length = strlen(password);
    int complexity = 0;

    int hasUppercase = 0;
    int hasLowercase = 0;
    int hasDigits = 0;
    int hasSpecialChars = 0;

    for (int i = 0; i < length; ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z')
            hasUppercase = 1;
        else if (password[i] >= 'a' && password[i] <= 'z')
            hasLowercase = 1;
        else if (password[i] >= '0' && password[i] <= '9')
            hasDigits = 1;
        else
            hasSpecialChars = 1;
    }

    complexity = hasUppercase + hasLowercase + hasDigits + hasSpecialChars;

    if (length >= 12 && complexity >= 3)
        return 4; // Strong
    else if (length >= 8 && complexity >= 2)
        return 3; // Moderate
    else if (length >= 6 && complexity >= 1)
        return 2; // Weak
    else
        return 1; // Very weak
}

void main() {
    srand(time(NULL));

    int length;
    printf("Enter the desired password length(in number): ");
    scanf("%d", &length);
    printf("-----------------------");

    int useUppercase, useLowercase, useDigits, useSpecialChars;
    printf("\nInclude uppercase letters? (0 for no, 1 for yes): ");
    scanf("%d", &useUppercase);
    printf("-----------------------");
    printf("\nInclude lowercase letters? (0 for no, 1 for yes): ");
    scanf("%d", &useLowercase);
    printf("-----------------------");
    printf("\nInclude digits? (0 for no, 1 for yes): ");
    scanf("%d", &useDigits);
    printf("-----------------------");
    printf("\nInclude special characters? (0 for no, 1 for yes): ");
    scanf("%d", &useSpecialChars);
    printf("-----------------------");

    char password[MAX_PASSWORD_LENGTH + 1];
    generatePassword(password, length, useUppercase, useLowercase, useDigits, useSpecialChars);

    printf("\nGenerated Password: %s\n", password);

    int strength = evaluatePasswordStrength(password);
    printf("Password Strength: ");
    switch (strength) {
        case 1:
            printf("Very weak\n");
            break;
        case 2:
            printf("Weak\n");
            break;
        case 3:
            printf("Moderate\n");
            break;
        case 4:
            printf("Strong\n");
            break;
    }

}
