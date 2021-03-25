#include <iostream>
#include <fstream>
#include <string>

// 4210191011 M. Alifian

std::string txtData;
std::string endLine = "<endl>";
struct Siswa
{
	std::string nrp, name, gender;
} dataSiswa[28];
static int dataSiswaLength = 28;

void LoadFileTXT() {
	// Open File
	std::ifstream file("daftar-nama.txt");
	if (!file) {
		std::cout << "Error In Opening File!!!\n";
		exit(0);
	}

	// Copy all data
	char temp[1000];
	int MAX = 1000;
	// Copy
	while (!file.eof()) {
		file.getline(temp, MAX);
		txtData += temp;
		txtData += endLine;
	}

	// Close
	file.close();
}
void ProcessData(std::string dataSiswaTemp[27]) {
	// Find nrp, nama, jenis_kelamin each line
	for (int i = 0; i < dataSiswaLength; i++) {
		int findFront = 0, findBack = 0, lenght = 0;

		findFront = dataSiswaTemp[i].find("\t", findFront) + 1;
		findBack = dataSiswaTemp[i].find("\t", findFront);
		lenght = findBack - findFront;
		dataSiswa[i].nrp = dataSiswaTemp[i].substr(findFront, lenght);
		
		findFront = dataSiswaTemp[i].find("\t", findFront) + 1;
		findBack = dataSiswaTemp[i].find("\t", findFront);
		lenght = findBack - findFront;
		dataSiswa[i].name = dataSiswaTemp[i].substr(findFront, lenght);

		findFront = dataSiswaTemp[i].find("\t", findFront) + 1;
		findBack = dataSiswaTemp[i].find("\t", findFront);
		lenght = findBack - findFront;
		dataSiswa[i].gender = dataSiswaTemp[i].substr(findFront, lenght);
	}
}
void LoadData() {
	int findFront = 0, findBack, lenght;
	std::string dataSiswaTemp[28];

	// Find each line inside data
	for (int i = 0; i < dataSiswaLength; i++) {
		findFront = txtData.find(endLine, findFront + 1) + endLine.size();
		findBack = findFront;
		findBack = txtData.find(endLine, findBack);
		lenght = findBack - findFront;
		dataSiswaTemp[i] = txtData.substr(findFront, lenght); 
	}	

	ProcessData(dataSiswaTemp);
}

void MakeAndSaveDataCSV() {
	// Make a new file.csv
	std::ofstream file("4210191011_M-Alifian.csv");

	// Rewrite and input siswa data (and header)
	for (int i = 0; i < dataSiswaLength; i++) {
		file << dataSiswa[i].nrp << "," << dataSiswa[i].name << "," << dataSiswa[i].gender << std::endl;
	}

	// Close file.csv
	file.close();
}
void RewriteDataReverse() {
	// Open existed file
	std::fstream file("4210191011_M-Alifian.csv", std::ios::in | std::ios::out);
	std::string dataCSV[29];

	// Copy all data
	char temp[1000];
	int MAX = 1000, i = 0;
	while (!file.eof()) {
		file.getline(temp, MAX);
		dataCSV[i] += temp;
		i++;
	}

	file.clear();
	file.seekg(0);

	// Add reversed data without header
	for (int i = dataSiswaLength; i > 0; i--) {
		file << dataCSV[i] << std::endl; //std::cout << dataCSV[i] << "<endl>\n";
	}	file << "                      ";

	// Close file
	file.close();
}

int main() {
	LoadFileTXT();
	LoadData();
	std::cout << "\nLoad txt data Complete\n";

	MakeAndSaveDataCSV();
	std::cout << "\nMake and add CSV data complete\n";
	RewriteDataReverse();
	std::cout << "\nRewrite and reverse CSV data complete\n";

	return 0;
}