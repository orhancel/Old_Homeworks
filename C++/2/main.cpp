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
int move(int line,reg_t *reg,string dos[],unsigned int memory[]);
int add(int line,reg_t *reg,string dos[],unsigned int memory[]);
int sub(int line,reg_t *reg,string dos[],unsigned int memory[]);
int jump(int *line,reg_t *reg,string dos[]);
int print(int line,reg_t *reg,string dos[]); 	
int checkcommand(string line,int *i);
int checkreg(string line,int *i);
int checkcoma(string line,int *i);
int checkcons(string line,int *i);
int checkdotcoma(string line,int *i);
int checksyntax(string dos[]);
int checkhash(string line,int *i);
int jpn(int *line,reg_t *reg,string dos[]);
	
int main(int argc, char** argv) {
    string x;				/*A temporary string to use through out the code*/
    
    char yedek;					/*A temporary char to use through out the code**/
    string dos[201];		/*An array of strings to put all the lines in the file so we can jump between lines*/
    int imlec=0,temp=0,line=0,i=0;
    unsigned int memory[50];
    reg_t reg;		/*Struct of registers*/
    ifstream dosya;
    dosya.open(argv[1]);
    reg.r1=0;
    reg.r2=0;
    reg.r3=0;
    reg.r4=0;
    reg.r5=0;
    for(line=0;line<50;line++)/*INIT�AL�ZE MEMORY ARRAY*/
        memory[line]=0;
    
    for(line=0;line<200;++line)				/*Makes all the chracters in the file upper case*/
	{	getline(dosya,x);			/*First get the string from the file*/
   		for(i=0; x[i]!='\0' ;i++)
   	 	{   if(x[i]<='z' && x[i]>='a')
   	        x[i]=x[i]-('a'-'A');
	  	}

		dos[line]=x;			/*And we put them in the string array*/
	}
	
	if(checksyntax(dos)==0)/*SYNTAX CHECK�NG FUNT�ON*/
	    return 0;

    temp=0;
    for(line=0;line<256;++line)	/*TH�S LOOPS REMOVES ALL OF THE WH�TESPACES*/
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
		if(*argv[2]=='1' || *argv[2]=='2')/*TH�S LOOP ALLOWS US THE SEE THE �NSTRUCT�ONS*/
    	{	cout << dos[line][0]<<dos[line][1]<<dos[line][2]<<' ';
			for(imlec=3;dos[line][imlec]!='\0';imlec++)
			{	
				if(dos[line][imlec]==';')
					break;
				else if(dos[line][imlec]!=',')
					cout<<dos[line][imlec];
				else if(dos[line][imlec]==',')
					cout<<' '<<','<<' ';
			}
		    
		    
    	}	
		
    	if(dos[line][0]=='H' && dos[line][1]=='L' && dos[line][2]=='T')/*WE CALL THE FUNCT�ONS ,ACCORD�NG TO OUR �NSTRUCT�ONS*/
			return 0;
		else if(dos[line][0]=='M' && dos[line][1]=='O' && dos[line][2]=='V')
    		move(line,&reg,dos,memory);
    	else if(dos[line][0]=='A' && dos[line][1]=='D' && dos[line][2]=='D')
			add(line,&reg,dos,memory);
		else if(dos[line][0]=='S' && dos[line][1]=='U' && dos[line][2]=='B')
			sub(line,&reg,dos,memory);
		else if(dos[line][0]=='J' && dos[line][1]=='M' && dos[line][2]=='P')
			jump(&line,&reg,dos);
		else if(dos[line][0]=='P' && dos[line][1]=='R' && dos[line][2]=='N')
			print(line,&reg,dos);
		
		else if(dos[line][0]=='J' && dos[line][1]=='P' && dos[line][2]=='N')
			jpn(&line,&reg,dos);
		if(*argv[2]=='1')/*Option 1 means we can see registers*/
		{
		    cout<<" R1="<<reg.r1<<" R2="<<reg.r2<<" R3="<<reg.r3<<" R4="<<reg.r4<<" R5="<<reg.r5<<endl;
		}
    	else if(*argv[2]=='2')/*Option 2 means we can see registers*/
    	{	
		    cout<<" memory1="<<memory[0]<<" memory2="<<memory[1]<<" memory3="<<memory[2]<<" memory4="<<memory[3]<<" memory5="<<memory[4]<<
		    " memory6="<<memory[5]<<" memory7="<<memory[6]<<" memory8="<<memory[7]<<" memory9="<<memory[8]<<" memory10="<<memory[9]<<endl;
    	}	
    
	}
    	return 0;
}
	
int checksyntax(string dos[])/*SYNTAX CHECK�NG FUNT�ON*/
{
    string x;
    int temp=0;
    int imlec=0;
    int line=0;

    for(line=0;line<200;line++)/*WE GO THROUGH THE L�NES �N THE ARRAY*/
	{	x=dos[line];/*X �S JUST A SUB FOR DOS[L�NE] .IT'S WAS EASY TO TYPE*/
		imlec=0;
		
		if(checkcommand(x,&imlec)==1)		/*Command types has different return values.add,sub has 1, jump has 2,halt has 3,print has 4,MOVE HAS 6*/
		{	imlec=imlec+3;
			
			if(checkreg(x,&imlec)==1)		/*checks first THE REG�STERS.There has to be a register,not a constant OR ADDRESS*/
			{	
				if(checkcoma(x,&imlec)==1)	/*then coma the seperate them,ignores the spaces.*/
				{	temp=imlec;
					
					if(checkreg(x,&imlec)==1)		/*then another register.But this time it could be a constant*/
					{
						if(checkdotcoma(x,&imlec)==1)/*if it's a register,then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error1"<<endl;
							return 0;
						}
					}
				
					else if(checkcons(x,&imlec)==2)	/*If we can't find a register,we look for a constant*/
  					{
					  	if(checkdotcoma(x,&imlec)==1)	/*	then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error2"<<endl;
							return 0;
						}
					}
					else if(checkcons(x,&temp)==1)	/*This one is for NEGAT�VE NUMBERS.FUNCT�ON RETURNS 1*/
					{	
						if(checkdotcoma(x,&temp)==1)
							continue;
						else
						{	cout<<"Syntax Error3"<<endl;/*ANYTH�NG OTHER THAN THAT �S A SYNTAX ERROR*/
							return 0;
						}
					}
					else
					{	cout<<"Syntax Error4"<<endl;
							return 0;
						}
				}
				else
				{	cout<<"Syntax Error5"<<endl;
							return 0;
						}
			}
			else
			{	cout<<"Syntax Error6"<<endl;
							return 0;
						}
		}
		else if(checkcommand(x,&imlec)==2)		/*TH�S ONE �S FOR JUMP AND JPN*/
		{	imlec=imlec+4;
			if(checkreg(x,&imlec)==1)
			{	
				if(checkcoma(x,&imlec)==1)
				{	
					if(checkreg(x,&imlec)==1)
					{	if(checkdotcoma(x,&imlec)==1)
							continue;
						else
						{	cout<<"Syntax Error7"<<endl;
							return 0;
						}
					}
					if(checkcons(x,&imlec)==2)
  					{	if(checkdotcoma(x,&imlec)==1)
							continue;
						else
						{	cout<<"Syntax Error8"<<endl;
							return 0;
						}
					}
					else
					{	cout<<"Syntax Error9"<<endl;
							return 0;
						}
				}
				else
				{	cout<<"Syntax Error10"<<endl;
							return 0;
						}
			}
			else if(checkcons(x,&imlec)==2)
  			{	
			  	if(checkdotcoma(x,&imlec)==1)
					continue;
				else
				{	cout<<"Syntax Error11"<<endl;
						return 0;
				}
			}
			else
			{	cout<<"Syntax Error12"<<endl;
				return 0;
			}
		}
		else if(checkcommand(x,&imlec)==3)	/*TH�S ONE �S FOR HALT*/
		{	imlec=imlec+4;
			if(checkdotcoma(x,&imlec)==1)
					continue;
			else
			{	cout<<"Syntax Error13"<<endl;
				return 0;
			}
		}
		else if(checkcommand(x,&imlec)==4)	/*TH�S ONE �S FOR PR�NT.WE CAN PR�NT NEGAT�VE NUMBERS TOO*/
		{	imlec=imlec+4;
			if(checkreg(x,&imlec)==1)
			{	if(checkdotcoma(x,&imlec)==1)
					continue;
				else
				{	cout<<"Syntax Error14"<<endl;
					return 0;
				}
			}
			else if(checkcons(x,&imlec)==2)
			{	if(checkdotcoma(x,&imlec)==1)
					continue;
				else
				{	cout<<"Syntax Error15"<<endl;
					return 0;
				}
			}
			
			else
			{	cout<<"Syntax Error16"<<endl;
				return 0;
			}
		}
		
		else if(checkcommand(x,&imlec)==6)/*TH�S ONR �S FOR MOVE*/
		{   imlec=imlec+3;
			
			if(checkreg(x,&imlec)==1)		/*checks first THE register.*/
			{	
				if(checkcoma(x,&imlec)==1)	/*then coma the seperate them,ignores the spaces.*/
				{	temp=imlec;
					
					if(checkreg(x,&imlec)==1)		/*then another register.But this time it could be a constant*/
					{
						if(checkdotcoma(x,&imlec)==1)/*if it's a register,then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error17"<<endl;
							return 0;
						}
					}
				
					else if(checkcons(x,&imlec)==2)	/*If we can't find a register,we look for a constant*/
  					{
					  	if(checkdotcoma(x,&imlec)==1)	/*	then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error18"<<endl;
							return 0;
						}
					}
					else if(checkcons(x,&temp)==1)	/*This one is for NEGAT�VE NUMBERS.FUNCT�ON RETURNS 1*/
					{	
						if(checkdotcoma(x,&temp)==1)
							continue;
						else
						{	cout<<"Syntax Error19"<<endl;
							return 0;
						}
					}
					else if(checkhash(x,&imlec)==1)/*OR WE CHECK FOR ADRESS*/
					{	
						if(checkdotcoma(x,&imlec)==1)
							continue;
						else
						{	cout<<"Syntax Error20"<<endl;
							return 0;
						}
					}
					else
					{	cout<<"Syntax Error21"<<endl;
							return 0;
					}
				}
				else
				{	cout<<"Syntax Error22"<<endl;
							return 0;
				}
			}
			else if(checkhash(x,&imlec)==1)/*F�RST ONE CAN BE AN ADDRESS TOO FOR MOVE �NSTRUCT�ON*/
			{   
			    if(checkcoma(x,&imlec)==1)	/*then coma the seperate them,ignores the spaces.*/
				{	temp=imlec;
					
					if(checkreg(x,&imlec)==1)		/*then another register.*/
					{
						if(checkdotcoma(x,&imlec)==1)/*if it's a register,then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error23"<<endl;
							return 0;
						}
					}
				
					else if(checkcons(x,&imlec)==2)	/*If we can't find a register,we look for a constant*/
  					{
					  	if(checkdotcoma(x,&imlec)==1)	/*	then we look for semicolon*/
							continue;
						else
						{	cout<<"Syntax Error24"<<endl;
							return 0;
						}
					}
					else if(checkcons(x,&temp)==1)	/*This one is for NEGAT�VE NUMBERS.FUNCT�ON RETURNS 1*/
					{	
						if(checkdotcoma(x,&temp)==1)
							continue;
						else
						{	cout<<"Syntax Error25"<<endl;
							return 0;
						}
					}
					else
					{	cout<<"Syntax Error26"<<endl;
							return 0;
					}
					
				}
				else
				{	cout<<"Syntax Error27"<<endl;
							return 0;
				}
			
		    }
		    else
				{	cout<<"Syntax Error28"<<endl;
							return 0;
				}
		}
		else if(checkcommand(x,&imlec)==5)/*EMTY L�NE*/
		    continue;
		else if(line==199)/*END OF THE F�LE*/
		    return 1;
		else
		{	cout<<"Syntax Error29  "<<endl;
			return 0;
		}
			
	}

	return 1;
    
}

int checkhash(string line,int *i)/*CHECKS SYNTAX FOR ADDRESS*/
{
    while(line[*i]!='\0')/*WH�LE �N THE L�NE*/
	{
	    if(line[*i]==' ')/*� STANDS FOR �MLEC*//*IF WE F�ND A SPACE,WE JUST SK�P �T*/
			*i+=1;/*UPDATE THE CURSOR,IMLEC*/
		else if(line[*i]=='#')/*IF WE F�ND HASH WE START ANOTHER ALGOR�THM*/
		{   *i+=1;/*UPDATE THE CURSOR,IMLEC*/
		    while(line[*i]<='9' && line[*i]>='0')/*WE LOOK AT THE CONSTANTS AFTER THE HASH*/
				{	
					if(line[*i+1]==' ' || line[*i+1]==',')/*IF EVERYTH�NG �S F�NE,WE RETURN 1*/
					{	*i+=1;/*UPDATE THE CURSOR,IMLEC*/
						return 1;
					}
					else
						*i+=1;/*UPDATE THE CURSOR,IMLEC*/
				}
			return 0;
		}
	}

}
int checkcommand(string line,int *i)/*SYNTAX FUNCT�ONFOR CHECK�NG COMMAND TYPE.I �S THE CURSOR NUMBER OF THAT L�NE*/
{	*i=0;
	for(*i=0;line[*i]!='\0';*i=*i+1)
	{  
		if(line[*i]==' ')
			continue;
		else if(line[*i]<='Z' && line[*i]>='A')
		{	if(line[*i]=='M' && line[*i+1]=='O' && line[*i+2]=='V' && line[*i+3]==' ')/*EVERY COMMAND TYPE HAS A D�FFERENT RETURN NUMBER*/
				return 6;
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
			else if(line[*i]=='J' && line[*i+1]=='P' && line[*i+2]=='N' && line[*i+3]==' ')
				return 2;
			else
			    return 0;
	    }
		
		
	}
	
	if(line[*i]=='\0')/*FOR EMTY L�NES*/
	{    
	    return 5;
	}
		
	
	return 0;
		
}

int checkreg(string line,int *i)/*SYNTAX FUNCT�ON TO CHECK REG�STERS*/
{	
	while(line[*i]!='\0')/*WH�LE �N L�NE*/
	{
		
		if(line[*i]==' ')/*SK�P THE SPACES*/
			*i+=1;/*UPDATE THE CURSOR,IMLEC*/
		else if(line[*i]=='R' && line[*i+1]<='9' && line[*i+1]>='0')/*CHECK FOR R AND A CONSTANT NUMBER*/
		{	*i+=2;/*UPDATE THE CURSOR,IMLEC*/
			return 1;/*RETURN 1 �F EVERYTH�NG �S F�NE*/
		}
		else
		{	
			return 0;
		}
	}

	return 0;	
}
int checkcoma(string line,int *i)//*SYNTAX FUNCT�ON TO CHECK COMA*/
{   
	while(line[*i]!='\0')
	{   
		if(line[*i]==' ')/*WH�LE �N L�NE*/
			{
			    *i+=1;/*UPDATE THE CURSOR,IMLEC*/
			}
		else if(line[*i]==',' && line[*i+1]==' ')/*F�ND THE COMA*/
		{	
		    *i=*i+2;/*UPDATE THE CURSOR,IMLEC*/
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
	
}
int checkcons(string line,int *i)/*SYNTAX FUNCT�ON TO CHECK CONSTANT NUMBERS*/
{	
	while(line[*i]!='\0')
	{	
		if(line[*i]==' ')
			*i+=1;/*UPDATE THE CURSOR,IMLEC*/
		else if(line[*i]=='-')/*FOR NEGAT�VE ONES*/
		{	*i+=1;/*UPDATE THE CURSOR,IMLEC*/
			
			while(line[*i]<='9' && line[*i]>='0')
				{	
					if(line[*i+1]==' ' || line[*i+1]=='\0' || line[*i+1]==';')
					{	*i=*i+1;/*UPDATE THE CURSOR,IMLEC*/
						return 1;
					}
					else
						*i+=1;/*UPDATE THE CURSOR,IMLEC*/
				}
			return 0;
		}
		else if(line[*i]<='9' && line[*i]>='0')	/*FOR POS�T�VE ONES*/
		{	
			while(line[*i]<='9' && line[*i]>='0')
			{	
				if(line[*i+1]==' ' || line[*i+1]=='\0' || line[*i+1]==';')
				{	
					*i=*i+1;/*UPDATE THE CURSOR,IMLEC*/
					return 2;
				}
				else 
				{
					*i+=1;/*UPDATE THE CURSOR,IMLEC*/
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
int checkdotcoma(string line,int *i)/*SYNTAX FUNCT�ON TO CHECK SEM�COLON*/
{	while(line[*i]!='\0')
	{	
	    if(line[*i]==' ')
			*i+=1;/*UPDATE THE CURSOR,IMLEC*/
		else if(line[*i]==';')
			return 1;
		else
		{
			return 0;
		}
	}
	
	return 1;
}	

int sqrt(int x,int y)/*POWER FUNCT�ON*/
{	int temp=1,i=0;

	for(i=0;i<y;i++)
	{	temp=x*temp;
	}
	return temp;
	
}

int move(int line,reg_t *reg,string dos[],unsigned int memory[])
{	int imlec=0;
	int *first=0;
	int temp=0;
	int cons=0,conshash=0;
	int sign=1;/*FOR NEGAT�VE NUMBERS*/
	    
   
    	if(dos[line][3]=='R' && dos[line][4]=='1')
    	{	first=&reg->r1;/*F�RST �S OUR POINTER*//*WE LOAD THE REG�STER ADRESS TO A PO�NTER*/
    		imlec=6;/*UPDATE THE CURSOR,IMLEC*/	}		/*LOAD THE F�RST REG�STER TO A VAR�ABLE*/
    	else if(dos[line][3]=='R' && dos[line][4]=='2')/*THE ONE AT THE LEFT OF THE COMA*/
    	{   first=&reg->r2;
    		imlec=6;}/*UPDATE THE CURSOR,IMLEC*/
    	else if(dos[line][3]=='R' && dos[line][4]=='3')
    	{	first=&reg->r3;
    		imlec=6;}/*UPDATE THE CURSOR,IMLEC*/
    	else if(dos[line][3]=='R' && dos[line][4]=='4')
    	{	first=&reg->r4;
    		imlec=6;}/*UPDATE THE CURSOR,IMLEC*/
    	else if(dos[line][3]=='R' && dos[line][4]=='5')
    	{	first=&reg->r5;
    		imlec=6;}/*UPDATE THE CURSOR,IMLEC*/
    	else if(dos[line][3]=='#')/*OR F�RST ONE COULD BE AN ADDRESS*/
    	{   temp=-1;
   		    imlec=4;
   		    
   			while(dos[line][imlec]>='0' && dos[line][imlec]<='9')/*F�ND THE CONSTANT ARRAY NUMBER OF THAT MEMORY*/
   			{	
		   		temp+=1;  /*GO THOROUGH THE NUMBERS*/
   				imlec+=1;
   			}
   			
   			imlec=imlec-temp-1;/*THEN GO BACK TO THE BEG�NN�NG OF THE CONSTANT*/
   			
			while(temp>=0)  /*THEN GO THROUGH THE NUMBER AGA�N BUT MULT�PLY THEM W�TH THE�R POWERS*/
			{	
				conshash=(conshash+((dos[line][imlec]-'0')*sqrt(10,temp)));/*SQRT �S MY POWER FUNCT�ON.I WROTE �T*/
			    
				temp-=1;
				imlec+=1;
			}
			imlec+=1;
			conshash-=1;/*MEMORY 1 �S MEMORY[0].SO WE SUBTRACT 1*/
			
			if(dos[line][imlec]=='R' && dos[line][imlec+1]=='1')		/*THEN MOVE THE F�RST REG�STER OR ADRESS TO THE R�GHT REG�STER*/
    		{    
    		    reg->r1=memory[conshash];
    		    return 0;
    		}
        	else if(dos[line][imlec]=='R' && dos[line][imlec+1]=='2')
        	{	reg->r2=memory[conshash];
        		return 0;}
        	else if(dos[line][imlec]=='R' && dos[line][imlec+1]=='3')
        	{	reg->r3=memory[conshash];
        		return 0;}
        	else if(dos[line][imlec]=='R' && dos[line][imlec+1]=='4')
        	{	reg->r4=memory[conshash];
        		return 0;}
        	else if(dos[line][imlec]=='R' && dos[line][imlec+1]=='5')
        	{	reg->r5=memory[conshash];
        		return 0;}
        	
        	if(dos[line][imlec]=='-')/*FOR NEGAT�VE NUMBERS*/
        	{	imlec+=1;
        		sign=-1;/*�F S�GN CHANGES SO DOES CONSTANT*/
        	}
       		if(dos[line][imlec]>='0' && dos[line][imlec]<='9')
       		{	temp=-1;
       		
       			while(dos[line][imlec]>='0' && dos[line][imlec]<='9')/*CHAR �NT TRANFORM LOOP START*/
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
			    memory[conshash]=cons;/*CHAR �NT TRANFORM LOOP ENDS*//*AND WE ADD CONSTANT NUMBER TO MEMORY ARRAY*/
            	return 0;
		    }
    
    
        }/*END OF ADRESS MOVE ALGOR�THM*//*IF THE F�RST ONE �S ADRESS L�KE (MOVE #1,40)*/
    
    	if(dos[line][imlec]=='-')
    	{	imlec+=1;
    		sign=-1;
    	}
   		if(dos[line][imlec]>='0' && dos[line][imlec]<='9')/*CONSTANT NUMBER MOVE ALGOR�THM START*/
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
			*first=cons*sign;/*CONSTANT NUMBER MOVE ALGOR�THM END*/
			
   			return 0;
   			
  	 	}
	   
	   
	   
	   	else if(dos[line][6]=='R' && dos[line][7]=='1')		/*MOVE THE F�RST REG�STER TO THE R�GHT REG�STER*/
    		reg->r1=*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='2') /*EXAMPLE(MOVE R1,R2)*/
    		reg->r2=*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='3')
    		reg->r3=*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='4')
    		reg->r4=*first;
    	else if(dos[line][6]=='R' && dos[line][7]=='5')
    		reg->r5=*first;		
   	    else if(dos[line][imlec]=='#')/*ADRESS CONVERS�ON ALGOR�THM*/
    	{   temp=-1;
   		    imlec+=1;
   			while(dos[line][imlec]>='0' && dos[line][imlec]<='9')
   			{	
		   		temp+=1;
   				imlec+=1;
   			}
   			
   			imlec=imlec-temp-1;
			while(temp>=0)  
			{	
				conshash=(conshash+((dos[line][imlec]-'0')*sqrt(10,temp)));
			
				temp-=1;
				imlec+=1;
			}
			conshash-=1;
			imlec+=1;
			memory[conshash]=*first;
		}
   	return 0;
}

int add(int line,reg_t *reg,string dos[],unsigned int memory[])/*FOR ADD�NG*/
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
   	
   		while(dos[line][imlec]>='0' && dos[line][imlec]<='9')/*STR�NG TO �NTEGER CONVERS�ON*/
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
   	    else if(dos[line][imlec]=='#')/*MEMORY ADRESS CHECK*/
    	{    temp=-1;
   		    imlec+=1;
   			while(dos[line][imlec]>='0' && dos[line][imlec]<='9')/*STR�NG TO �NTEGER CONVERS�ON*/
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
			imlec+=1;
			*first=*first+memory[cons];
		}
   	
   	return 0;
}


int sub(int line,reg_t *reg,string dos[],unsigned int memory[])/*FOR SUBTRACT�NG �NSTRUCT�ON*/
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
   	
   		while(dos[line][imlec]>='0' && dos[line][imlec]<='9')/*STR�NG TO �NTEGER CONVERS�ON*/
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
    		*first=*first-reg->r1;
    		
    	else if(dos[line][6]=='R' && dos[line][7]=='2')
    		*first=*first-reg->r2;
    	else if(dos[line][6]=='R' && dos[line][7]=='3')
    		*first=*first-reg->r3;
    	else if(dos[line][6]=='R' && dos[line][7]=='4')
    		*first=*first-reg->r4;
    	else if(dos[line][6]=='R' && dos[line][7]=='5')
    		*first=*first-reg->r5;
    	else if(dos[line][imlec]=='#')
    	{    temp=-1;
   		    imlec+=1;
   			while(dos[line][imlec]>='0' && dos[line][imlec]<='9')/*STR�NG TO �NTEGER CONVERS�ON*/
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
			imlec+=1;
			*first=*first+memory[cons];
		}	
   		
   	return 0;
}

int jump(int *line,reg_t *reg,string dos[])/*FOR JUMP �NSTRUCT�ON*/
{	int imlec=3;
	int *first=0;
	int temp=0;
	int cons=0;
		
	if(dos[*line][imlec]>='0' && dos[*line][imlec]<='9')
   	{	temp=-1;
   	
   		while(dos[*line][imlec]>='0' && dos[*line][imlec]<='9')/*STR�NG TO �NTEGER CONVERS�ON*/
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

int print(int line,reg_t *reg,string dos[])/*FOR PR�NT �NSTRUCT�ON*/
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
   	
	cout<<"   "<<*first<<endl;
   	
	return 0;
   	
}

int jpn(int *line,reg_t *reg,string dos[])/*FOR THE SECOND JUMP �NSTRUCT�ON*/
{	int imlec=3;
	int *first=0;
	int temp=0;
	int cons=0;

   	if(dos[*line][3]=='R' && dos[*line][4]=='1')
   		first=&reg->r1;
  	else if(dos[*line][3]=='R' && dos[*line][4]=='2')
   		first=&reg->r2;
   	else if(dos[*line][3]=='R' && dos[*line][4]=='3')
   		first=&reg->r3;
   	else if(dos[*line][3]=='R' && dos[*line][4]=='4')
   		first=&reg->r4;
   	else if(dos[*line][3]=='R' && dos[*line][4]=='5')
   		first=&reg->r5;
   	
   	if(*first<=0)
   		
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
		
		*line=cons-2;/*-1 BECAUSE  MEMORY[0] MEANS MEMORY 1,OTHER -1 �S FOR THE LOOP AT THE MA�N FUNCT�ON*/
		            /*AFTER DO�NG THE JPN �NSTRUCT�ON ,LOOP HAS TO �NCREASE THE L�NE 1 MORE T�ME.WE HAVE TO NEGATE THAT �NCREASE.*/
		return 0;	
	}
   	return 0;	
}

	
		
		
	

