#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<int> readData(std::string fileName)
{
	std::vector<int> data;
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Napaka pri odpiranju datoteke!\n";
		return data;
	}
	int temp;
	while (file >> temp)
		data.push_back(temp);
	file.close();
	return data;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Nepravilno stevilo argumentov!\nUporaba: " << argv[0] << " <tip_sortiranja> <ime_datoteke>\n\t-tip_sortiranja: 0 = Counting sort, 1 = Roman sort\n\t-ime_datoteke: ime tekstovne datoteke s podatki, npr. vhod.txt\n";
		return 1;
	}
	std::string a1 = argv[1];
	std::string a2 = argv[2];
	bool useRomanSort;
	std::string fileName;
	try
	{
		if (a1 == "0")
			useRomanSort = false;
		else if (a1 == "1")
			useRomanSort = true;
		else
			throw std::exception();

		if (a2.substr(a2.size() - 4) == ".txt")
			fileName = a2;
		else
			throw std::exception();
	}
	catch (std::exception e)
	{
		std::cerr << "Nepravilna uporaba argumentov!\nUporaba: " << argv[0] << " <tip_sortiranja> <ime_datoteke>\n\t-tip_sortiranja: 0 = Counting sort, 1 = Roman sort\n\t-ime_datoteke: ime tekstovne datoteke s podatki, npr. vhod.txt\n";
		return 1;
	}

	return 0;
}
