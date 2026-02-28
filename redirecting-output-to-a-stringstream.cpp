/* File "redirecting-output-to-a-stringstream.test.cpp"
 *
 *
 */

#include <sstream>
#include <iostream>

using namespace std;

int main()
{

    // Create an output stream to a file or any other ostream:
    stringstream os;

    // Store default cout's buffer
    streambuf *cout_buf = cout.rdbuf();

    // Get the streambuf of the ostream:
    streambuf *other_buf = os.rdbuf();

    // Redirect cout to the ostream by setting cout's buffer to its buffer:
    cout.rdbuf(other_buf);

    cout << "This line will be written to an std::stringstream";

    // Flush to ensure all the data is written
    cout.flush();

    // Redirect cout back to its default buffer
    cout.rdbuf(cout_buf);

    cout << "This line will be written to console";
    cout << "\nHaving undone the redirection, our stringstream object outputs to cout:\n  \"";
    cout << os.str() << "\"\n";


    return 0;
};
