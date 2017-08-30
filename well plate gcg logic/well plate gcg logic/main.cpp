#include <iostream>
using namespace std;

static const string FR_EXTRUDE = "200";
static const string DWELL = "1000";
static const string Z_FEEDRATE = "400";

static const string PETRI_Z_CACL2 = "2.5";
static const string PETRI_Z_ALGINATE = "10";
static const string PETRI_Z_ABTS = "10";

static const string PLATE_Z_CACL2 = "5";            //to be changed. need to confirm values
static const string PLATE_Z_ALGINATE = "12.5";
static const string PLATE_Z_ABTS = "12.5";

static const string FR_MOVE_XY = "6000";

static const int PLATE_XY_MOVE = 9;
static const string PETRI_Z_MOVE = "5";
static const string PLATE_Z_MOVE = "10";  //need to confirm or calculate after ^^^^^^^

static const string EXTRUDE = "1";

static const string ALG_EXT = "2.4";
static const string ALG_EXT_REV = "0.8";
static const string ALG_DWELL = "3000";

static const string ABTS_EXT = "1.7";
static const string ABTS_EXT_REV = "0.4";
static const string FR_ABTS_EXT = "50";

static const string DISH_HEIGHT = "25"; //given 10 mm clearance

static const string COORD_1 = "30";
static const string COORD_2 = "130";

static const string PLATE_HEIGHT = "25";  //14.2mm height, given 10mm clearance
static const string PLATE_START_X = "18.5";
static const string PLATE_START_Y = "18";


//petri dish dims
static const int X_BORDER = 40;
static const int Y_BORDER = 40;
static const int DISH_DIAMETER = 100;



//to be removed
static const int widthInput = 3;
static const int heightInput = 3;
static const int materialInput = 0;
static const string nameInput = "Brendan";
static const int printType = 1;
static const string monthString = "08";
static const string dayString = "30";
static const string yearString = "2017";
static const int positionInput = -1;







int main(int argc, const char * argv[]) {

    int calc;
    
    string output; //remove later bc class var in wizard
    
    string materialString; //remove later
    switch(materialInput)
    {
        case 0:
            materialString =  "CaCl2";
            break;
        case 1:
            materialString = "HPR";
            break;
        case 2:
            materialString =  "ABTS";
            break;
    }
    
    output = "";
    
    //G-Code commented confirmation of inputs
    if (nameInput != "")
        output += "(Name: " + nameInput + ")\n";
    
    
    output += "(Type: Well Plate)\n";
    output += "(Material: " + materialString + ")\n";
    output += "(Size: " + QString::number(widthInput) + "x" + QString::number(heightInput) + ")\n";
    output += "(Date: " + monthString + "/" + dayString + "/" + yearString + ")\n\n";
    
    
    //Begin building gcode
    output += "G90\n";
    output += "G1 Z" + PLATE_HEIGHT + " F1000\n";
    output += "G1 X" + PLATE_START_X + " Y" + PLATE_START_Y + " F" + FR_MOVE_XY + "\n";

    switch(materialInput)
    {
        case 0:
            //Calcium Carbonate
            output += "G1 Z" + PLATE_Z_CACL2 + " F1000\n";
            break;
        case 1:
            //HPR
            output += "G1 Z" + PLATE_Z_ALGINATE + " F1000\n";
            break;
        case 2:
            //ABTS
            output += "G1 Z" + PLATE_Z_ABTS + " F1000\n";
            break;
    }
    
    //Relative positioning start
    output += "\nG91\n\n";
    
    switch(materialInput)
    {
            //CaCl2 print
        case 0:
            for (int row = 0; row < heightInput; row++)
            {
                for (int col = 0; col < (widthInput - 1); col++)
                {
                    output += "G1 E" + EXTRUDE + " F" + FR_EXTRUDE + "\n";
                    output += "G4 P" + DWELL + "\n";
                    output += "G1 Z" + PLATE_Z_MOVE + " F" + Z_FEEDRATE + "\n";
                    
                    calc = row % 2 ? -1 : 1;
                    calc *= PLATE_XY_MOVE;
                    QString temp  = QString::number(calc);
                    
                    output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n";
                    output += "G1 Z-" + PLATE_Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
                }
                output += "G1 E" + EXTRUDE + " F" + FR_EXTRUDE + "\n";
                output += "G4 P" + DWELL + "\n";
                output += "G1 Z" + PLATE_Z_MOVE + " F" + Z_FEEDRATE + "\n";
                
                if (row < heightInput - 1)
                {
                    output += "G1 Y" + QString::number(PLATE_XY_MOVE) + " F" + FR_MOVE_XY + "\n";
                    output += "G1 Z-" + PLATE_Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
                }
                else
                    output += "\n\n";
            }
            output += "G90\n";
            output += "G1 Z" + DISH_HEIGHT + " F1000\n";
            output += "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
            output += "G1 X100 Y10 F6000\n";
            output += "M84\n";
            break;
            
            // 1% HPR Alginate Mixture
        case 1:
            for (int row = 0; row < heightInput; row++)
            {
                for (int col = 0; col < (widthInput - 1); col++)
                {
                    output += "G1 E" + ALG_EXT + " F" + FR_EXTRUDE + "\n";
                    output += "G1 E-" + ALG_EXT_REV + " F" + FR_EXTRUDE + "\n";
                    output += "G4 P" + ALG_DWELL + "\n";
                    
                    calc = row % 2 ? -1 : 1;
                    calc *= PLATE_XY_MOVE;
                    QString temp = QString::number(calc);
                    
                    output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n\n";
                }
                output += "G1 E" + ALG_EXT + " F" + FR_EXTRUDE + "\n";
                output +=  "G1 E-" + ALG_EXT_REV + " F" + FR_EXTRUDE + "\n";
                output += "G4 P" + ALG_DWELL + "\n";
                
                if (row < heightInput - 1)
                    output += "G1 Y" + QString(PLATE_XY_MOVE) + " F" + FR_MOVE_XY + "\n\n";
                else
                    output += "\n\n";
            }
            output += "G90\n";
            output += "G1 Z" + DISH_HEIGHT + " F1000\n";
            output += "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
            output += "G1 X100 Y10 F6000\n";
            output += "M84\n";
            break;
            
            //ABTS Substrate -- assay print
        case 2:
            for (int row = 0; row < heightInput; row++)
            {
                for (int col = 0; col < (widthInput - 1); col++)
                {
                    output += "G1 E" + ABTS_EXT + " F" + FR_EXTRUDE + "\n";
                    output += "G1 E-" + ABTS_EXT_REV + " F" + FR_ABTS_EXT + "\n";
                    output += "G4 P" + DWELL + "\n";
                    
                    calc = row % 2 ? -1 : 1;
                    calc *= PLATE_XY_MOVE;
                    QString temp = QString::number(calc);
                    
                    output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n\n";
                }
                output += "G1 E " + ABTS_EXT + " F " + FR_EXTRUDE + "\n";
                output += "G1 E-" + ABTS_EXT_REV + " F" + FR_ABTS_EXT + "\n";
                output += "G4 P" + DWELL + "\n";
                
                if (row < heightInput - 1)
                    output += "G1 Y" + QString(PLATE_XY_MOVE) + " F" + FR_MOVE_XY + "\n\n";
                else
                    output += "\n\n";
            }
            break;
    }
    
    
    
    
    emit emitOutput(output);




}
