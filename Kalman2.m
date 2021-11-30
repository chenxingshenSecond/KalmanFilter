clear all; 
clc ; close all; 
run data2 ;  
sigmax_2 =  var( tmp1( 3000:end , 1 ) ) ; 
sigmay_2 =  var( tmp1( 3000:end , 2 ) ) ; 
sigmaz_2 =  var( tmp1( 3000:end , 3 ) ) ;   
%% 
run data4 ;  
Ts   =  0.02  ; 
position    =  tmp1( 2 : end  , : )  ;  % 
velocity    = ( position - tmp1(1:end-1,:)  ) / Ts ;  %  
accleration = ( velocity(2:end,:) - velocity(1:end-1,:)  ) / Ts  ; %%    
accleration = [0 0 0;accleration] ; 

% u = [ velocity , accleration  ]' ;
% u = [ velocity  ]' ;
u  = accleration' ; % 
smoothed = tmp2( 2 : end , : ) ; 
%% 
A  = [ 1 0 0 Ts 0 0; 
       0 1 0 0 Ts 0; 
       0 0 1 0 0 Ts; 
       0 0 0 1 0 0 ; 
       0 0 0 0 1 0; 
       0 0 0 0 0 1 ];   % define the state matrix      
   
C  = [ 1 0 0 0 0 0 ; 
       0 1 0 0 0 0 ; 
       0 0 1 0 0 0 ] ;  % define the output matrix 

B  = [ 0.5*Ts^2      0          0; 
       0          0.5*Ts^2      0; 
       0             0       0.5*Ts^2;
       Ts            0           0 ;
       0             Ts          0 ; 
       0              0          Ts ];  % define the input matrix  
%%  
measurmentsV = [  sigmax_2     0          0     ;    
                   0       sigmay_2       0     ;  
                   0           0     sigmaz_2 ] ; %
               
Q             = [  sigmax_2     0          0       ;    
                   0         sigmay_2      0       ;  
                   0            0       sigmaz_2 ] ; %
               
R  = measurmentsV * ( C * C') ;  % 
%  Initializing P % 
P = B * Q * B';  
% 
Xest       = zeros ( 6 , length( position )  ) ;  % 
Xest(:,1)  = [ 0 ;  0   ;   0   ; 0 ; 0 ; 0  ] ;  %   
% 
Prediction = position' ; 
velocity   = velocity' ; 
%  
for i = 2 : 1 : length( position  ) % 
    P          = A * P * A'   +  B * Q * B'   ; % predicting P
    Xest(:,i)  = A * Xest(:,i-1) + B * u (:,i-1) ; % Predicitng the state
    K          = P * C'/( C * P * C'+ R )     ; % calculating the Kalman gains
    Xest(:,i)  = Xest(:,i) + K * (  Prediction(:,i)  - C*Xest(:,i) ) ; % Correcting: estimating the state
    P          = ( eye(6) - K * C ) * P       ; % Correcting:estimating P
end 
%%   

figure ; 
plot( Xest     ( 3 , : ) , 'b' )   ;  hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
plot( tmp1     ( 1:end , 3 ) ,'r')  ; hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
plot( smoothed ( 1:end , 3 ) ,'g')  ; hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
legend( 'my predict' , 'original data' , 'smoothed by leapmotion' )