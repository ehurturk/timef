# Timef

Timef is a simple program that outputs the current system time in a stylized way into console.

It was a simple practice project for me - don't expect much functionality.

Timef only works in UNIX-like systems since it uses headers that only exist and heavily depend on UNIX systems.

## Build & Install
As previously mentioned, the program is for UNIX systems, not for Windows.
To build the project from the source, type the following into your terminalmal:
``` shell
make # compiles the script 
make install # installs the binary to the system
```
If you encounter a problem in `make install`, try adding sudo to the beginning of the command.

## Usage
To use the program, type `./timef -[flags]` into your terminal.
All possible flags are:

  💡 -s : show seconds

  💡 -m : show minutes

  💡 -h : show hours

  💡 -y : show years

  💡 -d : show days

  💡 -D : show names of the days

  💡 -M : show months

  💡 -2 : show hours in 24h format (default 24 hour format if no -1 is specified)

  💡 -1 : show hours in 12h format

Example usage:
`timef -s -m -h -d -D -M -2 -y` - which would output:
`Tue/Jul/13 - 18:14:26 - 2021`.

To quit, press `q` and you will return back to your classic terminal screen.

Important Note: I've tried to implement non-blocking user input, which I am fairly new to, and if you press a key different than `q`, and then press `q`, the program would wait a few-seconds multiplied by how many non-`q` keys you have pressed, then it would exit. 

When using the flag -1, there would be additional "AM" or "PM" next to seconds.

## Uninstall
To uninstall, simply run `make uninstall` or `sudo make uninstall` from the directory which you have downloaded the source of this project. Alternatively, you can simply delete the binary executable named `timef` located at `/usr/local/bin` by running `rm -rf /usr/local/lib` from your terminal.

Thanks for being interested in.
