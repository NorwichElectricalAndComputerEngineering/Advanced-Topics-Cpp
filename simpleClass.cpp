// classes example
#include <iostream>
#include <time.h>
#include <windows.h>
#include <math.h>
using namespace std;
void draw(int, int);
void readRSSI();
//create a drone class to read in lat long alt and RSSI measurements.
class drone {
  public:
    int xPosition, yPosition;
    double rssi;

    void setValues (int,int);
    int readDrone() {return rssi;}
};
void drone::setValues (int x, int z) {
  xPosition = x;
  yPosition = z;
}
bool found = false;
int moveDrone;
drone drone1;//create object drone1
int xTargetLocation;
int yTargetLocation;
int main () {
  //seed random position for target
	srand((int)time(0));
	xTargetLocation = rand() % 10;//seed random integer to place target on the map
    yTargetLocation = xTargetLocation; //got lazy

  drone1.setValues(5, 5);//initialize the variables in drone1


  //start search routine
  do{
//accept user input 2486 to move except out of bounds
    cout<<"2486 to move drone"<<endl;
    cin>> moveDrone;
switch (moveDrone){
case 2:
    if(drone1.yPosition!=10){
        drone1.yPosition+=1;
    }
break;
case 4:
    if(drone1.xPosition!=0){
        drone1.xPosition-=1;
    }break;
case 6:
    if(drone1.xPosition!=10){
        drone1.xPosition+=1;
    }break;
case 8:
    if(drone1.yPosition!=0){
        drone1.yPosition-=1;
    }default:
    break;
    }
    draw(5, 5);

  }while(!found);
  return 0;
}
void draw(int x, int y)
{
readRSSI();
cout<<"RSSI: "<<drone1.readDrone()<<endl;
    for(int i = 0; i < 11; i++)
        {


            for(int j = 0; j < 11; j++)
            if(i == drone1.yPosition && j == drone1.xPosition)
                cout<<" x ";
            else if (i==xTargetLocation && j==yTargetLocation)
                cout<<" 0 ";
            else if(xTargetLocation==drone1.xPosition && yTargetLocation == drone1.yPosition)
                found = true;
            else
                cout<<" . ";

            if (!found)
                cout<<endl;
            else
                cout<<"Target Found"<<endl;
        }
}
void readRSSI(){
    double distancex = (drone1.xPosition-xTargetLocation)*(drone1.xPosition-xTargetLocation);
    double distancey = (drone1.yPosition-yTargetLocation)*(drone1.yPosition-yTargetLocation);
    cout<<"x: "<<distancex<<endl<<"y: "<<distancey<<endl;
    drone1.rssi = sqrt(distancex + distancey);
}
