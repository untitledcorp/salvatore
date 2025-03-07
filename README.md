![Salvatore](https://github.com/user-attachments/assets/f449310f-6128-4213-83a9-8b2cdfd6d326)

**Salvatore** (*SAHL-vah-tor-eh*, named after the [Swiss mountain](https://en.wikipedia.org/wiki/Monte_San_Salvatore)) is a open-source virtualization software.

# Documentation

Salvatore currently does not have a documentation explaining how the software works, but you can check back later!

> [!NOTE]
> You could help out with the documentation, but Salvatore is in a very early state, so it's not the best idea for now.

# To-do list

> [!TIP]
> If you think there's anything missing here, let us know! Make an issue in our [tracker](https://github.com/notzekkie/salvatore/issues) and we'll see if we can add it.

- Finish the bootloader
- Implement RAM allocation and CPU emulation
- Make Arch Linux fully bootable (or any other non GUI operating system)
- Make full CLI application
- (*Saved for later*) Make a GUI version of the application



# Get Started

> [!WARNING]
> This application is currently **untested on macOS and Linux**. Development has, at the moment, only been done on **Windows**. 

To get started, all you need is **G++**. 

- If you're on Windows, you need **[MSYS2](https://www.msys2.org)**.

- If you're on Linux, it should already be installed. If not, run `sudo apt install g++`.

- If you're on macOS, it should be installed alongside the **Xcode Command Line Tools**.

No libraries are needed to be installed, as they are in the `lib/` folder.

Next, download the repository, and compile it with:

```sh
g++ main.cpp parsing.cpp datareader.cpp filesystem.cpp bootloader.cpp -o salvatore
```

Then:

```sh
./salvatore
```

An **.exe** file will show up in the directory. Salvatore is now compiled.

# Reporting Issues

[First thing first](https://open.spotify.com/album/54z1IV2vazAiNZoXEPpXfJ), ensure that the issue you're reporting **isn't** already reported in the repository's [issue tracker](https://github.com/notzekkie/salvatore/issues). 

When reporting issues, please provide as much useful information as you can. This can include:

- The version of Salvatore you are running
- Steps to reproduce your problem.
- An error message, if there is one (in the UI and on the console)
- A fix/solution.

If you forget about something important, we'll probably ask.
