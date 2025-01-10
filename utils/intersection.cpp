bool isExistIntersection(Vec2 point1, Vec2 point2, int xSize, int ySize){
    bool xInClip;
    bool yInClip;
    if (point1.get(0) >= 0 && point1.get(0) < xSize){
        xInClip = true;
    }else{
        xInClip = false;
    }

    if (point2.get(0) >= 0 && point2.get(0) < ySize){
        yInClip = true;
    }else{
        yInClip = false;
    }

    return xInClip ^ yInClip; 
}
// Given three collinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Vec2 p, Vec2 q, Vec2 r) 
{ 
    if (q.get(0) <= std::max(p.get(0), r.get(0)) && q.get(0) >= std::min(p.get(0), r.get(0)) && 
        q.get(1) <= std::max(p.get(1), r.get(1)) && q.get(1) >= std::min(p.get(1), r.get(1))) 
       return true; 
  
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Vec2 p, Vec2 q, Vec2 r) 
{ 
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
    // for details of below formula. 
    int val = (q.get(1) - p.get(1)) * (r.get(0) - q.get(0)) - 
              (q.get(0) - p.get(0)) * (r.get(1) - q.get(1)); 
  
    if (val == 0) return 0;  // collinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  


  
//https://www.cs.ucr.edu/~eldawy/19SCS133/notes/line-line-intersection.pdf
// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool isLineIntersect(Vec2 point1, Vec2 point2, Vec2 point3, Vec2 point4){
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(point1, point2, point3); 
    int o2 = orientation(point1, point2, point4); 
    int o3 = orientation(point3, point4, point1); 
    int o4 = orientation(point3, point4, point2); 
    
    // General case: lines intersect if they have different
    // orientations
    /*if (o1 != o2 && o3 != o4) {
      
        // Compute intersection point
        double a1 = point2.get(1) - point1.get(1);
        double b1 = point1.get(0) - point2.get(0);
        double c1 = a1 * point1.get(0) + b1 * point1.get(1);

        double a2 = point4.get(1) - point3.get(1);
        double b2 = point3.get(0) - point4.get(0);
        double c2 = a2 * point3.get(0) + b2 * point3.get(1);

        double determinant = a1 * b2 - a2 * b1;

        if (determinant != 0) {
            std::cout << "\n";
            std::cout << "x: " << (c1 * b2 - c2 * b1) / determinant << std::endl;
            std::cout << " y: " << (a1 * c2 - a2 * c1) / determinant << std::endl;
            std::cout << "\n";

        }
    } */
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(point1, point3, point2)) return true; 
  
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(point1, point4, point2)) return true; 
  
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(point3, point1, point4)) return true; 
  
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(point3, point2, point4)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
}

bool isPointInsideClip(Vec2 point, int Xsize, int Ysize){
    if (point.get(0) < Xsize 
        && point.get(0) > 0 
        && point.get(1) < Ysize
        && point.get(1) > 0){
        return true;
    }
    return false;
}

Vec2 isLineIntersectPos(Vec2 point1, Vec2 point2, Vec2 point3, Vec2 point4){
    Vec2 intersect;

    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(point1, point2, point3); 
    int o2 = orientation(point1, point2, point4); 
    int o3 = orientation(point3, point4, point1); 
    int o4 = orientation(point3, point4, point2); 
    
    // General case: lines intersect if they have different
    // orientations
    if (o1 != o2 && o3 != o4) {
      
        // Compute intersection point
        double a1 = point2.get(1) - point1.get(1);
        double b1 = point1.get(0) - point2.get(0);
        double c1 = a1 * point1.get(0) + b1 * point1.get(1);

        double a2 = point4.get(1) - point3.get(1);
        double b2 = point3.get(0) - point4.get(0);
        double c2 = a2 * point3.get(0) + b2 * point3.get(1);

        double determinant = a1 * b2 - a2 * b1;

        if (determinant != 0) {
            intersect.set(0, (c1 * b2 - c2 * b1) / determinant);
            intersect.set(1, (a1 * c2 - a2 * c1) / determinant);

            /*std::cout << "\n";
            std::cout << "x: " << (c1 * b2 - c2 * b1) / determinant << std::endl;
            std::cout << " y: " << (a1 * c2 - a2 * c1) / determinant << std::endl;
            std::cout << "\n";*/
        }
    } 
    return intersect; 
}

