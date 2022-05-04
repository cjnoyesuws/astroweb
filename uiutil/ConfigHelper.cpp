#include "astro.h"
#include "flags.h"
#include "useri.h"
#include "dataext.h"
#include "ConfigHelper.h"
#include <string.h>
#include <assert.h>

static entry progressed[3]={{"secondary",SECONDARY_PR}, {"tertiary",TERTIARY_PR}, {"minor",MINOR_PR}};
static entry rect[2]={{"solar",SOLARCHART},{"flat",FLATCHART}};
static entry charts[5]={{"natal",NATAL_CH},{"progressed",PROGR_CH},{"compatibility",COMPA_CH},{"transits",TRANS_CH},{"composite",COMPO_CH}};
static entry house[10] = {{"equal", EQUAL},{"koch",KOCH},{"placidus",PLACIDUS},{"m-house",M_HOUSE},{"companus",COMPANUS},
    {"regiomontanus",REGIOMONT},{"morinus",MORINUS},{"topocentric",TOPOCENTRIC},{"meridian",MERIDIAN},{"porphryryx",PORPHYRYX}};
static entry flags[8] = {{"default",DEFAULTFLGS},{"sidereal",SIDEREAL},{"houses",HOUSES},{"aspects",ASPECTS},{"extra-aspects", EXT_ASPECTS},
    {"vertext-eastpoint",VERT_EAST},{"rectify",NOBIRTHTIM},{"asteroids",ASTEROID}};


unsigned short ConfigHelper::parseFlags(char *text) {
    unsigned short flagsval= 0;
    int pos=0;
    char buf[40];

    memset(buf,0,40);

    if (strchr(text,'|')==0) {
        return (unsigned short)findEntry(text,flags,8);
    }

    for (int i = 0; i < strlen(text); i++) {
        if (text[i] != '|') {
            buf[pos++]=text[i];
        }
        else {
            buf[pos++]='\0';
            flagsval |= findEntry(buf,flags,8);
            pos=0;
        }
    }

    buf[pos++]='\0';
    flagsval |= findEntry(buf,flags,8);
    return flagsval;
}

short ConfigHelper::findHouses(char *text) {
    return findEntry(text,house,10);
}


short ConfigHelper::findRect(char *text) {
    return findEntry(text,rect,3);
}


short ConfigHelper::findProgressed(char *text) {
    return findEntry(text,progressed,3);
}


short ConfigHelper::findChartCode(char *text) {
    return findEntry(text,charts,5);
}

short ConfigHelper::findEntry(char *text, entry *entries, int count, int dflt) {
   assert(entries != 0);
   assert(text != 0);

   for (int i = 0;  i < count; i++ ) {
       if (stricmp(entries[i].label, text)==0) {
           return entries[i].value;
       }
   }
   return dflt;
}
