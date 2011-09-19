#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
cout << "Phitherek_' s Startup Profiler - Config Tool v. 0.1 (c) 2011 by Phitherek_" << endl;
system("echo $HOME > houm");
ifstream houm("houm");
string homedir;
houm >> homedir;
houm.close();
system("rm houm");
string settingsdir = homedir + "/.phsp/";
string profiledir = settingsdir + "profiles/";
string cmd = "ls " + profiledir + "*.phsp > " + settingsdir + "profilelist";
system(cmd.c_str());
string fn;
fn = settingsdir + "profilelist";
ifstream profilelist(fn.c_str());
vector<string> profiles;
while(!profilelist.eof()) {
string tmp;
profilelist >> tmp;
if(profilelist) {
profiles.push_back(tmp);
}
}
profilelist.close();
fn = settingsdir + "active";
ifstream active(fn.c_str());
if(active) {
string act;
active >> act;
active.close();
cout << "Now using profile: " << act << endl;
} else {
cout << "Active profile not set!" << endl;
active.close();
}
cout << endl << "List of available profiles: " << endl << endl;
if(profiles.size() == 0) {
cout << "List empty! Exiting..." << endl;
return EXIT_FAILURE;
}
for(int i = 0; i < profiles.size(); i++) {
cout << i << ") " << profiles[i] << endl;	
}
bool exit = false;
while(!exit) {
cout << endl << "Enter a number of selected profile: ";
int choice;
cin >> choice;
if(choice < profiles.size() and choice >= 0) {
cmd = "rm " + fn;
system(cmd.c_str());
ofstream actout(fn.c_str());
actout << profiles[choice];
actout.close();
exit = true;
} else {
cout << "Bad choice!" << endl;	
}
}
cout << "Done! Thank you for using Phitherek_' s Startup Profiler!" << endl;
return EXIT_SUCCESS;
}
