/*
 * main.cpp
 *
 *  Created on: 27-Sep-2011
 *      Author:		Omar Asif Shaikh
 *      			
 */

/***********************************************************************************************************************************


keywords: prefix 'F'-FCFS	'S'-SJF		'P'-Priority	'R'-Round Robin

************************************************************************************************************************************/
#include<iostream>
//#include"process.h"
#include<GL/glut.h>
using namespace std;

GLfloat colors[][3]={{1.0,0.0,0.0}//red
,{1.0,1.0,0.0}//yellow
,{0.0,1.0,0.0}//green
,{0.0,0.0,1.0}//blue
,{1.0,0.0,1.0}//Purple
,{0.0,1.0,1.0}//Cyan
,{0.0,0.0,0.0}//Black
,{1.0,1.0,1.0}//White
};


int Num_Processes,Bsum=0,Fdp[500],Sdp[500],Pdp[500],Rdp[500];				//Bsum- sum of all process.burst....    <<< Dp for opengl renderer
int pr=0,a=0;							//used as flags in input()for arrival time and priority;



class process
{
public:
//int Pnum;
int ArrivalTime,BurstTime,Priority;
int WaitingTime,TurnAroundTime;
int Fstart,Fend;						//For FCFS
int RemBurstTime;
int FWaitingTime,FTurnAroundTime;
int SWaitingTime,STurnAroundTime;
int PWaitingTime,PTurnAroundTime;
int RWaitingTime,RTurnAroundTime;

process()							//Default constructor
{
	ArrivalTime=BurstTime=Priority=0;
	WaitingTime=0;
	Fstart=Fend=0;
	FWaitingTime=FTurnAroundTime=0;
	SWaitingTime=STurnAroundTime=0;
	PWaitingTime=PTurnAroundTime=0;
	RWaitingTime=RTurnAroundTime=0;
}

};



//process *p;
process P[30];

void input()
{


	cout<<"\nIf specifying Arrival time, enter '1' else '0' :";
	cin>>a;
	cout<<"\nIf specifying priority, enter '1' else '0' :";
	cin>>pr;

	for(int i=0;i<Num_Processes;i++)
	{
		cout<<"\n\nEnter the details of process "<<i+1<<":\n";
		cout<<"Burst time:";
		cin>>P[i].BurstTime;
		P[i].RemBurstTime=P[i].BurstTime;
		if(a)
		{
		cout<<"Arrival Time:";
		cin>>P[i].ArrivalTime;
		}
		if(pr)
		{
		cout<<"Priority:";
		cin>>P[i].Priority;
		}

	}
	cout<<"\nProcess    \tBurst time\tArrival Time\tPriority";
	for(int i=0;i<Num_Processes;i++)
	{
		Bsum+=P[i].BurstTime;
		cout<<"\n"<<i+1<<"\t\t"<<P[i].BurstTime<<"\t\t"<<P[i].ArrivalTime<<"\t\t"<<P[i].Priority;
	}
	cout<<endl;

}
void init()
{
	for(int i=0;i<Num_Processes;i++)
	{
		P[i].RemBurstTime=P[i].BurstTime;
	}
}

void WaitCal()
{
	int b=0,index;
	init();					//FCFS
	while(b<Bsum)
	{
		index=Fdp[b];
		for(int i=0;i<Num_Processes;i++)
		{
			if(i!=index&&P[i].RemBurstTime>0&&P[i].ArrivalTime<=b)
				P[i].FWaitingTime++;

		}
		P[index].RemBurstTime--;
		b++;


	}

	b=0;
	init();						//SJF
	while(b<Bsum)
		{
			index=Sdp[b];
			for(int i=0;i<Num_Processes;i++)
			{
				if(i!=index&&P[i].RemBurstTime>0&&P[i].ArrivalTime<=b)
					P[i].SWaitingTime++;

			}
			P[index].RemBurstTime--;
			b++;


		}

	b=0;
	init();						//Priority
	while(b<Bsum)
		{
			index=Pdp[b];
			for(int i=0;i<Num_Processes;i++)
			{
				if(i!=index&&P[i].RemBurstTime>0&&P[i].ArrivalTime<=b)
					P[i].PWaitingTime++;

			}
			P[index].RemBurstTime--;
			b++;


		}

	b=0;
	init();						//Round-Robin
	while(b<Bsum)
		{
			index=Rdp[b];
			for(int i=0;i<Num_Processes;i++)
			{
				if(i!=index&&P[i].RemBurstTime>0&&P[i].ArrivalTime<=b)
					P[i].RWaitingTime++;

			}
			P[index].RemBurstTime--;
			b++;


		}
	for(int i=0;i<Num_Processes;i++)
	{
		P[i].FTurnAroundTime=P[i].FWaitingTime+P[i].BurstTime;
		P[i].STurnAroundTime=P[i].SWaitingTime+P[i].BurstTime;
		P[i].PTurnAroundTime=P[i].PWaitingTime+P[i].BurstTime;
		P[i].RTurnAroundTime=P[i].RWaitingTime+P[i].BurstTime;
	}
	//////BOTH WORKING FOR SINGLE ARRAY[Pdp]
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat BlockSize,x,y,FPx,FPy,SPx,SPy,PPx,PPy,RPx,RPy,Gridx,Gridy;
	GLint b=0,index;

	BlockSize=300/Bsum;
	FPy=100;	FPx=100;
	SPy=200;	SPx=100;
	PPy=300;	PPx=100;
	RPy=400;	RPx=100;


	//Opengl FCFS
			x=FPx;
			y=FPy;
			b=0;
		while(b<Bsum)
		{
			index=Fdp[b];
			glColor3fv(colors[index]);
			glBegin(GL_QUADS);
			glVertex2f(x,y);
			glVertex2f(x+BlockSize,y);
			glVertex2f(x+BlockSize,y+10);
			glVertex2f(x,y+10);
			glEnd();
			b++;
			x=x+BlockSize;
		}
	//Opengl SJF
			x=SPx;
			y=SPy;
			b=0;
		while(b<Bsum)
		{
			index=Sdp[b];
			glColor3fv(colors[index]);
			glBegin(GL_QUADS);
			glVertex2f(x,y);
			glVertex2f(x+BlockSize,y);
			glVertex2f(x+BlockSize,y+10);
			glVertex2f(x,y+10);
			glEnd();
			b++;
			x=x+BlockSize;
		}
	//Opengl Priority
			x=PPx;
			y=PPy;
			b=0;
		while(b<Bsum)
		{
			index=Pdp[b];
			glColor3fv(colors[index]);
			glBegin(GL_QUADS);
			glVertex2f(x,y);
			glVertex2f(x+BlockSize,y);
			glVertex2f(x+BlockSize,y+10);
			glVertex2f(x,y+10);
			glEnd();
			b++;
			x=x+BlockSize;
		}

	//Opengl Round Robin
		x=RPx;
		y=RPy;
		b=0;
	while(b<Bsum)
	{
		index=Rdp[b];
		glColor3fv(colors[index]);
		glBegin(GL_QUADS);
		glVertex2f(x,y);
		glVertex2f(x+BlockSize,y);
		glVertex2f(x+BlockSize,y+10);
		glVertex2f(x,y+10);
		glEnd();
		b++;
		x=x+BlockSize;
	}
	Gridx=100;

	glColor3fv(colors[7]);
	glBegin(GL_LINES);
	while(Gridx<400-BlockSize)
	{

		glVertex2f(Gridx,Gridy);
		Gridy+=500;

		glVertex2f(Gridx,Gridy);
		Gridx+=BlockSize;

		glVertex2f(Gridx,Gridy);
		Gridy-=500;

		glVertex2f(Gridx,Gridy);
		Gridx+=BlockSize;

	}
	glEnd();


	glFlush();


}
void Display1()
{
	cout<<"\n\nFinal Display";
	cout<<"\nProcess   \tBurst time\tArrival Time\tPriority\tStart    \tEnd\tWaiting Time";
	for(int i=0;i<Num_Processes;i++)
	{
		Bsum+=P[i].BurstTime;
		cout<<"\n"<<i+1<<"\t\t"<<P[i].BurstTime<<"\t\t"<<P[i].ArrivalTime<<"\t\t"<<P[i].Priority<<"\t\t"<<P[i].Fstart<<"\t\t"<<P[i].Fend;
		cout<<"\t"<<P[i].WaitingTime;
	}
	cout<<endl;

}
void Display2()

{
	cout<<endl<<"FCFS:\t";
	for(int b=0;b<Bsum;b++)
	{
		cout<<Fdp[b];
	}
	cout<<endl<<"SJF:\t";
		for(int b=0;b<Bsum;b++)
		{
			cout<<Sdp[b];
		}
	cout<<endl<<"Priority:\t";
	for(int b=0;b<Bsum;b++)
	{
		cout<<Pdp[b];
	}
	cout<<endl<<"Round Robin:\t";
		for(int b=0;b<Bsum;b++)
		{
			cout<<Rdp[b];
		}
	cout<<"\n\nFinal Display";
	cout<<"\nProcess   \tBurst time\tArrival Time\tPriority";
	for(int i=0;i<Num_Processes;i++)
	{
		cout<<"\n"<<i+1<<"\t\t"<<P[i].BurstTime<<"\t\t"<<P[i].ArrivalTime<<"\t\t"<<P[i].Priority;

	}
	cout<<endl;
	cout<<"\nProcess     \tFWaiting Time  \tFTurnaround Time\tSWaiting Time  \tSTurnaround Time\tPWaiting Time  \tPTurnaround Time\tRWaiting Time  \tRTurnaround Time";
		for(int i=0;i<Num_Processes;i++)
		{
			cout<<"\n"<<i+1<<"\t\t"<<P[i].FWaitingTime<<"\t\t"<<P[i].FTurnAroundTime<<"\t\t\t"<<P[i].SWaitingTime<<"\t\t"<<P[i].STurnAroundTime;
			cout<<"\t\t\t"<<P[i].PWaitingTime<<"\t\t"<<P[i].PTurnAroundTime<<"\t\t\t"<<P[i].RWaitingTime<<"\t\t"<<P[i].RTurnAroundTime;
		}

		cout<<endl<<"Process 1 Color: Red";
		cout<<endl<<"Process 2 Color: Yellow";
		cout<<endl<<"Process 3 Color: Green";
		cout<<endl<<"Process 4 Color: Blue";
		cout<<endl<<"Process 5 Color: Purple";
		cout<<endl<<"Process 6 Color: Cyan";
		cout<<endl<<"Process 7 Color: Black";

}

void Fcfs()
														//WORKING!!!!
{
	int ctr=0,actr=0,bctr=0,maxa=0;
	init();
	if(!a)
	{
	for(int i=0;i<Num_Processes;i++)
	{
		P[i].Fstart=ctr;
		for(int j=ctr;j<(ctr+P[i].BurstTime);j++)
		{
			Fdp[j]=i;
		}
		ctr+=P[i].BurstTime;
		P[i].Fend=ctr;
		P[i].WaitingTime=P[i].Fstart-P[i].ArrivalTime;
	}
	}
	else
	{
		ctr=actr=bctr=maxa=0;
		for(int i=0;i<Num_Processes;i++)
		{
			if(P[i].ArrivalTime>maxa)
			maxa=P[i].ArrivalTime;
		}
		while(actr<=maxa)
		{
			for(int i=0;i<Num_Processes;i++)
			{
				if(actr==P[i].ArrivalTime&&P[i].RemBurstTime>0)
				{
					P[i].Fstart=ctr;
					for(int j=ctr;j<(ctr+P[i].BurstTime);j++)
					{
						Fdp[j]=i;					//gotta DEBUG!!!!!!
					}
					ctr+=P[i].BurstTime;
					P[i].RemBurstTime=0;
					P[i].Fend=ctr;
					P[i].WaitingTime=P[i].Fstart-P[i].ArrivalTime;

				}
			}
			actr++;


		}
	}




}

void Sjf()																//CONFIRM RELEASE
{
	int ctr=0,ch,bctr=0,minb,Pind;
	init();

	cout<<"\n Enter 1 if non preemptive for Shortest JOB first (SJF)\n";
	cin>>ch;
	if(ch&&!a)
	{
	while(bctr<Bsum)			//non-preemptive;;
	{
	 for(int i=0;i<Num_Processes;i++)
	 {
	 	if(bctr==P[i].BurstTime&&P[i].RemBurstTime>0)
		{
			P[i].Fstart=ctr;
			for(int j=ctr;j<(ctr+P[i].BurstTime);j++)
			{
				Sdp[j]=i;					//working...
			}
			P[i].RemBurstTime=0;
			ctr+=P[i].BurstTime;
			P[i].Fend=ctr;

		}
	 }
	bctr++;
    }
    }
        else
        {
        	for(int b=0;b<Bsum;b++)
        	{	Pind=-1;
        		minb=999;
        		for(int i=0;i<Num_Processes;i++)
        		if((P[i].ArrivalTime<=b)&&(P[i].RemBurstTime<minb)&&(P[i].RemBurstTime>0))
        		{
        			minb=P[i].RemBurstTime;
        			Pind=i;
        		}
        		if(Pind!=-1)
        		{
        			Sdp[b]=Pind;
        			P[Pind].RemBurstTime--;
        		}

        	}

        }


}

void Priority()															//working!!!
{
	int Pind,maxp,ch,bctr;
	init();
	cout<<"\n Enter 1 if non preemptive for Priority\n";
	cin>>ch;
	if(ch)
	{
		bctr=0;
		while(bctr<Bsum)
		{
		maxp=0;
		//non-preemptive
		for(int i=0;i<Num_Processes;i++)
		{
			if((P[i].ArrivalTime<=bctr)&&(P[i].Priority>=maxp)&&(P[i].RemBurstTime>0))
			{
				Pind=i;
				maxp=P[i].Priority;
			}
		}
		for(int i=bctr;i<(bctr+P[Pind].BurstTime);i++)
		{
			Pdp[i]=Pind;
		}
		P[Pind].RemBurstTime=0;
		bctr+=P[Pind].BurstTime;
		}
	}
	else
	{
	//preemptive
	for(int b=0;b<Bsum;b++)
	{
		Pind=-1;
		maxp=0;
		for(int i=0;i<Num_Processes;i++)
		{
			if((P[i].ArrivalTime<=b)&&(P[i].Priority>=maxp)&&(P[i].RemBurstTime>0))
			{
				maxp=P[i].Priority;
				Pind=i;
			}
		}
		if(Pind>=0)
		{
			Pdp[b]=Pind;
			P[Pind].RemBurstTime--;
		}

	}
	}
}

void RoundRobin()
{
int quantum=1,bctr=0,qctr=0;
init();
cout<<"Enter the quantum value";
cin>>quantum;
while(bctr<Bsum)
	{
	for(int i=0;i<Num_Processes;i++)
	{
		while(qctr<quantum&&bctr<Bsum)
		{
			if(P[i].RemBurstTime>0)
			{
				Rdp[bctr]=i;
				P[i].RemBurstTime--;
				bctr++;
				qctr++;
			}
			else break;

		}
		qctr=0;
	}

	}
}


int main(int argc,char** argv)
{
	//int ch;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);


	glutCreateWindow("Process Scheduler");
	glutDisplayFunc(Display);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500.0,0.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);




	cout<<"Welcome to The Process scheduling program!!\n\n";
	cout<<"Enter the number of Processes(<=7)";
	cin>>Num_Processes;
	input();
	/***************************************
	//p=new(Num_Processes*sizeof(process));
	cout<<"\n Select your algorithm:\n";
	cout<<"1.First Come First Serve [FCFS]\n";
	cout<<"2.Shortest Job First [SJF]\n";
	cout<<"3.Priority Scheduling\n";
	cout<<"4.Round Robin Scheduling\n";
	cin>>ch;
	switch(ch)
	{
		case 1:
			Fcfs();
			Display2();
			break;
		case 2:
			Sjf();
			Display2();
			break;
		case 3:
			Priority();
			WaitCal();
			Display2();
			break;
		case 4:
			RoundRobin();
			Display2();
			break;

	}
	WaitCal();
	*********************************************/
	Fcfs();
	Sjf();
	if(pr)
	Priority();
	RoundRobin();
	WaitCal();
	Display2();

	glutMainLoop();
	return 0;
}
