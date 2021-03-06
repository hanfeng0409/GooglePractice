// GooglePractice.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	int n = 0;
	int m = 0;
	int case_num = 0;
	int some_case_num = 0;
	vector<int> case_serial_num;
	vector<double> case_data;
	vector<double> tmp_vector;
	double tmp;
	std::string line;
	std::ofstream outfile("..\\data\\A-small-practice.out");
	std::ifstream t("..\\data\\A-small-practice.in");
	std::stringstream buffer;
	//buffer << t.rdbuf();
	//std::string s = buffer.str();
	
	
	if (t)
	{
		while (!t.eof())//(getline(t,line))
		{
			//cout << line << endl;
			if (n == 0)
			{
				t >> case_num;
			}
			else				
			{
				if (m == 0)
				{
					t >> some_case_num;
					case_serial_num.push_back(some_case_num);
					m++;
				}
				else if(m<=some_case_num)
				{
					t >> tmp;
					case_data.push_back(tmp);
					m++;
				}
				else
				{
					m = 1;
					t >> some_case_num;
					case_serial_num.push_back(some_case_num);
				}
			}
			n++;
		}
	}

	vector<double>::iterator it = case_data.begin();
	for (int i = 0; i < case_serial_num.size(); i++)
	{
		for (int j = 0; j < case_serial_num[i]; ++j,++it)
		{
			tmp_vector.push_back(*it);
		}
		long long int result = 0;
		for (unsigned int a = 0; a < tmp_vector.size()-2; a++)
		{
			for (unsigned int b = a+1; b < tmp_vector.size() - 1; b++)
			{
				for (unsigned int c = b+1; c < tmp_vector.size(); c++)
				{
					if (tmp_vector[a] * tmp_vector[b] == tmp_vector[c] || tmp_vector[c] * tmp_vector[b] == tmp_vector[a] || tmp_vector[a] * tmp_vector[c] == tmp_vector[b])
					{
						result++;
					}
				}
			}
		}
		outfile << "Case #"<< i+1 <<": "<<result<<"\n";
		std::cout << result << endl;
		tmp_vector.clear();
	}
	
	outfile.close();

    return 0;
}