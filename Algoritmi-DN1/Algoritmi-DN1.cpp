#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define OUTPUT_FILE "out.txt"
#define CHECK_ORDER true

typedef unsigned char byte;

std::vector<byte> readData(std::string fileName)
{
	std::vector<byte> data;
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

void writeData(std::vector<byte>& data)
{
	std::ofstream file(OUTPUT_FILE);
	if (!file.is_open())
	{
		std::cerr << "Napaka pri odpiranju datoteke!\n";
		return;
	}
	for (int i = 0; i < data.size(); i++)
		file << int(data[i]) << " ";
	file.close();
}

bool checkOrder(const std::vector<byte>& data, const bool sortOrder)
{
	for (int i = 1; i < data.size(); i++)
		if (data[i] < data[i - 1])
			return false;
	return true;
}

void sortByBit(std::vector<byte>& A, const std::vector<bool>& D, const bool sortOrder)
{
	std::vector<byte> B(A.size());	// Zacasni vektor
	int j = 0;
	for (int i = 0; i < A.size(); i++)	// Prvi prehod
		if (sortOrder)
		{
			if (!D[i])
				B[j++] = A[i];
		}
		else
		{
			if (D[i])
				B[j++] = A[i];
		}
	for (int i = 0; i < A.size(); i++)	// Drugi prehod
		if (sortOrder)
		{
			if (D[i])
				B[j++] = A[i];
		}
		else
		{
			if (!D[i])
				B[j++] = A[i];
		}
	A = B;
}

void binaryRadixSort(std::vector<byte>& A, const bool sortOrder)
{
	for (int k = 0; k < 8; k++)
	{
		std::vector<bool> D(A.size());	// Vektor, ki hrani vrednosti bitov na mestu k
		for (int i = 0; i < A.size(); i++)
			D[i] = (A[i] >> k) & 1;
		sortByBit(A, D, sortOrder);	// Sortiramo A glede na bit k
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Uporaba: " << argv[0] << " <input_file> <smer_sortiranja>\n\t<smer_sortiranja> - asc = narascajoce, desc = padajoce\n";
		return 1;
	}

	std::string fileName = argv[1];
	std::vector<byte> data = readData(fileName);
	if (data.empty())
	{
		std::cerr << "Napaka pri branju podatkov!\n";
		return 1;
	}

	bool sortOrder;
	std::string orderStr = argv[2];
	if (orderStr == "asc")
		sortOrder = true;
	else if (orderStr == "desc")
		sortOrder = false;
	else
	{
		std::cerr << "Napaka pri vnosu smeri sortiranja!\n";
		std::cerr << "Uporaba: " << argv[0] << " <input_file> <smer_sortiranja>\n\t<smer_sortiranja> - asc = narascajoce, desc = padajoce";
		return 1;
	}

	binaryRadixSort(data, sortOrder);

	writeData(data);
	if (CHECK_ORDER)
	{
		if (checkOrder(data))
			std::cout << "Podatki uspesno sortirani!\n";
		else
			std::cerr << "Napaka pri sortiranju podatkov!\n";
	}

	return 0;
}