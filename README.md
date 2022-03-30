Name: Dong Bin Lee
Date: 11/15/2021

This program encrypts/decrypts any file using a bookfile as a key.
The program has backward compatability, meaning when encrypting a file,
decrypting the encrypting file should result in the original file.

The program uses assembly language in order to use registers for efficient
encryption/decryption. Each character's bits will swap halves, and then
will be XOR'd with the bookfile's next character.

/******************************/
/******   How To Use:    ******/
/******************************/
The usage of the program is as follows:
./encrypter (-d|-e) -b <bookfile> [-o <offset>] <encryption_file>

-d: Sets the program to decrypt
    (Exactly one of '-d' or '-e' must be chosen, but not both)

-e: Sets the program to encrypt
    (Exactly one of '-d' or '-e' must be chosen, but not both)

-b <bookfile>: The path to the input bookfile

-o <offset>: offset is an integer specifying the number of characters
    to offset from the start of the bookfile to use for encryption

<encryption_file>: T
    -When encrypting, this is the path to the output file to be written.
        The input file must be provided through stdin via the terminal
    -When decrypting, this is the path to the input file to be decrypted.

EXAMPLE USAGE:
./encrypter -e -b book encrypted_file < original_file
./encrypter -d -b book encrypted_file