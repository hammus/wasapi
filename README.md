This is not the repo you're looking for...

This is just a garbage dump it contains useless code that is just me stuffing around with the std io libraries.


# C++ STD library Stream: Input/Output 

> My notes from watching [this video series by Bo Qian](https://www.youtube.com/watch?v=hk5NYscSPHI) 

### Where are the headers for Streaming? 
Headers in : `<ostream> <istream>, <iostream>`


Common example of streams we've already used:

```cpp
cout << "Hello" << endl;
```

`cout` is a global object of type ostream
`ostream` is a `typdef basic_ostream<char> ostream`
Left shift `<<` operator is defined as 
```cpp
ostream& ostream::operator<< (string v);
```
So it takes a string of `v` outputs into the `ostream` and then returns a reference to the ostream `&ostream` hence chaining. 

`endl` is a little complicated but for now lets assume its just a new line plus a flush operation. 
Simplified e.g. 
`std::endl = '\n' + flush()`;

### What is Stream? 
Stream is a **serial** IO interface (it handles the IO data one by one) that is an interface to external devices (file, `stdin`/`stdout`, network etc.)

But what does Serial really mean in practice?

As a comparison lets look at a `string` which is a *Random Access* interface, like a C array:
```cpp


string s('Hello');

s[3] = t; // This is fine as 'string' is a Random Access interface

cout[3] = 't' // Error, we can't do this as 'cout' is a Serial interface.

```

### File Streams
We know that some streams **DO** provide limited random access for example we can seek through a `FILE*` to start reading at a certain point etc.

Let's look at some examples of the output file stream (`ofstream`):
```cpp

{
    ofstream of("MyLog.txt"); //Creates a new file for write, if the file doesn't exist

    // The left bitshift operator is overloaded for a variety of types
    of << "Experience is the mother of wisdom" << endl;
    of << 234 << endl;
    of << 2.34 << endl;

    of << bitset<8>(14) << endl; // writes 00001110 to file
    of << complex<int>(2,3) << endl; //writes (2,3) to the file.

} // another thing to note is that if the ofstream is in its own scope we dont need to close the file, ofstreams are destructed when they fall out of scope.

```

An IO operation typically has 2 steps
1. Formatting data
2. COmmunication data to external devices

Continuing on from the `ofstream` example above, opening files in append mode

```cpp

{
    //Append Mode
    ofstream of("MyLog.txt", ofstream::app); // Moves the output pointer to the end of the file
    of << "Honesty is the best policy" << endl;
}

```

And in Read/Write Mode (with arbitrary output/input pointer positions)
```cpp

{
   ofstream of("MyLog.txt", ofstream::in | ofstream::out); //Read/Write Mode (with arbitrary output/input pointer positions)
        of.seekp(10, ios::beg);                                 // Move the output pointer 10 chars after beginning of file
        of << "12345";                                          // Overwrite 5 chars
        of.seekp(-5, ios::end);                                 // Move the output pointer 5 chars before end
        of << "Nothing ventured, nothing gained" << endl;       // Overwite last 5 chars of "Honesty..." line (which letters depends on Win32 or Nix because of line endings)
        of.seekp(-5, ios::cur);                                 // Move the output pointer 5 chars before CURRENT position

}

```

#### File Stream Error Handling
```cpp
{
        // Input File Stream
        ifstream inf("MyLog.txt");
        int i;                      // Declare an integer
        inf >> i;                   // Read one word into i - will fail as first word is not an integer

        // Query the health of the stream (error status)
        // Error status: 4bits: goodbit, badbit, failbit, eofbit
        inf.good();                 // Everything is OK (goodbit == 1)
        inf.bad();                  // Non-recoverable error (badbit == 1)
        inf.fail();                 // Failed stream operation. Logic Generally Recoverable (failbit == 1 & badbit == 1)
        inf.eof();                  // End of file (eofbit == 1)

        inf.clear();                // Clear all error statuses
        inf.clear(ios::badbit);     // Sets a badbit to 1 and everyting else to 0
        inf.clear(ios::goodbit);    // Sets a goodbit to 1 and everyting else to 0
        
        inf.rdstate();              // Reads the current status flag
        
        inf.clear(inf.rdstate() & ~ios::failbit); // Clear only the failbit (~ operator here is the bitwise NOT)

        if(inf)                     // Equivalent to if(!inf.fail())
        {
            cout << "Read successful.";
        }

        if(inf >> i)                // Same as above because the >> operator returns a reference to the stream itself
        {
            cout << "Read successful.";
        }

        // With exceptions
        inf.exceptions(ios::badbit | ios::failbit);     // Set the exception mask so when badbit or failbit set to 1, exception ios::failure will be thrown
        inf.exceptions(ios::goodbit);                   // Set the exception mask so NO exceptions are generated.

} // Enclosing scope calls ofstream destructor when an ofstream falls out of scope

```

#### Formatted and Unformatted IO

```cpp



```

Binary numbers up to 20 for quick ref (Im hopeless at working these out)
```c
00000000 = 0
00000001 = 1
00000010 = 2
00000011 = 3
00000100 = 4
00000101 = 5
00000110 = 6
00000111 = 7
00001000 = 8
00001001 = 9
00001010 = 10
00001011 = 11
00001100 = 12
00001101 = 13
00001110 = 14
00001111 = 15
00010000 = 16
00010001 = 17
00010010 = 18
00010011 = 19
00010100 = 20

```

