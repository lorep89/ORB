#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>
#include <cstring>
#include <fstream>
#include <boost/version.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <filesystem>

#include "utilParse.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	if(argc != 2)
		cout<<"Error using parse!!\nUsage: ./parse [filename|cmd]"<<endl;
	else {
		string ifname;
		vector<string> ret,fname,strip;
		vector<vector<string>> par;
		int count = 0;

		stripFile(argv[1], &strip);

		if(!fs::exists(fs::status("./Autogen/src")))
			fs::create_directory("./Autogen/src");

		if(!fs::exists(fs::status("./Autogen/inc")))
			fs::create_directory("./Autogen/inc");

		if(!fs::exists(fs::status("./Autogen/imp")))
			fs::create_directory("./Autogen/imp");

//		system("sed -i \"1,15!d\"	./Autogen/Makefile");

		while(count != (int)(strip.size())) {
			count = analyzeStripped(&strip, count, &ifname, &ret, &fname, &par);


			makeIface(ifname, &ret, &fname, &par);
			makeProxy(ifname, &ret, &fname, &par);
			makeSkel(ifname, &ret, &fname, &par);
			makeService(ifname, &ret, &fname, &par);
			string argp = "sed -n \"/^"+ifname+"Objs/=\" ./Autogen/Makefile";
			string ls = exec(argp);
			if(ls.empty()) {
				cout<<"Risultato comando: "<<ls<<endl;
				addMake(ifname);
			}
			else
				cout<<"Interface "<<ifname<<" already present in ./Autogen/Makefile"<<endl;

			string arg = "./addIfaceTarget.sh " + ifname;
			const char * argstr = arg.c_str();
			system(argstr);

			cout<<"-----INTERFACE: "<<ifname<<"------"<<endl;
			cout<<"-----------RETURN TYPES------------"<<endl;
			for (int i=0; i<(int)(ret.size()); i++)
				cout<<ret.at(i)<<endl;
			cout<<"-----------FUNCTION NAMES------------"<<endl;
			for (int i=0; i<(int)(fname.size()); i++)
				cout<<fname.at(i)<<endl;
			cout<<"-----------PARAMETERS------------"<<endl;
			for (int i=0; i<(int)(par.size()); i++)
				for (int j=0; j<(int)(par.at(i).size()); j=j+2) {
					cout<<par.at(i).at(j)<<"\t"<<par.at(i).at(j+1);
					if (j+2 < (int)(par.at(i).size()))
						cout<<"\t";
					else
						cout<<endl;
				}
			cout<<"------- End of "<<ifname<<"----------"<<endl;
			ret.clear();
			fname.clear();
			par.clear();
		}
	}
	return 0;
}
