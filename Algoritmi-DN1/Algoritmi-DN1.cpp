#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define OUTPUT_FILE "out.txt"

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

void writeData(std::vector<int>& data)
{
	std::ofstream file(OUTPUT_FILE);
	if (!file.is_open())
	{
		std::cerr << "Napaka pri odpiranju datoteke!\n";
		return;
	}
	for (int i = 0; i < data.size(); i++)
		file << data[i] << " ";
	file.close();
}

void getMinMax(const std::vector<int>& data, int& min, int& max)
{
	min = data[0];
	max = data[0];
	for (int i = 1; i < data.size(); i++)
	{
		if (data[i] < min)
			min = data[i];
		if (data[i] > max)
			max = data[i];
	}
}

void countingSort(std::vector<int>& A)
{
	int min, max;
	getMinMax(A, min, max);
	std::vector<int> C(max - min + 1, 0);
	for (int i = 0; i < A.size(); i++)
		C[A[i] - min]++;
	for (int i = 1; i < C.size(); i++)
		C[i] += C[i - 1];
	std::vector<int> B(A.size());
	for (int i = A.size() - 1; i >= 0; i--)
		B[C[A[i] - min] - 1] = A[i],
		C[A[i] - min]--;
	A = B;
}

void romanSort(std::vector<int>& A)
{
	int min, max;
	getMinMax(A, min, max);
	std::vector<int> C(max - min + 1, 0);
	for (int i = 0; i < A.size(); i++)
		C[A[i] - min]++;
	std::vector<int> B(A.size());
	int index = 0;
	for (int i = 0; i < C.size(); i++)
		for (int j = 0; j < C[i]; j++)
			B[index++] = i + min;
	A = B;
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

	std::vector<int> data = readData(fileName);
	if (data.size() == 0)
	{
		std::cerr << "Napaka pri branju podatkov!\n";
		return 1;
	}
	if (useRomanSort)
		romanSort(data);
	else
		countingSort(data);

	writeData(data);

	return 0;
}
