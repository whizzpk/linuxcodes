#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

struct lineInfo
{
    string filename;
    int lineNumber;
};
int WriteFile(std::string fname, std::map<string, lineInfo> *m) {
    int count = 0;
    if (m->empty())
        return 0;
 
    FILE *fp = fopen(fname.c_str(), "w");
    if (!fp)
        return 0;
     
    for(std::map<string, lineInfo>::iterator it = m->begin(); it != m->end(); ++it) {
        fprintf(fp, "%s", (it->first.c_str()));
        count++;
    }
     
    fclose(fp);
    return count;
}
ostream& operator<<(ostream& oOstream, const lineInfo& iLineInfo)
{
    oOstream << iLineInfo.filename << " at line " << iLineInfo.lineNumber;
    return oOstream;
}

int main()
{
    map<string, lineInfo> lineMap;

    string fileName = "recurrance.txt";
    ifstream myFile(fileName.c_str());
    std::string line;

    int line_number = 1;
    while(getline(myFile, line))
    {
	if(line.length()>14)
 	line.erase (0,12);
        lineInfo currentLineInfo = {fileName, line_number};
        pair<string, lineInfo> newObject(line, currentLineInfo);
        pair<map<string, lineInfo>::iterator, bool> result = lineMap.insert(newObject);

        if (result.second == false)
        {
            std::cout << "\"" << line << "\"" << " in " << currentLineInfo << " was already in " << (*result.first).second << "." << std::endl;
        }
	
        ++line_number;
    }
   
	
	
	WriteFile("definite.txt", &lineMap);
	

    return 0;
}
