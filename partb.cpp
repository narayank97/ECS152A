#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv [])
{
    string dataBaseName = argv[1];
    string ipAdresses = argv[2];

    string lineDB;
    string IP;
    ifstream myfileIP(ipAdresses);
    ifstream myfileDB(dataBaseName);
    ofstream outfile("output.txt");

    vector<string> possibleMatches;
    vector<string> listOfIps;

    if(myfileIP.is_open())
    {
        while(getline(myfileIP,IP))
        {
            listOfIps.push_back(IP);
        }
    }
    myfileIP.close();
    
    for(int i = 0; i < listOfIps.size(); i++)
    {
        if(myfileDB.is_open())
        {
            int counter = 1;
            while(getline(myfileDB,lineDB))
            {
                
                string dbComp = lineDB.substr(0,counter).c_str();
                string ipComp = listOfIps[i].substr(0,counter).c_str();


                if(dbComp == ipComp)
                {
                    if(possibleMatches.empty())
                    {
                        possibleMatches.push_back(lineDB);
                        counter++;
                    }
                    else
                    {
                        possibleMatches.pop_back();
                        possibleMatches.push_back(lineDB);
                        counter++;
                    }                    
                }
            }
            int spaceCounter = 0;
            string myMatch = possibleMatches[0]; // this has a new line with it DO SOMETHING ABOUT IT
            for(int j = 0; j < myMatch.size() - 1; j++)
            {
                if(myMatch[j] == ' ' && spaceCounter == 0)
                {
                    spaceCounter++;
                    outfile << '/';
                }
                else if(myMatch[j] == ' ' && spaceCounter != 0)
                {
                    spaceCounter++;
                    outfile << ' ';
                }
                else
                {
                    outfile << myMatch[j];
                } 
            }
            outfile << ' ' << listOfIps[i].substr(0 , listOfIps[i].size() - 1);  // writes to output.txt
            if(i != listOfIps.size() - 1)
            {
                outfile << endl;
            }
            
            possibleMatches.erase(possibleMatches.begin());  
        }
        myfileDB.clear(); //clears the buffer
        myfileDB.seekg(0, ios::beg); //resets positon of text file to beginning

    }
    outfile.close();
    myfileDB.close();    
    return 0;
}