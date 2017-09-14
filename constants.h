#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

static const QString FR_EXTRUDE = "200";
static const QString DWELL = "1000";
static const QString Z_FEEDRATE = "400";

static const QString PETRI_Z_CACL2 = "2.5";
static const QString PETRI_Z_ALGINATE = "10";
static const QString PETRI_Z_ABTS = "10";

static const QString PLATE_Z_CACL2 = "10";      //change from 5        //to be changed. need to confirm values
static const QString PLATE_Z_ALGINATE = "12.5";
static const QString PLATE_Z_ABTS = "12.5";

static const QString FR_MOVE_XY = "6000";

static const int PLATE_XY_MOVE = 9;
static const QString PETRI_Z_MOVE = "5";
static const QString PLATE_Z_MOVE = "12";

static const QString EXTRUDE = "1";

static const QString ALG_EXT = "2.4";
static const QString ALG_EXT_REV = "0.8";
static const QString ALG_DWELL = "3000";

static const QString ABTS_EXT = "1.7";
static const QString ABTS_EXT_REV = "0.4";
static const QString FR_ABTS_EXT = "50";

static const QString DISH_HEIGHT = "25"; //given 10 mm clearance

static const QString COORD_1 = "30";
static const QString COORD_2 = "130";

static const QString PLATE_HEIGHT = "25";  //14.2mm height, given 10mm clearance
static const QString PLATE_START_X = "18.5";
static const QString PLATE_START_Y = "18";

static const int X_BORDER = 40;
static const int Y_BORDER = 40;
static const int DISH_DIAMETER = 100;

static const QString VERSION = "1.1.0";

static const QString PORTAL_LINK = "http://portal.se3d.com";
static const QString VISIT_LINK = "https://www.se3d.com/";
static const QString CONTACT_LINK = "https://www.se3d.com/connect";
static const QString SUPPLY_LINK = "https://google.com";

static const int OFFSET = 100;

#endif // CONSTANTS_H
