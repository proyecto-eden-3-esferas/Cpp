/* File "specific_ostream.test.cpp"
 */

#ifndef SPECIFIC_OSTREAM_H
#include "specific_ostream.h"
#endif

/* You can compile LaTeX documents online using Overleaf, a popular cloud-based editor that renders your code into a PDF automatically.
Top Online LaTeX Compilers
• Overleaf (https://www.overleaf.com/): The most popular platform with real-time collaboration, templates, and full TeX Live support.
• SciScribe: A free online tool featuring real-time compilation, templates, and built-in table/equation generators.
• CoCalc: A collaborative web workspace supporting advanced engines like pdfLaTeX, XeLaTeX, and LuaTeX.
• Cricet: A free alternative designed for large documents with fast compilation times.
 */


using namespace std;

int main (int argc, const char** argv) {

  LaTex_ostream latex0(std::cout, "letter");

  section sfish(
    "Fishes",
    "Fishes are animals that swim in water, but not all animals that swim in water are fish.",
    false
  );

  sfish.add_subsection("Sharks");
  sfish.add_subsection("Cod");

  for(const auto & sub : sfish)
    cout << sub.get_title() << ":\n" << sub.get_text() << '\n';

  return 0;

}
