En este proyecto existen 3 comunicaciones, del APP a COM, de COM a APP y de COM a NAV, a continuación se muestra la estructua de pauetes empleada para esta comunicación:

 __ __    [*X|Y|P|S#]    __ __                   __ __
|     |  ------------>  |     |    [*X|Y|P#]    |     |
| APP |      [*A#]      | COM |  ------------>  | NAV |
|__ __|  <------------  |__ __|                 |__ __|

X: coordenada X joystick [0-100]
Y: coordenada X joystick [0-100]
P: potencia motores [0-100]
S: activar semillero [0-1]
A: sensor calidad de aire [0-100]
