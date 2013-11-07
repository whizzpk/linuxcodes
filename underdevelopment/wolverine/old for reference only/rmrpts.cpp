#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <list>
using namespace std;


// Works like greater-than but forces 'figure x' to smallest
bool mySort(const string &s1, const string &s2) {
	if(*s2.begin()=='f')
		return true;
	else if(*s1.begin()=='f')
		return false;
	else
		return (s1>s2);
}


void readdata2()
{
	string parse,	// A line of text from the file
		   temp;	// A potential duplicate value
	ifstream infile("neighbor.txt");
	ofstream outfile("cplus.txt");
	outfile.close();	
	if(infile.good()) {
		while(!infile.eof()) {
			getline(infile, parse);
			/**/
				string tmp;
				getling(
			/**/
			if(parse!="") {
				list<string> line;
				istringstream iss(parse);
				while(!iss.eof()) {
					iss >> temp;
					if(temp=="figure") {	// Keep figure # together
						temp+=" ";	// Put the space in
						string fig;
						iss >> fig;		// Get the figure #
						temp+=fig;
					}
					line.push_back(temp);
				}
				line.sort(mySort);	// Custom sort to handle the figure #, descending
				line.unique();		// Strip the duplicates
				outfile.open("cplus.txt", ios::app);
				copy(line.begin(), line.end(), ostream_iterator<string> (outfile, " "));
				outfile << endl;
				outfile.close();
				line.clear();
			}
		}
		infile.close();
	}
}


//simple string wise removal

char* removeDuplicate(char str[])//remove duplicate characters from a string,so that each character in a string is not repeating
{
    int i = 0,j;
    char ch;
    while((ch = str[i++] )!= '\0')
    {
        j = i;
        while(str[j] != '\0')
        {
            if(ch == str[j])
            {
                while(str[j]!='\0')
                str[j] = str[++j];
                 i--;
                break;
            }
            j++;
        }
    }
   return str;
}


int main(){

//calling regex to read duplicates.
readdata2();

//sorting duplicates 
//mySort();



return 0;
}
