# QtLearning
Exercises from Graphics And Multimedia Labs about all kind of algorithms connected to paiting/drawing shapes on computer's screen
The project has 4 sections: 
- Curves, 
- QtLearning, 
- ModeleBarw (in Engilsh color Palette RGB, HSV),
- BlendModes

***
### CURVES
The curves is about B-spline curve and Bezier curve. User of this simple program can chose certain points and it will be drawn 
a curve depends of points. User can also delete points and change their position.

#### B-spline curve:
![B-Spline](http://www-users.mat.umk.pl/~marcinbedcyc/images/bSpline.png)
#### Bezier curve:
![Bezier](http://www-users.mat.umk.pl/~marcinbedcyc/images/bezier.png)

***
### MODELE BARW
modeleBarw is about conversion pixels' colors from RGB to HSV and from HSV to RGB. User can change every channel (H, S ,V).
It has impact on image's result.

#### Original image:
![Orginal night](http://www-users.mat.umk.pl/~marcinbedcyc/images/night.jpg)
#### After chanels' change:
![After change](http://www-users.mat.umk.pl/~marcinbedcyc/images/colorPallete.png)

***
### QTLEARNING
QtLearning is about:
- Drawing basic shapes like circles, elipses, rectagles, rectagles' frames, paiting with sprays,
- FloodFill algorithm which flood shapes with color chosen by user, 
- ScanLine algorithm which draws irregular polygons,
user chose points, connection between pairs creates edge, then it fills inside of shape with color using scanLine algorithm(liny by line), 
- Morphology operations e.g dilation, erosion.


#### Drawing shapes:
![Drawing](http://www-users.mat.umk.pl/~marcinbedcyc/images/drawing.png)

#### Flood fill algorithm:
![Flood fill](http://www-users.mat.umk.pl/~marcinbedcyc/images/floodFill.png)

#### Scan line:
![Scan line](http://www-users.mat.umk.pl/~marcinbedcyc/images/scanLine.png)

#### Morphology Operations:
![Morphology](http://www-users.mat.umk.pl/~marcinbedcyc/images/morphology.png)

***
### BLENDMODES
Blend modes project is about mixing layers using blend modes. I use modes like normal, average, multiply, darken, lighten, screen. 
Program is easy expandable with new blend functions. There are 3 permanently chosen images as layers, they have the same dimension (each width and height of images are the same)
to make code easier to write and rather focus on blend modes than on user's interface and scalability of image.

#### Example of mix:
![BlendMode](http://www-users.mat.umk.pl/~marcinbedcyc/images/blendModes.png)

#### Layers 0:
![Layers0](http://www-users.mat.umk.pl/~marcinbedcyc/images/gradient.png)

#### Layers 1:
![Layers1](http://www-users.mat.umk.pl/~marcinbedcyc/images/plaza.png)

#### Layers 2:
![Layers2](http://www-users.mat.umk.pl/~marcinbedcyc/images/zamek.png)
