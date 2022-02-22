#include"head.h"
#include<queue>
using namespace std;


int main(){
Content_::ContentControl wOb;
wOb.read_content();
wOb.split_content('\n');
string s("");
while (getline(cin,s))
{
   wOb<<s;
}



}


