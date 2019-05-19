#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <conio.h>
#include<time.h>
#define FILENAME "data.txt"
//please enter positive integer only
int function(int xp,int vp, int A, int a, int w, int k, int collision, int array[]);
void writeFile(int b, int arr[]);
int main(){
	//getting the attributes of the wave i.e y=a+Acos(wt-Kx)
	int i,j,w,k,xp,vp,a,A,collision=0,v0,c,sum=0;
	int array[10000];
	printf("Enter the initial particle velocity \n");
	scanf("%d",&v0);
	printf("Enter the amplitude of the wave A \n");
	scanf("%d",&A);
	printf("Enter the value of a \n");
	scanf("%d",&a);
	printf("Enter the wave frequency w \n");
	scanf("%d",&w);
	printf("Enter the wave number k \n");
	scanf("%d",&k);
	srand(time(NULL));
	// the maximum and the minimum amlitude of the particle vibrating on the wave is a+A and a-A respectively
	//generating the random number between 0 to a-A
	xp=(rand()%(a-A+1))+0;
	j=rand()-(RAND_MAX/2);
	if(j<0){
		vp=-v0;
	}
	else{
		vp=v0;
	}
	printf("intial velocity of the particle %d\n",vp);
	printf("initial position of the particle %d\n",xp);
	// generating randomly particle velocity between the given range 
	c=function(xp,vp,A,a,w,k,collision,array);
	printf(" no. of collision is %d\n",c);
	printf("energy of the particle after each collision\n");
	for(i=1; i<c; i++){
		printf("the energy of the particle after %dth collision is:%d\n",i,array[i]);
	}
	// calculating the average energy of the particle
	for(i=1; i<c; i++){
		sum=sum+array[i];
	}
	printf("the average energy of the particle %d\n",sum/c);
	writeFile(c,array);
}
int function(int xp,int vp, int A, int a, int w, int k,int collision, int array[]){
	int wxp,s,t,wvp,wep,x,u,r,count;
	int epd,ep;
	//srand(time(NULL));	
	// calculating particle's energy in the box
	ep=pow(vp,2);
	if (vp>0){
		collision=collision+1;
	// picking randomly a particle on the wave for that genarating a random number between a-A to a+A
	r=(rand()%((2*A)+1))+A;
	wxp=a+r;
	//printf(" value of wxp %d\n",wxp);
	// calculating the distance between the particle on the wave and in the 1-D box
	s= wxp-xp;
	// calculating the time of collision 
	t=s/vp;
	wvp=-(A*w*sin(w*t-k*wxp)); //printf("value of wvp %d\n",wvp); // particle's velocity at the instant of collision present on the wave
	//calculating particle's energy on the wave
	wep=pow(wvp,2);
	    if (wvp<=0){
		    epd=ep+wep;
		    }
    	else{
		   epd=abs(ep-wep);
       	} 
	array[collision]=epd;         
	//printf("energy %d\n",array[collision]);
	//printf("collision %d\n",collision);	 
	     if(array[collision]==0){
	     	return collision;
		 }  	
    x=wxp;
	u=-(sqrt(abs(epd))); 
    function(x,u,A,a,w,k,collision,array);
   }
  if(vp<0){
 	x=0;
 	collision=collision+0;
 	u=-vp;
    function(x,u,A,a,w,k,collision,array);
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
      for(a=1;a<=b;a++){
	  fprintf (fp, " %d\n ", arr[a]) ;
        }          
      fclose(fp);
}
// creating a function to read a file name
void readFile()
{
     int f;
     printf("Reading from the file \n");

     FILE *fr;
     fr=fopen(FILENAME,"r");
     fscanf (fr, " %d ", &f) ;
     fclose(fr);
     printf("the data from the file %d \n", f);
}




