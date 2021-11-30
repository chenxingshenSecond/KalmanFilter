clear all; 
clc ; close all; 
run data2 ;  
figure('color','w') % 
plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  % plot( tmp1( 1:end , 1 ) ) ; hold on ;  %  
plot( tmp2( 3000:end , 1 ) ) ; hold on ;  %  % 
% tmp1( 3000:end , 1 )

%% 
run data3 ;  
figure('color','w') % 
plot( tmp1( 1:end , 1 ) ,'r')  ; hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
plot( tmp2( 1:end , 1 ) ,'b' ) ; hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %   
%% 
 