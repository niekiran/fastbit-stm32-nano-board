/***
  Note: Change the serial port COM number according to your setup (e.g., "COM6")
  ***/
import processing.serial.*;
import processing.opengl.*;
import toxi.geom.*;
import toxi.processing.*;

Serial port;                         /* The serial port */
char[] data_Packet = new char[3];    /* Data packet for 3D processing */

float yaw = 0, pitch = 0, roll = 0;

int i = 0;

PImage img;

void setup() {

  size(1080, 720, P3D);

  smooth();

  // Serial Port settings
  String portName = "COM6";
  // open the serial port
  port = new Serial(this, portName, 115200);

}

void draw() {

  background(0);
  translate(width / 2, height / 2);

  Read_Angles(port); // Read pitch, yaw, roll angle values

  rotateX(radians(-pitch));  // MPU6050 pitch movement = Processing X axes rotation
  rotateY(radians(yaw));     // MPU6050 yaw movement   = Processing Y axes rotation
  rotateZ(radians(-roll));   // MPU6050 roll movement  = Processing Z axes rotation

  myObject(4); // Select your object as 1, 2, 3, 4......

}

void myObject(int select) {

  switch (select) {
    case 1:
      // Red box
      fill(255, 0, 0, 200);
      box(300);
      break;

    case 2:
      // Green box
      fill(0, 255, 0, 200);
      box(250);
      break;

    case 3:
      // Blue rectangle
      fill(0, 0, 250, 200);
      box(300, 100, 200);
      break;

    case 4:
      // Plane structure
      // draw main body in red
      fill(255, 0, 0, 200);
      box(10, 10, 200);

      // draw front-facing tip in blue
      fill(0, 0, 255, 200);
      pushMatrix();
      translate(0, 0, -120);
      rotateX(PI / 2);
      drawCylinder(0, 20, 20, 8);
      popMatrix();

      // draw wings and tail fin in green
      fill(0, 255, 0, 200);
      beginShape(TRIANGLES);
      vertex(-100, 2, 30);
      vertex(0, 2, -80);
      vertex(100, 2, 30);  // wing top layer
      vertex(-100, -2, 30);
      vertex(0, -2, -80);
      vertex(100, -2, 30);  // wing bottom layer
      vertex(-2, 0, 98);
      vertex(-2, -30, 98);
      vertex(-2, 0, 70);  // tail left layer
      vertex(2, 0, 98);
      vertex(2, -30, 98);
      vertex(2, 0, 70);  // tail right layer
      endShape();
      beginShape(QUADS);
      vertex(-100, 2, 30);
      vertex(-100, -2, 30);
      vertex(0, -2, -80);
      vertex(0, 2, -80);
      vertex(100, 2, 30);
      vertex(100, -2, 30);
      vertex(0, -2, -80);
      vertex(0, 2, -80);
      vertex(-100, 2, 30);
      vertex(-100, -2, 30);
      vertex(100, -2, 30);
      vertex(100, 2, 30);
      vertex(-2, 0, 98);
      vertex(2, 0, 98);
      vertex(2, -30, 98);
      vertex(-2, -30, 98);
      vertex(-2, 0, 98);
      vertex(2, 0, 98);
      vertex(2, 0, 70);
      vertex(-2, 0, 70);
      vertex(-2, -30, 98);
      vertex(2, -30, 98);
      vertex(2, 0, 70);
      vertex(-2, 0, 70);
      endShape();
      break;
  }
}

void Read_Angles(Serial port) {
 
 while(port.available() > 0){
   
   String data = port.readString();
  
    if (data != null) {
   
    // Split the received data from serial buffer (MCU Stm32F4 side split_data = '#')
    float [] angle = float(split(data, "#")); 

    // Read angles data roll, pitch and yaw values
    roll  = angle[0];
    pitch = angle[1];
    yaw   = angle[2];
    
     // Print message all angle values
    println( "DataReceived:\t" + data + "\t\tRoll:\t" + roll + "\t\tPitch:\t" + pitch+ "\t\tYaw:\t" + yaw);
    }
    else return;
                                                      
  }
  
}

void propeller(float topRadius, float bottomRadius, float tall, int sides) {
    float angle = 0;
    float angleIncrement = TWO_PI / sides;
    beginShape(QUAD_STRIP);
    for (int i = 0; i < sides + 1; ++i) {
        vertex(topRadius*cos(angle), 0, topRadius*sin(angle));
        vertex(bottomRadius*cos(angle), tall, bottomRadius*sin(angle));
        angle += angleIncrement;        
    }
    endShape();
    
    // If it is not a cone, draw the circular top cap
    if (topRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
        
        // Center point
        vertex(0, 0, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(topRadius * cos(angle), 0, topRadius * sin(angle));
            angle += angleIncrement;         
        }
        endShape();
    }
  
    // If it is not a cone, draw the circular bottom cap
    if (bottomRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
    
        // Center point
        vertex(0, tall, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(bottomRadius * cos(angle), tall, bottomRadius * sin(angle));
            angle += angleIncrement;  
        }
        endShape();
    }
}

void drawCylinder(float topRadius, float bottomRadius, float tall, int sides) {
    float angle = 0;
    float angleIncrement = TWO_PI / sides;
    beginShape(QUAD_STRIP);
    for (int i = 0; i < sides + 1; ++i) {
        vertex(topRadius*cos(angle), 0, topRadius*sin(angle));
        vertex(bottomRadius*cos(angle), tall, bottomRadius*sin(angle));
        angle += angleIncrement;
    }
    endShape();
    
    // If it is not a cone, draw the circular top cap
    if (topRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
        
        // Center point
        vertex(0, 0, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(topRadius * cos(angle), 0, topRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }
  
    // If it is not a cone, draw the circular bottom cap
    if (bottomRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
    
        // Center point
        vertex(0, tall, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(bottomRadius * cos(angle), tall, bottomRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }
}
