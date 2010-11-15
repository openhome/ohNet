 

/**
* Service Proxy for linn.co.uk:Diagnostics:1
* @module Zapp
* @title Diagnostics
*/

var ServiceDiagnostics = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Diagnostics-1/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Diagnostics";
	this.version = "1";
	this.serviceName = "linn.co.uk-Diagnostics-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["aStateVariable"] = new Zapp.ServiceProperty("aStateVariable");
	this.serviceProperties["Data"] = new Zapp.ServiceProperty("Data");
	this.serviceProperties["String"] = new Zapp.ServiceProperty("String");
	this.serviceProperties["Bool"] = new Zapp.ServiceProperty("Bool");
	this.serviceProperties["TUint"] = new Zapp.ServiceProperty("TUint");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceDiagnostics.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceDiagnostics.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "aStateVariable" property change events
* @method aStateVariable_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDiagnostics.prototype.aStateVariable_Changed = function (stateChangedFunction) {
    this.serviceProperties.aStateVariable.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Data" property change events
* @method Data_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDiagnostics.prototype.Data_Changed = function (stateChangedFunction) {
    this.serviceProperties.Data.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBinaryParameter(state)); 
	});
}


/**
* Adds a listener to handle "String" property change events
* @method String_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDiagnostics.prototype.String_Changed = function (stateChangedFunction) {
    this.serviceProperties.String.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "Bool" property change events
* @method Bool_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDiagnostics.prototype.Bool_Changed = function (stateChangedFunction) {
    this.serviceProperties.Bool.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "TUint" property change events
* @method TUint_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDiagnostics.prototype.TUint_Changed = function (stateChangedFunction) {
    this.serviceProperties.TUint.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Echo
* @method Echo
* @param {String} aIn An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.Echo = function(aIn, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Echo", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aIn", aIn);
    request.send(function(result){
		result["aOut"] = Zapp.SoapRequest.readStringParameter(result["aOut"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ElfFile
* @method ElfFile
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.ElfFile = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ElfFile", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aElfFile"] = Zapp.SoapRequest.readStringParameter(result["aElfFile"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ElfFingerprint
* @method ElfFingerprint
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.ElfFingerprint = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ElfFingerprint", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aElfFileFingerprint"] = Zapp.SoapRequest.readStringParameter(result["aElfFileFingerprint"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CrashDataStatus
* @method CrashDataStatus
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.CrashDataStatus = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CrashDataStatus", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aCrashDataStatus"] = Zapp.SoapRequest.readStringParameter(result["aCrashDataStatus"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CrashDataFetch
* @method CrashDataFetch
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.CrashDataFetch = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CrashDataFetch", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aCrashData"] = Zapp.SoapRequest.readBinaryParameter(result["aCrashData"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to CrashDataClear
* @method CrashDataClear
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.CrashDataClear = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CrashDataClear", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SysLog
* @method SysLog
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.SysLog = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SysLog", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aSysLog"] = Zapp.SoapRequest.readBinaryParameter(result["aSysLog"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Diagnostic
* @method Diagnostic
* @param {String} aDiagnosticType An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.Diagnostic = function(aDiagnosticType, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Diagnostic", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aDiagnosticType", aDiagnosticType);
    request.send(function(result){
		result["aDiagnosticInfo"] = Zapp.SoapRequest.readStringParameter(result["aDiagnosticInfo"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StateVariable
* @method StateVariable
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.StateVariable = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StateVariable", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aStateVariable"] = Zapp.SoapRequest.readIntParameter(result["aStateVariable"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStateVariable
* @method SetStateVariable
* @param {Int} aStateVariable An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.SetStateVariable = function(aStateVariable, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStateVariable", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aStateVariable", aStateVariable);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StateVariablePeriod
* @method StateVariablePeriod
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.StateVariablePeriod = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StateVariablePeriod", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aPeriod"] = Zapp.SoapRequest.readIntParameter(result["aPeriod"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStateVariablePeriod
* @method SetStateVariablePeriod
* @param {Int} aPeriod An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.SetStateVariablePeriod = function(aPeriod, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStateVariablePeriod", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aPeriod", aPeriod);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Reboot
* @method Reboot
* @param {Int} aDelay An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDiagnostics.prototype.Reboot = function(aDelay, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Reboot", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aDelay", aDelay);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



