clear all;  % 
clc ; close all;  % 
run data2 ;  
sigmax_2 =  var( tmp1( 3000:end , 1 ) ) ;  % 
sigmay_2 =  var( tmp1( 3000:end , 2 ) ) ;  %  
sigmaz_2 =  var( tmp1( 3000:end , 3 ) ) ;  %   
%% 
%%   
% filename = 'test_Leap -Leapmotion���Է����� - 2\test_Leap\ƽ��̨�˶� z�� ��Ӧ��leapmotionΪz�ᷴ��\' ; %%  
dim = 1  ; %% 
filename = 'test_Leap -Leapmotion���Է����� - 2\test_Leap\ƽ��̨�˶� y��  ��Ӧ��leapmotionΪx�ᷴ��\' ;  %%      
% filename = 'test_Leap -Leapmotion���Է����� - 2\test_Leap\ƽ��̨�˶� y��  ��Ӧ��leapmotionΪx��\' ;  %% 
% filename = 'test_Leap -Leapmotion���Է����� - 2\test_Leap\ƽ��̨�˶� x��  ��Ӧ��leapmotionΪy�ᷴ��\' ;  %% 
% filename = 'test_Leap -Leapmotion���Է����� - 2\test_Leap\ƽ��̨ ������ת�˶�\' ;  %% 
run data5 ; 
Ts   =  0.01  ; % 
tmp1        =  tmp1( : , dim ) ; 
position    =  tmp1 ( 2 : end  , : )  ;  % accleration =  ( velocity(2:end,:) - velocity(1:end-1,:)  ) / Ts  ; %%    

%%  
velocity  = speed( : , dim )' ; % 
smoothed  = tmp2( 2 : end , : ) ;  

sigmax_v2 = std(  speed(130:800,1) ) ; 
sigmay_v2 = std(  speed(130:800,2) ) ; 
sigmaz_v2 = std(  speed(130:800,3) ) ; 

% sigma_x2 =  std( tmp1( 3000:end , 1 ) ) ;  % 
% sigma_y2 =  std( tmp1( 3000:end , 2 ) ) ;  %  
% sigma_z2 =  std( tmp1( 3000:end , 3 ) ) ;  %  

% �ٶȵ� x��������� 1.1311        1.8787 
% �ٶȵ� y��������� 2.9846        3.7886 
% �ٶȵ� z��������� 1.4314        2.1648
 
%%  T = 100  %% 

A   =   1  ;  % define the state matrix       
C   =   1  ;  % define the output matrix 
B   =   Ts ;  % define the input matrix  

%%  
measurmentsV = 0.6 ; % 
Q   =  1.1 ; 
R  = measurmentsV * ( C * C') ;  % 
%  Initializing P % 
P = B * Q * B';  
% 
Xest       = zeros ( 1 , length( position )  ) ;  % 
Xest(:,1)  = position(1) ;  %   
% 
Prediction = position( : )' ; 
velocity   = velocity' ; 
%  
for i = 2:1:length( position ) -120   % 
    P          = A * P * A' + B * Q * B'   ; % predicting P
    Xest(:,i)  = A * Xest(:,i-1)  +  B*velocity(i-1)  ; % Predicitng the state
    K          = P * C' / (  C * P * C' +  R  )  ; % calculating the Kalman gains
    Xest(:,i)  = Xest(:,i) + K * (  Prediction(:,i) - C * Xest(:,i) )  ; % Correcting: estimating the state
    P          = ( 1 - K * C ) * P  ;  % Correcting:estimating P
end
%% 
figure ( 'color' , 'w' ) ;  %% 
plot( Xest     ( 1     , 1:end-130 ) , 'b' ) ;  hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
plot( tmp1     ( 2:end  ) , 'r' ) ;  hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
plot( smoothed ( 1:end ,dim ) ,'g') ; hold on ;  %  % plot( tmp1( 3000:end , 1 ) ) ; hold on ;  %  
h = legend( '$Kalman \,\, prediction$' , '$Original \,\, data$' , '$Smoothed \,\, by \,\, leapmotion$' )  ;
set(h,'Interpreter','latex') ;
h = xlabel( '$Time \,\, stamp$' ); 
set(h,'Interpreter','latex') ; 

h = ylabel( '$Motion/mm$' ); 
set(h,'Interpreter','latex') ;

h = title('$Hand \,\, motion \,\, in \,\, x \,\, direction$') ;  
set(h,'Interpreter','latex') ;

set(gca,'TickLabelInterpreter','latex')


%%
figure ( 'color' , 'w' ) ;  %%   
plot( velocity ) ; title('Hand velocity in y direction') ;  

%{  ���ٶȲ�֪��������£�����ֻ��Ϲ�£�û��ʵ�ʵ�����  %} 


