#include "DetectMemoryLeak.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>

using std::string;
using std::vector;
using std::list;
using std::map;
using std::stack;
using std::queue;

// DO NOT MODIFY ANY LINE ABOVE OR ADD EXTRA INCLUDES

/*! 
 *  \brief     DM2126 Assignment 2
 *  \details   Submit the whole solution, but only this file will be used to grade
 *  \author    Sri Sham Haran S/O R Raja
 *  \date      2015 
 *  \note      155129R
 */


// Balanced parenthesis
 bool Brackets(const string& input)
{
     stack<char> inputList;
     for (int i = 0; i < (int(input.size())); i++){
         if (input[i] == '[' ||
             input[i] == '{' ||
             input[i] == '(' ||
             input[i] == '<'
             ){
             inputList.push(input[i]);
         }
         if (input[i] == ']' ||
             input[i] == '}' ||
             input[i] == ')' ||
             input[i] == '>'){
             if (inputList.empty() == true){
                 return false;
             }
             else{
                
                 switch (inputList.top()){
                 case '[': if (input[i] == ']') inputList.pop(); break;
                 case '{': if (input[i] == '}') inputList.pop(); break;
                 case '(': if (input[i] == ')') inputList.pop(); break;
                 case '<': if (input[i] == '>') inputList.pop(); break;
                     
                 }
             }
         }
     }

    return inputList.empty();
}

// Query machine, hits
void QueryMachine(vector<int>& data, vector<int>& queries, vector<unsigned int>& results)
{
    map<int, int>iimap;
    for (auto d : data){
        iimap[d]++;
    }
    for (auto q : queries){
        results.push_back(iimap[q]);
    }
}