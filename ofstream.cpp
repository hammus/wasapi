#include <fstream>
#include <bitset>
#include <complex>

using namespace std;

int main()
{
    {
        ofstream of("MyLog.txt"); //Creates a new file for write, if the file doesn't exist

        // The left bitshift operator is overloaded for a variety of types
        of << "Experience is the mother of wisdom" << endl;
        of << 234 << endl;                  // write 234 to file
        of << 2.34 << endl;                 // write 2.34 to file
        of << bitset<8>(14) << endl;        // write 00001110 to file
        of << complex<int>(2, 3) << endl;   // write (2,3) to the file.

    } // Enclosing scope calls ofstream destructor when an ofstream falls out of scope

    {
        //Append Mode
        ofstream of("MyLog.txt", ofstream::app); // Moves the output pointer to the end of the file
        of << "Honesty is the best policy" << endl;

    } // Enclosing scope calls ofstream destructor when an ofstream falls out of scope

    {
        ofstream of("MyLog.txt", ofstream::in | ofstream::out); //Read/Write Mode (with arbitrary output/input pointer positions)
        of.seekp(10, ios::beg);                                 // Move the output pointer 10 chars after beginning of file
        of << "12345";                                          // Overwrite 5 chars
        of.seekp(-5, ios::end);                                 // Move the output pointer 5 chars before end
        of << "Nothing ventured, nothing gained" << endl;       // Overwite last 5 chars of "Honesty..." line (which letters depends on Win32 or Nix because of line endings)
        of.seekp(-5, ios::cur);                                 // Move the output pointer 5 chars before CURRENT position

    } // Enclosing scope calls ofstream destructor when an ofstream falls out of scope

    // Formatting
    {
        ofstream of("Formatting.txt");
        of << 34 << endl;                   // writes 34;
        of.setf(ios::oct, ios::basefield);  // set format to octal but clear decimal and hex flags which are also set in basefield
        of << 34 << endl;                   // writes 42 (octal representation of 34)
        of.setf(ios::showbase);             // Show the base identifier prefix
        of << 34 << endl;                   // writes 042 (octal representation of 34 with the base identifier prefix for octal - see hex verison below and this will be familiar)
        of.setf(ios::hex, ios::basefield);  // set format to hexidecimal but clear dec and oct flags
        of << 34 << endl;                   // writes 0x22 (hex representation of 34) with the base identifier prefix for hex

        of.unsetf(ios::showbase);           // Hide the base identifier prefix
        of << 34 << endl;                   // writes 22 (hex representation of 34)

        of.setf(ios::dec, ios::basefield);  // set format to decimal

        of.width(10);                       // Set the width of the write
        of << 34 << endl;                   // writes "        34"
        
    }
} 
