int DATAMON_XPOS = 30,
    DATAMON_YPOS = 56,
    DATAMON_X_SPACING = 291,
    DATAMON_Y_SPACING = 235,
    DATAMON_W = 278,
    DATAMON_H = 170,
    MON_3D_X = 922,
    MON_3D_Y = 56,
    MON_3D_W = 488,
    MON_3D_H = 501,
    SERIALMON_X = 922,
    SERIALMON_Y = 602,
    SERIALMON_W = 488,
    SERIALMON_H = 265;
    
    
void setup(){
  size(1440,900,P3D);
  background(51,51,51);
}

void draw(){
    drawMonitors();
}

void drawMonitors(){
  // 9 Data Monitors
  fill(0);
  stroke(255);
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
      rect(DATAMON_XPOS + i*DATAMON_X_SPACING, 
           DATAMON_YPOS + j*DATAMON_Y_SPACING,
           DATAMON_W, DATAMON_H);
    }
  }
  rect(MON_3D_X,MON_3D_Y,MON_3D_W,MON_3D_H); // 3D Monitor
  rect(SERIALMON_X,SERIALMON_Y,SERIALMON_W,SERIALMON_H); // Serial Monitor
}
