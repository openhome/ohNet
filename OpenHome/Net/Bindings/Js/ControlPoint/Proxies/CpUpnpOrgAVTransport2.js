 

/**
* Service Proxy for CpProxySchemasUpnpOrgAVTransport2
* @module ohnet
* @class AVTransport
*/
    
var CpProxySchemasUpnpOrgAVTransport2 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-AVTransport-2/control";  // upnp control url
    this.domain = "schemas-upnp-org";
    this.type = "AVTransport";
    this.version = "2";
    this.serviceName = "upnp.org-AVTransport-2";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["LastChange"] = new ohnet.serviceproperty("LastChange","string");
    this.serviceProperties["DRMState"] = new ohnet.serviceproperty("DRMState","string");

                  
    this.DRMStateAllowedValues = [];
    this.DRMStateAllowedValues.push("OK");
    this.DRMStateAllowedValues.push("UNKNOWN");
    this.DRMStateAllowedValues.push("PROCESSING_CONTENT_KEY");
    this.DRMStateAllowedValues.push("CONTENT_KEY_FAILURE");
    this.DRMStateAllowedValues.push("ATTEMPTING_AUTHENTICATION");
    this.DRMStateAllowedValues.push("FAILED_AUTHENTICATION");
    this.DRMStateAllowedValues.push("NOT_AUTHENTICATED");
    this.DRMStateAllowedValues.push("DEVICE_REVOCATION");

}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "LastChange" property change events
* @method LastChange_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.LastChange_Changed = function (stateChangedFunction) {
    this.serviceProperties.LastChange.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "DRMState" property change events
* @method DRMState_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.DRMState_Changed = function (stateChangedFunction) {
    this.serviceProperties.DRMState.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}


/**
* A service action to SetAVTransportURI
* @method SetAVTransportURI
* @param {Int} InstanceID An action parameter
* @param {String} CurrentURI An action parameter
* @param {String} CurrentURIMetaData An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.SetAVTransportURI = function(InstanceID, CurrentURI, CurrentURIMetaData, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetAVTransportURI", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("CurrentURI", CurrentURI);
    request.writeStringParameter("CurrentURIMetaData", CurrentURIMetaData);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetNextAVTransportURI
* @method SetNextAVTransportURI
* @param {Int} InstanceID An action parameter
* @param {String} NextURI An action parameter
* @param {String} NextURIMetaData An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.SetNextAVTransportURI = function(InstanceID, NextURI, NextURIMetaData, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetNextAVTransportURI", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("NextURI", NextURI);
    request.writeStringParameter("NextURIMetaData", NextURIMetaData);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetMediaInfo
* @method GetMediaInfo
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetMediaInfo = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetMediaInfo", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["NrTracks"] = ohnet.soaprequest.readIntParameter(result["NrTracks"]); 
        result["MediaDuration"] = ohnet.soaprequest.readStringParameter(result["MediaDuration"]); 
        result["CurrentURI"] = ohnet.soaprequest.readStringParameter(result["CurrentURI"]); 
        result["CurrentURIMetaData"] = ohnet.soaprequest.readStringParameter(result["CurrentURIMetaData"]); 
        result["NextURI"] = ohnet.soaprequest.readStringParameter(result["NextURI"]); 
        result["NextURIMetaData"] = ohnet.soaprequest.readStringParameter(result["NextURIMetaData"]); 
        result["PlayMedium"] = ohnet.soaprequest.readStringParameter(result["PlayMedium"]); 
        result["RecordMedium"] = ohnet.soaprequest.readStringParameter(result["RecordMedium"]); 
        result["WriteStatus"] = ohnet.soaprequest.readStringParameter(result["WriteStatus"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetMediaInfo_Ext
* @method GetMediaInfo_Ext
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetMediaInfo_Ext = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetMediaInfo_Ext", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentType"] = ohnet.soaprequest.readStringParameter(result["CurrentType"]); 
        result["NrTracks"] = ohnet.soaprequest.readIntParameter(result["NrTracks"]); 
        result["MediaDuration"] = ohnet.soaprequest.readStringParameter(result["MediaDuration"]); 
        result["CurrentURI"] = ohnet.soaprequest.readStringParameter(result["CurrentURI"]); 
        result["CurrentURIMetaData"] = ohnet.soaprequest.readStringParameter(result["CurrentURIMetaData"]); 
        result["NextURI"] = ohnet.soaprequest.readStringParameter(result["NextURI"]); 
        result["NextURIMetaData"] = ohnet.soaprequest.readStringParameter(result["NextURIMetaData"]); 
        result["PlayMedium"] = ohnet.soaprequest.readStringParameter(result["PlayMedium"]); 
        result["RecordMedium"] = ohnet.soaprequest.readStringParameter(result["RecordMedium"]); 
        result["WriteStatus"] = ohnet.soaprequest.readStringParameter(result["WriteStatus"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetTransportInfo
* @method GetTransportInfo
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetTransportInfo = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetTransportInfo", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentTransportState"] = ohnet.soaprequest.readStringParameter(result["CurrentTransportState"]); 
        result["CurrentTransportStatus"] = ohnet.soaprequest.readStringParameter(result["CurrentTransportStatus"]); 
        result["CurrentSpeed"] = ohnet.soaprequest.readStringParameter(result["CurrentSpeed"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetPositionInfo
* @method GetPositionInfo
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetPositionInfo = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetPositionInfo", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["Track"] = ohnet.soaprequest.readIntParameter(result["Track"]); 
        result["TrackDuration"] = ohnet.soaprequest.readStringParameter(result["TrackDuration"]); 
        result["TrackMetaData"] = ohnet.soaprequest.readStringParameter(result["TrackMetaData"]); 
        result["TrackURI"] = ohnet.soaprequest.readStringParameter(result["TrackURI"]); 
        result["RelTime"] = ohnet.soaprequest.readStringParameter(result["RelTime"]); 
        result["AbsTime"] = ohnet.soaprequest.readStringParameter(result["AbsTime"]); 
        result["RelCount"] = ohnet.soaprequest.readIntParameter(result["RelCount"]); 
        result["AbsCount"] = ohnet.soaprequest.readIntParameter(result["AbsCount"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetDeviceCapabilities
* @method GetDeviceCapabilities
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetDeviceCapabilities = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetDeviceCapabilities", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["PlayMedia"] = ohnet.soaprequest.readStringParameter(result["PlayMedia"]); 
        result["RecMedia"] = ohnet.soaprequest.readStringParameter(result["RecMedia"]); 
        result["RecQualityModes"] = ohnet.soaprequest.readStringParameter(result["RecQualityModes"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetTransportSettings
* @method GetTransportSettings
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetTransportSettings = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetTransportSettings", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["PlayMode"] = ohnet.soaprequest.readStringParameter(result["PlayMode"]); 
        result["RecQualityMode"] = ohnet.soaprequest.readStringParameter(result["RecQualityMode"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Stop
* @method Stop
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.Stop = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Stop", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Play
* @method Play
* @param {Int} InstanceID An action parameter
* @param {String} Speed An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.Play = function(InstanceID, Speed, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Play", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Speed", Speed);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Pause
* @method Pause
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.Pause = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Pause", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Record
* @method Record
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.Record = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Record", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Seek
* @method Seek
* @param {Int} InstanceID An action parameter
* @param {String} Unit An action parameter
* @param {String} Target An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.Seek = function(InstanceID, Unit, Target, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Seek", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("Unit", Unit);
    request.writeStringParameter("Target", Target);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Next
* @method Next
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.Next = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Next", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Previous
* @method Previous
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.Previous = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Previous", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetPlayMode
* @method SetPlayMode
* @param {Int} InstanceID An action parameter
* @param {String} NewPlayMode An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.SetPlayMode = function(InstanceID, NewPlayMode, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetPlayMode", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("NewPlayMode", NewPlayMode);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetRecordQualityMode
* @method SetRecordQualityMode
* @param {Int} InstanceID An action parameter
* @param {String} NewRecordQualityMode An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.SetRecordQualityMode = function(InstanceID, NewRecordQualityMode, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetRecordQualityMode", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("NewRecordQualityMode", NewRecordQualityMode);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetCurrentTransportActions
* @method GetCurrentTransportActions
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetCurrentTransportActions = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetCurrentTransportActions", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["Actions"] = ohnet.soaprequest.readStringParameter(result["Actions"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetDRMState
* @method GetDRMState
* @param {Int} InstanceID An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetDRMState = function(InstanceID, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetDRMState", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.send(function(result){
        result["CurrentDRMState"] = ohnet.soaprequest.readStringParameter(result["CurrentDRMState"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetStateVariables
* @method GetStateVariables
* @param {Int} InstanceID An action parameter
* @param {String} StateVariableList An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.GetStateVariables = function(InstanceID, StateVariableList, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetStateVariables", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("StateVariableList", StateVariableList);
    request.send(function(result){
        result["StateVariableValuePairs"] = ohnet.soaprequest.readStringParameter(result["StateVariableValuePairs"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetStateVariables
* @method SetStateVariables
* @param {Int} InstanceID An action parameter
* @param {String} AVTransportUDN An action parameter
* @param {String} ServiceType An action parameter
* @param {String} ServiceId An action parameter
* @param {String} StateVariableValuePairs An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgAVTransport2.prototype.SetStateVariables = function(InstanceID, AVTransportUDN, ServiceType, ServiceId, StateVariableValuePairs, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetStateVariables", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("InstanceID", InstanceID);
    request.writeStringParameter("AVTransportUDN", AVTransportUDN);
    request.writeStringParameter("ServiceType", ServiceType);
    request.writeStringParameter("ServiceId", ServiceId);
    request.writeStringParameter("StateVariableValuePairs", StateVariableValuePairs);
    request.send(function(result){
        result["StateVariableList"] = ohnet.soaprequest.readStringParameter(result["StateVariableList"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



