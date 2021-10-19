#include <iostream>
#include <string>
#include <sstream>

#include <stdlib.h>

#include "prodcon.h"

using namespace std;


int main(int argc, char *argv[])
{
    const int nthreads = atoi(argv[1]);
    const int id = (argc <= 2) ? 0 : atoi(argv[2]);

    stringstream ss;
    ss << id;
    string out_fname = id == 0 ? "prodcon.log" : "prodcon." + ss.str() + ".log";

    cout << "nthreads: " << nthreads << endl;
    cout << "id: " << id << endl;
    cout << out_fname << endl;

}
