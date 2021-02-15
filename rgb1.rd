Display "RGB Color Cube" "Screen" "rgbdouble"


Background 0.4 0.6 0.8

ObjectBegin "ColorCube"

Rotate "X" 54.74
Rotate "Z" 45.0

PolySet "PC"
8 6

-1.0 -1.0 -1.0  0.0 0.0 0.0  # Black
 1.0 -1.0 -1.0  1.0 0.0 0.0  # Red
 1.0  1.0 -1.0  1.0 1.0 0.0  # Yellow
-1.0  1.0 -1.0  0.0 1.0 0.0  # Green
-1.0 -1.0  1.0  0.0 0.0 1.0  # Blue
 1.0 -1.0  1.0  1.0 0.0 1.0  # Magenta
 1.0  1.0  1.0  1.0 1.0 1.0  # White
-1.0  1.0  1.0  0.0 1.0 1.0  # Cyan

0 3 2 1 -1
4 5 6 7 -1
3 7 6 2 -1
1 5 6 2 -1
0 4 7 3 -1
0 1 5 4 -1

ObjectEnd

CameraFOV  20.0
CameraAt 0.0 0.0 0.0
CameraEye 0.0 -30.0 0.0
CameraUp 0.0 0.0 1.0

WorldBegin

XformPush
Translate 2.0  0.0 3.464
ObjectInstance "ColorCube"
XformPop

XformPush
Translate 4.0  0.0 0.0
Rotate "Z" 60.0
ObjectInstance "ColorCube"
XformPop

XformPush
Translate 2.0  0.0 -3.464
Rotate "Z" 120.0
ObjectInstance "ColorCube"
XformPop

XformPush
Translate -2.0  0.0 -3.464
Rotate "Z" 180.0
ObjectInstance "ColorCube"
XformPop

XformPush
Translate -4.0  0.0 0.0
Rotate "Z" 240.0
ObjectInstance "ColorCube"
XformPop

XformPush
Translate -2.0  0.0 3.464
Rotate "Z" 300.0
ObjectInstance "ColorCube"
XformPop


WorldEnd
