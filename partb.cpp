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
            int periodCount = 0;
            for(int j = 0; j < counter; j++)
            {
                
                if(possibleMatches[0][j] == '.')
                {
                    periodCount++;
                }
                cout << possibleMatches[0][j];
            }
            if(possibleMatches[0][counter] == '.')
            {
                cout << ".0";
            }
            while(periodCount != 2)
            {
                cout << ".0";
                periodCount++;
            }

            cout << endl;
            //cout<<possibleMatches[0]<< endl;  
            outfile<< possibleMatches[0] << endl;  // writes to output.txt
            possibleMatches.erase(possibleMatches.begin());  
        }
        myfileDB.clear(); //clears the buffer
        myfileDB.seekg(0, ios::beg); //resets positon of text file to beginning

    }
    outfile.close();
    myfileDB.close();    
    return 0;
}