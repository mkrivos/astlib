///
/// \package astlib
/// \file ast2json.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 9Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include <Poco/NumberParser.h>
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"
#include <iostream>
#include <sstream>

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;

class SampleApp: public Application
{
public:
    SampleApp() :
        _helpRequested(false)
    {
    }

protected:
    void initialize(Application& self)
    {
        loadConfiguration(); // load default configuration files, if present
        Application::initialize(self);
        // add your own initialization code here
    }

    void uninitialize()
    {
        // add your own uninitialization code here
        Application::uninitialize();
    }

    void reinitialize(Application& self)
    {
        Application::reinitialize(self);
        // add your own reinitialization code here
    }

    void defineOptions(OptionSet& options)
    {
        Application::defineOptions(options);

        options.addOption(Option("help", "h", "display help information on command line arguments").required(false).repeatable(false).callback(OptionCallback<SampleApp>(this, &SampleApp::handleHelp)));
        options.addOption(Option("config", "c", "load configuration data from a file").required(false).repeatable(false).argument("file").callback(OptionCallback<SampleApp>(this, &SampleApp::handleConfig)));
        options.addOption(Option("port", "p", "bind to UDP port").required(true).repeatable(false).argument("value").callback(OptionCallback<SampleApp>(this, &SampleApp::handlePort)));
    }

    void handleHelp(const std::string& name, const std::string& value)
    {
        _helpRequested = true;
        displayHelp();
        stopOptionsProcessing();
    }

    void handleConfig(const std::string& name, const std::string& value)
    {
        loadConfiguration(value);
    }

    void handlePort(const std::string& name, const std::string& port)
    {
        _port = Poco::NumberParser::parse(port);
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("Simple Asterix From Network To Json Decode & Display Application.");
        helpFormatter.format(std::cout);
    }

    void prepareDecoders()
    {

    }

    int main(const ArgVec& args)
    {
        if (!_helpRequested)
        {
            prepareDecoders();
            logger().information("Listening on udp port %d", _port);
        }
        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
    int _port = 10000;
};

POCO_APP_MAIN(SampleApp)

