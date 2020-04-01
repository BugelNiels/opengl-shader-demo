# OpenGL

The main thing of this submission is the metallic shader. 
Might add more stuff to this in the future.

The shader is composed of the following:
- The shader uses a specular map to determine the roughness and amount of reflection.
- Reflections are based on a cube map
- A normal map to alter the normals to get some smaller details showing
- A Fresnel like mix factor to make the edges more reflective

# Disclaimer

The code quality is extremely mediocre, since I started a bit late and had to take some shortcuts.

# Replicating the images
In order to replicate the images, run the code in QtCreator, select the object and set the shader to metallic.

You can move around using WASD. Rotating the camera left and right can be done using Q and E.
You can rotate the object along the y axis by dragging the mouse.

If you want a fancier looking texture, click filter options. 
Once that menu opens, set the magnifying method to GL_LINEAR and the minifying method to GL_LINEAR_MIPMAP_LINEAR

# Images

The images can also be found in the screenshots folder

# Extra 

If you want to see the wireframe of the object, press Z.
You should also be able to change the cube map to a different one by changing "lake" to "river" on line 23 of scene_initialisation.cpp


# Resources

The object was taken from sketchfab: https://sketchfab.com/3d-models/uruk-hai-lowpoly-helmet-ab00c959688a41e0a750d9ff3221ffe9 and adjusted slightly in Blender.
Textures were taken from https://www.textures.com/download/pbr0585/138834 and adjusted in GIMP.
Cubemap texture was taken from http://www.humus.name/index.php?page=Textures&start=8 and adjusted in Gimp