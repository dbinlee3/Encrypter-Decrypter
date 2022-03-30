#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#define BFSZ 1024

/**
 * This function will encrypt a single char type using a char type from a book file.
 * The function is fully implemented in assembly language, using registers for
 * efficiency. An encrypted char type will be returned.
 * 
 * @param inchar - A char type that will be encrypted
 * @param key - A char type from the book file that will be XOR'd
 * @return extern char - The encrypted char type
 */
extern char encrypt(char inchar, char key);

/**
 * This function will decrypt a single char type using a char type from a book file.
 * The function is fully implemented in assembly language, using registers for
 * efficiency. A decrypted char type will be returned.
 * 
 * @param inchar - A char type that will be decrypted
 * @param key - A char type from the book file that will be XOR'd
 * @return extern char - The decrypted char type
 */
extern char decrypt(char inchar, char key);

/**
 * Function which prints to stderr when user inputs incorrect usage.
 * 
 * @param argv - Argument options from the terminal
 */
void usage(char **argv);

/**
 * USAGE: 
 * ./encrypter (-d|-e) -b <bookfile> [-o <offset>] <encryption_file>
 */
int main (int argc, char **argv) {
    
    int option;
    char *bookfile; //Argument for -o
    char *endptr; //Argument for strtol()
    long offset; //Return for strtol()

    //Option flags
    int dFlag = 0;
    int eFlag = 0;
    int reqFlag = 0;
    int willDecrypt = 0;
    int willEncrypt = 0;

    FILE *bookPtr;
    FILE *encryptionPtr;
    struct stat stats;

    char buffer[BFSZ];
    char outBuffer[BFSZ];

    //Option Handling 
    while ((option = getopt(argc, argv, "deb:o:")) != -1) {

        switch (option){

            //Decrypt option flag
            case 'd':
                reqFlag++;
                if (dFlag){
                    usage(argv);
                    exit(1);
                } else{
                    dFlag++;
                    eFlag++;
                    willDecrypt++;
                }
                break;
            
            //Encryption option flag
            case 'e':
                reqFlag++;
                if (eFlag){
                    usage(argv);
                    exit(1);
                } else{
                    dFlag++;
                    eFlag++;
                    willEncrypt++;
                }
                break;

            //Bookfile flag
            case 'b':
                bookfile = optarg;
                break;

            //Offset flat
            case 'o':
                offset = strtol(optarg, &endptr, 10);
                break;

            default:
                usage(argv);
                exit(1);

        }
    }

    //If no Filename is included:
    if (argv[optind] == NULL) {
        fprintf(stderr, "Filename is required\n");
        exit(1);
    }

    //If neither -d or -e used:
    if (!reqFlag){
        usage(argv);
        exit(1);
    }

    //Open/check book file
    if ((bookPtr = fopen(bookfile, "r")) == NULL){
        printf("Unable to open book file: (null)");
        exit(1);
    } else {
        stat(bookfile, &stats);
    }

    //Create allocated array of chars
    char *bookArr = (char *)malloc(stats.st_size);
    char cryptChar;

    //Read the bookfile into an array
    fread ( bookArr, sizeof(char), stats.st_size, bookPtr );

    //If Encrypting:
    if (willEncrypt){

        //Open the encryption_file for writing
        encryptionPtr = fopen( argv[optind], "w");

        //Get each line of stdin, and store it into buffer
        while( fgets(buffer, BFSZ, stdin) != NULL ) {
            
            //Traverse through each index of buffer
            for (unsigned int i = 0; i < strlen(buffer); i++ ){

                long moduloIndex = ( offset % stats.st_size );
                cryptChar = encrypt(buffer[i], bookArr[moduloIndex]);
                outBuffer[i] = cryptChar;
                offset++;
            }
            fwrite(buffer, sizeof(char), strlen(buffer), encryptionPtr);
        }
    }
    else if (willDecrypt){

        //Open the encryption file for reading
        encryptionPtr = fopen( argv[optind], "r");

        //Read each line of the encrypted file, store into buffer
        while( fgets(buffer, BFSZ, encryptionPtr) != NULL ) {

            //Traverse through each character of the buffer line
            for (unsigned int i = 0; i < strlen(buffer); i++ ){

                //Decrypt
                long moduloIndex = ( (i + offset) % stats.st_size );
                cryptChar = decrypt(buffer[i], bookArr[moduloIndex]);
                printf("%c", cryptChar);
            }
        
        }
    }

    //Close files and free memory:
    fclose(encryptionPtr);
    fclose(bookPtr);
    free(bookArr);
    bookArr = NULL;
}

//Function which prints to stderr when user inputs incorrect usage
void usage(char **argv) {
    fprintf(stderr,"Usage: %s (-d|-e) -b <bookfile> [-o <offset>] <filename>\n", *argv);
    return;
}