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


step(H,Haprox)
title('');
xlabel(['Tiempo (s)']);
ylabel('Respuesta al impulso');
legend('Modelo segundo orden','Aproximación POMTM','Location','east');

%% Controlador

%Metodo de Arrieta

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

Kc_arrieta=(a+b*((tm/tau)^c))/Kp;
Ti_arrieta=(d+e*((tm/tau)^f))*tau;
Td_arrieta=(g+h*((tm/tau)^i))*tau;

% Metodo de Kaya y Scheib para minimizar IAE en funcion de servo control
Kc_kaya=(0.65/Kp)*(tau/tm)^1.04;
Ti_kaya=tau/(0.99+0.10*(tm/tau));
Td_kaya=0.51*tau*(tm/tau)^1.08;


%% Implementación lazo cerrado de control

Ts=0.1; % Tiempo de muestreo

%Ganancias derivativas e integrales
Ki_arrieta=Kc_arrieta/Ti_arrieta; 
Kd_arrieta=Td_arrieta*Kc_arrieta;
Ki_kaya=Kc_kaya/Ti_kaya;
Kd_kaya=Td_kaya*Kc_kaya;

Tf=10; %filtro derivativo 1/alpha
b=0.5; %beta
c=0;   %parte derivativa no tiene peso en el valor deseado r

% Controlador discreto en paralelo, 2 grados de libertad
C_arrieta=pid2(Kc_arrieta,Ki_arrieta,Kd_arrieta,Tf,b,c,Ts);
C_kaya=pid2(Kc_kaya,Ki_kaya,Kd_kaya,Tf,b,c,Ts);

%Equivalente retenedor-planta ERP
Hs=H/s; 
Hz=c2d(Hs,Ts);
z=tf('z',Ts);
%Hz=Hz*z^(-0.4/Ts); %Usar esta linea si hay que agregar tiempo muerto
Gz=(1-(1/z))*Hz;

%Lazo cerrado de control
%sys=(Gz.*C_arrieta,Ts))/(1+Gz.*C_arrieta,Ts));

C2tf_arrieta = tf(C_arrieta);
Cr_arrieta = C2tf_arrieta(1);
Cy_arrieta = C2tf_arrieta(2);

C2tf_kaya = tf(C_kaya);
Cr_kaya = C2tf_kaya(1);
Cy_kaya = C2tf_kaya(2);












