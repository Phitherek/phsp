#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

int main() {
cout << "Phitherek_' s Startup Profiler - Profile Starter v. 0.1" << endl;
system("echo $HOME > houm");
ifstream houm("houm");
string homedir;
houm >> homedir;
houm.close();
system("rm houm");
string settingsdir = homedir + "/.phsp/";
string fn = settingsdir + "active";
ifstream active(fn.c_str());
if(active) {
string act;
active >> act;
active.close();
system(act.c_str());
cout << "Startup profile started! Thank you for using Phitherek_' s Startup Profiler" << endl;
} else {
active.close();
cout << "Can' t read active config file! Run phsp-conf to select profile!" << endl;
return EXIT_FAILURE;
}
return EXIT_SUCCESS;
}
