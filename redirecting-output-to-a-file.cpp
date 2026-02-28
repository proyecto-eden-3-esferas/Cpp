/* File "redirecting-output-to-a-file.cpp"
 *
 *
 */

#include <fstream>
#include <iostream>

using namespace std;

int main()
{

    // Create an output stream to a file
    ofstream file;
    file.open("writeFile.txt");

    // Store default cout's buffer
    streambuf *cout_buf = cout.rdbuf();

    // Get the streambuf of the file
    streambuf *file_buf = file.rdbuf();

    // Redirect cout to the file by setting cout's buffer to the file's buffer
    cout.rdbuf(file_buf);

    cout << "This line will be written to "
         << "'writeFile.txt'";

    // Flush to ensure all the data is written
    cout.flush();

    // Redirect cout back to its default buffer
    cout.rdbuf(cout_buf);

    cout << "This line will be writtein to console";

    // Close the file stream
    file.close();

    return 0;
}
