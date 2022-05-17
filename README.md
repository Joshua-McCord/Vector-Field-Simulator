# Vector Field Simulator
Vector Field Simulator written in C++ and OpenGL. <br> 
The simulator contains 10 different vector field functions, three different solvers, and supports velocity based coloring of the vectors. 
## Available Functions, Mappings, and Controls
(some visibility issues may arise with dark theme) <br> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[1]=f(x,y,z)=<x^2+y^2,2xy,z>"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[2]=f(x,y,z)=<y,-x+y,z>" /> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[3]=f(x,y,z)=<-x,-y,z>" /> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[4]=f(x,y,z)=<0,x^2,z>"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[5]=f(x,y,z)=<x,y,z>"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[6]=f(x,y,z)=<y-x,-x-y,z>"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[7]=f(x,y,z)=<-y,x,z>"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[8]=f(x,y,z)=<2x,-y,z>"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[9]=f(x,y,z)=<y,x,z>"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[0]=f(x,y,z)=<x^2,y^2,z>"/> <br>

<img src="https://latex.codecogs.com/svg.latex?\Large&space;[\leftarrow]=\text{Euler}" title="\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[\uparrow]=\text{Midpoint}" title="\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}"/> <br>
<img src="https://latex.codecogs.com/svg.latex?\Large&space;[\rightarrow]=4^{th}\:\text{Order}\:\text{Runge-Kutta}" title="\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}"/> <br>

## Euler vs. RK4
<p float="left">
<img src="https://github.com/Joshua-McCord/Vector-Field-Simulator/blob/master/euler_instability_gif.gif"  style="border:20px;margin:0px;float:left;width:400px;" />
<img src="https://github.com/Joshua-McCord/Vector-Field-Simulator/blob/master/rk4_instability.gif" style="border:20px;margin:0px;float:left;width:400px;"/>
</p>
To compare the difference between Euler and RK4, there is a vector field that is perfect for testing the stability. 
In the two GIFs above, you can see the differences between the stability of Euler (left) and RK4 (right). 
The simulator is being run on <i>f(x,y,z)=<-y,x,z></i> with a step size <i>h=0.05</i>. 
Because of Euler's smaller convergence rate, RK4 will spiral out at a much slower rate than Euler.  
