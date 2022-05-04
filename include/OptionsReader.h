#ifndef _OPTIONSREADER_H_
#define _OPTIONSREADER_H_
#pragma once

class OptionsReader {
protected:
	FILE *stream;
public:
	OptionsReader(FILE *in) { stream = in; }
	virtual ~OptionsReader() {}
	int virtual readOptions(Options &options);
};


#endif