// codestats.cpp : Defines the entry point for the application.
//

#include "codestats.h"

using namespace std;

int main(int argc, char* argv[])
{
	map<string, int> langMap;
	int totalLines = 0;

	string input_path;
	
	if (argc > 1) {
		input_path = argv[1];
	}
	else {
		//get current working directory
		char cwd[FILENAME_MAX];
		if (_getcwd(cwd, sizeof(cwd)) != NULL) {
			input_path = cwd;
		}
		else {
			cout << "Error getting current working directory" << endl;
			return 1;
		}
	}

	//get all files in directory and subdirectories
	for (const auto& entry : fs::recursive_directory_iterator(input_path)) {
		if (entry.is_regular_file()) {
			bool ignore = false;
			for (auto& x : ignore_list) {
				if (entry.path().string().find(x) != string::npos) {
					ignore = true;
					break;
				}
			}
			if (ignore) continue;
				
			
			string extension = entry.path().extension().string();
			ifstream file(entry.path());
			if (file.is_open()) {
				//get count of lines
				int lineCount = 0;
				string line;
				while (getline(file, line)) {
					lineCount++;
				}
				file.clear();
				
				extension = convert_extension(extension);
				
				if (langMap.find(extension) == langMap.end()) {
					langMap[extension] = lineCount;
				}
				else {
					langMap[extension] += lineCount;
				}
				totalLines += lineCount;
			}
		}
	}
	
	//find the language with the longest key length
	int longestLang = 0;
	for (auto& x : langMap) {
		if (x.first.length() > longestLang) {
			longestLang = x.first.length();
		}
	}
	
	//print out the titles Language, Lines and Percent seperated differently depending on the longest language name
	printf("LANGUAGE");
	for (int i = 0; i < longestLang - 4; i++) {
		printf(" ");
	}
	printf("\LINES\tPERCENT\n");
	for (int i = 0; i < longestLang + 19; i++) {
		printf("-");
	}
	printf("\n");
	
	//sort langmap by lines
	vector<pair<string, int>> vec;
	for (auto& x : langMap) {
		vec.push_back(x);
	}
	sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
		return a.second > b.second;
	});
	
	
	for (auto& x : vec) {
		float percentF = ((float)x.second / totalLines) * 100;
		percentF = roundf(percentF * 100) / 100;
		string percent = to_string(percentF);
		percent = percent.substr(0, percent.find(".") + 3).append("%");
		
		
		//make it so regardless of length, they will all be in the same column
		string lang = x.first;
		if (lang.length() < 8) {
			lang.append("\t");
		}
		printf("%s\t%d\t%s\n", lang.c_str(), x.second, percent.c_str());
	}
	
	
	return 0;
}
