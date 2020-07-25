#include "app.h"

App app = App();

void setup(){
    app.setup();
    app.info();
    Serial.println("------------------ Ready -------------------------------------- ");
}
void loop(){
    app.loop();
}