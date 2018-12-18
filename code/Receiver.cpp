#include"Receiver.h"
Receiver::Receiver()
{
	Receiver_map();
}


void Receiver::Receiver_map()
{
	for (int i = 0; i <= 11; i++)
	{
		char c = i + '0';
		bitset<8> bin_x((int(c)));
		pair<char, bitset<8>>myp;
		myp.first = c; myp.second = bin_x;
		Rec_bits_of_ascii.insert(myp);
	}
	char c = 'A';
	for (int i = 0; i < 26; i++)
	{
		pair<char, bitset<8>>myp;
		bitset<8> bin_x((int(c + i)));
		myp.first = char(c + i);
		myp.second = bin_x;
		Rec_bits_of_ascii.insert(myp);

	}
	c = 'a';
	for (int i = 0; i < 26; i++)
	{
		pair<char, bitset<8>>myp;
		bitset<8> bin_x((int(c + i)));
		myp.first = char(c + i);
		myp.second = bin_x;
		Rec_bits_of_ascii.insert(myp);

	}
}


vector<string> Receiver::Receiver_split(string s)
{
	vector<string>te;
	string temp = "";
	int start = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			temp = s.substr(start, i - start);
			start = i + 1;
			te.push_back(temp);
		}
	}
	temp = s.substr(start, s.length() - start);
	te.push_back(temp);
	return te;
}


int Receiver::Receiver_bin_string_to_int(string s)
{
	int dec = 0;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (s[i] == '1')
			dec += pow(2, s.length() - 1 - i);
		else if (s[i] != '0' && s[i] != '1')
			throw "binary number is not correct";  //throw exception
	}
	return dec;
}


void Receiver::Receive_frames(string input_file_path, string output_file_path)
{
	ifstream myfile(input_file_path);
	ofstream fout;
	fout.open(output_file_path);
	string line;
	if(!myfile)
	{
		throw "File not found";
	}
	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{
			vector<string>temp = Receiver_split(line);

			int x_or = 0;
			for (int i = 0; i < temp.size() - 1; i++)
			{
				int te = Receiver_bin_string_to_int(temp[i]);
				x_or ^= te;
			}

			if (Receiver_bin_string_to_int(temp[0]) - int('0') == temp.size() - 1 && x_or == 0)
			{
				for (int i = 1; i < temp.size() - 2; i++)
				{
					int te = Receiver_bin_string_to_int(temp[i]);

					fout << char(te);
				}
				fout << endl;
			}
			else{
				fout << "ERROR" << endl;
			}
			temp.clear();
		}
		fout.close();
	}
}

map<char, bitset<8>> Receiver::get_Receiver_map()
{
	return Rec_bits_of_ascii;
}

float Receiver::Error_accepting(int num_of_tatal_send_data, int num_error_data)
{
	float Error_precent = (float(num_error_data )/ num_of_tatal_send_data)*100;

	return Error_precent;
}