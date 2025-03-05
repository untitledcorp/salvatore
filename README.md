![Salvatore](https://github.com/user-attachments/assets/f449310f-6128-4213-83a9-8b2cdfd6d326)

**Salvatore** (*SAHL-vah-tor-eh*, named after the [Swiss mountain](https://en.wikipedia.org/wiki/Monte_San_Salvatore)) is a open-source virtualization software.

# Get Started
To get started, all you need is **G++**. 
- If you're on Windows, you need [MSYS2](https://www.msys2.org).

- If you're on Linux, it should already be installed. If not, run ```sudo apt install g++```.

- If you're on macOS, it should be installed alongside the **Xcode Command Line Tools**.

No libraries are needed to be installed, as they are in the `lib/` folder.

Next, download the repository, and compile it with:

```g++ -o salvatore main.cpp parser.cpp datareader.cpp isohandler.cpp debug.cpp -o```
```./salvatore```

An **.exe** file will show up in the directory. Open it to ensure everything is fine.
wip readme 😵‍💫
