# bytemod
This repository contains a proof-of-concept program for encrypting files by manipulating their individual bytes in a formulaic way. The program takes in a direcotory and applies a specified encryption algorithm to all files of specified wildcard.

## Installation

To install this program, clone this repository onto your local machine using the following command:

`$ git clone https://github.com/your_username/your_repository.git`

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

## Credits

This program was created by wldfngrs as part of a custom-malware build project.
