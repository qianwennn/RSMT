#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct Pin_St    //创建<点>结构体
{
//	int pinid;
	int x;
	int y;
};

struct MyEdge
{
	int x1;
	int y1;
	int x2;
    int y2;
};

struct Gets    //help to get steiner pins
{
//	int pinid;
	int x;
	int y;
	int ifs;
};

void showMyPins(const Pin_St &mm);

int Distance(Pin_St mypin1, Pin_St mypin2);

int Edge_len(MyEdge myedge);

int getdis(Pin_St pin1, Pin_St pin2, Pin_St pin3);

int getpin0(vector<Pin_St> Mypins,Pin_St pin1,Pin_St pin2);//get pin closest to two pins and get edge, steiner
//get hanan list of thre pins
vector<Gets> hanan(Pin_St pin1,Pin_St pin2,Pin_St pin3);

Gets getpin1(Pin_St pin1,Pin_St pin2,Pin_St pin3);//get the stenier pin

int main()
{
	clock_t startTime,endTime;
    startTime = clock();
	vector <Pin_St> Nas;
	Pin_St nas;// store the steiner points	
	vector <Pin_St> Setiners;
	Pin_St steiner;// store the steiner points
	vector <MyEdge>  MyEdges;
	MyEdge myedge1;
	MyEdge myedge2;// store the edges

	vector <int> everypins;//每个点为一个单位存储的数组 
	vector <Pin_St> Mypins; //创建点的数组
	Pin_St mypin; //实例化点
	Pin_St pin1;
	Pin_St pin2;
	Pin_St pin3;
	Gets spin;
	Pin_St pins;
	Pin_St pinss;
	int j1;
	int j2;
	int j3;
	int t;
	int ch;
	int edgelen = 0;
	ifstream fin;
	fin.clear();
	//string s = "1_10";
	string s;
	cout << "please input the file name(without'.txt')" << endl;
	cin >> s;
	fin.open(s + ".txt");
	ofstream fout;
	fout.open(s + "_steiners.txt",ios::out);
	ofstream foute;
	foute.open(s + "_edges.txt",ios::out);


	for (int i = 0; !fin.eof(); i++)
	{
		fin >> ch;
		everypins.push_back(ch);
		fin.get();//分隔符，	
	}
    int pinnums = everypins.size();
	for (int ii = 0; ii<pinnums/3 ; ii++)   //5行
	{
		int x_two = everypins[3 * ii + 1];
		int y_three = everypins[3 * ii + 2];
		mypin.x = x_two;
		mypin.y = y_three;
		Mypins.push_back(mypin);//get the pins vector
	}
// test distance function
	int result = Distance(Mypins[1],Mypins[2]);
//get the pins in text	

// get the closest pins
	int oneva = 10000;
    for (int j=0 ; j< pinnums/3; j++)
	{
		for (int jj= j+1 ; jj< pinnums/3 ; jj++)
		{
			int dis = abs(Mypins[jj].x-Mypins[j].x) + abs(Mypins[jj].y-Mypins[j].y);
			if (dis < oneva){
				oneva = dis;
				j1 = j;
				j2 = jj;
			}

		};	
	};
	pin1 = Mypins[j1];
	pin2 = Mypins[j2];
    Mypins.erase(Mypins.begin()+j1);
	Mypins.erase(Mypins.begin()+j2-1);

	while(Mypins.size() != 0)
	{
	
		int ed;
		j3 = getpin0(Mypins,pin1,pin2);
		pin3 = Mypins[j3];
		spin = getpin1(pin1,pin2,pin3);
		if (spin.ifs == 1)
		{
			pins.x = spin.x;pins.y= spin.y;
			Setiners.push_back(pins);
			Nas.push_back(pins);
			fout << pins.x << " " << pins.y << endl; 
			myedge1.x1 = pin1.x;
			myedge1.y1 = pin1.y;
			myedge1.x2 = pins.x;
			myedge1.y2 = pins.y;
			ed = Edge_len (myedge1);
			foute << myedge1.x1 << " " << myedge1.y1 <<" "<< myedge1.x2<< " "<<myedge1.y2 <<endl;
			edgelen += ed;
			MyEdges.push_back(myedge1);
			myedge1.x1 = pins.x;
			myedge1.y1 = pins.y;
			myedge1.x2 = pin2.x;
			myedge1.y2 = pin2.y;
			foute << myedge1.x1 << " " << myedge1.y1 <<" "<< myedge1.x2<< " "<<myedge1.y2 <<endl;
			ed = Edge_len (myedge1);
			edgelen += ed;
			MyEdges.push_back(myedge1);
		}
		else
		{
			pins.x = spin.x;pins.y= spin.y;
			Nas.push_back(pins);
			myedge1.x1 = pin1.x;
			myedge1.y1 = pin1.y;
			myedge1.x2 = pin2.x;
			myedge1.y2 = pin2.y;
			foute << myedge1.x1 << " " << myedge1.y1 <<" "<< myedge1.x2<< " "<<myedge1.y2 <<endl;
			ed = Edge_len (myedge1);
			edgelen += ed;
			MyEdges.push_back(myedge1);
		}
		pin1 = pins;
		pin2 = pin3;
		Mypins.erase(Mypins.begin()+j3);
	}

	//for_each(Setiners.begin(), Setiners.end(), showMyPins);
	fin.close();
	fout << "num of setiners: " <<  Setiners.size() << endl;
	foute << "overall edgelen: " <<  edgelen << endl;
    endTime = clock();//计时结     
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	fout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
void showMyPins (const Pin_St &mm)
{
	cout << "pin:" << mm.x << " " << mm.y << endl;
}
// get distance between teo pins
int Distance(Pin_St pin1, Pin_St pin2)
{
    int distance;
    distance = abs(pin1.x-pin2.x) + abs(pin1.y-pin2.y);
    return distance;
}
//get the length of edge(1,4,4,5)
int Edge_len(MyEdge myedge)
{
	int edge_len;
	edge_len = abs(myedge.x1 - myedge.x2) + abs(myedge.y1 - myedge.y2);
	return edge_len;
}


int getdis(Pin_St pin1, Pin_St pin2, Pin_St pin3)
{
	int disx;
	int dis;
	dis= 10000;
	if(pin3.x > min(pin1.x,pin2.x) && pin3.x<max(pin1.x,pin2.x))
	{
		disx = min(abs(pin3.y-pin1.y),abs(pin3.y-pin2.y));
	}
	else if(pin3.y > min(pin1.y,pin2.y) && pin3.y<max(pin1.y,pin2.y))
	{
		disx = min(abs(pin3.x-pin1.x),abs(pin3.x-pin2.x));
	}
	else
	{
		int dis1 = min(abs(pin3.x-pin2.x), abs(pin1.x-pin3.x)); 
		int dis2 = min(abs(pin3.y-pin2.y), abs(pin1.y-pin3.y));
		disx = dis1 + dis2;
	}
	if ( disx > 0 && disx < dis)
	{
		dis = disx;
	}
	return dis;
};


int getpin0(vector<Pin_St> Mypins,Pin_St pin1,Pin_St pin2)//get pin closest to two pins and get edge, steiner
{
	int tt;
	int dis=10000;
	Pin_St thepin;
    vector<Pin_St>::iterator it; 
    for(int t=0;t< Mypins.size() ; t++)
    {
		int dis1;
		dis1 = getdis(pin1, pin2, Mypins[t]);	
		//if (t != j1 and t!= j2)
		//dis1 = getdis(Mypins[j1], Mypins[j2], Mypins[t]);			
		if (dis1 > 0 and dis1 < dis)
		{
			dis = dis1;
			tt = t;
		}
	};
	//thepin.x = Mypins[tt].x;
	//thepin.y = Mypins[tt].y;
//	Mypins.erase(Mypins.begin()+ tt );
	return tt;
};

vector<Gets> hanan(Pin_St pin1,Pin_St pin2,Pin_St pin3)
{
	Gets pin;
    vector<Gets> Pin;
	pin.x =pin1.x;pin.y=pin1.y;pin.ifs = 0;Pin.push_back(pin);
	pin.x =pin2.x;pin.y=pin2.y;pin.ifs = 0;Pin.push_back(pin);
	if (pin1.x != pin2.x && pin1.y != pin2.y)
	{
		if (pin3.x > min(pin1.x,pin2.x) && pin3.x<max(pin1.x,pin2.x))
		{
			pin.x =pin3.x;pin.y=pin2.y;pin.ifs = 1;Pin.push_back(pin);
			pin.x =pin3.x;pin.y=pin1.y;pin.ifs = 1;Pin.push_back(pin);
		}
		else if(pin3.y > min(pin1.y,pin2.y) && pin3.y<max(pin1.y,pin2.y))
		{
			pin.x =pin1.x;pin.y=pin3.y;pin.ifs = 1;Pin.push_back(pin);
			pin.x =pin2.x;pin.y=pin3.y;pin.ifs = 1;Pin.push_back(pin);
		}
		else
		{
			pin.x =pin1.x;pin.y=pin2.y;pin.ifs = 1;Pin.push_back(pin);
		    pin.x =pin2.x;pin.y=pin1.y;pin.ifs = 1;Pin.push_back(pin);
		}
	}
	else if(pin1.y = pin2.y && pin3.x > min(pin1.x,pin2.x) && pin3.x<max(pin1.x,pin2.x))
	{
		pin.x =pin3.x;pin.y=pin1.y;pin.ifs = 0;Pin.push_back(pin);
	}
	else if (pin1.x = pin2.x && pin3.x > min(pin1.x,pin2.x) && pin3.x<max(pin1.x,pin2.x))
	{
		pin.x =pin1.x;pin.y=pin3.y;pin.ifs = 0;Pin.push_back(pin);
	}
    return Pin;
};

Gets getpin1(Pin_St pin1,Pin_St pin2,Pin_St pin3)
{
    vector<Gets> Pin;	
	Pin = hanan(pin1,pin2,pin3);
    int distance = 10000;
	int d;

	for (int i = 0; i< 8 ; i++)
	{
		Pin_St pin;
		pin.x = Pin[i].x;
		pin.y = Pin[i].y;
		int dis = Distance(pin,pin3);
		if (dis < distance)
		{
			d = i;
			distance = dis;
		}
    };
	if (d >1 )
	{
		return Pin[d];
	}
	else
	{
		return Pin[d];
	}
};