#include"head.h"

using namespace std;


int main(){
Content_::ContentControl wOb;
wOb.read_content();
wOb.split_content('\n');
string s("");
cout<<"Write word or words divided by space and use _ symbol for missing letters then press Enter\nFor example:he__o wo__d\n";
while (getline(cin,s))
{
   wOb<<s;
}



}


