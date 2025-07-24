#include <iostream>
using namespace std;
int main(){
	int d1,d2,d3,d4;
	cout<<"Enter the 1st bit in data\n";
	cin>>d1;
	cout<<"Enter the 2nd bit in data\n";
	cin>>d2;
	cout<<"Enter the 3rd bit in data\n";
	cin>>d3;
	cout<<"Enter the 4th bit in data\n";
	cin>>d4;
	int p1=0,p2=0,p3=0;
	int arr[]={p1,p2,d1,p3,d2,d3,d4};
	
	cout<<"p1  p2  d1  p3  d2  d3  d4\n";
	cout<<"4-Bit Number with parity\n";
	cout<<arr[0]<<"  "<<arr[1]<<"  "<<arr[2]<<"  "<<arr[3]<<"  "<<arr[4]<<"  "<<arr[5]<<"  "<<arr[6]<<"\n";
	 
	if (arr[2]+arr[4]+arr[6]%2==0){
		p1=arr[0]=0;
	}else{
		p1=arr[0]=1;
	}
	if (arr[2]+arr[5]+arr[6]%2==0){
		p2=arr[0]=0;
	}else{
		p2=arr[0]=1;
	}
	if (arr[4]+arr[5]+arr[6]%2==0){
		p3=arr[0]=0;
	}else{
		p3=arr[0]=1;
	}
	cout<<"Final data With Parity Bits :\n";
	cout<<arr[0]<<"  "<<arr[1]<<"  "<<arr[2]<<"  "<<arr[3]<<"  "<<arr[4]<<"  "<<arr[5]<<"  "<<arr[6]<<"\n";
	
	return 0;
}
