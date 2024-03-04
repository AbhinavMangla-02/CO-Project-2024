#include<bits/stdc++.h>
using namespace std;
int main()
{
fstream newfile;
newfile.open("Output.txt" ,ios::out);
while (newfile.is_open())
{
    newfile << "Yo I am Writing in this file << \n" ;
    newfile.close();
}

}