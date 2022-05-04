#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H


class ProgramOptions
{
    public:
        /** Default constructor */
        ProgramOptions() {}
        ProgramOptions(int _argc, char **_argv) { argc=_argc; argv=_argv;}
        /** Default destructor */
        virtual ~ProgramOptions() {}
        /** Access format
         * \return The current value of format
         */
        char * getFormat() { return format; }
        /** Set format
         * \param val New value to set
         */
        void setFormat(char * val) { format = val; }
        /** Access type
         * \return The current value of type
         */
        char * getType() { return type; }
        /** Set type
         * \param val New value to set
         */
        void setType(char * val) { type = val; }
        /** Access datadir
         * \return The current value of datadir
         */
        char * getDatadir() { return datadir; }
        /** Set datadir
         * \param val New value to set
         */
        void setDataDir(char * val) { datadir = val; }
        /** Access input
         * \return The current value of input
         */
        char * GetInput() { return input; }
        /** Set input
         * \param val New value to set
         */
        void setInput(char * val) { input = val; }
        /** Access output
         * \return The current value of output
         */
        char * getOutput() { return output; }
        /** Set output
         * \param val New value to set
         */
        void setOutput(char * val) { output = val; }
        /** Access config
         * \return The current value of config
         */
        char * getConfig() { return config; }
        /** Set config
         * \param val New value to set
         */
        void setConfig(char * val) { config = val; }

        char * getErrorMessage() { return errorMessage; }

        int parse();
    protected:
    private:
        int argc;
        char **argv;
        char *errorMessage;
        char * format; //!< Member variable "format"
        char * type; //!< Member variable "type"
        char * datadir; //!< Member variable "datadir"
        char * input; //!< Member variable "input"
        char * output; //!< Member variable "output"
        char * config; //!< Member variable "config"
};

#endif // PROGRAMOPTIONS_H
