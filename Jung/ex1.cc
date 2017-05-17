#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>
#include <time.h>
#include <string>
using namespace std;





bool addNumber(double &mean,string str, int pos,int n){               //adds number to mean if line is valid and returns 1, otherwise returns 0
    
    int i=pos+1;
    
    int pos2=i;
    int point;
    
    
    while(str[i]==' '){
        i++;
    }
    if(str[i]<48||str[i]>57){
        return false;
    }
    else{
        pos2=i;
        while(str[i]>47&&str[i]<58){
            i++;
        }
        
        point=i;
        int pos3=i;
        if(str[i]==' '){
            while(str[i]==' '){
                i++;
            }
            if(str[i]!=0){
                return false;
            }
        }
        else if(str[i]==0){
            
        }
        else if(str[i]=='.'){
            i++;
            while(str[i]>47&&str[i]<58){
            i++;
            }
            pos3=i-1;
            while(str[i]==' '){
                i++;
            }
            if(str[i]!=0){
                return false;
            }
            
        }
        else{
            return false;
        }
        
        double numb=0.0;
        for(int j=point-pos3;j<0;j++){         //numbers behind comma
            numb=numb+(str[point-j]-48)*pow(10,j);
        }
        for(int j=0;j<point-pos2;j++){          //numbers before comma
            numb=numb+(str[point-j-1]-48)*pow(10,j);
        }
        
        
        if(mean==0){
            mean=numb;
        }
        else{
            long double exponent=(1+(log(1/mean))/(log(numb)))/(n+1);
            mean=mean*pow(numb,exponent);
        }
        return true;
        
        
    }
    
}

int getLoc(int &pos, string str){                            //gets location, returns 0 if nonvalid location, sets new position after nex semicolon
    

    int i=pos+1;
    while(str[i]==' '){
        i++;
    }
    
    if(str[i]!='1'&&str[i]!='2'){
        return 0;
    }
    else{
        int loc=str[i]-48;
        i++;
        while(str[i]==' '){
            i++;
        }
        if(str[i]!=';'){
            return 0;
        }
        else{
            pos=i;
            return loc;
        }
    }
}


int mean(int &loc1,int &loc2,double &mean1,double &mean2,string filename) {
     
     
     
     
	ifstream file;
	file.open(filename);
	string str;
	int count = 0;
	
	while (file.peek() != -1) {
	    
	     getline(file, str);
		    count++;
	    
	    if(str[0]=='#'){                //ignore lines with semicolon
	    }
	    else{
	        
	       int length=str.length();
	       
	       if (length<4){               //ignore nonvalid lines
	       }
	       else{
	           	      
	           int pos=str.find_first_of(';',0);
	           
	           if(pos>length){          //ignore lines with no semicolon
	               
	           }
	           else{
	               

	               
	               int loc=getLoc(pos,str);
	                if(loc==1){
	                   bool is=addNumber(mean1,str,pos,loc1);
	                   if(is){
	                    loc1++;
	                   }
	               }
	               else if(loc==2){
	                    bool is=addNumber(mean2,str,pos,loc2);
	                   if(is){
	                    loc2++;
	                   }
	               }
	           }
	       }
	    }
		
	}
	file.close();
	return count;
	
}


int main(int argc, char* argv[]) {
    	clock_t tStart = clock();
    	
    	int loc1=0;
    	int loc2=0;
    	double mean1=0.0;
    	double mean2=0.0;
    	int count=mean(loc1,loc2,mean1,mean2,argv[1]);
    	
    	cout<< "File: ex1.dat with :"<< count << "  lines"<< endl;
        cout<<" Valid Values Loc1:"<< loc1<< "  With GeoMean: "<<mean1<<endl;
        cout<<" Valid Values Loc2:"<< loc2<< "  With GeoMean: "<<mean2<<endl;

		cout << "Time needed: ";
	    cout << (double)(clock() - tStart) / CLOCKS_PER_SEC << " seconds" << endl;
	   
	return 0;
 }