#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define FILENAME "data1.txt"
#define PI 3.141592
int fun(int x0, int y0, int v, int A, int a, int w, int k, int l, int m, int count, int arr[]);
void writeFile(int b, int arr[]);
int main(){
	int i,x0,y0,v,m,l,a,A,w,k,count=0,c,arr[10000],sum=0;
	// getting the required parameters
	printf("enter the particle initial speed \n");
	scanf("%d",&v);
	printf("enter the amplitude of the wave \n");
	scanf("%d",&A);
	printf("Enter the value of a \n");
	scanf("%d",&a);
	printf("Enter the wave frequency w \n");
	scanf("%d",&w);
	printf("Enter the wave number k \n"); 
	scanf("%d",&k);
	// getting coordinates of the 2-D box
	printf("enter the maximum width of the box \n");
	scanf("%d",&l);
	printf("enter the maximum height of the box \n");
	scanf("%d",&m);
	srand(time(NULL));
	x0=(rand()%(l+1))+0;
	y0=(rand()%(m-a-A+1))+(a+A);
	printf("intial coordinates of the particle is %d\n %d\n",x0,y0);
	c=fun(x0,y0,v,A,a,w,k,l,m,count,arr);
	printf(" total no. of collision is %d\n",c);
	printf("energy of the particle after each collision\n");
	for(i=1; i<c; i++){
		printf("the energy of the particle after %dth collision is:%d\n",i,arr[i]);
	}
	// calculating the average energy of the particle
	for(i=1; i<c; i++){
		sum=sum+arr[i];
	}
	printf("the average energy of the particle %d\n",sum/c);
	writeFile(c,arr);
}
int fun(int x0, int y0, int v, int A, int a, int w, int k, int l, int m, int count, int arr[]){
	double slope,ang1,ang2,ang3,ang4,vx,vy;
	int x,y,t,e,wpv,eac,wpe,x1,y1,u;
	slope=atan((double)y0/x0);
	//printf("slope %1f\n",slope);
	vx=v*cos(slope);
	vy=v*sin(slope);
	//printf("vx,vy %1f\n%1f\n",vx,vy);
	// converting into degree 
	//sploeD=(slopeR*180)/3.14;
	ang1=atan((double)(a+A-y0)/(0-x0));
	ang2=atan((double)(a+A-y0)/(l-x0));
	ang3=atan((double)(m-y0)/(0-x0));
	ang4=atan((double)(m-y0)/(l-x0));
	//printf("ang1 %1f\n",ang1+PI);
	//printf("ang2 %1f\n",ang2+PI);
	//printf("ang3 %1f\n",ang3+PI);
	e=pow(vx,2)+pow(vy,2);
	//printf("e %d\n",e);
	if(slope>(PI+ang1)||-(PI-ang2)<slope){    // condition to collide with the oscillating wall 
	    count=count+1;
	    x=(rand()%(l+1))+0;
	    //printf("x on moving wall %d\n",x);
	    t=abs(x0-x)/vx;
            y=a+A*cos(w*t-k*x);
	    wpv=-(A*w*sin(w*t-k*x));
	    wpe=pow(wpv,2);
            //printf("velocity of particle on moving wall %d\n",wpv);
		   if(wpv>0){
		   	eac=e+wpe;
		   }
		   else{
		   	eac=abs(e-wpe);
		   }
		arr[count]=eac;
		//printf("energy after %dth collision is %d\n",count,arr[count]);
		//printf("energy %d\n",eac);
		  if(arr[count]==0){
		  	return count;
		  }   
		x1=x;
		y1=y;
		u=(sqrt(abs(eac)));
		fun(x1,y1,u,A,a,w,k,l,m,count,arr);	
	}
	else if(ang4<slope<ang3){
			y1=m;
			t=abs(y0-y)/vy;
			x1=x0+vx*t;
			//printf("%d\n",x1);
			count=count+0;
                        
			fun(x1,y1,v,A,a,w,k,l,m,count,arr);
		 }
	else if(-(PI-ang2)<slope<ang4 || slope==0.000000){
			x1=l;
			t=abs(x0-l)/vx;
			y1=y0+vy*t;
			//printf("%d\n",y1);
			count=count+0;
			fun(x1,y1,v,A,a,w,k,l,m,count,arr);
		}
	else if(ang3<slope<(PI+ang1)){
			x1=0;
			t=x0/vx;
			y1=y0+vy*t;
			//printf("%d\n",y1);
			count=count+0;
			fun(x1,y1,v,A,a,w,k,l,m,count,arr);
		}
	else {
                 printf("no condition is satisfied\n");
	    }
}
// creating a function to write a file
void writeFile(int b, int arr[])
{
     FILE *fp;
     int a;
      fp = fopen(FILENAME, "w");
      //checking if the file exist
      if (fp == NULL)
      {
        perror("File could not be opened for writing\n");
      }
      else
      {
        printf("File created\n");
      }
      for(a=1;a<b;a++){
	  fprintf (fp, " %d\n ", arr[a]) ;
        }          
      fclose(fp);
}














