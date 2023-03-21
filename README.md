# bytemod
This repository contains a proof-of-concept program for encrypting files by manipulating their individual bytes in a formulaic way. The program takes in a directory and applies a hard-coded encryption algorithm to all files of a specified wildcard.

## Installation

To install this program, clone this repository onto your local machine using the following command:

`$ git clone https://github.com/wldfngrs/bytemod.git`

Once you have cloned the repository, navigate to the project directory and run the following command:

`$ make bytemod`

This will compile the program and create an executable file in the `bin` directory.

## Usage

To encrypt a file, run the following command:

`$ ./bin/bytemod input_file/directory] --encrypt`

To decrypt a file, run the following command:

`$ ./bin/bytemod [input_file/directory] --decrypt`

## Testing

A test directory has been provided which contains sample input and output files for testing purposes. To test the program, run the following command:

`$ ./bin/bytemod test/*.h -encrypt`

and to decrypt,

`$ ./bin/bytemod test/*.h -decrypt`

To view the individual bytes before and after encryption, set the MAX_DEBUG_FLAG flag. Else, the commands produce no output.

## Credits

This program was created by wldfngrs as part of a custom-malware build project.
