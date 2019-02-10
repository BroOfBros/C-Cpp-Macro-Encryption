# Compile time encryption C/C++
Using macros only in order to encrypt strings during compilation time.
![The result](https://i.imgur.com/YRmp9qa.png)


# Known bugs
When using it in multiple sources, the __TIME__ will change (it indicates the time the current source file was compiled).
I couldn't find a fix for this yet, the only way to 'fix' it is by simply using a static value..

# Limitations
This is nowhere as good as the so renowned XOR method.You can't use it in functions like std::cout or printf. You can't
encrypt a variable while passing it as a function parameter (you will need to declare the string first and encrypt it.
You can however decrypt strings in functions, since it returns a pointer.).
