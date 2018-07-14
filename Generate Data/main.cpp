// Generate Data.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>

#include "compress_quicklz.h"

using namespace std;

int main()
{
	const char * input = "itemdata.txt";
	const char * output = "itemdata.dat";
	// Read input file
	ifstream inf(input);
	if (!inf.is_open()) {
		cerr << "Error: cannot open input file '" << input << "'\n";
		return 1;
	}
	string in_buf;
	in_buf.assign(istreambuf_iterator<char>(inf), istreambuf_iterator<char>());
	inf.close();
	// Compress data
	string out_buf;
	if (!CCompressorQuickLZ().compress(in_buf, out_buf)) {
		cerr << "Error: cannot compress input data (len=" << in_buf.size() << ")\n";
		return 1;
	}
	// Write output file
	ofstream outf(output, ios_base::binary);
	if (!outf.is_open()) {
		cerr << "Error: cannot open output file '" << output << "'\n";
		return 1;
	}
	outf.write(out_buf.c_str(), out_buf.size());
	return 0;
}
