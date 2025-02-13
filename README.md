# RayTracer
### Write up portion
#### 1. The up vector affects the result of the image by rotating the image. For instance, if the up vector is pointing towards the x-axis instead of the y-axis then the image will appear rotated by 90 degrees. This is assuming the viewing direction is not parallel to the up vector. If we change the coordinate of the up vector to tilt it towards or away from the viewing direction, nothing changes until the 2 vectors become parallel.

#### 2. The vertical field of view affects how zoomed in the image appears. The larger the field of view, the more zoomed-out the image appears; the smaller the field of view, the more it appears to be zoomed-in. The horizontal field of view doesn't scale linearly with the vertical field of view, meaning that if the aspect ratio is n:1 then the horizontal field of view is not n * vertical field of view.  

#### 3 The more drastic the viewing direction changes the more warped the image becomes. Points closer to the center are shown up to scale while points closer to the edges of the image window appear to be stretched. The up vector as said before, determines the rotation of the image. The vertical field of view affects how zoomed in it is.


### How to run
#### just type 
```make```
#### and it will compile everything needed. and run it by typing 
```make run```

#### to quit the program just type q and press enter.
