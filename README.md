# BookShop Management System

This is a simple program that simulate working in BookShop System

Here you can do:

1. Add Books
2. View all books in System
3. Find Books
4. Modify Books
5. Delete Books

## Build and Run requirements
g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

cmake version 3.16.3

## How to build a Project
Use terminal Linux to build it

First of all create directory "build" and go there

In directory "build" write "cmake .. " and wait 

After compiling in directory build write "make"

Wait some seconds, in directory will be created file "BookSystem"

Just write "./BookSystem" to run the program 

### Everything done working with JSON library nlohmann and C++
Note that to run the project you should compile it using cmake and CMakeLists.txt (in Linux)

Each Book saves in Base.json file 

All working connected with reading/writing into json objects and finally into base file Base.json