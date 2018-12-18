#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
#include <bitset>
using namespace std;

class Sender
{
private:
	map<char, bitset<8>>Sender_bits_of_ascii;
	vector<vector<bitset<8>>>sender_output;
public:
	Sender();
	void Sender_map();
	void Build_frames(string file_path);
	void Sender_output(string file_path);
	map<char, bitset<8>> get_Sender_map();
	vector<vector<bitset<8>>> get_Sender_output();
};