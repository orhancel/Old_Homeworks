#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>



using namespace std;

/*
 * 
 */
 struct reg_t{
 	int r1,r2,r3,r4,r5;
 	};
 	
int sqrt(int x,int y);
int move(int line,reg_t *reg,string dos[]);
int add(int line,reg_t *reg,string dos[]);
int sub(int line,reg_t *reg,string dos[]);
int jump(int *line,reg_t *reg,string dos[]);
int print(int line,reg_t *reg,string dos[]); 	
int checkcommand(string line,int *i);
int checkreg(string line,int *i);
int checkcoma(string line,int *i);
int checkcons(string line,int *i);
int checkdotcoma(string line,int *i);

	
int main(int argc, char** argv) {
    string x;				/*A temporary string to use through out the code*/
    
    char yedek;					/*A temporary char to use through out the code**/
    string dos[256];		/*An array of strings to put all the lines in the file so we can jump between lines*/
    int imlec=0,temp=0,line=0,i=0;
    
    reg_t reg;		/*Struct of registers*/
    ifstream dosya;
    dosya.open(argv[1]);
    reg.r1=0;
    reg.r2=0;
    reg.r3=0;
    reg.r4=0;
    reg.r5=0;
  
    for(line=0;line<256;++line)				/*Makes all the chracters in the file upper case*/
	{	getline(dosya,x);			/*First get the string from the file*/
   		for(i=0; x[i]!='\0' ;i++)
   	 	{   if(x[i]<='z' && x[i]>='a')
   	        x[i]=x[i]-('a'-'A');
	  	}

		dos[line]=x;					/*And we put them in the string array*/
	}
	
	for(line=0;line<250;line++)			/*Syntax checking function*/
	{	x=dos[line];
		
		if(checkcommand(x,&imlec)==1)		/*Command types has different return values.move,add,sub has 1, jump has 2,halt has 3,print has 4*/
		{	imlec=imlec+3;
			
			if(checkreg(x,&imlec)==1)		/*checks the first register.There has to be a register,not a constant*/
			{	
				if(checkcoma(x,&imlec)==1)	/*then coma the seperate them,ignores the spaces.*/
				{	temp=imlec;
					
					if(checkreg(x,&imlec)==1)		/*then another register.But this time it could be a constant*/
					{
						if(checkdotcoma(x,&imlec)==1)/*if it's a register,then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error"<<endl;
							return 0;
						}
					}
				
					else if(checkcons(x,&imlec)==2)	/*If we can't find a register,we look for a constant*/
  					{
					  	if(checkdotcoma(x,&imlec)==1)	/*	then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error"<<endl;
							return 0;
						}
					}
					else if(checkcons(x,&temp)==1)	/*This one is for NEGATÝVE NUMBERS.FUNCTÝON RETURNS 1*/
					{	
						if(checkdotcoma(x,&temp)==1)
							continue;
						else
						{	cout<<"Syntax Error"<<endl;
							return 0;
						}
					}
					else
					{	cout<<"Syntax Error"<<endl;
							return 0;
						}
				}
				else
				{	cout<<"Syntax Error"<<endl;
							return 0;
						}
			}
			else
			{	cout<<"Syntax Error"<<endl;
							return 0;
						}
		}
		else if(checkcommand(x,&imlec)==2)		/*THÝS ONE ÝS FOR JUMP*/
		{	imlec=imlec+4;
			if(checkreg(x,&imlec)==1)
			{	
				if(checkcoma(x,&imlec)==1)
				{	
					if(checkreg(x,&imlec)==1)
					{	if(checkdotcoma(x,&imlec)==1)
							continue;
						else
						{	cout<<"Syntax Error"<<endl;
							return 0;
						}
					}
					if(checkcons(x,&imlec)==2)
  					{	if(checkdotcoma(x,&imlec)==1)
							continue;
						else
						{	cout<<"Syntax Error"<<endl;
							return 0;
						}
					}
					else
					{	cout<<"Syntax Error"<<endl;
							return 0;
						}
				}
				else
				{	cout<<"Syntax Error"<<endl;
							return 0;
						}
			}
			else if(checkcons(x,&imlec)==2)
  			{	
			  	if(checkdotcoma(x,&imlec)==1)
					continue;
				else
				{	cout<<"Syntax Error"<<endl;
						return 0;
				}
			}
			else
			{	cout<<"Syntax Error"<<endl;
				return 0;
			}
		}
		else if(checkcommand(x,&imlec)==3)	/*THÝS ONE ÝS FOR HALT*/
		{	imlec=imlec+4;
			if(checkdotcoma(x,&imlec)==1)
					break;
			else
			{	cout<<"Syntax Error"<<endl;
				return 0;
			}
		}
		else if(checkcommand(x,&imlec)==4)	/*THÝS ONE ÝS FOR PRÝNT.WE CAN PRÝNT NEGATÝVE NUMBERS TOO*/
		{	imlec=imlec+4;
			if(checkreg(x,&imlec)==1)
			{	if(checkdotcoma(x,&imlec)==1)
					continue;
				else
				{	cout<<"Syntax Error"<<endl;
					return 0;
				}
			}
			else if(checkcons(x,&imlec)==2)
			{	if(checkdotcoma(x,&imlec)==1)
					continue;
				else
				{	cout<<"Syntax Error"<<endl;
					return 0;
				}
			}
			
			else
			{	cout<<"Syntax Error"<<endl;
				return 0;
			}
		}
		else
		{	cout<<"Syntax Error"<<endl;
			return 0;
		}
			
	}
	
    

    temp=0;
    for(line=0;line<256;++line)	/*THÝS LOOPS REMOVES ALL OF THE WHÝTESPACES*/
    {	
		for(imlec=0; dos[line][imlec]!='\0' ;imlec++)
    		{	if(dos[line][imlec]!=' ')
    			{	yedek=dos[line][imlec];
	    			dos[line][imlec]=' ';
	    			dos[line][temp]=yedek;
	    			temp+=1;
	    		}
	    	}
	
		temp=0;
		if(*argv[2]=='1')/*DEPENDS OF THE ENTERED OPTÝON NUMBER,THÝS LOOP ALLOWS US THE SEE THE ÝNSTRUCTÝONS AND */
    		{	cout << dos[line][0]<<dos[line][1]<<dos[line][2]<<' ';/*REGÝSTER NUMBERS*/
			for(imlec=3;dos[line][imlec]!='\0';imlec++)
			{	
				if(dos[line][imlec]==';')
					break;
				else if(dos[line][imlec]!=',')
					cout<<dos[line][imlec];
				else if(dos[line][imlec]==',')
					cout<<' '<<','<<' ';
			}
		cout<<" R1="<<reg.r1<<" R2="<<reg.r2<<" R3="<<reg.r3<<" R4="<<reg.r4<<" R5="<<reg.r5<<endl;
    		}
		
    	
		if(dos[line][0]=='M' && dos[line][1]=='O' && dos[line][2]=='V')/*WE CALL THE FUNCTÝONS ,ACCORDÝNG TO OUR ÝNSTRUCTÝONS*/
    		move(line,&reg,dos);
    	else if(dos[line][0]=='A' && dos[line][1]=='D' && dos[line][2]=='D')
			add(line,&reg,dos);
		else if(dos[line][0]=='S' && dos[line][1]=='U' && dos[line][2]=='B')
			sub(line,&reg,dos);
		else if(dos[line][0]=='J' && dos[line][1]=='M' && dos[line][2]=='P')
			jump(&line,&reg,dos);
		else if(dos[line][0]=='P' && dos[line][1]=='R' && dos[line][2]=='N')
			print(line,&reg,dos);
		else if(dos[line][0]=='H' && dos[line][1]=='L' && dos[line][2]=='T')
			return 0;
			
    
	}
    	return 0;
}
	

int checkcommand(string line,int *i)/*SYNTAX FUNCTÝON.i ÝS THE CURSOR NUMBER OF THAT LÝNE*/
{	
	for(*i=0;line[*i]!='\0';*i=*i+1)
	{
		if(line[*i]==' ')
			continue;
		else if(line[*i]<='Z' && line[*i]>='A')
		{	if(line[*i]=='M' && line[*i+1]=='O' && line[*i+2]=='V' && line[*i+3]==' ')
				return 1;
			else if(line[*i]=='A' && line[*i+1]=='D' && line[*i+2]=='D' && line[*i+3]==' ')
				return 1;
			else if(line[*i]=='S' && line[*i+1]=='U' && line[*i+2]=='B' && line[*i+3]==' ')
				return 1;
			else if(line[*i]=='J' && line[*i+1]=='M' && line[*i+2]=='P' && line[*i+3]==' ')
				return 2;
			else if(line[*i]=='P' && line[*i+1]=='R' && line[*i+2]=='N' && line[*i+3]==' ')
				return 4;
			else if(line[*i]=='H' && line[*i+1]=='L' && line[*i+2]=='T' && line[*i+3]==' ')
				return 3;
			else
			{
				return 0;
			}
		}
		else if(line[*i]>='Z' ||  line[*i]<='A')
		{
			return 0;
		}
	}
		
	
	return 0;
		
}

int checkreg(string line,int *i)/*SYNTAX FUNCTÝON TO CHECK REGÝSTERS*/
{	
	while(line[*i]!='\0')
	{
		
		if(line[*i]==' ')
			*i+=1;
		else if(line[*i]=='R' && line[*i+1]<='9' && line[*i+1]>='0')
		{	*i+=2;
			return 1;
		}
		else
		{	
			return 0;
		}
	}

	return 0;	
}
int checkcoma(string line,int *i)//*SYNTAX FUNCTÝON TO CHECK COMA*/
{
	while(line[*i]!='\0')
	{
		if(line[*i]==' ')
			*i+=1;
		else if(line[*i]==',' && line[*i+1]==' ')
		{	*i=*i+2;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
	
}
int checkcons(string line,int *i)/*SYNTAX FUNCTÝON TO CHECK CONSTANT NUMBERS*/
{	
	while(line[*i]!='\0')
	{	
		if(line[*i]==' ')
			*i+=1;
		else if(line[*i]=='-')/*FOR NEGATÝVE ONES*/
		{	*i+=1;
			
			while(line[*i]<='9' && line[*i]>='0')
				{	
					if(line[*i+1]==' ')
					{	*i=*i+1;
						return 1;
					}
					else
						*i+=1;
				}
			return 0;
		}
		else if(line[*i]<='9' && line[*i]>='0')	/*FOR POSÝTÝVE ONES*/
		{	
			while(line[*i]<='9' && line[*i]>='0')
			{	
				if(line[*i+1]==' ')
				{	
					*i=*i+1;
					return 2;
				}
				else 
				{
					*i+=1;
				}
			}
		}
		else
		{	
			return 0;
		}
				
	}

	return 0;
	
}
int checkdotcoma(string line,int *i)/*SYNTAX FUNCTÝON TO CHECK SEMÝCOLON*/
{	while(line[*i]!='\0')
	{	if(line[*i]==' ')
			*i+=1;
		else if(line[*i]==';')
			return 1;
		else
		{
			return 0;
		}
	}
	
	return 1;
}	

int sqrt(int x,int y)/*POWER FUNCTÝON*/
{	int temp=1,i=0;

	for(i=0;i<y;i++)
	{	temp=x*temp;
	}
	return temp;
	
}

int move(int line,reg_t *reg,string dos[])
{	int imlec=0;
	int *first=0;
	int temp=0;
	int cons=0;
	int sign=1;/*FOR NEGATÝVE NUMBERS*/
	
   
    	if(dos[line][3]=='R' && dos[line][4]=='1')
    		first=&reg->r1;							/*LOAD THE LEFT REGÝSTER TO A VARÝABLE*/
    	else if(dos[line][3]=='R' && dos[line][4]=='2')
    		first=&reg->r2;
    	else if(dos[line][3]=='R' && dos[line][4]=='3')
    		first=&reg->r3;
    	else if(dos[line][3]=='R' && dos[line][4]=='4')
    		first=&reg->r4;
    	else if(dos[line][3]=='R' && dos[line][4]=='5')
    		first=&reg->r5;
    
			
				
    	imlec=6;
    	if(dos[line][imlec]=='-')
    	{	imlec=7;
    		sign=-1;
    	}
   		if(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   		{	temp=-1;
   		
   			while(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   			{	
		   		temp+=1;
   				imlec+=1;
   			}
   			imlec=imlec-temp-1;
			while(temp>=0)  
			{	
				cons=(cons+((dos[line][imlec]-'0')*sqrt(10,temp)));
			
				temp-=1;
				imlec+=1;
			}
			*first=cons*sign;
			
   			return 0;
   			
  	 	}
	   
	   
	   
	   	else if(dos[line][6]=='R' && dos[line][7]=='1')		/*THEN MOVE THE FÝRST REGÝSTER TO THE RÝGHT REGÝSTER*/
    		reg->r1=*first;
    		
    	else if(dos[line][6]=='R' && dos[line][7]=='2')
    		reg->r2=*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='3')
    		reg->r3=*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='4')
    		reg->r4=*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='5')
    		reg->r5=*first;		
   	
   	return 0;
}

int add(int line,reg_t *reg,string dos[])/*FOR ADDÝNG*/
{
	int imlec=0;
	int *first=0;
	int temp=0;
	int cons;	
		
   	if(dos[line][3]=='R' && dos[line][4]=='1')
   		first=&reg->r1;
  	else if(dos[line][3]=='R' && dos[line][4]=='2')
   		first=&reg->r2;
   	else if(dos[line][3]=='R' && dos[line][4]=='3')
   		first=&reg->r3;
   	else if(dos[line][3]=='R' && dos[line][4]=='4')
   		first=&reg->r4;
   	else if(dos[line][3]=='R' && dos[line][4]=='5')
   		first=&reg->r5;
    		
   
    	
    	
    	
   	imlec=6;
    	
   	if(dos[line][imlec]>='0' && dos[line][imlec]=='9')
   	{	temp=-1;
   	
   		while(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((dos[line][imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}
		*first=*first+cons;
			
   		return 0;
   			
 	}
	   
	   else if(dos[line][6]=='R' && dos[line][7]=='1')
    		reg->r1=reg->r1+*first;
    		
    	else if(dos[line][6]=='R' && dos[line][7]=='2')
    		reg->r2=reg->r2+*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='3')
    		reg->r3=reg->r3+*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='4')
    		reg->r4=reg->r4+*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='5')
    		reg->r5=reg->r5+*first;	
   	
   	
   	return 0;
}


int sub(int line,reg_t *reg,string dos[])
{	
	int imlec=0;
	int *first=0;
	int temp=0;
	int cons=0;	
		
   	if(dos[line][3]=='R' && dos[line][4]=='1')
   		first=&reg->r1;
  	else if(dos[line][3]=='R' && dos[line][4]=='2')
   		first=&reg->r2;
   	else if(dos[line][3]=='R' && dos[line][4]=='3')
   		first=&reg->r3;
   	else if(dos[line][3]=='R' && dos[line][4]=='4')
   		first=&reg->r4;
   	else if(dos[line][3]=='R' && dos[line][4]=='5')
   		first=&reg->r5;
    		
   
    	
    	
    	
   	imlec=6;
    	
   	if(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   	{	
	   	temp=-1;
   	
   		while(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((dos[line][imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}
		*first=*first-cons;
			
   		return 0;
   			
 	}
	   
	   else if(dos[line][6]=='R' && dos[line][7]=='1')
    		reg->r1=reg->r1-*first;
    		
    	else if(dos[line][6]=='R' && dos[line][7]=='2')
    		reg->r2=reg->r2-*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='3')
    		reg->r3=reg->r3-*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='4')
    		reg->r4=reg->r4-*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='5')
    		reg->r5=reg->r5-*first;	
   		
   	return 0;
}

int jump(int *line,reg_t *reg,string dos[])
{	int imlec=3;
	int *first=0;
	int temp=0;
	int cons=0;
		
	if(dos[*line][imlec]>='0' && dos[*line][imlec]<='9')
   	{	temp=-1;
   	
   		while(dos[*line][imlec]>='0' && dos[*line][imlec]<='9')
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((dos[*line][imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}
		*line=cons-2;
		
		return 0;	
	}
	
	
	
   	else if(dos[*line][3]=='R' && dos[*line][4]=='1')
   		first=&reg->r1;
  	else if(dos[*line][3]=='R' && dos[*line][4]=='2')
   		first=&reg->r2;
   	else if(dos[*line][3]=='R' && dos[*line][4]=='3')
   		first=&reg->r3;
   	else if(dos[*line][3]=='R' && dos[*line][4]=='4')
   		first=&reg->r4;
   	else if(dos[*line][3]=='R' && dos[*line][4]=='5')
   		first=&reg->r5;
   	
   	if(*first==0)
   		
   	{	imlec=6;
	   	temp=-1;
   	
   		while(dos[*line][imlec]>='0' && dos[*line][imlec]<='9')
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((dos[*line][imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}
		*line=cons-2;
		return 0;	
	}
   		
	return 0;
	
	
}

int print(int line,reg_t *reg,string dos[])
{	int imlec=3;
	int *first=0;
	int temp=0; 
	int cons=0;
	
	if(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   	{	temp=-1;
   	
   		while(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((dos[line][imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}
		cout<<cons<<endl;
		return 0;	
	}

	if(dos[line][3]=='R' && dos[line][4]=='1')
   		first=&reg->r1;
  	else if(dos[line][3]=='R' && dos[line][4]=='2')
   		first=&reg->r2;
   	else if(dos[line][3]=='R' && dos[line][4]=='3')
   		first=&reg->r3;
   	else if(dos[line][3]=='R' && dos[line][4]=='4')
   		first=&reg->r4;
   	else if(dos[line][3]=='R' && dos[line][4]=='5')
   		first=&reg->r5;
   	
	cout<<*first<<endl;
   	
	return 0;
   	
}


		
		
		
	

