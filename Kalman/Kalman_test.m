clc;
clear all;
close all;

Ts = 0.1 ; %define the sample time

A  = [ 1 0 0 Ts 0 0; 
       0 1 0 0 Ts 0; 
       0 0 1 0 0 Ts; 
       0 0 0 1 0 0 ; 
       0 0 0 0 1 0; 
       0 0 0 0 0 1 ];   % define the state matrix 
 
C  = [ 1 0 0 0 0 0 ; 
       0 1 0 0 0 0 ; 
       0 0 1 0 0 0 ] ;  % define the output matrix 
   
B  = [ 0.5*Ts^2 0 0; 
       0 0.5*Ts^2 0; 
       0 0 0.5*Ts^2;
       Ts    0   0 ;
       0    Ts   0 ; 
       0    0   Ts ];  % define the input matrix  