#include"Sender.h"

Sender::Sender()
{
	Sender_map();
}


void Sender::Sender_map()
{
	for (int i = 0; i <= 11; i++)
	{
		char c = i + '0';
		bitset<8> bin_x((int(c)));
		pair<char, bitset<8>>myp;
		myp.first = c; myp.second = bin_x;
		Sender_bits_of_ascii.insert(myp);
	}
	char c = 'A';
	for (int i = 0; i < 26; i++)
	{
		pair<char, bitset<8>>myp;
		bitset<8> bin_x((int(c + i)));
		myp.first = char(c + i);
		myp.second = bin_x;
		Sender_bits_of_ascii.insert(myp);

	}
	c = 'a';
	for (int i = 0; i < 26; i++)
	{
		pair<char, bitset<8>>myp;
		bitset<8> bin_x((int(c + i)));
		myp.first = char(c + i);
		myp.second = bin_x;
		Sender_bits_of_ascii.insert(myp);

	}
}


void Sender::Build_frames(string file_path)
{
	ifstream myfile(file_path);
	if (!myfile)
	{
		throw "File not found";
	}
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector<bitset<8>>temp;
			int length = line.length() + 2;
			char c = length + '0';

			temp.push_back(Sender_bits_of_ascii[c]);
			int x_or = 0;
			x_or ^= int(Sender_bits_of_ascii[c].to_ulong());
			for (int i = 0; i < line.length(); i++)
			{
				x_or ^= int(Sender_bits_of_ascii[line[i]].to_ulong());
				temp.push_back(Sender_bits_of_ascii[line[i]]);
			}
			bitset<8> bin_x(x_or);
			temp.push_back(bin_x);
			sender_output.push_back(temp);
			temp.clear();
		}
		myfile.close();
	}
}


void Sender::Sender_output(string file_path)
{
	ofstream fout;
	fout.open(file_path);
	for (int i = 0; i < sender_output.size(); i++)
	{
		for (int j = 0; j < sender_output[i].size(); j++)
		{
			fout << sender_output[i][j] << " ";
		}
		fout << endl;
	}
}

vector<vector<bitset<8>>> Sender::get_Sender_output()
{
	return sender_output;
}

map<char, bitset<8>> Sender::get_Sender_map()
{
	return Sender_bits_of_ascii;
}
