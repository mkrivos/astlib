///
/// \package astlib
/// \file benchmark.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13.4.2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///


var astlib = require('bindings')('addon.node');
const Utils = require('./asterix_utils.js');

Utils.declareAsterixCodes(astlib);

var asterixRecord = astlib.createAsterixRecord();
var codecs = astlib.enumerateAllCodecs();

var SIC = 44;
var SAC = 88;

function Model() 
{
    this.positionX = 0;
    this.positionY = 0;
    this.velocityX = 100,
    this.velocityY = 100;
    this.trackNumber = 0;
    this.callsign = "";
}

var ProfileTrack159 = {
    polarPosition: true,
    relativePosition: true,
    polarVelocity: false,
};

function Instance(trackNumber, callsign) {
    this.socketAddress = "localhost:50000";
    this.protocol = "Eurocontrol-159:2.0";
    this.profile = ProfileTrack159;
    this.record = astlib.createAsterixRecord();
    this.model = new Model();
    this.model.trackNumber = trackNumber;
    if (callsign)
        this.model.callsign = callsign;
}

function setPosition(profile, record, model) {    
    if (profile.relativePosition) {           
        if (profile.polarPosition) {
            range = model.positionX;
            azimuth = model.positionY;
            
            astlib.setNumber(record, TRACK_POSITION_RANGE, range);        
            astlib.setNumber(record, TRACK_POSITION_AZIMUTH, azimuth);
        } else {
            astlib.setNumber(record, TRACK_POSITION_X, model.positionX);        
            astlib.setNumber(record, TRACK_POSITION_Y, model.positionY);
        }
    } else {
        // WGS84
    }

    astlib.setNumber(record, TIMEOFDAY, Utils.secsAfterMidnight());
}

function setSourceId(profile, record, model) {   
    astlib.setNumber(record, DSI_SAC, SAC);
    astlib.setNumber(record, DSI_SIC, SIC);
}

function setFacility(profile, record, model) {
    astlib.setNumber(record, TRACK_NUMBER, model.trackNumber);
    astlib.setString(record, AIRCRAFT_ADDRESS, '23FFAA');
    astlib.setString(record, AIRCRAFT_IDENTIFICATION, 'PAKON321');

    astlib.setBoolean(record, MODE3A_V, true);
    astlib.setBoolean(record, MODE3A_G, true);
    astlib.setBoolean(record, MODE3A_L, true);
    astlib.setNumber(record, MODE3A_VALUE, 7777);
}

function setOther(profile, record, model) {
    astlib.setBoolean(record, TRACK_TEST, true);
    astlib.setBoolean(record, TRACK_SIMULATED, true);
}

function emitRecord(instance) {
    let profile = instance.profile;
    let record = instance.record;
    let model = instance.model;
    let protocol = instance.protocol;
    
    setSourceId(profile, record, model);
    setFacility(profile, record, model);
    setPosition(profile, record, model);
    setOther(profile, record, model);

    var buffer = astlib.encodeAsterixRecord(record, protocol);           
    console.log(astlib.toJson(record));
    console.log(buffer);
}

function fireOut(stations) {
    for(let i = 0; i < stations.length; i++) {
        let instance = stations[i];
        emitRecord(instance);
    }
}

var stations = [
    new Instance(1, "Jano"),
    new Instance(2, "Juro"),
];

stations[1].protocol = 'Eurocontrol-48:1.21';

setInterval(fireOut, 1000, stations);


