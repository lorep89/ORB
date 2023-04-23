#ifndef UTILPARSE_H
#define UTILPARSE_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <boost/version.hpp>
#include <stdio.h>
#include <boost/algorithm/string.hpp>


using namespace std;

void makeUtil(string ifname) ;

void makeIface(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p);

void makeProxy(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p);

void makeSkel(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p);

void makeService(string ifname, vector<string>* r, vector<string>* f, vector<vector<string>>* p);

void addMake(string ifname);

void getMethod (int* c, vector<string>* s, vector<string>* r, vector<string>* f, vector<vector<string>>* p);

void stripFile(string fname, vector<string>* strippedFile);

int analyzeStripped(vector<string>* stripped, int c, string* ifname, vector<string>* ret, vector<string>* fname, vector<vector<string>>* par);

#endif
