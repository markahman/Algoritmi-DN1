#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Uporaba: " << argv[0] << " <vhodna_datoteka>\n";
		return 1;
	}
	std::string fileName = argv[1];

	return 0;
}
