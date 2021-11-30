clear all;  % 
clc ; close all;  % 
run data2 ;  
sigmax_2 =  var( tmp1( 3000:end , 1 ) ) ;  % 
sigmay_2 =  var( tmp1( 3000:end , 2 ) ) ;  %  
sigmaz_2 =  var( tmp1( 3000:end , 3 ) ) ;  % 
%%  
run data4
Ts   =  0.02  ; 
tmp1 = tmp1( 3000:end , 1 ) ; 
position    =  tmp1 ( 2 : end  , : )  ;  % 
velocity    = ( position - tmp1(1:end-1,:)  ) / Ts ;  %   
velocity    =  [ 0;0;0;0 ; velocity ]  ;  
accleration =  ( velocity(2:end,:) - velocity(1:end-1,:)  ) / Ts  ; %%    
% accleration = [0 0 0;accleration] ; 
% u = [ velocity , accleration  ]' ;
% u = [ velocity  ]' ;
u  = 0.0001 * velocity(:,1)' ; % 
smoothed = tmp2( 2 : end , : ) ; 
%%  T = 100  %% 
A   =   1  ;  % define the state matrix       
C   =   1  ;  % define the output matrix 
B   =   Ts ;  % define the input matrix  
%%  
measurmentsV = 0.6 ; % 
Q   =  241.1 ; 
R  = measurmentsV * ( C * C') ;  % 
%  Initializing P % 
P = B * Q * B';  
% 
Xest       = zeros ( 1 , length( position )  ) ;  % 
Xest(:,1)  = position(1) ;  %   
% 
Prediction = position(:,1)' ; 
velocity   = velocity' ; 
%  
for i = 2:1:length( position )  % 
    P          = A * P * A' + B * Q * B'   ; % predicting P
    Xest(:,i)  = A * Xest(:,i-1)  ; % Predicitng the state
    K          = P * C' / (  C * P * C' +  R  )  ; % calculating the Kalman gains
    Xest(:,i)  = Xest(:,i) + K * (  Prediction(:,i) - C * Xest(:,i) )  ; % Correcting: estimating the state
    P          = ( 1 - K * C ) * P  ;  % Correcting:estimating P
end
%%   
figure ; 
plot( Xest     ( 1     , : ) , 'b' ) ;  hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
plot( tmp1     ( 1:end , 1 ) , 'r' ) ;  hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
plot( smoothed ( 3000:end ,1) ,'g') ; hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
legend( 'my predict' , 'original data' , 'smoothed by leapmotion' )
%{ 
加速度不知道的情况下，我们只能瞎猜；没有实际的输入 %
%}

