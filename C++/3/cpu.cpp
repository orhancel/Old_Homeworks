#include <string>
#include <iostream>
#include <fstream>
#include "cpu.h"

CPU::CPU(int option){//CONTRUCTOR TO GET THE OPTION NUMBER FROM THE USER//
	int temp=0;
	setoption(option);
	sethalttru();//SET HALT BOOL TRUE//
	setlineNumber(0);//SET LINE NUMBER OF STRIN ARRAY//
	for(temp=0;temp<5;temp++)
		r[temp]=0;//ASSING A NUMBER TO REGISTER ARRAYS//

}

int CPU::getlineNumber(){//GET THE LINE NUMBER OF INSTRUCTION STRING ARRAY//
	return currLine;
}

void CPU::setlineNumber(int set){//SET THE LINE NUMBER OF INSTRUCTION STRING ARRAY
	
	currLine=set;

}

bool CPU::HLT(){//RETURN HALT CONDITION//
	return halt;
}

string CPU::Uppercase(string line,int size){//MAKES THE CHARS UPPER CASE//
	int imlec=0;
	for(imlec=0;imlec<size;++imlec)	/*Makes all the chracters in the file upper case*/
	{				
		for(i=0; line[i]!='\0' ;i++)
	 	{   if(line[i]<='z' && line[i]>='a')
		line[i]=line[i]-('a'-'A');
	  	}

		
	}
	return line;//RETURN THE CHANGED STRING//	
}
int CPU::execute(string line){//EXECUTE THE INSTRUCTION//
	int imlec=0;
	char yedek;
	int temp=0;

	if(checksyntax(line)==0){//CHECK FOR ERRORS//
		cout<<"at line number "<<getlineNumber()<<endl;
		sethaltfalse();//IF THERE IS AN ERROR,HALT THE PROGRAM//
	}
	
	for(imlec=0; line[imlec]!='\0' ;imlec++)//THiS LOOP REMOVES ALL OF THE WHITESPACES//
   	{	if(line[imlec]!=' ')
   		{	yedek=line[imlec];
	   		line[imlec]=' ';
	  		line[temp]=yedek;
	 		temp+=1;
		}
	}
	
	if(option=='1')/*DEPENDS OF THE ENTERED OPTION NUMBER,THIS LOOP PRINTS THE INSTRUCTIONS AND REGISTERS*/
	{	cout << line[0]<<line[1]<<line[2]<<' ';
		for(imlec=3;line[imlec]!='\0';imlec++)
		{	
			if(line[imlec]==';')
				break;
			else if(line[imlec]!=',')
				cout<<line[imlec];
			else if(line[imlec]==',')
				cout<<' '<<','<<' ';
		}
	cout<<" R1="<<r[0]<<" R2="<<r[1]<<" R3="<<r[2]<<" R4="<<r[3]<<" R5="<<r[4]<<endl;
	}
		
	
	if(line[0]=='M' && line[1]=='O' && line[2]=='V')/*WE CALL THESE FUNCTIONS ,ACCORDING TO OUR INSTRUCTIONS*/
   		move(line);
   	else if(line[0]=='A' && line[1]=='D' && line[2]=='D')
		add(line);
	else if(line[0]=='S' && line[1]=='U' && line[2]=='B')
		sub(line);
	else if(line[0]=='J' && line[1]=='M' && line[2]=='P')
		jump(getlineNumber(),line);
	else if(line[0]=='P' && line[1]=='R' && line[2]=='N')
		print(line);
	else if(line[0]=='H' && line[1]=='L' && line[2]=='T'){
		
		sethaltfalse();
		HLT();
	}
	setlineNumber(getlineNumber()+1);
	return 0;
}


int CPU::move(string line)
{	int imlec=0;
	int *first=0;
	int temp=0;
	int cons=0;
	int sign=1;/*FOR NEGATIVE NUMBERS*/
	
   
    	if(line[3]=='R' && line[4]=='1')
    		first=&r[0];		/*LOAD THE LEFT REGISTER TO A VARIABLE*/
    	else if(line[3]=='R' && line[4]=='2')
    		first=&r[1];
    	else if(line[3]=='R' && line[4]=='3')
    		first=&r[2];
    	else if(line[3]=='R' && line[4]=='4')
    		first=&r[3];
    	else if(line[3]=='R' && line[4]=='5')
    		first=&r[4];
    
			
				
    	imlec=6;
    	if(line[imlec]=='-')//IF THE NUMBER IS NEGATIVE
    	{	imlec=7;
    		sign=-1;
    	}
	if(line[imlec]>='0' && line[imlec]<='9')//STRING TO CONSTANT CONVERSION LOOP//
	{	temp=-1;
	
		while(line[imlec]>='0' && line[imlec]<='9')
		{	
	   		temp+=1;
			imlec+=1;
		}
		imlec=imlec-temp-1;
		while(temp>=0)  
		{	
			cons=(cons+((line[imlec]-'0')*sqrt(10,temp)));
		
			temp-=1;
			imlec+=1;
		}//END OF LOOP//
		*first=cons*sign;
		
		return 0;
		
 	}
	   
	   
	   
	else if(line[6]=='R' && line[7]=='1')/*MOVE THE FIRST REGISTER TO THE RIGHT REGISTER*/
    		r[0]=*first;
    		
    	else if(line[6]=='R' && line[7]=='2')
    		r[1]=*first;
    	else if(line[6]=='R' && line[7]=='3')
    		r[2]=*first;
    	else if(line[6]=='R' && line[7]=='4')
    		r[3]=*first;
    	else if(line[6]=='R' && line[7]=='5')
    		r[4]=*first;		
   	
   	return 0;
}


int CPU::add(string line)/*FOR ADDING*/
{
	int imlec=0;
	int *first=0;
	int temp=0;
	int cons;	
		
   	if(line[3]=='R' && line[4]=='1')
   		first=&r[0];
  	else if(line[3]=='R' && line[4]=='2')
   		first=&r[1];
   	else if(line[3]=='R' && line[4]=='3')
   		first=&r[2];
   	else if(line[3]=='R' && line[4]=='4')
   		first=&r[3];
   	else if(line[3]=='R' && line[4]=='5')
   		first=&r[4];
    		
   	imlec=6;//MOVE THE INDEX POINT//
    	//IF THE RIGHT SIDE IS CONSTANT//
   	if(line[imlec]>='0' && line[imlec]=='9')//STRING TO CONSTANT CONVERSION LOOP//
	{	temp=-1;

		while(line[imlec]>='0' && line[imlec]<='9')
		{	
	   		temp+=1;
			imlec+=1;
		}
		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((line[imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}
		*first=*first+cons;
		
		return 0;
   			
 	}
	//IF THE RIGHT SIDE IS REGISTER//
	else if(line[6]=='R' && line[7]=='1')
    		r[0]=r[0]+*first;
    		
    	else if(line[6]=='R' && line[7]=='2')
    		r[1]=r[1]+*first;
    	else if(line[6]=='R' && line[7]=='3')
    		r[2]=r[2]+*first;
    	else if(line[6]=='R' && line[7]=='4')
    		r[3]=r[3]+*first;
    	else if(line[6]=='R' && line[7]=='5')
    		r[4]=r[4]+*first;	
   	
   	
   	return 0;
}

int CPU::sub(string line)//SUBTRACTIN FUNCTION//
{	
	int imlec=0;
	int *first=0;
	int temp=0;
	int cons=0;	
		
   	if(line[3]=='R' && line[4]=='1')//FIND THE REGISTER ON THE LEFT SIDE//
   		first=&r[0];
  	else if(line[3]=='R' && line[4]=='2')
   		first=&r[1];
   	else if(line[3]=='R' && line[4]=='3')
   		first=&r[2];
   	else if(line[3]=='R' && line[4]=='4')
   		first=&r[3];
   	else if(line[3]=='R' && line[4]=='5')
   		first=&r[4];
    		
   
    	
    	
    	
   	imlec=6;//MOVE THE CURSOR.SINCE THERE IS NO WHITESPACE LEFT IN THE STRING,WE KNOW WHERE TO MOVE IT//
    	
   	if(line[imlec]>='0' && line[imlec]<='9')
   	{	
	   	temp=-1;
   	
   		while(line[imlec]>='0' && line[imlec]<='9')//CONSTANT NUMBER CONVERSİON LOOP// 
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((line[imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}//CONSTANT NUMBER CONVERSİON LOOP END// 
		*first=*first-cons;//SUBTRACTION OF THAT CONSTANT NUMBER//
			
   		return 0;
   			
 	}
	   
	else if(line[6]=='R' && line[7]=='1')//IF THE RIGHT SIDE IS NOT A CONSTANT,WE CHECK FOR REGISTERS//
    		r[0]=r[0]-*first;//AND DO THE SUBRACTION//
    		
    	else if(line[6]=='R' && line[7]=='2')
    		r[1]=r[1]-*first;
    	else if(line[6]=='R' && line[7]=='3')
    		r[2]=r[2]-*first;
    	else if(line[6]=='R' && line[7]=='4')
    		r[3]=r[3]-*first;
    	else if(line[6]=='R' && line[7]=='5')
    		r[4]=r[4]-*first;	
   		
   	return 0;
}

int CPU::jump(int satir,string line)//JUMP FUNCTION//
{	int imlec=3;//MOVE THE INDEX CURSOR.NO WHITESPACE LEFT IN THE STRING.WE KNOW WHERE TO MOVEIT//
	int *first=0;
	int temp=0;
	int cons=0;
		
	if(line[imlec]>='0' && line[imlec]<='9')//STRING TO CONSTANT NUMBER CONVERSİON LOOP//
   	{	temp=-1;
   	
   		while(line[imlec]>='0' && line[imlec]<='9')
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((line[imlec]-'0')*sqrt(10,temp));//SQRT IS MY FUNCTION//
			temp-=1;
			imlec+=1;
		}
		//LOOP ENDS//
		setlineNumber(cons-2);//-1 BECAUSE ARRAY[0] İS 1.ANOTHER -1 BECAUSE AFTER CALLING JUMP,LOOP IN THE MAIN WILL INCREMENT 1.WE NEED TO NEGATE IT//
		
		return 0;	
	}
	
	
	
   	else if(line[3]=='R' && line[4]=='1')//IF THERE IS NO CONSTANT AT INDEX 4,WE CHECK FOR REGISTERS//
   		first=&r[0];
  	else if(line[3]=='R' && line[4]=='2')
   		first=&r[1];
   	else if(line[3]=='R' && line[4]=='3')
   		first=&r[2];
   	else if(line[3]=='R' && line[4]=='4')
   		first=&r[3];
   	else if(line[3]=='R' && line[4]=='5')
   		first=&r[4];
   	
   	if(*first==0)//IF REGISTER IS 0,THEN JUMP//
   		
   	{	imlec=6;
	   	temp=-1;
   	
   		while(line[imlec]>='0' && line[imlec]<='9')//STRING TO CONSTANT CONVERSION LOOP//
   		{	
	   		temp+=1;
   			imlec+=1;
   		}
   		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((line[imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}//LOOP ENDS//
		setlineNumber(cons-2);
		return 0;	
	}
   		
	return 0;
	
	
}

int CPU::print(string line)//PRINT FUNCTION//
{	int imlec=3;//MOVE THE INDEX CURSOR.NO WHITESPACE LEFT IN THE STRING.WE KNOW WHERE TO MOVEIT//
	int *first=0;
	int temp=0; 
	int cons=0;

	if(line[imlec]>='0' && line[imlec]<='9')//STRING TO CONSTANT NUMBER CONVERSİON LOOP//
	{	temp=-1;

		while(line[imlec]>='0' && line[imlec]<='9')
		{	
	   		temp+=1;
			imlec+=1;
		}
		imlec=imlec-temp-1;
		while(temp>=0)  			
		{	
			cons=cons+((line[imlec]-'0')*sqrt(10,temp));
			temp-=1;
			imlec+=1;
		}
		//LOOP ENDS//
		cout<<cons<<endl;//PRINT THE CONSTANT NUMBER//
		return 0;	
	}

	if(line[3]=='R' && line[4]=='1')
		first=&r[0];
	else if(line[3]=='R' && line[4]=='2')
		first=&r[1];
	else if(line[3]=='R' && line[4]=='3')
		first=&r[2];
	else if(line[3]=='R' && line[4]=='4')
		first=&r[3];
	else if(line[3]=='R' && line[4]=='5')
		first=&r[4];

	cout<<*first<<endl;

	return 0;
   	
}


int CPU::checksyntax(string line)/*SYNTAX CHECKıNG FUNTÝON*/
{
    
    int temp=0;
    i=0;
	if(checkcommand(line)==1)/*Command types has different return values.add,sub,move has 1, jump has 2,halt has 3,print has 4*/
	{i=i+3;
		
		if(checkreg(line)==1)/*checks first THE REGÝSTERS.There has to be a register,not a constant OR ADDRESS*/
		{	
			if(checkcoma(line)==1)/*then coma the seperate them , ignores the spaces.*/
			{	temp=i;
				
				if(checkreg(line)==1)/*then another register.But this time it could be a constant*/
				{
					if(checkdotcoma(line)==1)/*if it's a register,then we look for semicolon*/
						return 1;
					else
					{	cout<<"Syntax Error1"<<endl;
						return 0;
					}
				}
			
				else if(checkcons(line)==2)	/*If we can't find a register,we look for a constant*/
				{
				  	if(checkdotcoma(line)==1)	/*	then we look for semicolon*/
						return 1;
					else
					{	cout<<"Syntax Error2"<<endl;
						return 0;
					}
				}
				setindex(temp);
				if(checkcons(line)==1)	/*This one is for NEGATIVE NUMBERS.FUNCTION RETURNS 1*/
				{	
					if(checkdotcoma(line)==1)//CHECK SEMICOLON//
						return 1;
					else
					{	cout<<"Syntax Error3"<<endl;/*ANYTHING OTHER THAN THAT IS A SYNTAX ERROR*/
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
	else if(checkcommand(line)==2)		/*THIS ONE IS FOR JUMP*/
	{	i=i+4;
		if(checkreg(line)==1)
		{	
			if(checkcoma(line)==1)
			{	
				if(checkreg(line)==1)
				{	if(checkdotcoma(line)==1)
						return 1;
					else
					{	cout<<"Syntax Error7"<<endl;
						return 0;
					}
				}
				if(checkcons(line)==2)
				{	if(checkdotcoma(line)==1)
						return 1;
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
		else if(checkcons(line)==2)
		{	
		  	if(checkdotcoma(line)==1)
				return 1;
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
	else if(checkcommand(line)==3)	/*THIS ONE IS FOR HALT*/
	{	i=i+4;
		if(checkdotcoma(line)==1)
				return 1;
		else
		{	cout<<"Syntax Error13"<<endl;
			return 0;
		}
	}
	else if(checkcommand(line)==4)	/*THIS ONE IS FOR PRINT.WE CAN PRINT NEGATIVE NUMBERS TOO*/
	{	i=i+4;
		if(checkreg(line)==1)
		{	if(checkdotcoma(line)==1)
				return 1;
			else
			{	cout<<"Syntax Error14"<<endl;
				return 0;
			}
		}
		else if(checkcons(line)==2)
		{	if(checkdotcoma(line)==1)
				return 1;
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
	
	else if(checkcommand(line)==5)/*EMTY LINE*/
	    return 1;
	else
	{	cout<<"Syntax Error29  "<<endl;
		return 0;
	}

return 1;

}


	
int CPU::checkcommand(string line)/*SYNTAX FUNCTION FOR CHECKING COMMAND TYPE.IMLEC IS THE INDEX NUMBER OF THAT LINE*/
{	int imlec=0;
	for(i=0;line[imlec]!='\0';i=i+1)
	{  
		if(line[imlec]==' ')
			continue;
		else if(line[imlec]<='Z' && line[imlec]>='A')
		{	if(line[imlec]=='M' && line[imlec+1]=='O' && line[imlec+2]=='V' && line[imlec+3]==' ')/*EVERY COMMAND TYPE HAS A DIFFERENT RETURN NUMBER*/
				return 1;
			else if(line[imlec]=='A' && line[imlec+1]=='D' && line[imlec+2]=='D' && line[imlec+3]==' ')
				return 1;
			else if(line[imlec]=='S' && line[i+1]=='U' && line[i+2]=='B' && line[i+3]==' ')
				return 1;
			else if(line[imlec]=='J' && line[imlec+1]=='M' && line[imlec+2]=='P' && line[imlec+3]==' ')
				return 2;
			else if(line[imlec]=='P' && line[imlec+1]=='R' && line[imlec+2]=='N' && line[imlec+3]==' ')
				return 4;
			else if(line[imlec]=='H' && line[imlec+1]=='L' && line[imlec+2]=='T' && line[imlec+3]==' ')
				return 3;
			else if(line[imlec]=='J' && line[imlec+1]=='P' && line[imlec+2]=='N' && line[imlec+3]==' ')
				return 2;
			else
			    return 0;
	    }
		
		
	}
	
	if(line[imlec]=='\0')/*FOR EMTY LINES*/
	{    
	    return 5;
	}
		
	
	return 0;
		
}

int CPU::checkreg(string line)/*SYNTAX FUNCTION TO CHECK REGISTERS*/
{	
	while(line[i]!='\0')/*WHILE IN LINE*/
	{	
		
		if(line[i]==' ')/*SKIP THE SPACES*/
			i+=1;/*UPDATE THE INDEX,IMLEC*/
		else if(line[i]=='R' && line[i+1]<='9' && line[i+1]>='0')/*CHECK FOR R AND A CONSTANT NUMBER*/
		{	
			i+=2;/*UPDATE THE INDEX,IMLEC*/
			return 1;/*RETURN 1 IF EVERYTHING IS FINE*/
		}
		else
		{	
			return 0;
		}
	}

	return 0;	
}

int CPU::checkcoma(string line)//*SYNTAX FUNCTION TO CHECK COMA*/
{   
	while(line[i]!='\0')
	{   
		if(line[i]==' ')/*WHILE IN LINE*/
			{
			    i+=1;/*UPDATE THE CURSOR,IMLEC*/
			}
		else if(line[i]==',' && line[i+1]==' ')/*FIND THE COMA*/
		{	
		    i=i+2;/*UPDATE THE CURSOR,IMLEC*/
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
	
}

int CPU::checkcons(string line)/*SYNTAX FUNCTION TO CHECK CONSTANT NUMBERS*/
{	
	while(line[i]!='\0')
	{	
		if(line[i]==' ')
			i+=1;/*UPDATE THE INDEX,IMLEC*/
		else if(line[i]=='-')/*FOR NEGATIVE ONES*/
		{	i+=1;/*UPDATE THE INDEX,IMLEC*/
			
			while(line[i]<='9' && line[i]>='0')
				{	
					if(line[i+1]==' ' || line[i+1]=='\0' || line[i+1]==';')
					{	i=i+1;/*UPDATE THE CURSOR,IMLEC*/
						return 1;//RETURN 1 FOR NEGATIVE NUMBERS//
					}
					else
						i+=1;/*UPDATE THE CURSOR,IMLEC*/
				}
			return 0;
		}
		else if(line[i]<='9' && line[i]>='0')	/*FOR POSITIVE ONES*/
		{	
			while(line[i]<='9' && line[i]>='0')
			{	
				if(line[i+1]==' ' || line[i+1]=='\0' || line[i+1]==';')
				{	
					i=i+1;/*UPDATE THE INDEX,IMLEC*/
					return 2;//RETURN 2 FOR POSITIVE NUMBERS//
				}
				else 
				{
					i+=1;/*UPDATE THE INDEX,IMLEC*/
				}
			}
		}
		else
		{	
			return 0;//RETURN 0 FOR ERRORS//
		}
				
	}

	return 0;
	
}
int CPU::checkdotcoma(string line)/*SYNTAX FUNCTION TO CHECK SEMICOLON*/
{	while(line[i]!='\0')
	{	
	    if(line[i]==' ')
			i+=1;/*UPDATE THE INDEX,IMLEC*/
		else if(line[i]==';')
			return 1;
		else
		{
			return 0;
		}
	}
	
	return 1;
}	
int CPU::sqrt(int x,int y)/*POWER FUNCTION*/
{	int temp=1,sayac=0;

	for(sayac=0;sayac<y;sayac++)
	{	temp=x*temp;
	}
	return temp;
	
}
