clear;
clc;

%% Caracterizacion de la planta

s=tf('s');
R=4700;
C=470*10^(-6);
H=(1/(R*C)^2)/(s^2+(3/(R*C))*s+1/(R*C)^2); %Modelo original, segundo orden

Kp=1;
tm=0.4219;
tau=6.2056;
Haprox=exp(-tm*s)/(tau*s+1); %Aproximacion Half-Rule (POMTM)

figure(1)
step(H,Haprox,'--')
title('');
xlabel(['Tiempo (s)','']);
ylabel('Respuesta al impulso');
legend('Modelo segundo orden','Aproximación POMTM','Location','east');

%% Obtención de los parámetros del controlador

%Metodo de Arrieta servo control
%Parametros para optimizar IAE en funcion de servo control
a=0.2268;
b=0.8051;
c=-0.9597;
d=1.0068;
e=0.3658;
f=1.0092;
g=-0.0146;
h=0.3500;
i=0.8100;

Kc_arrieta_servo=(a+b*((tm/tau)^c))/Kp;
Ti_arrieta_servo=(d+e*((tm/tau)^f))*tau;
Td_arrieta_servo=(g+h*((tm/tau)^i))*tau;

%Metodo de Arrieta control regulatorio, optimizacion IAE
a_reg=0.1050;
b_reg=1.2432;
c_reg=-0.9946;
d_reg=-0.2512;
e_reg=1.3581;
f_reg=0.4796;
g_reg=-0.0003;
h_reg=0.3838;
i_reg=0.9479;

Kc_arrieta_reg=(a_reg+b_reg*((tm/tau)^c_reg))/Kp;
Ti_arrieta_reg=(d_reg+e_reg*((tm/tau)^f_reg))*tau;
Td_arrieta_reg=(g_reg+h_reg*((tm/tau)^i_reg))*tau;

% Metodo de Kaya y Scheib para minimizar IAE en funcion de servo control
Kc_kaya_servo=(0.65/Kp)*(tau/tm)^1.04;
Ti_kaya_servo=tau/(0.99+0.10*(tm/tau));
Td_kaya_servo=0.51*tau*(tm/tau)^1.08;

% Metodo de Kaya y Scheib para minimizar IAE en funcion de control
% regulatorio
Kc_kaya_reg=(0.98/Kp)*(tau/tm)^0.76;
Ti_kaya_reg=(tau/0.91)*(tau/tm)^1.05;
Td_kaya_reg=0.60*tau*(tm/tau)^0.9;

%PI
%Metodo de Arrieta servo control, optimazacion IAE

a_arrieta_pi_servo=0.2438;
b_arrieta_pi_servo=0.5305;
c_arrieta_pi_servo=-1.0299;
d_arrieta_pi_servo=0.9377;
e_arrieta_pi_servo=0.4337;
f_arrieta_pi_servo=0.8714;

Kc_arrieta_pi_servo=(a_arrieta_pi_servo+b_arrieta_pi_servo*((tm/tau)^c_arrieta_pi_servo))/Kp;
Ti_arrieta_pi_servo=(d_arrieta_pi_servo+e_arrieta_pi_servo*((tm/tau)^f_arrieta_pi_servo))*tau;

%Metodo de Arrieta control regulatorio, optimazacion IAE

a_arrieta_pi_reg=0.4485;
b_arrieta_pi_reg=0.6494;
c_arrieta_pi_reg=-1.1251;
d_arrieta_pi_reg=-0.2551;
e_arrieta_pi_reg=1.8205;
f_arrieta_pi_reg=0.4749;

Kc_arrieta_pi_reg=(a_arrieta_pi_reg+b_arrieta_pi_reg*((tm/tau)^c_arrieta_pi_reg))/Kp;
Ti_arrieta_pi_reg=(d_arrieta_pi_reg+e_arrieta_pi_reg*((tm/tau)^f_arrieta_pi_reg))*tau;

%% Obtención del controlador en tiempo continuo

Ts=0.1; % Tiempo de muestreo

Tf=10; %filtro derivativo 1/alpha
beta=0.5; %beta
der_r=0;   %parte derivativa no tiene peso en el valor deseado r

% Controlador discreto en paralelo, 2 grados de libertad

C_kaya_servo = tf(pidstd2(Kc_kaya_servo,Ti_kaya_servo,Td_kaya_servo,10,beta,der_r));
C_kaya_reg = tf(pidstd2(Kc_kaya_reg,Ti_kaya_reg,Td_kaya_reg,10,beta,der_r));

C_arrieta_servo = tf(pidstd2(Kc_arrieta_servo,Ti_arrieta_servo,Td_arrieta_servo,10,beta,der_r));
C_arrieta_reg = tf(pidstd2(Kc_arrieta_reg,Ti_arrieta_reg,Td_arrieta_reg,10,beta,der_r));

C_arrieta_pi_servo = tf(pidstd(Kc_arrieta_pi_servo,Ti_arrieta_pi_servo));
C_arrieta_pi_reg = tf(pidstd(Kc_arrieta_pi_reg,Ti_arrieta_pi_reg));

%%Controlador utilizado basado en PI regulatorio de Arrieta
C_final=tf(pidstd2(13.8191,1.9683,0.1,10,1,0));

%% Lazo abierto de control

L_kaya_servo=(C_kaya_servo(1))*H;
L_kaya_reg=(C_kaya_reg(1))*H;

L_arrieta_servo=(C_arrieta_servo(1))*H;
L_arrieta_reg=(C_arrieta_reg(1))*H;

L_arrieta_pi_servo=(C_arrieta_pi_servo)*H;
L_arrieta_pi_reg=(C_arrieta_pi_reg)*H;

L_final=(C_final(1))*H;

figure(2)
margin(L_final)
xlabel('Frecuencia');

figure(3)
rlocus(L_final)
title('');
xlabel(['Eje real','']);
ylabel('Eje imaginario');










