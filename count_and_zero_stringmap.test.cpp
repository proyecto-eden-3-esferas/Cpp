/* count_and_zero_stringmap.test.cpp */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>

#ifndef COUNT_AND_ZERO_STRINGMAP_H
#include "count_and_zero_stringmap.h"
#endif

typedef count_and_zero_stringmap<std::map<std::string,std::string>> count_and_zero_stringmap_t;

typedef std::     map<std::string, std::string>      map_t;
typedef std::multimap<std::string, std::string> multimap_t;

map_t en2es{
  {"black", "negro"},
  {"white", "blanco"},
  {"red",   "rojo"},
  {"green", "verde"}
};

typedef std::vector<     map_t>      map_vector_t;
typedef std::vector<multimap_t> multimap_vector_t;
map_vector_t healthVector{
  {
    {"topic", "varicose veins treatment"},
    {"remedy", "wear graduated compression stockings to squeeze the legs and improve blood circulation"},
    {"remedy", "prop your legs up above heart level multiple times a day to use gravity to push blood back toward your heart"},
    {"remedy", "exercise regularly, maintain a healthy weight, and avoid standing or sitting still for long periods"},
    {"remedy", "Eat a high-fiber and low-salt diet: Fiber prevents constipation (which adds lower-body pressure), and low salt reduces water retention and swelling"},
    {"remedy", "Stay hydrated: Drinking plenty of water keeps your blood flowing smoothly"},
    {"minimally invasive", "Endothermal Ablation (Laser or Radiofrequency): Uses heat from a laser or radiofrequency fiber inserted via a catheter to seal shut damaged saphenous or underlying veins"},
    {"minimally invasive", "Sclerotherapy and Foam Sclerotherapy: Injects a chemical solution or microfoam directly into the vein, causing it to scar, close, and fade away over time"},
    {"minimally invasive", "Ambulatory Phlebectomy: Removes surface varicose veins through tiny skin punctures or micro-incisions using specialized tools"},
    {"minimally invasive", "VenaSeal / Vein Glue: Seals closed the affected vein using a medical adhesive delivered via a catheter"},
    {"vitamin", "Vitamin B3 (Niacin): Widens (dilates) blood vessels, improves blood flow, and helps lower cholesterol"},
    {"vitamin", "Vitamin C: Builds and maintains collagen, which keeps vein walls strong, elastic, and supported"}
  },
  {
    {"term", "flavonoid"},
    {"definition", "a diverse group of plant-derived polyphenolic secondary metabolites with a shared 15-carbon skeleton structure (C6-C3-C6)"},
    {"effect", "act as natural antioxidants, anti-inflammatories, and cellular protectors in both plants and humans"},
    {"subclass", "flavonols"},
    {"subclass", "flavan-3-ols (catechins)"},
    {"subclass", "anthocyanins"},
    {"subclass", "flavanones"},
    {"subclass", "flavones"},
    {"subclass", "isoflavones"}
    /*
• Flavonols: Found in onions, kale, broccoli, and apples.
• Flavan-3-ols (Catechins): Found in green/black tea, dark chocolate/cocoa, grapes, and berries.
• Anthocyanins: Give rich red, purple, and blue colors to berries, cherries, plums, and red wine.
• Flavanones: Found abundantly in citrus fruits like oranges, lemons, and grapefruits.
• Flavones: Found in herbs like parsley, celery, and chamomile.
• Isoflavones: Found in soybeans and legumes.
     */
  },
  {
    {"term", "phitochemical"},
    {"definition", ""},
    {"effect", ""}
  },
  {
    {"term", "osteopathy"},
    {"type", "alternative medicine"},
    {"definition", ""}
  }/*,
  {
    {"", ""},
    {"", ""},
    {"", ""}
  }.
  {
    {"", ""},
    {"", ""},
    {"", ""}
  }
  */
};

#include <iostream>

using namespace std;

int main() {

  std::ofstream testout("test.text", std::fstream::out | std::fstream::trunc);
  //count_and_zero_serialize(testout, en2es);
  count_and_zero_stringmap_t::serialize(testout, en2es);
  testout.close();

  en2es.clear();

  cout << "Now \'en2es\' has " << en2es.size() << " element(s).\n";

  std::ifstream testin("test.text", std::fstream::in);
  //count_and_zero_deserialize(testin, en2es);
  count_and_zero_stringmap_t::deserialize(testin, en2es);
  testin.close();

  cout << "After deserializing, \'en2es\' has " << en2es.size() << " element(s).\n";

  return 0;
}
