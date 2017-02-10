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

#include "astlib/BinaryAsterixDekoder.h"
#include "astlib/CodecRegister.h"
#include "astlib/Exception.h"

#include <Poco/NumberParser.h>
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"

#include "Poco/Net/Net.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"

#include "Poco/JSON/JSON.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/JSONException.h"

#include <iostream>
#include <sstream>

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;
using Poco::Net::Socket;
using Poco::Net::DatagramSocket;
using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;


class SampleApp: public Application
{
public:
    SampleApp() :
        _helpRequested(false)
    {
    }

    class MyValueDecoder :
        public astlib::TypedValueDecoder
    {
        Poco::JSON::Object::Ptr json;
        Poco::JSON::Object::Ptr item;
        Poco::JSON::Array::Ptr localArray;

        virtual void begin()
        {
            json = new Poco::JSON::Object();
            //json->set("message", "ast");
        }
        virtual void dataItem(const astlib::ItemDescription& uapItem)
        {
            item = new Poco::JSON::Object();
            json->set(uapItem.getDescription(), item);
        }
        virtual void repetitive(int index)
        {
            std::cout << " [" << index << "]" << std::endl;
        }
#if 0
        virtual void decode(Poco::UInt64 value, const astlib::ValueDecoder::Context& ctx)
        {
        }
#endif
        virtual void decodeBoolean(const std::string& identification, bool value)
        {
            item->set(identification, Poco::Dynamic::Var(value));
        }
        virtual void decodeSigned(const std::string& identification, Poco::Int64 value)
        {
            item->set(identification, Poco::Dynamic::Var(value));
        }
        virtual void decodeUnsigned(const std::string& identification, Poco::UInt64 value)
        {
            item->set(identification, Poco::Dynamic::Var(value));
        }
        virtual void decodeReal(const std::string& identification, double value)
        {
            item->set(identification, Poco::Dynamic::Var(value));
        }
        virtual void decodeString(const std::string& identification, const std::string& value)
        {
            item->set(identification, Poco::Dynamic::Var(value));
        }
        virtual void end()
        {
            json->stringify(std::cout, 2);
            std::cout << std::endl;
            json = nullptr;
            item = nullptr;
        }
    } decoderHandler;

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
        astlib::CodecRegister codecRegister;
        codecRegister.populateCodecsFromDirectory("specs");
        auto codecs = codecRegister.enumerateCodecsByCategory();

        for(auto codec: codecs)
        {
            logger().information("registering %s", codec->getCategoryDescription().toString());
            _codecs[codec->getCategoryDescription().getCategory()] = codec;
        }
    }

    int main(const ArgVec& args)
    {
        if (!_helpRequested)
        {
            try
            {
                prepareDecoders();

                _socket.bind(SocketAddress(_port), true);
                logger().information("Listening on udp port %d", _port);

                Poco::Timespan span(250000);
                while (!_stop)
                {
                    if (_socket.poll(span, Socket::SELECT_READ))
                    {
                        try
                        {
                            astlib::Byte buffer[astlib::BinaryAsterixDekoder::MAX_PACKET_SIZE];
                            SocketAddress sender;
                            int bytes = _socket.receiveFrom(buffer, sizeof(buffer), sender);

                            if (bytes > 0)
                            {
                                //logger().information("received %d bytes", bytes);

                                int category = buffer[0];
                                auto codec = _codecs[category];
                                if (codec)
                                {
                                    _decoder.decode(*codec, decoderHandler, buffer, bytes);
                                }
                            }
                        }
                        catch (Poco::Exception& exc)
                        {
                            std::cerr << "ast2json: " << exc.displayText() << std::endl;
                        }
                    }
                }
            }
            catch(astlib::Exception& e)
            {
                logger().error(e.displayText());
                return Application::EXIT_OK;
            }
        }
        return Application::EXIT_OK;
    }

private:
    std::map<int, astlib::CodecDescriptionPtr> _codecs;
    astlib::BinaryAsterixDekoder _decoder;
    Poco::Net::DatagramSocket _socket;
    int _port = 10000;
    bool _helpRequested;
    bool _stop = false;
};

POCO_APP_MAIN(SampleApp)

