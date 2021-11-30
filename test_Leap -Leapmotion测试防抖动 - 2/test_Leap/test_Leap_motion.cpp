// test_Leap_motion.cpp : 定义控制台应用程序的入口点 // 

#include "controler.h"
#include "stdafx.h" 
#include "time.h"  
#include "iostream" 
using namespace std ;  //   


int  main(int argc, char* argv[])
{
	SampleListener   *  listener   = new SampleListener(); //   包含所有的变量   //
	int jishu     = 0 ;  

	FILE *fp          =  fopen("Projection_Matrix_Unstable.txt","w");   
	FILE *fp2         =  fopen("Projection_Matrix_Stable.txt","w");   
	FILE *f_fp_speed  =  fopen("fp_speed.txt","w");   
	FILE *f_interval  =  fopen("interval.txt","w");  
	// 
	float last[]  = {-222222.0,-222222,3222222 } ;
	float last2[] = {-222222.0,-222222,3222222 } ;
	//  
	int    first  = listener->timestamp;     
	int    second = listener->timestamp;     
	clock_t start = clock();  
	clock_t end = clock(); 

	int iter = 0; 
	while (1)  
	{   // 
		iter++ ;  //   	// 
		if(listener->if_right_exist)
		{
			std::cout<<"right= "<<listener->position.x<<"  "<<listener->position.y<<"  "<<listener->position.z<<std::endl  ; 
		}
		// 
		// 
		if(  listener->position.x!=last[0]  ||  listener->position.y!=last[1]  ||  listener->position.z!=last[2] ) 
		{
			fprintf(fp,"%f %f %f \n" , listener->position.x, listener->position.y, listener->position.z  ) ; //   
			last[0]  =  listener->position.x ; // 
 			last[1]  =  listener->position.y ; // 
			last[2]  =  listener->position.z ; //   
			//  ****************************************   //
			fprintf( fp2  , " %f %f %f \n" ,  listener->pos_bal.x, listener->pos_bal.y, listener->pos_bal.z  ) ; //    
			fprintf( f_fp_speed  ,"%f %f %f \n" , listener->speed.x, listener->speed.y, listener->speed.z  ) ; //      
			// 
			second = listener->timestamp ;  //    
			clock_t end = clock();   //  
			cout<<  (second-first) <<endl ;  
			// **************************************************** // 
			fprintf( f_interval  ,"%f \n"  ,(end-start)/1000.0  ) ; //      
			start   =  end ;  
			first   =  second ;  
			// **************************************************** // 
		}  
	}
	fprintf(fp,"\n") ;
	// fprintf(fp,"\n") ;  


	fclose(    fp      ); 
	fclose(    fp2     ); 
	fclose( f_fp_speed ); 
	fclose( f_interval ); 

	return 0 ; 
}