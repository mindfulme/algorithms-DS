/**
Name: Minhas Kamal
Description: This program reads a prefix notation from a file & finds the result
Date: Oct-2013
**/

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;


double stringToDouble(string str);
double exponent(double a, double b);

struct element{
    string str;     //string property
    double value;    //value of the string
    bool opert;      //operator-true, operand-false
};


int main(){
    ifstream input; //the input file

    input.open("PrefixEvaluation_Input.txt");
    if(!input.is_open()){   //when file is not found exit
        cout << "File name is wrong!\n";
        return 0;
    }


    string s;   //stores the input file's element as string
    vector<element> inputElement;   //holds the behaviour of the input elements

    element el; //pushing a '(' to determine the start
    el.opert=true;
    el.str="(";
    el.value=-0;
    inputElement.push_back(el);


    while(input >> s){  //the loop determines the behaviour of the input elements
        element elem;
        elem.str = s;

        if(s[0]=='+' || s[0]=='-' || s[0]=='*' || s[0]=='/' || s[0]=='^' || s[0]=='(' || s[0]==')'){ //when an operator is found
            elem.value = -0.0;
            elem.opert = true;
        }
        else{
            elem.value = stringToDouble(s); //this method converts string to double
            elem.opert = false;
        }

        inputElement.push_back(elem);
    }

    input.close();  //closing the stream


    /*cout << "string \toperat \tvalue \n";   //output of the inputElement
    for(int i=0; i<inputElement.size(); i++){
        cout << inputElement[i].str << "\t" << inputElement[i].opert << "\t" << inputElement[i].value << endl;
	}*/

	stack<element> tempStore;  //here operands are stored temporarily

    for(int i=0; i<inputElement.size(); i++){
        tempStore.push(inputElement[i]);

        if(!tempStore.top().opert){
            double a = tempStore.top().value;   //taking the first elements of the stack
            string s = tempStore.top().str;
            tempStore.pop();

            double result = a;

            if(tempStore.top().opert){
                element e;
                e.opert=false;
                e.str=s;
                e.value=a;

                tempStore.push(e);
            }
            else
                while(1){
                    double b = tempStore.top().value;
                    tempStore.pop();


                    if(tempStore.top().str[0]=='+') result = b+result;
                    else if(tempStore.top().str[0]=='-') result = b-result;
                    else if(tempStore.top().str[0]=='*') result = b*result;
                    else if(tempStore.top().str[0]=='/') result = b/result;
                    else if(tempStore.top().str[0]=='^') result = exponent(b, result);

                    tempStore.pop();    //pop the operator

                    //cout << "After finding " << b << " result is: " << result << endl; //analysing every step

                    if(tempStore.top().opert){
                        element elem;
                        elem.str = result;
                        elem.opert=false;
                        elem.value=result;

                        tempStore.push(elem);
                        break;
                    }
                }
        }
    }

    cout << "The result is: " << tempStore.top().value << "\n\n\n";

    return 0;
}


double stringToDouble(string str){  //converts a string to a double
    double value=0, //holds the value of the string
           afterPoint=0;    //holds the value after a point

    bool flag = false;  //represents if any point is found in the string
    int numberOfElementAfterPoint=0;

    for(int i=0; str[i]!=NULL; i++){
        if(str[i]=='.') flag = true;
        else{
            if(flag){
                afterPoint = afterPoint*10 + (str[i]-48);
                numberOfElementAfterPoint++;
            }
            else
                value = value*10 + (str[i]-48);
        }
    }

    int divisor=1;  //divides the afterPoint element by precise number of 10s
    for(int i=0; i<numberOfElementAfterPoint; i++) divisor = divisor*10;

    value = value + afterPoint/divisor;

    return value;
}


double exponent(double a, double b){
    double result=1;

    for(int i=0; i<b; i++) result = result*a;

    return result;
}



