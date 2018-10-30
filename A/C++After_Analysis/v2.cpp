// GooglePractice.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main()
{

	int n = 0;
	int m = 0;
	unsigned case_num = 1;
	int some_case_num = 0;
	vector<int> case_serial_num;
	vector<vector<long long int> > case_data;
	vector<long long int> tmp_vector;
	int tmp;
	std::string line;
	std::ofstream outfile("..\\data\\a-large-practice.out");
	std::ifstream t("..\\data\\a-large-practice.in"); //读文件ifstream,写文件ofstream，可读可写fstream
	std::stringstream buffer;
	//buffer << t.rdbuf();
	//std::string s = buffer.str();


	if (t)
	{
		while (!t.eof())//(getline(t,line))
		{
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
				else if (m <= some_case_num)
				{
					t >> tmp;
					tmp_vector.push_back(tmp);
					m++;
				}
				else
				{
					m = 1;
					t >> some_case_num;
					case_data.push_back(tmp_vector);
					tmp_vector.clear();
					case_serial_num.push_back(some_case_num);
				}
			}
			n++;
		}
	}


	case_data.push_back(tmp_vector);
	tmp_vector.clear();
	case_serial_num.push_back(some_case_num);
	t.close();

	long long int z = 0;
	vector<vector<long long int>>::iterator it = case_data.begin();
	for (unsigned int i = 0; i < case_num; i++, ++it)
	{
		long long int ans = 0;
		tmp_vector = *it;
		sort(tmp_vector.begin(), tmp_vector.begin()+ tmp_vector.size());

		std::unordered_map<long long int, long long int> map;

		for ( int a = tmp_vector.size()-1; a >= 0; a--)
		{
			for ( int b = a - 1; b >= 0; b--)
			{
				z = tmp_vector[a] * tmp_vector[b];
				if (z != 0)
				{
					if (map.find(z) != map.end())
					{
						ans = ans + map[int(z)];
					}
				}
				else
				{
					ans = ans + b;
				}
			}

			if (map.find(tmp_vector[a]) != map.end())
			{
				map[int(tmp_vector[a])] = map[int(tmp_vector[a])] + 1;
			}					
			else
			{
				map[int(tmp_vector[a])] = 1;
			}
						
			
		}
		outfile << "Case #" << i + 1 << ": " << ans << "\n";
		std::cout << ans << endl;
		tmp_vector.clear();
	}

	outfile.close();

	return 0;
}

