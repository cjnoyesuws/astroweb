#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "ConfigHelper.h"
#include "DataReader.h"
#include <assert.h>
#include "errors.fns"
#include "cJSON.h"
#include "setup.hpp"
#include "JsonDataReader.h"
#include "OptionsReader.h"
#include "JsonOptionsReader.h"


int JsonDataReader::readData() {
	int type = 0;
	if (loadJson()==1) {
	   return 1;
	}
	pJsonSub = pJson->child;
	if (pJsonSub->type != cJSON_Object) {
		error_message("Invalid Json, Expecting Object, key: %s", pJsonSub->string);
		return 1;
	}
	do {
		strncpy(section, pJsonSub->string,34);
	    if (strcmp("Birth",section)==0) {
				type=readBirth(birth_rec.birth_data);
			}
			else if (strcmp("Comp",section)==0) {
				type=readBirth(comp_rec.birth_data);
			}
			else if (strcmp("Trans",section)==0) {
				type=readBirth(trans_rec.birth_data);
			}
			else if (strcmp("BirthRect",section)==0) {
				type=readRect(birth_rectd);
			}
			else if (strcmp("CompRect",section)==0) {
				type=readRect(comp_rectd);
			}
			else if (strcmp("TransData",section)==0) {
				type=readTrans(transit_data);
			}
			else if (strcmp("ProgrData",section)==0) {
				type=readProg(progress_data);
			}
			else {
				error_message("Unknown %s\n", section);
				return(2);
			}

		pJsonSub  = pJsonSub->child;
	}   while (pJsonSub != 0);
	return 0;
}

int JsonDataReader::loadJson() {
	if (stream != NULL) {
        inbuf = new char[10000];
        char *line = new char[500];
        char *read=NULL;

        inbuf[0] = '\0';

        while ((read=fgets(line, 499, stream)) != NULL) {
            strcat(inbuf,read);
        }
        if (ferror(stream)) {
            delete line;
            return 1;
        }
	}
	else if (inbuf == 0 || strlen(inbuf)==0) {
	   return 1;
	}

	pJson = cJSON_Parse((const char *)inbuf);
	if (pJson==0) {
		error_message("Error Parsing Json");
		return 1;
	}
	else if (pJson->type != cJSON_Object) {
		error_message("Invalid Json Expecting Object");
		return 1;
	}
    return 0;
}

cJSON *JsonDataReader::getSubObject(const char *key) {
	cJSON *val = cJSON_GetObjectItem(pJson,key);
	if (val ==0) {
	   return 0;
	}
	if (val->type != cJSON_Object) {
	    error_message("Invalid Json, Expecting Object key; %s", key);
		return 0;
	}
	pJsonSub = val;
	pChild = val->child;
	return val;
}

int JsonDataReader::readLine() {
	if (pChild == 0) {
	   return SECTION_RD;
	}
	pChild = pChild->child;
	if (pChild == 0) {
	   return SECTION_RD;
	}
    strncpy(key,pChild->string,34);
	switch (pChild->type) {
		case cJSON_String:
			strncpy(value,pChild->valuestring,99);
			break;
		case cJSON_NULL:
			strcpy(value,"");
			break;
		case cJSON_True:
			strcpy(value,"1");
			break;
		case cJSON_False:
			strcpy(value,"0");
			break;
		case cJSON_Number:
		    if (pChild->valuedouble != (double)pChild->valueint) {
			   sprintf(value,"%d", pChild->valuedouble);
		    }
		    else {
               sprintf(value,"%d", pChild->valueint);
		    }
			break;
        case cJSON_Object:
            if (strcmp(key,"config")==0) {
                if (pOptions != 0) {
                    JsonOptionsReader *rdr = new JsonOptionsReader(pChild->child);
                    int val =rdr->readOptions(*pOptions);
                    if (val != 0) {
                        error_message("problem reading config");
                    }
                    delete rdr;
                }
                else {
                    error_message("Options* needs to be non-null");
                }
            }
            else {
               error_message("Unexpected Object or Array, key: %s", pChild->string);
            }
            break;
		default:
			error_message("Unexpected Object or Array, key: %s", pChild->string);
			break;
	}
	return VARIABLE_RD;
}
