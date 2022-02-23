#ifndef __HEAD_H_
#define __HEAD_H_
#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include<vector>
#include<map>
#include<list>

namespace Content_{
    using namespace std;
    class ContentControl{
       
        
        string fName="";
        string fContent="";
        string chars="";
        map<int,vector<string>> ordered_list;
        map<char,int> letter_count;
        const char* message="The most possible letter or letters to open:";
        struct search_info{
            string origin;
            regex search_reg;
            vector<string>::const_iterator itBeg;
            vector<string>::const_iterator itEnd;     
            int len;
       
        };
        template<class T>
        string set_pos_char(T it){
            int max=-1;
            string s="";
            for(auto i:it){
                if(i.second==max){
                    s.push_back(' ');
                    s+=i.first;
                }
                else if(i.second>max){
                    max=i.second;
                    s="";
                    s.push_back(' ');
                    s+=i.first;
              

                }
            }
           return s;
        }
        template<class T>
        void find_match(T it,T b,T e){
            
            if(it==e){
                cout<<endl;
                it=b;
                bool done=true;
                while (it!=e)
                {
                    if(it->itBeg==it->itEnd)
                        it++;
                    else
                    {
                        done=false;
                        break;
                    }
                }
                
                if(done){
                    
                    cout<<this->message<<this->set_pos_char(this->letter_count)<<endl;
                    return;
                }
                it=b;
                
            }

            
                while (it->itBeg!=it->itEnd)
                {
                    string s=*(it->itBeg++);
                    if(regex_search(s,it->search_reg)){

                        cout<<s+" ";
                        string letters=this->uniq_chars(regex_replace(s,regex("["+this->chars+"]"),""));
                        for(char ch:letters){
                            if(this->letter_count.count(ch))
                            {
                                this->letter_count[ch]++;
                                continue;
                            }
                            this->letter_count.insert(pair<char,int>(ch,1));
                        }
                        break;
                    }
                   
                }
               
            
            if(it->itBeg==it->itEnd){
                int j=0;
                while (j<=it->len)
                {
                    j++;
                    cout<<" ";
                }
                

            }

            this->find_match(++it,b,e);
        }
       
        public:
        string uniq_chars(string s){
            list<char> chList;
            for(char ch :s)
                chList.push_back(ch);
            
            chList.sort();
            chList.unique();
            s="";
            for(char ch:chList)
                s+=ch;
            return s;
        }
        void operator<<(string s)
        {
            istringstream is(s);
            this->chars="";
            vector<search_info> v_ser_inf;
            string letters=regex_replace(s,regex("[^a-zA-Z]"),"");
            this->chars=this->uniq_chars(letters);

           
            string ch="_";
            while (!is.eof())
            {
                string s1("");
                getline(is,s1,' ');
                s1=this->low_case(s1);
                regex se=regex("^"+regex_replace(s1,regex(ch),"[^"+this->chars+"]")+"$");
                int len=s1.length();
                v_ser_inf.push_back({s1,se,this->ordered_list[len].cbegin(),this->ordered_list[len].cend(),len});

            }
            this->find_match(v_ser_inf.begin(),v_ser_inf.begin(),v_ser_inf.end());
            
        };
        ContentControl(string s="words.txt"):fName(s){};
        void read_content(int len=0){
            ifstream i(this->fName);
            if(i.good()){
                string s("");
                if(len){
                    int j=0;
                    char ch;
                    while(j<len&&!i.eof()){
                        i.get(ch);
                        s+=ch;
                        j++;

                    }    
                    this->fContent=s;
                    return;
                }

                getline(i,s,'\0');
                this->fContent=s;
            }

            if(i.is_open())
                i.close();

        }
        int content_len(){return this->fContent.length();}
        string show_content(int len=0) const{
            
            if(len)
                return this->fContent.substr(0,len);
            
            return this->fContent.substr(0,this->fContent.length());
        }
        string low_case(string s){
            string s1("");
            for(char ch:s){
                s1+=::tolower(ch);
            }

            return s1;
        }
        
        void split_content(char ch){
            int n=0;
            
            istringstream is(this->fContent);
            
            while (!is.eof())
            {
                string s("");

                getline(is,s,ch);
                s=this->low_case(s);
                int len=s.length();
                if(!this->ordered_list.count(len))
                    this->ordered_list.insert(pair<int,vector<string>>(len,vector<string>(1,s)));
                else{
                    vector<string> &pt=this->ordered_list[len];
                    int n=pt.size();
                    pt.resize(n+1);
                    auto it=pt.begin();
                    *(it+n)=s;


                }
                
                
            }
            
    
           

        }
     
    };

 
}
#endif