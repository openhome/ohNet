 

/**
* Service Proxy for CpProxyOpenhomeOrgTestBasic1
* @module ohnet
* @class TestBasic
*/
    
var CpProxyOpenhomeOrgTestBasic1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-TestBasic-1/control";  // upnp control url
    this.domain = "openhome-org";
    this.type = "TestBasic";
    this.version = "1";
    this.serviceName = "openhome.org-TestBasic-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["VarUint"] = new ohnet.serviceproperty("VarUint","int");
    this.serviceProperties["VarInt"] = new ohnet.serviceproperty("VarInt","int");
    this.serviceProperties["VarBool"] = new ohnet.serviceproperty("VarBool","bool");
    this.serviceProperties["VarStr"] = new ohnet.serviceproperty("VarStr","string");
    this.serviceProperties["VarBin"] = new ohnet.serviceproperty("VarBin","binary");

                                  
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyOpenhomeOrgTestBasic1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyOpenhomeOrgTestBasic1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "VarUint" property change events
* @method VarUint_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyOpenhomeOrgTestBasic1.prototype.VarUint_Changed = function (stateChangedFunction) {
    this.serviceProperties.VarUint.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VarInt" property change events
* @method VarInt_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyOpenhomeOrgTestBasic1.prototype.VarInt_Changed = function (stateChangedFunction) {
    this.serviceProperties.VarInt.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VarBool" property change events
* @method VarBool_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyOpenhomeOrgTestBasic1.prototype.VarBool_Changed = function (stateChangedFunction) {
    this.serviceProperties.VarBool.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBoolParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VarStr" property change events
* @method VarStr_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyOpenhomeOrgTestBasic1.prototype.VarStr_Changed = function (stateChangedFunction) {
    this.serviceProperties.VarStr.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "VarBin" property change events
* @method VarBin_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyOpenhomeOrgTestBasic1.prototype.VarBin_Changed = function (stateChangedFunction) {
    this.serviceProperties.VarBin.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readBinaryParameter(state)); 
    });
}


/**
* A service action to Increment
* @method Increment
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.Increment = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Increment", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Value", Value);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readIntParameter(result["Result"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to EchoAllowedRangeUint
* @method EchoAllowedRangeUint
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.EchoAllowedRangeUint = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("EchoAllowedRangeUint", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Value", Value);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readIntParameter(result["Result"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Decrement
* @method Decrement
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.Decrement = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Decrement", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Value", Value);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readIntParameter(result["Result"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Toggle
* @method Toggle
* @param {Boolean} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.Toggle = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Toggle", this.url, this.domain, this.type, this.version);     
    request.writeBoolParameter("Value", Value);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readBoolParameter(result["Result"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to EchoString
* @method EchoString
* @param {String} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.EchoString = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("EchoString", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("Value", Value);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readStringParameter(result["Result"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to EchoAllowedValueString
* @method EchoAllowedValueString
* @param {String} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.EchoAllowedValueString = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("EchoAllowedValueString", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("Value", Value);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readStringParameter(result["Result"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to EchoBinary
* @method EchoBinary
* @param {String} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.EchoBinary = function(Value, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("EchoBinary", this.url, this.domain, this.type, this.version);     
    request.writeBinaryParameter("Value", Value);
    request.send(function(result){
        result["Result"] = ohnet.soaprequest.readBinaryParameter(result["Result"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetUint
* @method SetUint
* @param {Int} ValueUint An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.SetUint = function(ValueUint, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetUint", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("ValueUint", ValueUint);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetUint
* @method GetUint
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.GetUint = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetUint", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ValueUint"] = ohnet.soaprequest.readIntParameter(result["ValueUint"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetInt
* @method SetInt
* @param {Int} ValueInt An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.SetInt = function(ValueInt, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetInt", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("ValueInt", ValueInt);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetInt
* @method GetInt
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.GetInt = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetInt", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ValueInt"] = ohnet.soaprequest.readIntParameter(result["ValueInt"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetBool
* @method SetBool
* @param {Boolean} ValueBool An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.SetBool = function(ValueBool, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetBool", this.url, this.domain, this.type, this.version);     
    request.writeBoolParameter("ValueBool", ValueBool);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetBool
* @method GetBool
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.GetBool = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetBool", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ValueBool"] = ohnet.soaprequest.readBoolParameter(result["ValueBool"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetMultiple
* @method SetMultiple
* @param {Int} ValueUint An action parameter
* @param {Int} ValueInt An action parameter
* @param {Boolean} ValueBool An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.SetMultiple = function(ValueUint, ValueInt, ValueBool, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetMultiple", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("ValueUint", ValueUint);
    request.writeIntParameter("ValueInt", ValueInt);
    request.writeBoolParameter("ValueBool", ValueBool);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetMultiple
* @method GetMultiple
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.GetMultiple = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetMultiple", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ValueUint"] = ohnet.soaprequest.readIntParameter(result["ValueUint"]); 
        result["ValueInt"] = ohnet.soaprequest.readIntParameter(result["ValueInt"]); 
        result["ValueBool"] = ohnet.soaprequest.readBoolParameter(result["ValueBool"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetString
* @method SetString
* @param {String} ValueStr An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.SetString = function(ValueStr, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetString", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("ValueStr", ValueStr);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetString
* @method GetString
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.GetString = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetString", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ValueStr"] = ohnet.soaprequest.readStringParameter(result["ValueStr"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetBinary
* @method SetBinary
* @param {String} ValueBin An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.SetBinary = function(ValueBin, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetBinary", this.url, this.domain, this.type, this.version);     
    request.writeBinaryParameter("ValueBin", ValueBin);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetBinary
* @method GetBinary
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.GetBinary = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetBinary", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["ValueBin"] = ohnet.soaprequest.readBinaryParameter(result["ValueBin"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to ToggleBool
* @method ToggleBool
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.ToggleBool = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ToggleBool", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to ReportError
* @method ReportError
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.ReportError = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("ReportError", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to WriteFile
* @method WriteFile
* @param {String} Data An action parameter
* @param {String} FileFullName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.WriteFile = function(Data, FileFullName, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("WriteFile", this.url, this.domain, this.type, this.version);     
    request.writeStringParameter("Data", Data);
    request.writeStringParameter("FileFullName", FileFullName);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Shutdown
* @method Shutdown
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestBasic1.prototype.Shutdown = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Shutdown", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



