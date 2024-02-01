#include <chrono>
#define BTF_SIZE 100
#define DICE_SIZE 6
using std::chrono::operator""ms;
#define FIGHT_DURATION 30000ms

#define BACKWARD_COMPATIBILITY false  // Old rules
// note: If enabled, will use old set of kill-rules. Otherwise - new rules;
//       New rules: Everyone will kill anyone :3

// Output config
#define INFO false                  // Clash information
#define DISPLAY_DEAD false          // Dead NPCs displayed on map
#define MAP true                    // Display map

// Random config
#define holyRand_UP 1000
#define holyRand_DOWN 1             

#define ESPILON 0.001