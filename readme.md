# Kernel from scratch

A project to have a better understanding of how a linux-like OS works and practice C++.

## Getting Started

### Prerequisites
I use the following softwares to build and test my kernel.

- GNU Make 4.1
- grub-mkrescue 2.02
- QEMU emulator version 2.5.0

I use the `grub-mkrescue` command to create a bootable image.
You need to be on a linux filesystem that have an accessible `/boot/grub` folder to make it work correctly.

### Installing
Builds the kernel with
````
$ make
````

Creates the bootable images
````
$ make install
````

Launch the kernel on QEMU
````
 $ make run
 ````

## Contributing

I really like to know how the things work under the hood, this project allows me to have
a better understanding of how computers work.

I also decided to do this project in C++ to learn and practice this language and the object oriented programming.

Feel free to make me know where I can improve my code in terms of design, performances, readability,
comments and explanations that can help other novice OS developers.
