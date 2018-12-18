#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
#include <cmath>
#include <bitset>
#include<stdio.h>
using namespace std;

class Receiver
{
private:
	map<char, bitset<8>>Rec_bits_of_ascii;
public:
	Receiver();
	void Receiver_map();
	vector<string> Receiver_split(string s);
	int Receiver_bin_string_to_int(string s);
	void Receive_frames(string input_file_path, string output_file_path);
	map<char, bitset<8>> get_Receiver_map();
	float Error_accepting(int total_num_send_data, int num_of_error_data);
};