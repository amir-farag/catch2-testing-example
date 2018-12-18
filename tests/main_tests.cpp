#include<iostream>
#include"../code/Sender.h"
#include"../code/Receiver.h"

#define CATCH_CONFIG_MAIN
#include"catch.hpp"



/////////////////////////////////////////////////////////////////////////////////////////////////
				/*Sender class testing */
/////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Exception testing in sender class","[Sender][2]")
{
	Sender s;
	string file_path = "input.txt";
	string test_path = "input15.txt";

	SECTION("test Build_frames throwing exception")
	{
		SECTION("check if no throw") {
			CHECK_NOTHROW(s.Build_frames(file_path));
		}

		SECTION("Require if there is a throw") {
			REQUIRE_THROWS(s.Build_frames(test_path));
		}

		SECTION("Require if the throw contains this word") {
			REQUIRE_THROWS_WITH(s.Build_frames(test_path), Catch::Contains("File"));
		}

		SECTION("check the type of the throw") {
			CHECK_THROWS_AS(s.Build_frames(test_path), const char *);
		}

		SECTION("Require the type of the throw and if contains this word") {
			REQUIRE_THROWS_MATCHES(s.Build_frames(test_path), const char *, Catch::Contains("File"));
		}
	}
}

TEST_CASE("Matcher Expression testing in sender class","[Sender]") {
	Sender s;
	string file_path = "input.txt";
	string test_path = "input15.txt";

	SECTION("check the name of input file") {
		CHECK_THAT(file_path, Catch::EndsWith("INPut.txt", Catch::CaseSensitive::No));
		REQUIRE_THAT( file_path, Catch::EndsWith( "iNpUt.TxT" , Catch::CaseSensitive::No) ||
								 (Catch::StartsWith( "in" ) && !Catch::Contains( "hi" ) ) );
	}

	SECTION("test the elements in sender map") {
		map<char, bitset<8>>map_test = s.get_Sender_map();
		char ch1 = 3 + 'a'; //letter d
		char ch2 = 25 + 'a'; //letter z
		REQUIRE_THAT(map_test[ch1].to_string(), Catch::Equals("01100100"));
		CHECK_THAT(map_test[ch2].to_string(), Catch::EndsWith("1010") && !Catch::StartsWith("0110"));
	}
}

SCENARIO("Testing Sender_output", "[Sender][1]")
{
	GIVEN("Fill input.txt file with four words with upper or lower cases")
	{
		ofstream fout;
		fout.open("input.txt");
		fout << "PROJECT" << endl;
		fout << "Testing" << endl;
		fout << "cmp" << endl;
		fout << "EAsy" << endl;
		Sender s;
		WHEN("Build_frames called test size")
		{
			s.Build_frames("input.txt");
			vector<vector<bitset<8>>> test = s.get_Sender_output();

			THEN("Expected Sender_output size")
			{
				REQUIRE(test.size() == 4);
				REQUIRE(test[0].size() == 9);
				REQUIRE(test[1].size() == 9);
				REQUIRE(test[2].size() == 5);
				REQUIRE(test[3].size() == 6);
			}
		}
		WHEN("Build_frames called test output")
		{
			s.Build_frames("input.txt");
			vector<vector<bitset<8>>> test = s.get_Sender_output();

			THEN("Expected Sender_output ")
			{

				REQUIRE(test[0][0].to_string()=="00111001");
				REQUIRE(test[0][1].to_string() == "01010000");
				REQUIRE(test[0][2].to_string() == "01010010");
				REQUIRE(test[0][3].to_string() == "01001111");
				REQUIRE(test[0][4].to_string() == "01001010");
				REQUIRE(test[0][5].to_string() == "01000101");
				REQUIRE(test[0][6].to_string() == "01000011");
				REQUIRE(test[0][7].to_string() == "01010100");
				REQUIRE(test[0][8].to_string() == "01101100");
				REQUIRE(test[1][0].to_string() == "00111001");
				REQUIRE(test[1][1].to_string() == "01010100");
				REQUIRE(test[1][2].to_string() == "01100101");
				REQUIRE(test[1][3].to_string() == "01110011");
				REQUIRE(test[1][4].to_string() == "01110100");
				REQUIRE(test[1][5].to_string() == "01101001");
				REQUIRE(test[1][6].to_string() == "01101110");
				REQUIRE(test[1][7].to_string() == "01100111");
				REQUIRE(test[1][8].to_string() == "01101111");
				REQUIRE(test[2][0].to_string() == "00110101");
				REQUIRE(test[2][1].to_string() == "01100011");
				REQUIRE(test[2][2].to_string() == "01101101");
				REQUIRE(test[2][3].to_string() == "01110000");
				REQUIRE(test[2][4].to_string() == "01001011");
				REQUIRE(test[3][0].to_string() == "00110110");
				REQUIRE(test[3][1].to_string() == "01000101");
				REQUIRE(test[3][2].to_string() == "01000001");
				REQUIRE(test[3][3].to_string() == "01110011");
				REQUIRE(test[3][4].to_string() == "01111001");
				REQUIRE(test[3][5].to_string() == "00111000");

			}
		}

	}
}

TEST_CASE("Ensure which written in output file of sender correct size", "[Sender]")
{
	ofstream fout;
	fout.open("input_test.txt");
	fout << "PROJECT" << endl;
	fout << "Testing" << endl;
	Sender s;
	s.Build_frames("input_test.txt");
	vector<vector<bitset<8>>> test = s.get_Sender_output();
	s.Sender_output("output_test.txt");
	ifstream myfile("output_test.txt");
	if (myfile.is_open())
	{
		string line;
		int k = 0;
		while (getline(myfile, line))
		{
			Receiver r;
			vector<string>temp_test = r.Receiver_split(line);

			REQUIRE(temp_test.size()-1 == test[k].size());
			k++;

		}
	}
	myfile.close();
}

TEST_CASE("Ensure which written in output file of sender correct output", "[Sender]")
{
	ofstream fout;
	fout.open("input_test.txt");
	fout << "PROJECT" << endl;
	fout << "Testing" << endl;
	Sender s;
	s.Build_frames("input_test.txt");
	vector<vector<bitset<8>>> test = s.get_Sender_output();
	s.Sender_output("output_test.txt");
	ifstream myfile("output_test.txt");
	if (myfile.is_open())
	{
		string line;
		int k = 0;
		while (getline(myfile, line))
		{
			Receiver r;
			vector<string>temp_test = r.Receiver_split(line);

			for (int i = 0; i < 2; i++)
			{

				REQUIRE(test[k][i].to_string() == temp_test[i]);
			}
			k++;

		}
	}
	myfile.close();
}

TEST_CASE("Check filling sender map correct","[Sender]")
{
	Sender s;
	s.Sender_map();
	map<char, bitset<8>>temp_test = s.get_Sender_map();
	SECTION("Check characters from 0 to 11 in the map") {
		auto j = GENERATE(range(0,11));
		char c = j + '0';
		REQUIRE_FALSE(temp_test[c].to_string()=="00000000");
	}

	SECTION("Check characters from a to z in the map") {
		auto j = GENERATE(range(0, 25));
		char c = j + 'a';
		REQUIRE_FALSE(temp_test[c].to_string() == "00000000");
	}

	SECTION("Check characters from A to Z in the map") {
		auto j = GENERATE(range(0, 25));
		char c = j + 'A';
		REQUIRE_FALSE(temp_test[c].to_string() == "00000000");
	}

}

TEST_CASE("Check unexisting data in sender map ", "[Sender]")
{
	Sender s;
	s.Sender_map();
	map<char, bitset<8>>temp_test = s.get_Sender_map();
	SECTION("Check characters from 0 to 11 in the map") {
		int j = 12;
		char c = j + '0';
		CHECK(temp_test[c].to_string() == "00000000");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
								/*Receiver class testing */
/////////////////////////////////////////////////////////////////////////////////////////////////

SCENARIO("Exception testing in receiver class","[Receiver]") {
	GIVEN("An object from receiver class") {
		Receiver r;
		string out_file_path = "output2.txt";

		WHEN("path String is wrong") {

			string test_in_path = "input15.txt";

			THEN("Check if there is a throw") {
				REQUIRE_THROWS(r.Receive_frames(test_in_path,out_file_path));
			}

			THEN("Check if the throw contains this word") {
				CHECK_THROWS_WITH(r.Receive_frames(test_in_path,out_file_path), Catch::Contains("File"));
			}

			THEN("Check the type of the throw") {
				CHECK_THROWS_AS(r.Receive_frames(test_in_path,out_file_path), const char *);
			}

			THEN("Check the type of the throw and match the the condition") {
				REQUIRE_THROWS_MATCHES(r.Receive_frames(test_in_path,out_file_path), const char *,
									   Catch::Contains("File") && !Catch::EndsWith("out"));
			}
		}

		WHEN("Path string is right") {
			string in_file_path = "output.txt";

			THEN("check if no throw") {
				CHECK_NOTHROW(r.Receive_frames(in_file_path, out_file_path));
			}
		}

		WHEN("A binary number with something wrong")
		{
			string s_wrong = "10020010";
			THEN("The binary to integer converter will give a throw ") {
				REQUIRE_THROWS(r.Receiver_bin_string_to_int(s_wrong));
				CHECK_THROWS_AS(r.Receiver_bin_string_to_int(s_wrong), const char *);
			}
		}

		WHEN("A binary number with no problem")
		{
			string s_right = "10101011";
			THEN("The binary to integer converter will not throw") {
				REQUIRE_NOTHROW(r.Receiver_bin_string_to_int(s_right));
			}
		}
	}
}

TEST_CASE("Matcher Expression testing in receiver class","[Receiver]") {
	Receiver r;
	string in_file_path = "output.txt";
	string out_file_path = "output2.txt";
	string test_path = "input15.txt";

	SECTION("check the name of input file") {
		CHECK_THAT(in_file_path, Catch::EndsWith("OUTput.txt", Catch::CaseSensitive::No) && Catch::Contains("tp"));
		REQUIRE_THAT(in_file_path, Catch::EndsWith( "ouTpUt.TxT" , Catch::CaseSensitive::No) ||
								   (Catch::StartsWith( "out" ) && !Catch::Contains( "not file" ) ) );
	}

	SECTION("test the elements in sender map") {
		map<char, bitset<8>>map_test = r.get_Receiver_map();
		char ch1 = 1 + 'a'; //letter b
		char ch2 = 23 + 'A'; //letter X
		REQUIRE_THAT(map_test[ch1].to_string(), Catch::Equals("01100010"));
		CHECK_THAT(map_test[ch2].to_string(), Catch::EndsWith("1000") && !Catch::StartsWith("0100"));
	}
}

TEST_CASE("Check filling Receiver map correct", "[Receiver][1]")
{
	Receiver r;
	r.Receiver_map();
	map<char, bitset<8>>temp_test = r.get_Receiver_map();
	SECTION("Check characters from 0 to 11 in the map") {
		auto j = GENERATE(range(0, 11));
		char c = j + '0';
		REQUIRE_FALSE(temp_test[c].to_string() == "00000000");
	}

	SECTION("Check characters from a to z in the map") {
		auto j = GENERATE(range(0, 25));
		char c = j + 'a';
		REQUIRE_FALSE(temp_test[c].to_string() == "00000000");
	}

	SECTION("Check characters from A to Z in the map") {
		auto j = GENERATE(range(0, 25));
		char c = j + 'A';
		REQUIRE_FALSE(temp_test[c].to_string() == "00000000");
	}

}

TEST_CASE("Check un existing data in Receiver map ", "[Receiver]")
{
	Receiver r;
	r.Receiver_map();
	map<char, bitset<8>>temp_test = r.get_Receiver_map();
	SECTION("Check characters from 0 to 11 in the map") {
		int j = 12;
		char c = j + '0';
		CHECK(temp_test[c].to_string() == "00000000");
	}
}

TEST_CASE("Split string according space function test", "[Receiver][1]")
{
	string test = "Testing project should support code coverage";
	Receiver r;
	vector<string> temp_test = r.Receiver_split(test);
	SECTION("Check size of vector equal the number of words") {
		REQUIRE(temp_test.size() == 6);
	}
	SECTION("Check returned actal words in sentence  equal the separated words ") {
		REQUIRE(temp_test[0] =="Testing");
		REQUIRE(temp_test[1] == "project");
		REQUIRE(temp_test[2] == "should");
		REQUIRE(temp_test[3] == "support");
		REQUIRE(temp_test[4] == "code");
		REQUIRE(temp_test[5] == "coverage");
	}
}

TEST_CASE("Test return of binary string to integer", "[Receiver]")
{
	string bin_str = "10101101";
	Receiver r;
	int dec = r.Receiver_bin_string_to_int(bin_str);
	CHECK(dec == 173);
}


TEST_CASE("Check if receiver receive correct num of words", "[Receiver]")
{
	ofstream fout;
	fout.open("input_test.txt");
	fout << "PROJECT" << endl;
	fout << "Testing" << endl;
	Sender s;
	s.Build_frames("input_test.txt");
	s.Sender_output("output_test.txt");
	Receiver r;
	r.Receive_frames("output_test.txt", "rec_output_test.txt");
	ifstream myfile("rec_output_test.txt");
	if (myfile.is_open())
	{
		string line;
		vector<string>temp_test;
		while (getline(myfile, line))
		{
			temp_test.push_back(line);
		}
		REQUIRE(temp_test.size() == 2);
		temp_test.clear();
	}
	myfile.close();
}

TEST_CASE("Check if receiver receive correct", "[Receiver]")
{
	ofstream fout;
	fout.open("input_test.txt");
	fout << "PROJECT" << endl;
	fout << "Testing" << endl;
	Sender s;
	s.Build_frames("input_test.txt");
	s.Sender_output("output_test.txt");
	Receiver r;
	r.Receive_frames("output_test.txt", "rec_output_test.txt");
	ifstream myfile("rec_output_test.txt");
	if (myfile.is_open())
	{
		string line;
		vector<string>temp_test;
		while (getline(myfile, line))
		{
			temp_test.push_back(line);
		}
		CHECK(temp_test[0] =="PROJECT");
		CHECK(temp_test[1] == "Testing");
	}
	myfile.close();
}


TEST_CASE("Check if receiver receive incorrect data because of limitation of number of characters", "[Receiver][1]")
{
	ofstream fout;
	fout.open("input_test.txt");
	fout << "Department" << endl;
	fout << "computer" << endl;
	Sender s;
	s.Build_frames("input_test.txt");
	s.Sender_output("output_test.txt");
	Receiver r;
	r.Receive_frames("output_test.txt", "rec_output_test.txt");
	ifstream myfile("rec_output_test.txt");
	if (myfile.is_open())
	{
		string line;
		vector<string>temp_test;
		while (getline(myfile, line))
		{
			temp_test.push_back(line);
		}
		CHECK_FALSE(temp_test[0] == "Department");
		CHECK(temp_test[1] == "computer");
	}
	myfile.close();
}

TEST_CASE("Error accepting", "[Receiver]")
{
	Receiver r;
	float Error_percent = r.Error_accepting(70, 3);
	REQUIRE(Error_percent == Approx(5).epsilon(0.7));

}

TEST_CASE("Error not accepting", "[Receiver]")
{
	Receiver r;
	float Error_percent = r.Error_accepting(70,7);
	CHECK_FALSE(Error_percent == Approx(5).epsilon(0.7));

}
