//============================================================================
// Name        : CSE365.cpp
// Author      : Sujjanaraj Muruganandam
// Description : CSE 365 Assignment1 ABAC Access Control Engine
//============================================================================


//#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iomanip>
#include<bits/stdc++.h>
#include <vector>
using namespace std;

std::vector<string> ATTRS;
std::vector<string> PERMS;
std::vector<string> PA;
std::vector<string> ENTITIES(1000);
std::vector<string> AA;
std::vector<string> word1;
std::vector<string> word2;





void load(string filename)
{
    ifstream file;
    file.open(filename.c_str());
    //string line;
    int count = 0;
    string line;
    int k = 0;
    int c = 0;
    int visited = 0;

    while (file)
    {
        getline(file, line);
        k = 0;
        count = 0;
        c = 0;
            for (int i = 0; i<line.size(); i++)
            {
                //cout << line;
                //cout << line.size();
                c++;

                if (line.at(i) == '=')
                {
                    //cout << line.substr(0, c);
                    if (line.substr(0, c) == "ATTRS =")
                    {
                        ATTRS.push_back(line.substr(0, c));
                        count = 1;
                        //cout << count;

                    }

                    if (line.substr(0, c) == "PERMS =")
                    {
                        PERMS.push_back(line.substr(0, c));
                        count = 2;
                        //cout << count << endl;
                        //cout << line << endl;
                    }

                    if (line.substr(0, c) == "PA =")
                    {
                        PA.push_back(line.substr(0, c));
                        count = 3;
                        //cout << count;
                    }

                    if (line.substr(0, c) == "ENTITIES =")
                    {
                        ENTITIES.push_back(line.substr(0, c));
                        count = 4;
                        //cout << count;
                    }

                    if (line.substr(0, c) == "AA =" && visited == 0)
                    {
                        AA.push_back(line.substr(0, c));
                        count = 5;
                        //cout << line.substr(0, c);
                        visited = 1;
                    }
                    k = i + 1;
                    c = 0;
                }

                if (line.at(i) == ';')
                {
                    visited = 0;
                    //cout << count ;
                    if (count == 1)
                    {
                        ATTRS.push_back(line.substr(k, c));
                        //cout << line.substr(k, c);
                        //cout << count;
                    }
                    if (count == 2)
                    {
                        PERMS.push_back(line.substr(k, c));
                        //cout << line.substr(k, c);
                        //cout << line <<endl;
                    }
                     if (count == 4)
                    {
                        ENTITIES.push_back(line.substr(k, c));

                    }
                    if (count == 5 && visited == 0)
                    {
                        AA.push_back(line.substr(k, c));
                        visited = 1;

                    }
                    //cout << line.substr(k, c);
                    if (count != 3)
                    {
                        k = i + 1;
                        c = 0;
                    }

                }
                if (line.at(i) == '-')
                {
                    if (count == 3)
                    {
                        PA.push_back(line.substr(k, c));
                        k = i + 1;
                        c = 0;
                    }
                }

                if ((i + 1) == line.size())
                {
                    if (count == 1)
                        ATTRS.push_back(line.substr(k, c));
                    if (count == 2)
                        PERMS.push_back(line.substr(k, c));
                    if (count == 3)
                        PA.push_back(line.substr(k, c));
                    if (count == 4)
                        ENTITIES.push_back(line.substr(k, c));
                    if (count == 5)
                        AA.push_back(line.substr(k, c));

                    //cout << line.substr(k, c);

                }

            }

    }
}
void removePartAA(string word1, string word2, string word3)
{
	string search; int u=0;
		//cout<< perms<<word1<<word2<<endl;
			 for (int r = 0; r < PA.size(); r++)
			{
				 u=0;
				search = AA[r];
				int offset = search.find(word1, 0);
				if (offset != string::npos)
				{
					int offset2=search.find(word2, 0);
					if (offset2 != string::npos)
					{
						int offset3=search.find(word3, 0);
						if (offset3 != string::npos)
						{
						AA[r]="";
						}
					}



				}

			}
}

void addAA(string word1, string word2, string word3)
{
	string temp="<"+word1+"> : <";
	temp+=word2+", "+word3+">;";
	AA.push_back(temp);

}

void addPA(string check, string perms)
{
	string temp, temp2; int num=0; //cout<<1;
	if(check == "add-attributes-to-permission")
	{
		for(int i=0; i<word1.size();i++)
		{
			//cout<<word1[i]<<word2[i];
			if((i+1)==word1.size())
			{
				temp+="<"+word1[i]+", "+word2[i]+"> ";
			}
			else
		    temp+="<"+word1[i]+", "+word2[i]+">; ";
		}
		temp+=":"+perms;
		PA[PA.size()-1]+=" -";
		PA.push_back(temp);

	    }
}

void removePA(string perms, string word1, string word2)
{
	string search; int u=0;
	//cout<< perms<<word1<<word2<<endl;
		 for (int r = 0; r < PA.size(); r++)
		{
			 u=0;
			search = PA[r];
			int offset = search.find(perms, 0);
			if (offset != string::npos)
			{
				int offset2=search.find(word1, 0);
				if (offset2 != string::npos)
				{
					int offset3=search.find(word2, 0);
					if (offset3 != string::npos)
					{
					for (int i = offset2; i < search.size(); i++)
					{
						u++;
						if (search.at(i) == '>')
					{
						//cout<<2<<endl;
					  PA[r] = search.substr(0, offset2-3)+(search.substr(u+offset2, (search.size()-(offset2+u-3))));
					  //cout<<PA[r]<<endl;
					}
					}
					}
				}



			}

		}
}

void removeAA(string word)
{
	string search;
	 for (int r = 0; r < AA.size(); r++)
	{
		search = AA[r];
		int offset = search.find(word, 0);
		if (offset != string::npos)
		{
			//r++;
			for (int i = r; i < AA.size()-1; i++)
			{
				if ((i + 1) == AA.size() - 1)
				{
				 AA[i]="";
				}
				else
				{
					AA[i] = AA[i + 1];
					//AA[i + 1] = "";
					//cout << AA[i];
				}
				//t++;
				AA[AA.size() - 1] = "";
			}


		}

	}
}
void addPERMS(string word)
{
	string temp="; ";
	temp+="<"+word+">";
	PERMS.push_back(temp);

}


void removePartPA(string word)
{
	//cout<< word;
	string search;
	string temp;
	int u=0;
		 for (int r = 0; r < PA.size(); r++)
		{
			search = PA[r];
			//cout<< search;
			int offset = search.find(word, 0);
			u=0;
			//cout<<offset<<endl;
			if (offset != string::npos)
			{
				//cout<<offset<<endl;
				for (int i = offset; i < search.size(); i++)
				{
					u++;
					//cout<<u<<endl;
					if((offset-2) == 0)
					{
						//cout<<1;
						PA[r]="";
						for(int c=r; c< PA.size(); c++)
						{
							PA[c]=PA[c+1];
							PA[c+1]="";
						}
					}
					if (search.at(i) == '>')
					{

					  PA[r] = search.substr(0, offset-3)+(search.substr(u+offset, (search.size()-(offset+u-3))));

					}
				}
               }
          }
}

void removeATTRS(string word)
{
	string fo;
	    	int g=0;
	    	for(int y=0; y<ATTRS.size(); y++)
	    	{
	    		fo = ATTRS[y];
	    		int offset = fo.find(word, 0);
	    		if(offset != string::npos)
	    		{
	    			for (int u=y; u< ATTRS.size(); u++)
	    			{
	    				if((u+1) == ATTRS.size() -1)
	    				{
	    					ATTRS[u]="";
	    				}
	    				else
	    				{
	    					ATTRS[u] = ATTRS[u+1];
	    				}
	    				ATTRS[ATTRS.size()-1]="";
	    			}
	    		}
	    	  }
	    	removeAA(word);
	    	removePartPA(word);
}
void operate(string operate, string word)
{
    string temp, temp2;
    string search;
    int t = 0;

    if (operate == "add-entity")
    {
        temp = ";";
        temp += "<" + word + ">";
        ENTITIES.push_back(temp);

    }

    if (operate == "remove-entity")
    {

        temp2 = "<" + word + ">";
        temp2 += ";";
        //cout << temp;
        vector<string>::iterator result = find(ENTITIES.begin(), ENTITIES.end(), temp2);
        if (result == ENTITIES.end())
            cout << "Invalid Entry" << endl;
        else
            ENTITIES.erase(result);
        removeAA(word);
      }


}





void print()
{
    for (int i = 0; i < ATTRS.size(); i++)
    {
        cout << ATTRS[i];
    }
    cout << endl;

    for (int i = 0; i < PERMS.size(); i++)
    {
    	if(PERMS[i] == "")
		{
			int d;
		}
    	else
        cout << PERMS[i];
    }
    cout << endl;
    for (int i = 0; i < PA.size(); i++)
    {
    	if(PA[i] == "")
		{
			int d;
		}
		else
		{
			cout << PA[i];
			cout << endl;
		}
    }

    for (int i = 0; i < ENTITIES.size(); i++)
    {
    	if(ENTITIES[i] == "")
		{
			int d;
		}
		else
		{
			cout << ENTITIES[i];
		}

    }
    cout << endl;

    for (int i = 0; i < AA.size(); i++)
    {
    	if(AA[i] == "")
    	{
    		int d;
    	}
    	else
    	{
    		cout << AA[i];
    		cout << endl;
    	}

    }

}

void check(string word1, string word2, string word3, string word4)
{
    string sea1="yyy"; string sea; int p=0;

    int c = 0; int offset; int value = -1;
    word1 = "<" + word1 + ">";
    for (int i = 0; i < AA.size(); i++)
    {
        sea = AA[i];


        offset = sea.find(word1, 0);
        //cout<<offset<<endl;
        if (offset != string::npos)
        {
        	p++;
        	//cout<<sea;

            for (int h = 0; h < sea.size(); h++)
            {
                if (sea.at(h) == ':')
                {
                	//cout<<h<<endl;

                    for (int g = h+1; g < sea.size(); g++)
                    {
                        c++;
                        if(sea.at(g) == '>')
                        {
                        	//cout<<g<<endl;
                        	//cout<<sea<<endl;
                        	sea1 = sea.substr(h+2, c-1);

                        	  for (int v = 0; v < PA.size(); v++)
                        	    {
                        	        string sea3 = PA[v];

                        	        int offset4 = sea3.find(word4, 0);
                        	        //cout<<offset4<<endl;
                        	        p=0;
                        	        if (offset4 != string::npos)
                        	        {
                        	        	// cout<<sea3<<endl;
                        	        	// cout<<sea1<<endl;
                        	            int offset2 = sea3.find(sea1);
                        	           // cout<<offset2<<endl;
                        	            if (offset2 != string::npos)
                        	            {
                        	                value = 1;
                        	                p=1;
                        	                //cout<< value<<endl;
                        	                break;
                        	            }

                        	        }
                        	    }
                        }
                    }
                }
            }

        }

    }
    //cout<<p<<endl;
    if(p==0)
    	value=0;

    if (value == 1)
    {
        cout << "Permission GRANTED!";
    }
    else
    {
        cout << "Permission DENIED!";
    }

}

int removePERMS(string word)
{
	int t=0;
	string temp2 = " <" + word + ">";
	        temp2 += ";";

	        vector<string>::iterator result = find(PERMS.begin(), PERMS.end(), temp2);
	        if (result == PERMS.end())
                t=0;
	        else
	            PERMS.erase(result);



        for (int r = 0; r < PA.size(); r++)
        {
            string search = PA[r];
            int offset = search.find(word, 0);

            if (offset != string::npos)
            {

                for (int i = r; i < PA.size() - 1; i++)
                {
                    if ((i + 1) == PA.size() - 1)
                    {
                        PA[i] = "";
                    }
                    else
                    {
                        PA[i] = PA[i + 1];

                    }

                    PA[PA.size() - 1] = "";
                }
                t++;
            }
        }

        return t;
}

void addATTRS(string funcName, string ATTname, string ATTtype)
{

	if(funcName == "add-attribute")
	{
		string temp=";";
		temp+="<"+ATTtype+","+ATTname+">";
		ATTRS.push_back(temp);
	}

}

void process(std::vector <std::string>  vec)
{
    std::string filename;

    for (int d = 0; d < vec.size(); d++)
    {

        if (vec[d] == "load-policy")
        {
            filename = vec[d + 1];

            load(filename);
        }
        if (vec[d] == "show-policy")
        {
           // print();
        }
        if (vec[d] == "add-entity")
        {

            operate(vec[d], vec[d + 1]);

        }
        if (vec[d] == "remove-entity")
        {

            removeATTRS(vec[d + 1]);
        }
        if (vec[d] == "check-permission")
        {
            check( vec[d+1], vec[d+2], vec[d+3], vec[d + 4] );
        }
        if (vec[d] == "remove-permission")
        {
            int num = 1;
            for (int j = 0; num != 0; j++)
            {
                num = removePERMS(vec[d + 1]);
            }


        }
        if(vec[d] == "add-attribute")
        {
        	addATTRS(vec[d] , vec[d+1], vec[d+2]);

        }
        if(vec[d] == "remove-attribute")
		{
		    removeAA(vec[d+1]);
		}

        if(vec[d] == "add-permission")
        {
        	addPERMS(vec[d+1]);
        }

        if(vec[d] == "add-attributes-to-permission")
		{
        	string name = vec[d];
        	string perm = vec[d+1];
        	for(int i=d+2; i<vec.size(); i+=2)
        	{
        		if(vec[i-1]=="show-policy"||vec[i-1]=="add-entity"||vec[i-1]=="remove-entity"||vec[i-1]=="check-permission"||vec[i-1]=="remove-permission"||vec[i-1]=="add-attribute"||vec[i-1]=="remove-attribute"||vec[i-1]=="remove-permission"||vec[i-1]=="add-attributes-to-permission"||vec[i-1]=="remove-attribute-from-permission"||vec[i-1]=="add-attribute-to-entity"||vec[i-1]=="remove-attribute-from-entity")
				{
					break;
				}
				if(vec[i]=="show-policy"||vec[i]=="add-entity"||vec[i]=="remove-entity"||vec[i]=="check-permission"||vec[i]=="remove-permission"||vec[i]=="add-attribute"||vec[i]=="remove-attribute"||vec[i]=="remove-permission"||vec[i]=="add-attributes-to-permission"||vec[i]=="remove-attribute-from-permission"||vec[i]=="add-attribute-to-entity"||vec[i]=="remove-attribute-from-entity")
				{
					break;
				}
        		else
        		{
        		 word1.push_back(vec[i]);
        		 word2.push_back(vec[i+1]);
        		}
        	}
        	addPA(vec[d], vec[d+1]);

		 }

        if(vec[d] == "remove-attribute-from-permission")
		{
			removePA(vec[d+1],vec[d+2],vec[d+3]);

		}
        if(vec[d] == "add-attribute-to-entity")
		{
        	addAA(vec[d+1], vec[d+2], vec[d+3]);
		}
        if(vec[d] == "remove-attribute-from-entity")
		{
			removePartAA(vec[d+1], vec[d+2], vec[d+3]);
		}
    }
}





int main( int argc, char * argv[])
{
    std::vector <string> att;
    if (argc < 2)
    {
        cout << "Invalid Number of Arguments";
        exit(EXIT_FAILURE);
    }
    char * parts = std::strtok(argv[1], ";");
    std::vector <string> semi;
    int count = 0;
    int c = 0;
    int j = 0;
    int track = 0;


    int size;


    for (int i = 0; parts!=NULL; i++)
    {
        semi.push_back(parts);

        parts = std::strtok(NULL, ";");


    }

    for (int g = 1; g < semi.size(); g++)
    {
        string g1 = semi[g];
        if (g1.at(0) == ' ')
        {
            g1 = g1.substr(1);
            semi[g] = g1;
        }

    }


    for (int k = 0; k < semi.size(); k++)
    {
        std::string s = semi[k];

        j = 0;
        c = 0;

        for (int h = 0; h < s.size(); h++)
        {
            c++;
            if((s.at(h) == ' '))
            {
                att.push_back(s.substr(j,c-1));
                c = 0;
                j = h+1;

            }
            if ((h + 1) == s.size())
            {
                att.push_back(s.substr(j,c));
            }
        }

    }

    process(att);

}

