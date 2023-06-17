#include "utilParse.h"
#include <boost/tokenizer.hpp>

using namespace std;

string exec(string command) {
   char buffer[128];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

void makeIface(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p) {
	string upclass = ifname;
	boost::to_upper(upclass);

	ofstream typeout("./Autogen/inc/" + ifname + "Types.h");
	typeout	<<"#ifndef "<<upclass<<"TYPES_H\n"
			<<"#define "<<upclass<<"TYPES_H\n\n";

	for(std::size_t i = 0; i<f->size(); ++i){
		typeout	<<"class "<<ifname<<f->at(i)<<"Ret {\n"
				<<"public:\n"
				<<"\t"<<r->at(i)<<" m_ret;\n"
				<<"\t"<<ifname<<f->at(i)<<"Ret () {};\n"
				<<"\t"<<ifname<<f->at(i)<<"Ret ("<<r->at(i)<<" p_ret) :\n"
				<<"\t\tm_ret(p_ret) {};\n};\n\n";
		if(p->at(i).size() > 0){
			typeout	<<"class "<<ifname<<f->at(i)<<"Args {\n"
					<<"public:\n";
			string temp = "", temp2 = "\t\t";
			for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
				typeout<<"\t"<<p->at(i).at(j)<<" "<<"m_"<<p->at(i).at(j+1)<<";\n";
				temp += p->at(i).at(j)+" "+p->at(i).at(j+1);
				temp2 += "m_"+p->at(i).at(j+1)+"("+p->at(i).at(j+1)+")";
				if(j+2<p->at(i).size()) {
					temp += ", ";
					temp2 += ", ";
				}
				else {
					temp += ") : \n";
					temp2 += " {};\n";
				}
			}
			typeout<<"\t"<<ifname<<f->at(i)<<"Args () {};\n";
			typeout<<"\t"<<ifname<<f->at(i)<<"Args ("<<temp<<temp2<<"};\n\n";
		}
	}

	typeout <<"namespace boost {\n"<<"namespace serialization {\n\n";

	for(std::size_t i = 0; i<f->size(); ++i){
		typeout <<"template<class Archive>\n"
				<<"void serialize(Archive & ar, "<<ifname<<f->at(i)<<"Ret & p_args, const unsigned int version)\n{\n"
				<<"\tar &p_args.m_ret;\n"
				<<"};\n\n";
		if(p->at(i).size() > 0){
			typeout	<<"template<class Archive>\n"
					<<"void serialize(Archive & ar, "<<ifname<<f->at(i)<<"Args & p_args, const unsigned int version)\n{\n";
			for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
				typeout<<"\tar &p_args.m_"<<p->at(i).at(j+1)<<";\n";
			}
			typeout<<"};\n\n";
		}
	}

	typeout	<<"} // namespace serialization\n"
			<<"} // namespace boost\n\n";
	typeout<<"#endif";

	typeout.close();

	ofstream ifout("./Autogen/inc/" + ifname + "Iface.h");
	ifout	<<"#ifndef "<<upclass<<"IFACE_H\n"
			<<"#define "<<upclass<<"IFACE_H\n\n"
			<<"class "<<ifname<<"Iface {"
			<<"\npublic:\n"
			<<"\tvirtual ~"<<ifname<<"Iface() {};\n";

	for(std::size_t i = 0; i < r->size(); ++i) {

		ifout<<"\n\tvirtual "<<r->at(i)<<" "<<f->at(i)<<"(";
		if(p->at(i).size() > 0)
			for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
				ifout << p->at(i).at(j) << " " << p->at(i).at(j+1);
				if(j+2<p->at(i).size())
					ifout << ", ";
				else
					ifout << ") = 0;\n";
			}
		else
			ifout<<") = 0;\n";
	}
	ifout<<"};\n\n#endif";

	ifout.close();
	return;
}

void makeProxy(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p) {
	string line;
	string upclass = ifname;
	boost::to_upper(upclass);

	ofstream prout("./Autogen/inc/"+ifname+".h");
//	cout<<"Writing "<<ifname<<" Proxy"<<endl<<r->at(0)<<endl;
	prout	<<"#ifndef "<<upclass<<"_H\n"
			<<"#define "<<upclass<<"_H\n\n"
			<<"#include \""<<ifname<<"Proxy.h\"\n\n"
			<<"class "<<ifname<<" : public "<<ifname<<"Proxy {\n"
			<<"public:\n"
			<<"\t"<<ifname<<"(std::string name) : "<<ifname<<"Proxy(name) {};\n";

	for(std::size_t i = 0; i < r->size(); ++i) {

		prout<<"\n\t"<<r->at(i)<<" "<<f->at(i)<<"(";
		string temp;
		if(p->at(i).size() > 0){
			for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
				temp += p->at(i).at(j+1);
				prout<<p->at(i).at(j)<<" "<<p->at(i).at(j+1);
				if(j+2<p->at(i).size()) {
					prout << ", ";
					temp += ", ";
				}
				else {
					prout << ") {\n";
					temp += ");\n";
				}
			}
		}
		else {
			prout<<") {\n";
			temp += ");\n";
		}
		prout<<"\t\t"<<r->at(i)<<" ret = "<<ifname<<"Proxy::"<<f->at(i)<<"(";
		prout<<temp;
		prout<<"\t\treturn ret;\n\t};\n";
	}
	prout<<"};\n\n#endif";
	prout.close();

	ifstream prin("./inc/ProxyBase.h");
	prout.open("./Autogen/inc/"+ifname+"Proxy.h");
	if(prin.is_open()) {
		while(getline(prin, line)) {
			if(line == "//guard\r") {
//				cout<<"Making proxyH guards"<<endl;
				prout<<"#ifndef "<<upclass<<"PROXY_H\n";
				prout<<"#define "<<upclass<<"PROXY_H\n\n";
			}
			else if(line=="//include\r"){
				prout<<"#include \""<<ifname<<"Iface.h\"\n";
			}
			else if(line=="//class\r"){
				prout<<"class "<<ifname<<"Proxy : public "<<ifname<<"Iface {\n";
			}
			else if(line == "//constructor\r"){
				prout<<"\t"<<ifname<<"Proxy (string cname);\n";
			}
			else if(line == "//interface\r"){
				for(std::size_t i = 0; i < r->size(); ++i) {

					prout<<"\t"<<r->at(i)<<" "<<f->at(i)<<"(";

					if(p->at(i).size() > 0)
						for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
							prout<<p->at(i).at(j)<<" "<<p->at(i).at(j+1);
							if(j+2<p->at(i).size())
								prout<<", ";
							else
								prout<<") override;\n\n";
						}
					else
						prout<<") override;\n\n";
				}
			}
			else{
				prout<<line<<endl;
			}
		}
	}
	else
		cout<<"file not open"<<endl;
	prin.close();
	prout.close();

	prin.open("./src/ProxyBase.cpp");
	prout.open("./Autogen/src/"+ifname+"Proxy.cpp");
	if(prin.is_open()) {
		while(getline(prin, line)) {
			if(line == "//include\r")
				prout	<<"#include \""<<ifname<<"Proxy.h\"\n"
						<<"#include \""<<ifname<<"Types.h\"\n";
			else if(line == "//constructor\r") {
				prout	<<ifname<<"Proxy::"<<ifname<<"Proxy(string cname) {\n"
						<<"\ttype = \""<<ifname<<"\";\n";
			}
			else if(line == "//interface\r") {
				string temp = "", ini, always;
				for(std::size_t i = 0; i < r->size(); ++i) {
					prout<<r->at(i)<<" "<<ifname<<"Proxy::"<<f->at(i)<<"(";
					always = "\tstd::istringstream iss;\n";
					if(p->at(i).size() > 0) {
						ini = "\tstd::ostringstream oss;\n";
						ini += "\t"+ifname+f->at(i)+"Args l_args(";
//						ini += "\tboost::archive::text_oarchive oa(oss);\n";
//						temp = "\toa << ";
						for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
							prout<<p->at(i).at(j)<<" "<<p->at(i).at(j+1);
							ini += p->at(i).at(j+1);
							if(j+2<p->at(i).size()) {
								prout<<", ";
								ini += ", ";
							}
							else {
								prout<<") {\n";
								ini += ");\n";
							}

						}
						prout<<always<<ini<<"\tboost::archive::text_oarchive oa(oss);\n"
								<<"\toa << l_args;\n";
						prout<<"\tstring msg = type + \"/\" + name + \"/"+f->at(i)+"/\" + oss.str();\n";
					}
					else {
						prout<<") {\n"<<always;
						prout<<"\tstring msg = type + \"/\" + name + \"/"+f->at(i)+"/\";\n";
					}
					prout<<"\tstring resp = c.send(destIP, destPort, msg);\n"
						 <<"\tiss.str(resp);\n"
						 <<"\tboost::archive::text_iarchive ia(iss);\n"
						 <<"\t"<<ifname<<f->at(i)<<"Ret l_ret;\n"
						 <<"\tia >> l_ret;\n"
						 <<"\treturn l_ret.m_ret;\n}\n\n";
//					iss.str(resp);
//					boost::archive::text_iarchive ia(iss);
//					CaraccelRet l_ret;
//					ia >> l_ret;
//					string ret = l_ret.m_string;
//					return ret;
				}				
			}
			else
				prout<<line<<endl;
		}
	}
	prin.close();
	prout.close();
	return;
}

void makeSkel(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p) {
	string line;
	string upclass = ifname;
	string skelname = ifname + "Skel";
	boost::to_upper(upclass);

	ifstream skin("./inc/SkelBase.h");
	ofstream skout("./Autogen/inc/"+ifname+"Skel.h");
	if(skin.is_open()) {
		while(getline(skin, line)) {
			if(line == "//guard\r") {
				skout<<"#ifndef "<<upclass<<"SKEL_H\n";
				skout<<"#define "<<upclass<<"SKEL_H\n\n";
			}
			else if(line=="//class\r") {
				skout	<<"class "<<ifname<<"service;\n\n"
						<<"class "<<skelname<<" : public Skel {\n"
						<<"private:\n"
						<<"\tstd::map<string, "<<ifname<<"service*> ser;\n";
			}
			else if(line == "//constructor\r") {
				skout	<<"\t"<<skelname<<"();\n\n";
			}
			else
				skout<<line<<endl;
		}
	}
	skin.close();
	skout.close();

	skin.open("./src/SkelBase.cpp");
	skout.open("./Autogen/src/"+skelname+".cpp");
	if(skin.is_open()) {
		while(getline(skin, line)) {
			if(line == "//include\r") {
				skout<<"#include \""<<ifname<<"Skel.h\"\n";
				skout<<"#include \""<<ifname<<"service.h\"\n";
				skout<<"#include \""<<ifname<<"Types.h\"\n";
			}
			else if(line == "//constructor\r") {
				skout<<skelname<<"::"<<skelname<<" () {\n";
				for(std::size_t i = 0; i<r->size(); ++i)
					skout<<"\tfns[\""<<f->at(i)<<"\"] = "<<std::to_string(i)<<";\n";
				skout	<<"}\n\n"
						<<"bool "<<skelname<<"::add(Service* obj) {\n"
						<<"\tbool added = false;\n"
						<<"\tauto it = ser.find(obj->getName());\n"
						<<"\tif(it == ser.end()){\n"
						<<"\t\tser[obj->getName()] = dynamic_cast<"<<ifname<<"service*>(obj);\n"
						<<"\t\tadded = true;\n\t}\n"
						<<"\treturn added;\n"
						<<"}\n\n";
			}
			else if(line == "//skeldispatch\r")
				skout<<"string "<<skelname<<"::dispatch(std::vector<string> vet) {\n";
			else if(line == "//interface\r") {
				string respfun = "";//, argdecl = "", archass = "";
				for(std::size_t i = 0; i<r->size(); ++i) {
					if(p->at(i).size()>0) {
						skout	<<"\t\tcase "<<std::to_string(i)<<":\n"
								<<"\t\t{\n"
								<<"\t\t\tboost::archive::text_iarchive ia(iss);\n"
								<<"\t\t\tstd::ostringstream oss;\n"
								<<"\t\t\tboost::archive::text_oarchive oa(oss);\n"
								<<"\t\t\t"<<ifname<<f->at(i)<<"Args l_args;\n"
								<<"\t\t\tia >> l_args;\n";
//								<<argdecl<<archass<<respfun;
						respfun = "\t\t\t"+ifname+f->at(i)+"Ret l_ret(it->second->"+f->at(i)+"(";
//						archass = "\t\t\tia >> ";
						for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
							skout<<"\t\t\t"<<p->at(i).at(j)<<" "<<p->at(i).at(j+1)<<" = l_args.m_"<<p->at(i).at(j+1)<<";\n";
//							argdecl += "\t\t\t"+p->at(i).at(j)+" "+p->at(i).at(j+1)+";\n";
//							archass += p->at(i).at(j+1);
							respfun += p->at(i).at(j+1);
							if(j+2 < p->at(i).size()) {
								respfun += ",";
//								archass += " >> ";
							}
							else {
								respfun += "));\n";
//								archass += ";\n";
							}
						}
						skout<<respfun
							 <<"\t\t\toa << l_ret;\n"
							 <<"\t\t\tresp = oss.str();\n";
					}
					else {
						skout	<<"\t\tcase "<<std::to_string(i)<<":\n"
								<<"\t\t{\n"
								<<"\t\t\tstd::ostringstream oss;\n"
								<<"\t\t\tboost::archive::text_oarchive oa(oss);\n"
								<<"\t\t\t"<<ifname<<f->at(i)<<"Ret l_ret(it->second->"<<f->at(i)<<"());\n"
								<<"\t\t\toa << l_ret;\n"
								<<"\t\t\tresp = oss.str();\n";
					}
					skout<<"\t\t\tbreak;\n"
							<<"\t\t}\n";
//					argdecl = "";
				}
			}
			else
				skout<<line<<endl;
		}
	}
	skin.close();
	skout.close();
	return;
}

void makeService(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p) {
	string line;
	string upclass = ifname;
	string sername = ifname + "service";
	boost::to_upper(upclass);
	ifstream svin("./inc/serviceBase.h");
	ofstream svout("./Autogen/inc/"+sername+".h");

	if(svin.is_open()) {
		while(getline(svin, line)) {
			if(line == "//guard\r") {
				svout<<"#ifndef "<<upclass<<"SERVICE_H\n";
				svout<<"#define "<<upclass<<"SERVICE_H\n\n";
			}
			else if(line=="//include\r") {
				svout<<"#include \""<<ifname<<"Iface.h\"\n"
					<<"#include \""<<ifname<<"Skel.h\"\n";
			}
			else if(line == "//class\r")
				svout<<"class "<<sername<<" : public "<<ifname<<"Iface, public Service {\n";
			else if(line=="//constructor\r")
				svout<<"\t"<<sername<<"(string sname) : Service(sname, \""<<ifname<<"\") {};\n";
			else if(line=="//makeskel\r")
				svout<<"\t"<<"Skel* makeSkel() override {return new "<<ifname<<"Skel(); }\n";
			else if(line == "//interface\r")
				for(std::size_t i = 0; i < r->size(); ++i) {

					svout<<"\t"<<r->at(i)<<" "<<f->at(i)<<"(";

					if(p->at(i).size() > 0)
						for(std::size_t j = 0; j < p->at(i).size(); j=j+2) {
							svout<<p->at(i).at(j)<<" "<<p->at(i).at(j+1);
							if(j+2<p->at(i).size())
								svout<<", ";
							else
								svout<<") override;\n\n";

						}
					else
						svout<<") override;\n\n";
				}
			else
				svout<<line<<endl;
		}
	}
	svin.close();
	svout.close();
	return;
}

void addMake(string ifname) {
	ofstream mout("./Autogen/Makefile", std::ios_base::app);

	mout<<"\n"<<ifname<<"Objs = $(addprefix $(objdir)/,util.o Client.o "
		<<ifname<<"Proxy.o "<<ifname<<"Skel.o "<<ifname<<"service.o)\n";

	mout<<"\ncleanObjs += $(addprefix $(objdir)/,"<<ifname<<"Proxy.o "
		<<ifname<<"Skel.o "<<ifname<<"service.o)\n\n";

	mout<<ifname<<": $(libdir)/lib"<<ifname<<".so\n\n";

	mout<<"$(libdir)/lib"<<ifname<<".so: $("<<ifname<<"Objs)\n"
		<<"\t$(CXX) $(CXXFLAGS) -shared -Wl,-soname,lib"<<ifname<<".so $^ -o $@\n\n";

	mout<<"$(objdir)/"<<ifname<<"Skel.o:\n"
		<<"\t$(CXX) $(CXXFLAGS) -c -fPIC ./src/"<<ifname<<"Skel.cpp "<<"-o $@\n\n";

	mout<<"$(objdir)/"<<ifname<<"Proxy.o:\n"
		<<"\t$(CXX) $(CXXFLAGS) -c -fPIC ./src/"<<ifname<<"Proxy.cpp "<<"-o $@\n\n";

	mout<<"$(objdir)/"<<ifname<<"service.o:\n"
		<<"\t$(CXX) $(CXXFLAGS) -c -fPIC ./imp/"<<ifname<<"service.cpp "<<"-o $@\n\n";

	mout<<"cleanObjs += $(libdir)/lib"<<ifname<<".so\n";

	mout.close();
}

void getMethod (int* c, vector<string>* s, vector<string>* r, vector<string>* f, vector<vector<string>>* p) {
	r->push_back(s->at(*c));
	f->push_back(s->at(*c +1));
	*c+=2;
	if(s->at(*c) != "(")
		cout<<"Syntax error"<<endl;
	else {
		*c+=1;
		vector<string> arg;
		while(s->at(*c) != ")") {
			arg.push_back(s->at(*c));			
			arg.push_back(s->at(*c+1));
			*c+=2;
			if(s->at(*c) == ",")
				*c+=1;
		}
		p->push_back(arg);
		*c+=1;
	}
}

void stripFile(string fname, vector<string>* strippedFile) {
		typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

		ifstream fin (fname);
		ofstream fout ("strip.txt");

		fin.seekg(0, fin.end);
		int len = (int)fin.tellg() + 1;
		fin.seekg(0, fin.beg);
		char* buf = new char[len];
		fin.read(buf, len);
		string b = buf;
		boost::char_separator<char> s {" \t\r","\n{},();"};
		tokenizer t{b,s};
		bool comment = false;
		for(tokenizer::iterator beg=t.begin(); beg!=t.end(); ++beg) {
			if (beg->substr(0,2) == "//"){
				comment = true;
//				cout<<"begin comment at: "<< *beg<<endl;
			}
			if ((comment)&&(*beg == "\n")){
				comment = false;
//				cout<<"end comment at: "<<*beg<<endl;
			}


			if ((comment)||(*beg == "\n")) {
				continue;
			}
			strippedFile->push_back(*beg);
			fout<<"token: "<<*beg<<endl;
//			cout<<"token: "<<*beg<<endl;
		}
		fin.close();
		fout.close();
}

int analyzeStripped(vector<string>* stripped, int c, string* ifname, vector<string>* ret, vector<string>* fname, vector<vector<string>>* par) {
	int count = c;
	if(stripped->at(count) != "interface")
		cout<<"Syntax error: Declaration of interface must begin with keyword \"interface\""<<endl;
	else {
		*ifname = stripped->at(count + 1);
		count += 2;
//		cout<<*ifname<<endl;
//		cout<<"Next token: "<<stripped->at(count)<<endl;
		// for(auto it:strip)
		// 	cout<<it<<endl;
	}
	if (stripped->at(count) != "{")
		cout<<"Syntax error"<<endl;
	else {
		count+=1;
//		cout<<"Next token: "<<stripped->at(count)<<endl;
		while(stripped->at(count) != "}") {
//			cout<<"Getting methods. Next token: "<<stripped->at(count)<<endl;
			getMethod(&count, stripped, ret, fname, par);
			if(stripped->at(count) != ";")
				cout<<"Syntax error"<<endl;
			count+=1;
		}
	}
	count+=1;
//	cout<<"count: "<<count<<"\tsize: "<<stripped->size()<<endl;
	return count;
}
