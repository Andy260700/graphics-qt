# graphics-qt
basic graphics project on Qt

GUI application developed in Qt based on rastor graphics.
The application allows users to 

1. Draw lines by selecting 2 end points.
2. Draw custom circles by denoting the center and mentioning radius
3. Draw custom ellipse by denoting the center and the lengths of semi major and semi minor axes
4. Draw custom polygons by selecting vertices in order
5. Color fill by clicking inside enclosed area
6. Perform transformations like scaling, translating, rotating, shearing and reflecting on a rastor image.

The project includes the implementations of the following algorithms.

1. Bresenham and DDA for line drawing.
2. Bresenham and midpoint for circle drawing with eight point symmetry.
3. Bresenham and midpoint for ellipse drawing with four point symmetry.
4. Polar circle and ellipse drawing algorithm.
5. Boundary fill, flood fill and other seed fill algorithms for color filling.
6. scanline color filling algorithm.
7. polygon drawing and transformations using matrix multiplication.
