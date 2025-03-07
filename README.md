![Salvatore](https://github.com/user-attachments/assets/f449310f-6128-4213-83a9-8b2cdfd6d326)
![GitHub last commit](https://img.shields.io/github/last-commit/notzekkie/salvatore)   ![GitHub contributors](https://img.shields.io/github/contributors/notzekkie/salvatore)  ![GitHub language count](https://img.shields.io/github/languages/count/notzekkie/salvatore)  ![GitHub top language](https://img.shields.io/github/languages/top/notzekkie/salvatore)  ![GitHub License](https://img.shields.io/github/license/notzekkie/salvatore)  ![GitHub Release](https://img.shields.io/github/v/release/notzekkie/salvatore)  ![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/notzekkie/salvatore)  ![GitHub repo size](https://img.shields.io/github/repo-size/notzekkie/salvatore)  ![Current Stage](https://img.shields.io/badge/current_stage-in_early_development-blue)

**Salvatore** (*SAHL-vah-tor-eh*, named after the [Swiss mountain](https://en.wikipedia.org/wiki/Monte_San_Salvatore)) is an open-source virtualization software.

# Documentation

Salvatore currently does not have detailed documentation explaining how the software works. Please check back later!

> [!Note]  
> You can contribute to the documentation once the project stabilizes. However, it is still in early development, so it's better to wait for more features to be implemented.

# To-do List

> [!Tip]  
> If you think anything is missing here, feel free to [create an issue](https://github.com/notzekkie/salvatore/issues), and we'll review it!

- CPU Emulation
- Bootloader finished
- BIOS services
- Virtual devices

# Get Started

> [!Warning]  
> This application is currently **untested on macOS and Linux**. Development has primarily been done on **Windows**.

To get started, you will need **G++**:

- **Windows**: Install [MSYS2](https://www.msys2.org).
- **Linux**: Install G++ by running `sudo apt install g++`.
- **macOS**: G++ is installed with **Xcode Command Line Tools**.

No additional libraries are required as they are included in the `lib/` folder.

1. Download the repository and compile it with:

    ```sh
    g++ main.cpp BIOS.cpp parsing.cpp datareader.cpp filesystem.cpp bootloader.cpp VirtualMachine.cpp allocation.cpp -o salvatore
    ```

2. Then run:

    ```sh
    ./salvatore
    ```

An **.exe** file will be created in the directory. Salvatore is now compiled and ready to use!

# Reporting Issues

Before reporting an issue, make sure it hasn't already been reported in the [issue tracker](https://github.com/notzekkie/salvatore/issues).

When reporting an issue, please provide as much relevant information as possible:

- The version of Salvatore you're running
- Steps to reproduce the issue
- Any error messages or logs (both UI and console)
- Possible fixes or solutions

If you forget something, we'll ask for it later.

# Contributing

Feel free to fork the repository, make changes, and submit a pull request. Contributions are always welcome!
