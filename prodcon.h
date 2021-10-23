#include <string>

using namespace std;


enum Action {ask, receive, work, sleep};

void* consumer(void* args_p);
void print_action(const unsigned int id, string action, int* n);